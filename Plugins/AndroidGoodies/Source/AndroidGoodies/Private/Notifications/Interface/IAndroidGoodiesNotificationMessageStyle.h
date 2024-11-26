#pragma once

#include "Containers/UnrealString.h"
#include "Misc/DateTime.h"

class IAndroidGoodiesNotificationMessageStyle
{
public:
	virtual ~IAndroidGoodiesNotificationMessageStyle() = default;
	virtual void AddMessage(FString Text, FDateTime TimeStamp, FString Sender) = 0;
	virtual void SetConversationTitle(FString Title) = 0;
	virtual void SetGroupConversation(bool bIsGroupConversation) = 0;
};
