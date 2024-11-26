#pragma once

#include "Notifications/Enums/AGChannelImportance.h"
#include "Notifications/Enums/AGNotificationVisibility.h"

struct FAGAudioAttributes;

class IAndroidGoodiesNotificationChannel
{
public:
	virtual ~IAndroidGoodiesNotificationChannel() = default;

	virtual FString GetId() = 0;
	virtual void SetBypassDnd(bool Bypass) = 0;
	virtual bool CanBypassDnd() = 0;
	virtual void SetShowBadge(bool Show) = 0;
	virtual bool CanShowBadge() = 0;
	virtual void SetEnableLights(bool Enable) = 0;
	virtual bool ShouldShowLights() = 0;
	virtual void SetEnableVibration(bool Enable) = 0;
	virtual bool ShouldVibrate() = 0;
	virtual FAGAudioAttributes GetAudioAttributes() = 0;
	virtual void SetDescription(FString Description) = 0;
	virtual FString GetDescription() = 0;
	virtual void SetImportance(ChannelImportance Importance) = 0;
	virtual ChannelImportance GetImportance() = 0;
	virtual void SetLightColor(FColor Color) = 0;
	virtual FColor GetLightColor() = 0;
	virtual void SetLockScreenVisibility(NotificationVisibility Visibility) = 0;
	virtual NotificationVisibility GetLockScreenVisibility() = 0;
	virtual FString GetName() = 0;
	virtual FString GetSoundPath() = 0;
	virtual void SetVibrationPattern(TArray<float> Pattern) = 0;
	virtual TArray<float> GetVibrationPattern() = 0;
	virtual void SetSound(FString FilePath, FAGAudioAttributes Attributes) = 0;
	virtual FString GetGroupId() = 0;
	virtual void SetGroup(FString GroupId) = 0;
};
