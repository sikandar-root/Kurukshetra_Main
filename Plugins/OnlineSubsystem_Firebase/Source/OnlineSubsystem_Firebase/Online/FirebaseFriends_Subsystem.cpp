// Fill out your copyright notice in the Description page of Project Settings.


#include "FirebaseFriends_Subsystem.h"

#include "AudioDevice.h"
#include "Database/FGDatabaseRef.h"
#include "Database/FGDataSnapshot.h"
#include "Engine/Engine.h"
#include "FirebaseDatabasePath_Library.h"
#include "OnlineSubsystem.h"
#include "Common/FGValueVariant.h"
#include "Common/FGValueVariantAccess.h"
#include "Common/FGValueVariantConv.h"
#include "Database/FGDatabaseLibrary.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/PlayerController.h"
#include "Online/CoreOnline.h"
#include "OnlineSubsystemTypes.h"
#include "Interfaces/OnlineIdentityInterface.h"


void UFirebaseFriends_Subsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}


void UFirebaseFriends_Subsystem::SetNetID(APlayerState* playerstete,FUniqueNetIdRepl Ptr)
{
    
    // Set the custom Net ID in the PlayerState
    playerstete->SetUniqueId(Ptr);
}

FUniqueNetIdRepl UFirebaseFriends_Subsystem::CreateUniqueIdFromString(const FString& StringId)
{
    IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
    if (OnlineSubsystem)
    {
        const IOnlineIdentityPtr IdentityInterface =OnlineSubsystem->GetIdentityInterface();

        if (IdentityInterface.IsValid())
        {
            return IdentityInterface->CreateUniquePlayerId(StringId);
        }
    }
    return nullptr;
}



UGetFriendLists* UGetFriendLists::Get_Friend_List(UFirebaseFriends_Subsystem* Subsystem, FString UID)
{
    UGetFriendLists* AsyncAction = NewObject<UGetFriendLists>();
    UE_LOG(LogTemp, Log, TEXT("Async action created"));
    AsyncAction->Subsystem= Subsystem;
    AsyncAction->UID = UID;

    // Return the async function object so it can be activated
    return AsyncAction;
}

void UGetFriendLists::Activate()
{
    if (Subsystem->Friends.IsEmpty())
    {
        // Bind your delegate
        OnCompleted.BindDynamic(this, &UGetFriendLists::OnDataRecived);
        OnCancelled.BindDynamic(this, &UGetFriendLists::OnCancelledOperation);
    
        UFGDatabaseRef* Database =  UFirebaseDatabasePath_Library::FriendsDBPath(UID);
        Database->GetValue(OnCompleted,OnCancelled);
    }
    else
    {
        TArray<FString> FriendsParam ;
        FriendsParam = Subsystem->Friends;
        On_Completed.Broadcast(FriendsParam,true);
    }
    
}

void UGetFriendLists::OnDataRecived(UFGDataSnapshot* Data)
{
    TMap<FString, FFGValueVariant> Result ;
    TArray<FString> Friends ;
    FString Test;


    // Get the value from the snapshot
    FFGValueVariant Value = Data->GetValue();
        
    Result = UFGValueVariantAccess::GetMap(Value);
    Result.GetKeys(Friends);

    Subsystem->Friends = Friends;
    On_Completed.Broadcast(Friends,true);

}

void UGetFriendLists::OnCancelledOperation(int ErrorCode, FString ErrorMessage)
{
    TArray<FString> Friends ;
    
    // Log the creation of the async action object
    UE_LOG(LogTemp, Log, TEXT("On Canclled"));
    On_Completed.Broadcast(Friends,false);
}

UFindUser* UFindUser::FindUser(const FString Value)
{
    // Log the value being used for the query
    UE_LOG(LogTemp, Log, TEXT("FindUser called with Value: %s"), *Value);

    // Create a new instance of the async action
    UFindUser* AsyncAction = NewObject<UFindUser>();

    // Log the creation of the async action object
    UE_LOG(LogTemp, Log, TEXT("Async action created"));

    // Store the database reference and values
    AsyncAction->DatabaseRef = UFirebaseDatabasePath_Library::UserIdsDBPath(Value);

    // Log the database reference path being used
    //UE_LOG(LogTemp, Log, TEXT("Database path set to: %s"), *AsyncAction->DatabaseRef->GetPath());

    // Return the async function object so it can be activated
    return AsyncAction;
}

