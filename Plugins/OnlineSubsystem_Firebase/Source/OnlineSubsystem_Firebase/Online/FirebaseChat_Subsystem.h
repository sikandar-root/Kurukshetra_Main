// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Database/FGDatabaseRef.h"
#include "Auth/FGAuthLibrary.h"
#include "FirebaseFriends_Subsystem.h"
#include "Auth/FGFirebaseUser.h"
#include "FirebaseChat_Subsystem.generated.h"

/**
 * Structure representing a single chat message
 */
USTRUCT(BlueprintType)
struct FChatMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Chat")
    FString ChatID;
    
    UPROPERTY(BlueprintReadOnly, Category = "Chat")
    FString SenderID;
    
    UPROPERTY(BlueprintReadOnly, Category = "Chat")
    FString SenderName;
    
    UPROPERTY(BlueprintReadOnly, Category = "Chat")
    FString Message;
    
    UPROPERTY(BlueprintReadOnly, Category = "Chat")
    int64 Timestamp;

    bool operator==(const FChatMessage& Other) const
    {
        return ChatID == Other.ChatID
            && SenderID == Other.SenderID
            && SenderName == Other.SenderName
            && Message == Other.Message
            && Timestamp == Other.Timestamp;
    }

    bool operator!=(const FChatMessage& Other) const
    {
        return !(*this == Other);
    }


};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChatMessageReceived, const FChatMessage, NewMessage);

/**
 * Subsystem for handling both world and private chat functionality using Firebase
 */
UCLASS()
class ONLINESUBSYSTEM_FIREBASE_API UFirebaseChat_Subsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
    
public:
    // Begin USubsystem
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    // End USubsystem
    
    // World Chat Functions
    UFUNCTION(BlueprintCallable, Category = "Chat|World")
    void SendWorldChatMessage(const FString& Message);
    
    // Friend Chat Functions
    UFUNCTION(BlueprintCallable, Category = "Chat|Friend")
    void SendPrivateMessage(const FString& ChatID, const FString& Message);
    
    // Event Handlers
    UFUNCTION(BlueprintCallable, Category = "Chat|Events")
    void HandleChatMessage(EChileEventType EventType, UFGDataSnapshot* Data, FString PreviousChildName);
    
    // Delegates
    UPROPERTY(BlueprintAssignable, Category = "Chat|Events")
    FOnChatMessageReceived OnMessageReceived;
    
private:
    /** Initialize chat listeners after successful login */
    UFUNCTION()
    void HandleLogin(UFGFirebaseUser* User);
    
    /** Bind to login success event */
    UFUNCTION()
    void BindLoginSuccess();

    UFUNCTION()
    void TrytoGetFriendList();
    
    /** Callback when friend list is retrieved */
    UFUNCTION()
    void OnFriendListSuccess(const TArray<FFriendData>& Friends, bool bResult);

    
    
    /** Start listening to world chat messages */
    UFUNCTION()
    void StartListeningWorldChat();
    
    /** Stop all chat listeners */
    void StopListeningChat();
    
    /** Start listening to private chats with friends */
    UFUNCTION()
    void StartListeningPrivateChat();
    
    // Member variables
    FString CurrentUserID;           // Currently logged in user's ID
    FString CurrentUserName;         // Currently logged in user's display name

    FChatMessage LastMessage;        // Last received message
    
    // Database listeners
    UPROPERTY()
    FOnChildEventDelegate OnChildEventListener;
    
    UPROPERTY()
    FOnCancelledDelegate OnCancelledListener;
};