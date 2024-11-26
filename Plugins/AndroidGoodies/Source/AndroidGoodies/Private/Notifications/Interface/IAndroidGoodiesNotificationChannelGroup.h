#pragma once

#include "Containers/UnrealString.h"
#include "CoreMinimal.h"

class IAndroidGoodiesNotificationChannel;

class IAndroidGoodiesNotificationChannelGroup
{
public:
	virtual ~IAndroidGoodiesNotificationChannelGroup() = default;
	virtual FString GetId() = 0;
	virtual FString GetName() = 0;
	virtual FString GetDescription() = 0;
	virtual void SetDescription(FString description) = 0;
	virtual bool IsBlocked() = 0;
	virtual TArray<TSharedPtr<IAndroidGoodiesNotificationChannel>> GetChannels() = 0;
};