void UFindUser::Activate()
{
    // Log the activation of the action
    UE_LOG(LogTemp, Log, TEXT("Activate called"));

    // Bind your delegate
    OnCancelled.BindDynamic(this, &UFindUser::OnCancelledOperation);
    OnRecived.BindDynamic(this, &UFindUser::OnRecivedOperation);

    // Log that the delegate is set up
    UE_LOG(LogTemp, Log, TEXT("Delegates bound, calling GetValue"));

    DatabaseRef->GetValue(OnRecived, OnCancelled);
}

void UFindUser::OnCancelledOperation(int ErrorCode, FString ErrorMessage)
{
    // Log the error when the operation is cancelled
    UE_LOG(LogTemp, Warning, TEXT("Operation cancelled! ErrorCode: %d, ErrorMessage: %s"), ErrorCode, *ErrorMessage);

    // Broadcast the completion with failure status
    On_Completed.Broadcast(false, ErrorMessage);
}

void UFindUser::OnRecivedOperation(UFGDataSnapshot* Data)
{
    // Log the received data snapshot
    if (Data->Exists())
    {
        UE_LOG(LogTemp, Log, TEXT("Data received successfully"));

        // Get the value from the snapshot
        Values = Data->GetValue();

        // Log the value retrieved from the snapshot
        UE_LOG(LogTemp, Log, TEXT("Values retrieved from DataSnapshot: "));

        FString Ok = UFGValueVariantAccess::GetString(Values);
            
            // Log the string value retrieved
            UE_LOG(LogTemp, Log, TEXT("Test string: %s"), *Ok);
            
            // Broadcast the completion with success status
            On_Completed.Broadcast(true, Ok);
       
    }
    else
    {
        // Log if Data is null
        UE_LOG(LogTemp, Warning, TEXT("Received data is null"));

        // Broadcast failure completion
        On_Completed.Broadcast(false, FString("Received data is null"));
    }
}

UsendFriendRequest* UsendFriendRequest::SendFriendRequest(const FString FriendID, const FString UID)
{
 
    UsendFriendRequest* AsyncAction = NewObject<UsendFriendRequest>();
    UE_LOG(LogTemp, Log, TEXT("Async action created"));

    AsyncAction->FriendID = FriendID;
    AsyncAction->UID = UID;
    AsyncAction->DatabaseRef=UFirebaseDatabasePath_Library::UserIdsDBPath(FriendID);

    // Return the async function object so it can be activated
    return AsyncAction;
}

void UsendFriendRequest::Activate()
{
    OnFoundPlayerData.BindDynamic(this, &UsendFriendRequest::FoundedPlayerProfile);
    DatabaseRef->GetValue(OnFoundPlayerData, OnCancelled);
    
}

void UsendFriendRequest::FoundedPlayerProfile(UFGDataSnapshot* Data)
{
    if (Data->Exists())
    {
        Values = Data->GetValue();

        FString FriendUID = UFGValueVariantAccess::GetString(Values);

        SetValueDatabase(UID, FriendUID);
        
    }
    else
    {
        // Broadcast Success completion
        On_Completed.Broadcast(false, FString("Received data is null"));
    }
}

TMap<FString, FFGValueVariant> UsendFriendRequest::GetDatabaseValue(FString UIDParam, FString FriendUID, bool IsSender)
{
    TMap<FString, FFGValueVariant> Result;
    
        Result.Add(TEXT("from"),UFGValueVariantConv::Conv_StringToFGValueVariant(UIDParam));
        Result.Add(TEXT("to"),UFGValueVariantConv::Conv_StringToFGValueVariant(FriendUID));
        Result.Add(TEXT("IsSender"),UFGValueVariantConv::Conv_boolToFGValueVariant(IsSender));
    
    return Result;
}

