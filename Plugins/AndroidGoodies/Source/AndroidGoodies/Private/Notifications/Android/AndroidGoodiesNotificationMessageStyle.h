#pragma once

#include "Containers/UnrealString.h"
#include "Misc/DateTime.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"
#include "Notifications/Interface/IAndroidGoodiesNotificationMessageStyle.h"

class AndroidGoodiesNotificationMessageStyle : public IAndroidGoodiesNotificationMessageStyle
{
public:
	virtual ~AndroidGoodiesNotificationMessageStyle() override;
	AndroidGoodiesNotificationMessageStyle(jobject Style);
	jobject GetNativeStyle();

	virtual void AddMessage(FString Text, FDateTime TimeStamp, FString Sender) override;
	virtual void SetConversationTitle(FString Title) override;
	virtual void SetGroupConversation(bool bIsGroupConversation) override;

private:
	jobject NativeStyle;
};
