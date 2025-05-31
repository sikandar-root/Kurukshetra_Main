#include "FirebaseFriends_Subsystem.h"
#include "FirebaseDatabasePath_Library.h"
#include "Database/FGDatabaseLibrary.h"
#include "Database/FGDataSnapshot.h"
#include "Common/FGValueVariantAccess.h"
#include "Common/FGValueVariantConv.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"

void UFirebaseFriends_Subsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}

FUniqueNetIdRepl UFirebaseFriends_Subsystem::CreateUniqueIdFromString(const FString& StringId)
{
    if (IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get())
    {
        if (const IOnlineIdentityPtr IdentityInterface = OnlineSub->GetIdentityInterface())
        {
            return IdentityInterface->CreateUniquePlayerId(StringId);
        }
    }
    return nullptr;
}

void UFirebaseFriends_Subsystem::SetPlayerNetworkID(APlayerState* PlayerState, FUniqueNetIdRepl NetId)
{
    if (PlayerState != nullptr) // Changed from IsValid to simple nullptr check
    {
        PlayerState->SetUniqueId(NetId);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid PlayerState provided to SetPlayerNetworkID"));
    }
}

//////////////////////////////////////////////////////////////////////////
// Get Friend List Async Action
//////////////////////////////////////////////////////////////////////////

UGetFriendListAsync* UGetFriendListAsync::GetFriendList(UObject* WorldContextObject, const FString& UserID)
{
    UGetFriendListAsync* Action = NewObject<UGetFriendListAsync>();
    Action->TargetUserID = UserID;
    Action->FriendsSubsystem = UGameInstance::GetSubsystem<UFirebaseFriends_Subsystem>(UGameplayStatics::GetGameInstance(WorldContextObject));
    return Action;
}

void UGetFriendListAsync::Activate()
{
    if (FriendsSubsystem && !FriendsSubsystem->FriendData.IsEmpty())
    {
        OnCompleted.Broadcast(FriendsSubsystem->FriendData, true);
        return;
    }

    OnDataChangedDelegate.BindDynamic(this, &UGetFriendListAsync::OnDataReceived);
    OnCancelledDelegate.BindDynamic(this, &UGetFriendListAsync::OnOperationCancelled);

    UFGDatabaseRef* DatabaseRef = UFirebaseDatabasePath_Library::FriendsDBPath(TargetUserID);
    DatabaseRef->GetValue(OnDataChangedDelegate, OnCancelledDelegate);
}

void UGetFriendListAsync::OnDataReceived(UFGDataSnapshot* Data)
{
    TArray<FFriendData> FriendList;
    const TMap<FString, FFGValueVariant> FriendMap = UFGValueVariantAccess::GetMap(Data->GetValue());

    for (const auto& Pair : FriendMap)
    {
        FFriendData NewFriend;
        NewFriend.UserID = Pair.Key;

        const TMap<FString, FFGValueVariant> InnerMap = UFGValueVariantAccess::GetMap(Pair.Value);
        if (const FFGValueVariant* ChatIDValue = InnerMap.Find(TEXT("ChatID")))
        {
            NewFriend.ChatID = UFGValueVariantAccess::GetString(*ChatIDValue);
        }

        FriendList.Add(NewFriend);
    }

    if (FriendsSubsystem)
    {
        FriendsSubsystem->FriendData = FriendList;
    }

    OnCompleted.Broadcast(FriendList, true);
}

void UGetFriendListAsync::OnOperationCancelled(int32 ErrorCode, const FString ErrorMessage)
{
    OnCompleted.Broadcast(TArray<FFriendData>(), false);
}

//////////////////////////////////////////////////////////////////////////
// Find User Async Action
//////////////////////////////////////////////////////////////////////////

UFindUserAsync* UFindUserAsync::FindUser(UObject* WorldContextObject, const FString& UsernameOrID)
{
    UFindUserAsync* Action = NewObject<UFindUserAsync>();
    Action->SearchQuery = UsernameOrID;
    Action->DatabaseRef = UFirebaseDatabasePath_Library::UserIdsDBPath(UsernameOrID);
    return Action;
}

void UFindUserAsync::Activate()
{
    OnDataChangedDelegate.BindDynamic(this, &UFindUserAsync::OnDataReceived);
    OnCancelledDelegate.BindDynamic(this, &UFindUserAsync::OnOperationCancelled);
    DatabaseRef->GetValue(OnDataChangedDelegate, OnCancelledDelegate);
}

void UFindUserAsync::OnDataReceived(UFGDataSnapshot* Data)
{
    if (Data->Exists())
    {
        const FString UserID = UFGValueVariantAccess::GetString(Data->GetValue());
        OnCompleted.Broadcast(true, UserID);
    }
    else
    {
        OnCompleted.Broadcast(false, FString());
    }
}

void UFindUserAsync::OnOperationCancelled(int32 ErrorCode, const FString ErrorMessage)
{
    OnCompleted.Broadcast(false, ErrorMessage);
}

//////////////////////////////////////////////////////////////////////////
// Friend Request Base
//////////////////////////////////////////////////////////////////////////

