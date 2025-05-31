// Fill out your copyright notice in the Description page of Project Settings.

#include "FirebaseChat_Subsystem.h"
#include "FirebaseDatabasePath_Library.h"
#include "Database/FGDatabaseLibrary.h"
#include "Database/FGDataSnapshot.h"
#include "Common/FGValueVariant.h"
#include "Common/FGValueVariantAccess.h"
#include "Common/FGValueVariantConv.h"
#include "FirebaseDatabase_Subsystem.h"
#include "FirebaseFriends_Subsystem.h"
#include "FirebaseIdentity_Subsystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ChatHistoryManager.h"
#include "AGToastBPL.h"

void UFirebaseChat_Subsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    
    // Bind to login success event
    BindLoginSuccess();
}

void UFirebaseChat_Subsystem::Deinitialize()
{
    // Clean up listeners when subsystem is deinitialized
    StopListeningChat();
    
    Super::Deinitialize();
}

void UFirebaseChat_Subsystem::SendWorldChatMessage(const FString& Message)
{
    
    if (Message.IsEmpty() || CurrentUserID.IsEmpty())
    {
        UAGToastBPL::ShowToast("Cannot send empty message", ToastLength::Long);
        UE_LOG(LogTemp, Warning, TEXT("Cannot send empty message"));
        return;
    }
    
    // Prepare message data
    TMap<FString, FFGValueVariant> MessageData;
    MessageData.Add("ChatID", UFGValueVariantConv::Conv_StringToFGValueVariant("World_Chat"));
    MessageData.Add("sender_id", UFGValueVariantConv::Conv_StringToFGValueVariant(CurrentUserID));
    MessageData.Add("sender_name", UFGValueVariantConv::Conv_StringToFGValueVariant(CurrentUserName));
    MessageData.Add("message", UFGValueVariantConv::Conv_StringToFGValueVariant(Message));
    MessageData.Add("timestamp", UFGDatabaseLibrary::RealtimeDatabaseTimestamp());
    
    // Send to world chat database
    UFGDatabaseRef* WorldChatRef = UFirebaseDatabasePath_Library::WorldChatDBPath(CurrentUserID);
    WorldChatRef->UpdateChildren(MessageData);
}

void UFirebaseChat_Subsystem::SendPrivateMessage(const FString& ChatID, const FString& Message)
{
    if (Message.IsEmpty() || CurrentUserID.IsEmpty() || ChatID.IsEmpty())
    {
        UAGToastBPL::ShowToast("Cannot send empty message", ToastLength::Long);
        UE_LOG(LogTemp, Warning, TEXT("Cannot send private message - invalid parameters"));
        return;
    }
    
    // Prepare message data
    TMap<FString, FFGValueVariant> MessageData;
    MessageData.Add("ChatID", UFGValueVariantConv::Conv_StringToFGValueVariant(ChatID));
    MessageData.Add("sender_id", UFGValueVariantConv::Conv_StringToFGValueVariant(CurrentUserID));
    MessageData.Add("sender_name", UFGValueVariantConv::Conv_StringToFGValueVariant(CurrentUserName));
    MessageData.Add("message", UFGValueVariantConv::Conv_StringToFGValueVariant(Message));
    MessageData.Add("timestamp", UFGDatabaseLibrary::RealtimeDatabaseTimestamp());
    
    // Send to private chat database
    UFGDatabaseRef* PrivateChatRef = UFirebaseDatabasePath_Library::PrivateChatDBPath(ChatID, CurrentUserID);
    PrivateChatRef->UpdateChildren(MessageData);
}

void UFirebaseChat_Subsystem::StartListeningWorldChat()
{
    OnChildEventListener.BindDynamic(this, &UFirebaseChat_Subsystem::HandleChatMessage);
    
    UFGDatabaseRef* WorldChatRef = UFirebaseDatabasePath_Library::WorldChatListenerDBPath();
   // WorldChatRef->LimitToLast(50); // Only load last 50 messages
    WorldChatRef->AddChildListener(OnChildEventListener, OnCancelledListener);
    WorldChatRef->KeepSynced(true); // Keep the database in sync with the server
}

void UFirebaseChat_Subsystem::StopListeningChat()
{
    OnChildEventListener.Unbind();
    UFGDatabaseRef* WorldChatRef = UFirebaseDatabasePath_Library::WorldChatListenerDBPath();
    WorldChatRef->RemoveChildListener();
}

