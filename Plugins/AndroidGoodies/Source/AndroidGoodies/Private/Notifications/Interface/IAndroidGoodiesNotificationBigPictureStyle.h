#pragma once

#include "Engine/Texture2D.h"
#include "Containers/UnrealString.h"

class IAndroidGoodiesNotificationBigPictureStyle
{
public:
	virtual ~IAndroidGoodiesNotificationBigPictureStyle() = default;
	virtual void SetBigLargeIcon(UTexture2D* Icon) = 0;
	virtual void SetBigContentTitle(FString Title) = 0;
	virtual void SetSummaryText(FString Text) = 0;
};
