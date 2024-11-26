#pragma once

#include "Notifications/Interface/IAndroidGoodiesNotificationChannelGroup.h"
#include "Templates/SharedPointer.h"
#include "Containers/Array.h"
#include "Android/AndroidJNI.h"

class IAndroidGoodiesNotificationChannel;

class AndroidGoodiesNotificationChannelGroup : public IAndroidGoodiesNotificationChannelGroup
{
public:
	virtual ~AndroidGoodiesNotificationChannelGroup() override;
	AndroidGoodiesNotificationChannelGroup(jobject ChannelGroup);
	jobject GetNativeChannelGroup();
	virtual FString GetId() override;
	virtual FString GetName() override;
	virtual FString GetDescription() override;
	virtual void SetDescription(FString Description) override;
	virtual bool IsBlocked() override;
	virtual TArray<TSharedPtr<IAndroidGoodiesNotificationChannel>> GetChannels() override;

private:
	jobject NativeChannelGroup;
};
