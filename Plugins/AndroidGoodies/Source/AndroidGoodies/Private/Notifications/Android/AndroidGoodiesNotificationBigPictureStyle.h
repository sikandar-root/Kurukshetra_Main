#pragma once
#include "Notifications/Interface/IAndroidGoodiesNotificationBigPictureStyle.h"
#include "Android/AndroidJNI.h"
#include "Engine/Texture2D.h"
#include "Containers/UnrealString.h"

class AndroidGoodiesNotificationBigPictureStyle : public IAndroidGoodiesNotificationBigPictureStyle
{
public:
	virtual ~AndroidGoodiesNotificationBigPictureStyle() override;
	AndroidGoodiesNotificationBigPictureStyle(jobject Style);
	jobject GetNativeStyle();
	virtual void SetBigLargeIcon(UTexture2D* Icon) override;
	virtual void SetBigContentTitle(FString Title) override;
	virtual void SetSummaryText(FString Text) override;

private:
	jobject NativeStyle;
};
