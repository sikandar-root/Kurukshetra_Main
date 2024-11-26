#pragma once

#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJava.h"

#include "Notifications/Interface/IAndroidGoodiesNotificationChannel.h"

class AndroidGoodiesNotificationChannel : public IAndroidGoodiesNotificationChannel
{
public:
	virtual ~AndroidGoodiesNotificationChannel() override;
	AndroidGoodiesNotificationChannel(jobject Channel);
	jobject GetNativeNotificationChannel();

	virtual FString GetId() override;
	virtual void SetBypassDnd(bool Bypass) override;
	virtual bool CanBypassDnd() override;
	virtual void SetShowBadge(bool Show) override;
	virtual bool CanShowBadge() override;
	virtual void SetEnableLights(bool Enable) override;
	virtual bool ShouldShowLights() override;
	virtual void SetEnableVibration(bool Enable) override;
	virtual bool ShouldVibrate() override;
	virtual FAGAudioAttributes GetAudioAttributes() override;
	virtual void SetDescription(FString Description) override;
	virtual FString GetDescription() override;
	virtual void SetImportance(ChannelImportance Importance) override;
	virtual ChannelImportance GetImportance() override;
	virtual void SetLightColor(FColor Color) override;
	virtual FColor GetLightColor() override;
	virtual void SetLockScreenVisibility(NotificationVisibility Visibility) override;
	virtual NotificationVisibility GetLockScreenVisibility() override;
	virtual FString GetName() override;
	virtual FString GetSoundPath() override;
	virtual void SetVibrationPattern(TArray<float> Pattern) override;
	virtual TArray<float> GetVibrationPattern() override;
	virtual void SetSound(FString FilePath, FAGAudioAttributes Attributes) override;
	virtual FString GetGroupId() override;
	virtual void SetGroup(FString GroupId) override;

private:
	jobject NativeNotificationChannel;
};