TMap<FString, FFGValueVariant> UFriendRequestAsyncBase::CreateFriendDataValue(const FString& UserID, const FString& FriendID, bool bIsFriendRecord)
{
    TMap<FString, FFGValueVariant> Data;
    
    if (bIsFriendRecord)
    {
        TMap<FString, FFGValueVariant> FriendData;
        FriendData.Add(TEXT("CreatedAt"), UFGDatabaseLibrary::RealtimeDatabaseTimestamp());
        
        const FString ChatID = FString::Printf(TEXT("%s::%s"), *UserID, *FriendID);
        FriendData.Add(TEXT("ChatID"), UFGValueVariantConv::Conv_StringToFGValueVariant(ChatID));
        
        Data.Add(FriendID, UFGValueVariantConv::Conv_MapToFGValueVariant(FriendData));
    }
    else
    {
        Data.Add(TEXT("from"), UFGValueVariantConv::Conv_StringToFGValueVariant(UserID));
        Data.Add(TEXT("to"), UFGValueVariantConv::Conv_StringToFGValueVariant(FriendID));
        Data.Add(TEXT("IsSender"), UFGValueVariantConv::Conv_boolToFGValueVariant(bIsFriendRecord));
    }
    
    return Data;
}

//////////////////////////////////////////////////////////////////////////
// Send Friend Request Async Action
//////////////////////////////////////////////////////////////////////////

USendFriendRequestAsync* USendFriendRequestAsync::SendFriendRequest(UObject* WorldContextObject, const FString& SenderUserID, const FString& TargetUserID)
{
    USendFriendRequestAsync* Action = NewObject<USendFriendRequestAsync>();
    Action->SenderUserID = SenderUserID;
    Action->TargetUserID = TargetUserID;
    Action->UserDatabaseRef = UFirebaseDatabasePath_Library::UserIdsDBPath(TargetUserID);
    return Action;
}

void USendFriendRequestAsync::Activate()
{
    OnDataChangedDelegate.BindDynamic(this, &USendFriendRequestAsync::OnUserFound);
    OnCancelledDelegate.BindDynamic(this, &USendFriendRequestAsync::OnOperationCancelled);
    UserDatabaseRef->GetValue(OnDataChangedDelegate, OnCancelledDelegate);
}

void USendFriendRequestAsync::OnUserFound(UFGDataSnapshot* Data)
{
    if (Data->Exists())
    {
        const FString FriendUserID = UFGValueVariantAccess::GetString(Data->GetValue());
        
        // Update sender's request record
        UFGDatabaseRef* SenderDBRef = UFirebaseDatabasePath_Library::FriendRequestsDBPath(SenderUserID, FriendUserID, true);
        SenderDBRef->UpdateChildren(CreateFriendDataValue(SenderUserID, FriendUserID, false));
        
        // Update receiver's request record
        UFGDatabaseRef* ReceiverDBRef = UFirebaseDatabasePath_Library::FriendRequestsDBPath(SenderUserID, FriendUserID, false);
        ReceiverDBRef->UpdateChildren(CreateFriendDataValue(SenderUserID, FriendUserID, false));
        
        OnCompleted.Broadcast(true, FriendUserID);
    }
    else
    {
        OnCompleted.Broadcast(false, FString());
    }
}

void USendFriendRequestAsync::OnOperationCancelled(int32 ErrorCode, const FString ErrorMessage)
{
    OnCompleted.Broadcast(false, ErrorMessage);
}

//////////////////////////////////////////////////////////////////////////
// Accept Friend Request Async Action
//////////////////////////////////////////////////////////////////////////

UAcceptFriendRequestAsync* UAcceptFriendRequestAsync::AcceptFriendRequest(UObject* WorldContextObject, const FString& SenderUserID, const FString& TargetUserID)
{
    UAcceptFriendRequestAsync* Action = NewObject<UAcceptFriendRequestAsync>();
    Action->SenderUserID = SenderUserID;
    Action->TargetUserID = TargetUserID;
    return Action;
}

void UAcceptFriendRequestAsync::Activate()
{
    // Add friend to sender's list
    UFGDatabaseRef* SenderFriendsRef = UFirebaseDatabasePath_Library::FriendsDBPath(SenderUserID);
    SenderFriendsRef->UpdateChildren(CreateFriendDataValue(SenderUserID, TargetUserID, true));
    
    // Add friend to target's list
    UFGDatabaseRef* TargetFriendsRef = UFirebaseDatabasePath_Library::FriendsDBPath(TargetUserID);
    TargetFriendsRef->UpdateChildren(CreateFriendDataValue(TargetUserID, SenderUserID, true));
    
    // Remove request records
    UFGDatabaseRef* SenderRequestRef = UFirebaseDatabasePath_Library::FriendRequestsDBPath(SenderUserID, TargetUserID, true);
    SenderRequestRef->RemoveValue();
    
    UFGDatabaseRef* TargetRequestRef = UFirebaseDatabasePath_Library::FriendRequestsDBPath(SenderUserID, TargetUserID, false);
    TargetRequestRef->RemoveValue();
    
    OnCompleted.Broadcast(true, TargetUserID);
}

//////////////////////////////////////////////////////////////////////////
// Reject Friend Request Async Action
//////////////////////////////////////////////////////////////////////////

URejectFriendRequestAsync* URejectFriendRequestAsync::RejectFriendRequest(UObject* WorldContextObject, const FString& SenderUserID, const FString& TargetUserID)
{
    URejectFriendRequestAsync* Action = NewObject<URejectFriendRequestAsync>();
    Action->SenderUserID = SenderUserID;
    Action->TargetUserID = TargetUserID;
    return Action;
}

void URejectFriendRequestAsync::Activate()
{
    // Remove request records
    UFGDatabaseRef* SenderRequestRef = UFirebaseDatabasePath_Library::FriendRequestsDBPath(SenderUserID, TargetUserID, true);
    SenderRequestRef->RemoveValue();
    
    UFGDatabaseRef* TargetRequestRef = UFirebaseDatabasePath_Library::FriendRequestsDBPath(SenderUserID, TargetUserID, false);
    TargetRequestRef->RemoveValue();
    
    OnCompleted.Broadcast(true, TargetUserID);
}