void UFirebaseChat_Subsystem::StartListeningPrivateChat()
{
    
    
    if (UFirebaseFriends_Subsystem* FirebaseFriends = GetGameInstance()->GetSubsystem<UFirebaseFriends_Subsystem>())
    {
        UGetFriendListAsync* AsyncTask = UGetFriendListAsync::GetFriendList(FirebaseFriends, CurrentUserID);
         AsyncTask->OnCompleted.AddDynamic(this, &UFirebaseChat_Subsystem::OnFriendListSuccess);
        // UKismetSystemLibrary::Delay(this, 0.2f, LatentInfo);
       TrytoGetFriendList();
    }
}

void UFirebaseChat_Subsystem::TrytoGetFriendList()
{
    UFirebaseFriends_Subsystem* FirebaseFriends = GetGameInstance()->GetSubsystem<UFirebaseFriends_Subsystem>();
    
    if (!FirebaseFriends->FriendData.IsEmpty())
    {
        TArray<FFriendData> Friends =FirebaseFriends->FriendData;
        OnFriendListSuccess(Friends,true);
    }
    else
    {
        // Set up latent action for delayed retry
        FLatentActionInfo LatentInfo;
        LatentInfo.CallbackTarget = this;
        LatentInfo.ExecutionFunction = "TrytoGetFriendList";
        LatentInfo.Linkage = 0;
        LatentInfo.UUID = __LINE__;

        UKismetSystemLibrary::Delay(this, 0.2f, LatentInfo);
        
    }
}

void UFirebaseChat_Subsystem::OnFriendListSuccess(const TArray<FFriendData>& Friends, bool bResult)
{

        if (!Friends.IsEmpty())
        {
         

            for (const FFriendData& Friend : Friends)
            {
                UFGDatabaseRef* PrivateChatRef = UFirebaseDatabasePath_Library::PrivateChatListenerDBPath(Friend.ChatID);
                PrivateChatRef->AddChildListener(OnChildEventListener, OnCancelledListener);
                PrivateChatRef->KeepSynced(true); // Keep the database in sync with the server
            }
        }
}


void UFirebaseChat_Subsystem::HandleChatMessage(EChileEventType EventType, UFGDataSnapshot* Data, FString PreviousChildName)
{
    FChatMessage ChatMsg;
    const TMap<FString, FFGValueVariant> MessageData = UFGValueVariantAccess::GetMap(Data->GetValue());

    if (MessageData.Contains("ChatID"))
    {
        ChatMsg.ChatID = UFGValueVariantAccess::GetString(MessageData["ChatID"]);
        ChatMsg.SenderID = UFGValueVariantAccess::GetString(MessageData["sender_id"]);
        ChatMsg.SenderName = UFGValueVariantAccess::GetString(MessageData["sender_name"]);
        ChatMsg.Message = UFGValueVariantAccess::GetString(MessageData["message"]);
        ChatMsg.Timestamp = UFGValueVariantAccess::GetDateTime(MessageData["timestamp"]).ToUnixTimestamp();
    }

    // Store message in history
    if (UChatHistoryManager* Manager = GetGameInstance()->GetSubsystem<UChatHistoryManager>())
    {
        Manager->AddMessage(ChatMsg);
    }

    // Use the equality operator to check for duplicates
    // if (ChatMsg.Timestamp == LastMessage.Timestamp || ChatMsg.Message == LastMessage.Message || ChatMsg.SenderID == LastMessage.SenderID))
    // {
    //    return;
    // }
    
        OnMessageReceived.Broadcast(ChatMsg);
        LastMessage = ChatMsg;
  
}

void UFirebaseChat_Subsystem::HandleLogin(UFGFirebaseUser* User)
{
    CurrentUserID = User->GetUid();
    CurrentUserName = User->GetDisplayName();
    
    UE_LOG(LogTemp, Log, TEXT("Chat subsystem initialized for user: %s"), *CurrentUserID);
    
    StartListeningWorldChat();
    StartListeningPrivateChat();
}

void UFirebaseChat_Subsystem::BindLoginSuccess()
{
    UFirebaseIdentity_Subsystem* FirebaseIdentity = GetGameInstance()->GetSubsystem<UFirebaseIdentity_Subsystem>();
    
    if (FirebaseIdentity)
    {
        FirebaseIdentity->OnLoginSuccess.AddDynamic(this, &UFirebaseChat_Subsystem::HandleLogin);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Firebase Identity subsystem not found! Trying again in 0.2s"));
        
        // Set up latent action for delayed retry
        FLatentActionInfo LatentInfo;
        LatentInfo.CallbackTarget = this;
        LatentInfo.ExecutionFunction = "BindLoginSuccess";
        LatentInfo.Linkage = 0;
        LatentInfo.UUID = __LINE__;
        
        UKismetSystemLibrary::Delay(this, 0.2f, LatentInfo);
    }
}