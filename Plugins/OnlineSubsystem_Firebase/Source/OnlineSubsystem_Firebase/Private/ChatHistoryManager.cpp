#include "ChatHistoryManager.h"
#include "Engine/Engine.h"

void UChatHistoryManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	// Initialize with world chat
	ChatHistories.Add("World_Chat", FChatHistory{"World_Chat", {}, 0});
}

void UChatHistoryManager::Deinitialize()
{
	// Clean up before subsystem is destroyed
	ChatHistories.Empty();
	Super::Deinitialize();
}

void UChatHistoryManager::AddMessage(const FChatMessage& NewMessage)
{
	if (NewMessage.ChatID.IsEmpty()) return;

	FChatHistory& History = ChatHistories.FindOrAdd(NewMessage.ChatID);
	History.ChatID = NewMessage.ChatID;
    
	History.Messages.Add(NewMessage);

	// Better alternative to F1 key check:
	// Assume you have a way to track active chat
	// For example, store the currently viewed chat ID
	if (CurrentActiveChatID != NewMessage.ChatID)
	{
		History.UnreadCount++;
	}

	if (History.Messages.Num() > MaxMessagesPerChat)
	{
		History.Messages.RemoveAt(0);
	}
}

TArray<FChatMessage> UChatHistoryManager::GetChatHistory(const FString& ChatID) const
{
	if (const FChatHistory* History = ChatHistories.Find(ChatID))
	{
		return History->Messages;
	}
	return TArray<FChatMessage>();
}

void UChatHistoryManager::MarkChatAsRead(const FString& ChatID)
{
	if (FChatHistory* History = ChatHistories.Find(ChatID))
	{
		History->UnreadCount = 0;
	}
}

int32 UChatHistoryManager::GetUnreadCount(const FString& ChatID) const
{
	if (const FChatHistory* History = ChatHistories.Find(ChatID))
	{
		return History->UnreadCount;
	}
	return 0;
}