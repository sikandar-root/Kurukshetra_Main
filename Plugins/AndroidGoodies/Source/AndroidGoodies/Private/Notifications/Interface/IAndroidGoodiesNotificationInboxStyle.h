#pragma once

#include "Containers/UnrealString.h"

class IAndroidGoodiesNotificationInboxStyle
{
public:
	virtual ~IAndroidGoodiesNotificationInboxStyle() = default;
	virtual void AddLine(FString Line) = 0;
	virtual void SetBigContentTitle(FString Title) = 0;
	virtual void SetSummaryText(FString Summary) = 0;
};
