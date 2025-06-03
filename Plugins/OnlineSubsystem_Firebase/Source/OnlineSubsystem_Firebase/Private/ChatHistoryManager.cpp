#include "ChatHistoryManager.h"

#include "JsonObjectConverter.h"
#include "Engine/Engine.h"
#include "Kurukshetra_Main/Kurukshetra_FL.h"

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


FString FChatHistory::ToJson() const
{
	FString OutputString;
	TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(*this);
	if (JsonObject.IsValid())
	{
		TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
		JsonWriter->Close();
	}
	return OutputString;
}

FChatHistory FChatHistory::FromJson(const FString& JsonString)
{
	FChatHistory Result;
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
    
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), FChatHistory::StaticStruct(), &Result);
	}
    
	return Result;
}
TArray<TSharedPtr<FJsonValue>> UChatHistoryManager::ConvertChatHistoriesToJsonArray() const
{
	TArray<TSharedPtr<FJsonValue>> JsonArray;
    
	for (const auto& Pair : ChatHistories)
	{
		const FChatHistory& History = Pair.Value;
        
		TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(History);
		if (JsonObject.IsValid())
		{
			JsonArray.Add(MakeShared<FJsonValueObject>(JsonObject));
		}
	}
    
	return JsonArray;
}
bool UChatHistoryManager::SaveChatHistoryToStorage()
{
	TArray<TSharedPtr<FJsonValue>> JsonArray = ConvertChatHistoriesToJsonArray();
    
	FString OutputString;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
	if (FJsonSerializer::Serialize(JsonArray, JsonWriter))
	{
		JsonWriter->Close();
		return UKurukshetra_FL::WriteFileToAndroid("ChatHistory/Chat.json", OutputString,true);
	}
    
	JsonWriter->Close();
	return false;
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

int32 UChatHistoryManager::GetUnreadCountForChat(const FString& ChatID) const
{
	if (const FChatHistory* History = ChatHistories.Find(ChatID))
	{
		return History->UnreadCount;
	}
	return 0;
}

int32 UChatHistoryManager::GetTotalUnreadCount() const
{
	int32 Total = 0;
	for (const auto& Pair : ChatHistories)
	{
		Total += Pair.Value.UnreadCount;
	}
	return Total;
}

int32 UChatHistoryManager::GetPrivateUnreadCount() const
{
	int32 Total = 0;
	for (const auto& Pair : ChatHistories)
	{
		if (Pair.Key != "World_Chat")
		{
			Total += Pair.Value.UnreadCount;
		}
	}
	return Total;
}

void UChatHistoryManager::SetActiveChat(const FString& ChatID)
{
	CurrentActiveChatID = ChatID;
	MarkChatAsRead(ChatID);
}