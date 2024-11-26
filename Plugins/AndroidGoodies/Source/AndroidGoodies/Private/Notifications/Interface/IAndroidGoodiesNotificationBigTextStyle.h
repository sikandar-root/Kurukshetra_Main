#pragma once

#include "Containers/UnrealString.h"

class IAndroidGoodiesNotificationBigTextStyle
{
public:
	virtual ~IAndroidGoodiesNotificationBigTextStyle() = default;
	virtual void SetBigContentTitle(FString Title) = 0;
	virtual void SetSummaryText(FString Summary) = 0;
};
