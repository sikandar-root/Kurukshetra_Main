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

	// Convert to JSON string
	FString ToJson() const;
    
	// Create from JSON string
	static FChatHistory FromJson(const FString& JsonString);
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
	int32 GetUnreadCountForChat(const FString& ChatID) const;

	UFUNCTION(BlueprintCallable, Category = "Chat History")
	int32 GetTotalUnreadCount() const;

	UFUNCTION(BlueprintCallable, Category = "Chat History")
	int32 GetPrivateUnreadCount() const;

	UFUNCTION(BlueprintCallable, Category = "Chat History")
	void SetActiveChat(const FString& ChatID);
	
	UFUNCTION(BlueprintCallable, Category = "Chat History|Storage")
	bool SaveChatHistoryToStorage();

private:
	UPROPERTY()
	FString CurrentActiveChatID;
	TArray<TSharedPtr<FJsonValue>> ConvertChatHistoriesToJsonArray() const;
	
private:
	UPROPERTY()
	TMap<FString, FChatHistory> ChatHistories;

	// Max messages to keep in memory per chat
	UPROPERTY(EditDefaultsOnly, Category = "Chat Settings")
	int32 MaxMessagesPerChat = 500;
	
};
