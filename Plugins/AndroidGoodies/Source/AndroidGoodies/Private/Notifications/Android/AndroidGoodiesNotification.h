#pragma once
#include "Notifications/Interface/IAndroidGoodiesNotification.h"
#include "Android/AndroidJNI.h"

class AndroidGoodiesNotification : public IAndroidGoodiesNotification
{
public:
	virtual ~AndroidGoodiesNotification() override;
	AndroidGoodiesNotification(jobject Notification);
	jobject GetNativeNotification();

private:
	jobject NativeNotification;
};