void UsendFriendRequest::SetValueDatabase(FString UIDparam, FString FriendUIDparam)
{
    UFGDatabaseRef* SenderDatabaseRef = UFirebaseDatabasePath_Library::FriendRequestsDBPath(UIDparam,FriendUIDparam,true);
    SenderDatabaseRef->UpdateChildren(GetDatabaseValue(UIDparam, FriendUIDparam, true));
    UFGDatabaseRef* ReciverDatabaseRef = UFirebaseDatabasePath_Library::FriendRequestsDBPath(UIDparam,FriendUIDparam,false);
    ReciverDatabaseRef->UpdateChildren(GetDatabaseValue(UIDparam, FriendUIDparam, false));
    
    // Broadcast Success completion
    On_Completed.Broadcast(true, FriendUIDparam);
}





UAcceptFriendRequest* UAcceptFriendRequest::AcceptFriendRequest(const FString FriendUID, const FString UID)
{
    UAcceptFriendRequest* AsyncAction = NewObject<UAcceptFriendRequest>();
    UE_LOG(LogTemp, Log, TEXT("Async action created"));

    AsyncAction->FriendUID = FriendUID;
    AsyncAction->UID = UID;
    //AsyncAction->DatabaseRef=UFirebaseDatabasePath_Library::FriendsDBPath(FriendUID);

    // Return the async function object so it can be activated
    return AsyncAction;
}

void UAcceptFriendRequest::Activate()
{
    UFGDatabaseRef* PlayerDBRef = UFirebaseDatabasePath_Library::FriendsDBPath(UID);
    PlayerDBRef->UpdateChildren(GetDatabaseValue(UID, FriendUID, false));

    UFGDatabaseRef* FriendDBRef = UFirebaseDatabasePath_Library::FriendsDBPath(FriendUID);
    FriendDBRef->UpdateChildren(GetDatabaseValue(UID, FriendUID, true));


    UFGDatabaseRef* SenderDatabaseRef = UFirebaseDatabasePath_Library::FriendRequestsDBPath(UID,FriendUID,true);
    UFGDatabaseRef* ReciverDatabaseRef = UFirebaseDatabasePath_Library::FriendRequestsDBPath(UID,FriendUID,false);

    SenderDatabaseRef->RemoveValue();
    ReciverDatabaseRef->RemoveValue();

    On_Completed.Broadcast(true, FriendUID);
}

TMap<FString, FFGValueVariant> UAcceptFriendRequest::GetDatabaseValue(FString UIDParam, FString FriendUIDParam,
    bool IsFriend)
{

    TMap<FString, FFGValueVariant> Result;

    TMap<FString, FFGValueVariant> Value;

    FString ChatID = FString::Printf(TEXT("%s::%s"),*UIDParam,*FriendUIDParam);

    

    Value.Add(TEXT("CreatedAt"),UFGDatabaseLibrary::RealtimeDatabaseTimestamp());
    Value.Add(TEXT("ChatID"), UFGValueVariantConv::Conv_StringToFGValueVariant(ChatID));
    
    if (IsFriend)
    {
        Result.Add(UIDParam,UFGValueVariantConv::Conv_MapToFGValueVariant(Value));
    }
    else
    {
        Result.Add(FriendUIDParam,UFGValueVariantConv::Conv_MapToFGValueVariant(Value));
    }

    return Result;
}

URejectFriendRequest* URejectFriendRequest::RejectFriendRequest(const FString FriendUID, const FString UID)
{
    URejectFriendRequest* AsyncAction = NewObject<URejectFriendRequest>();
    UE_LOG(LogTemp, Log, TEXT("Async action created"));

    AsyncAction->FriendUID = FriendUID;
    AsyncAction->UID = UID;
    //AsyncAction->DatabaseRef=UFirebaseDatabasePath_Library::FriendsDBPath(FriendUID);

    // Return the async function object so it can be activated
    return AsyncAction;
}

void URejectFriendRequest::Activate()
{
    UFGDatabaseRef* SenderDatabaseRef = UFirebaseDatabasePath_Library::FriendRequestsDBPath(UID,FriendUID,true);
    SenderDatabaseRef->RemoveValue();

    
    UFGDatabaseRef* ReciverDatabaseRef = UFirebaseDatabasePath_Library::FriendRequestsDBPath(UID,FriendUID,false);
    ReciverDatabaseRef->RemoveValue();

    On_Completed.Broadcast(true, FriendUID);
}






