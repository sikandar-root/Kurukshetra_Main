#pragma once
#include "Notifications/Interface/IAndroidGoodiesNotificationBigTextStyle.h"
#include "Containers/UnrealString.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"

class AndroidGoodiesNotificationBigTextStyle : public IAndroidGoodiesNotificationBigTextStyle
{
public:
	virtual ~AndroidGoodiesNotificationBigTextStyle() override;
	AndroidGoodiesNotificationBigTextStyle(jobject Style);
	jobject GetNativeStyle();
	virtual void SetBigContentTitle(FString Title) override;
	virtual void SetSummaryText(FString Summary) override;

private:
	jobject NativeStyle;
};
