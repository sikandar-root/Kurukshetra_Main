#pragma once
#include "Notifications/Interface/IAndroidGoodiesNotificationInboxStyle.h"
#include "Containers/UnrealString.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"

class AndroidGoodiesNotificationInboxStyle : public IAndroidGoodiesNotificationInboxStyle
{
public:
	virtual ~AndroidGoodiesNotificationInboxStyle() override;
	AndroidGoodiesNotificationInboxStyle(jobject Style);
	jobject GetNativeStyle();
	
	virtual void AddLine(FString Line) override;
	virtual void SetBigContentTitle(FString Title) override;
	virtual void SetSummaryText(FString Summary) override;

private:
	jobject NativeStyle;
};
