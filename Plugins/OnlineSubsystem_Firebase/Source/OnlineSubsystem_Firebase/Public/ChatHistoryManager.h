// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem_Firebase/Online/FirebaseChat_Subsystem.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ChatHistoryManager.generated.h"


USTRUCT(BlueprintType)
struct FChatHistory
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString ChatID;

	UPROPERTY(BlueprintReadOnly)
	TArray<FChatMessage> Messages;

	UPROPERTY(BlueprintReadOnly)
	int32 UnreadCount = 0;
};

/**
 * 
 */
UCLASS()
class ONLINESUBSYSTEM_FIREBASE_API UChatHistoryManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Initialize/Deinitialize
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// Message handling
	UFUNCTION(BlueprintCallable, Category = "Chat History")
	void AddMessage(const FChatMessage& NewMessage);

	UFUNCTION(BlueprintCallable, Category = "Chat History")
	TArray<FChatMessage> GetChatHistory(const FString& ChatID) const;

	UFUNCTION(BlueprintCallable, Category = "Chat History")
	void MarkChatAsRead(const FString& ChatID);

	UFUNCTION(BlueprintCallable, Category = "Chat History")
	int32 GetUnreadCount(const FString& ChatID) const;

private:
	UPROPERTY()
	FString CurrentActiveChatID;

public:
	UFUNCTION(BlueprintCallable)
	void SetActiveChat(const FString& ChatID) 
	{
		CurrentActiveChatID = ChatID;
		MarkChatAsRead(ChatID);
	}
	
private:
	UPROPERTY()
	TMap<FString, FChatHistory> ChatHistories;

	// Max messages to keep in memory per chat
	UPROPERTY(EditDefaultsOnly, Category = "Chat Settings")
	int32 MaxMessagesPerChat = 500;
	
};
