// Copyright (c) 2019 Nineva Studios

#pragma once

#include "Enums/AGChannelImportance.h"
#include "Enums/AGNotificationVisibility.h"
#include "AGAudioAttributes.h"
#include "Kismet/BlueprintFunctionLibrary.h"

class IAndroidGoodiesNotificationChannel;

#include "AGNotificationChannel.generated.h"

UCLASS(BlueprintType)
class ANDROIDGOODIES_API UAGNotificationChannel : public UObject
{
	GENERATED_BODY()

public:
	virtual ~UAGNotificationChannel() override;

	/**
	* Return the id of this channel.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	FString GetId();

	/**
	* Set whether or not notifications posted to this channel can bypass the Do Not Disturb mode.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	UAGNotificationChannel* SetBypassDnd(bool Bypass);

	/**
	* Get whether or not notifications posted to this channel can bypass the Do Not Disturb mode.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	bool CanBypassDnd();

	/**
	* Set whether notifications posted to this channel can appear as badges in a Launcher application.
	* Note that badging may be disabled for other reasons.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	UAGNotificationChannel* SetShowBadge(bool bShow);

	/**
	* Get whether notifications posted to this channel can appear as badges in a Launcher application.
	* Note that badging may be disabled for other reasons.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	bool CanShowBadge();

	/**
	* Set whether notifications posted to this channel should display notification lights,
	* on devices that support that feature. Only modifiable before the channel is submitted to
	* UAGNotificationManager::CreateNotificationChannel().
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	UAGNotificationChannel* SetEnableLights(bool bEnable);

	/**
	* Get whether notifications posted to this channel should display notification lights,
	* on devices that support that feature.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	bool ShouldShowLights();

	/**
	* Set whether notification posted to this channel should vibrate.
	* Only modifiable before the channel is submitted to UAGNotificationManager::CreateNotificationChannel().
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	UAGNotificationChannel* SetEnableVibration(bool bEnable);

	/**
	* Get whether notification posted to this channel should vibrate.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	bool ShouldVibrate();

	/**
	* Return the audio attributes for sound played by notifications posted to this channel.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	FAGAudioAttributes GetAudioAttributes();

	/**
	* Set the user visible description of this channel.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	UAGNotificationChannel* SetDescription(FString Description);

	/**
	* Get the user visible description of this channel.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	FString GetDescription();

	/**
	* Set the notification importance e.g. ChannelImportance::Low for
	* notifications posted to this channel. Note: This value might be > ChannelImportance::None,
	* but notifications posted to this channel will not
	* be shown to the user if the parent NotificationChannelGroup or app is blocked.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	UAGNotificationChannel* SetImportance(ChannelImportance Importance);

	/**
	* Get the importance for notifications posted to this channel.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	ChannelImportance GetImportance();

	/**
	* Set the notification light color for notifications posted to this channel.
	* Irrelevant unless ShouldShowLights.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	UAGNotificationChannel* SetLightColor(FColor Color);

	/**
	* Get the notification light color for notifications posted to this channel.
	* Irrelevant unless ShouldShowLights.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	FColor GetLightColor();

	/**
	* Set whether or not notifications posted to this channel are shown
	* on the lockscreen in full or redacted form.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	UAGNotificationChannel* SetLockScreenVisibility(NotificationVisibility Visibility);

	/**
	* Get whether or not notifications posted to this channel are shown
	* on the lockscreen in full or redacted form.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	NotificationVisibility GetLockScreenVisibility();

	/**
	* Get the user visible name of this channel.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	FString GetName();

	/**
	* Get the notification sound file path for this channel.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	FString GetSoundPath();

	/**
	* Set the vibration pattern for notifications posted to this channel.
	* Will be ignored if vibration is not enabled by SetEnableVibration(true).
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	UAGNotificationChannel* SetVibrationPattern(TArray<float> Pattern);

	/**
	* Get the vibration pattern for notifications posted to this channel.
	* Will be ignored if vibration is not enabled by SetEnableVibration(true).
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	TArray<float> GetVibrationPattern();

	/**
	* Set the sound that should be played for notifications posted to this channel and its audio attributes.
	* Notification channels with an importance of at least ChannelImportance::DefaultImp
	* should have a sound. Only modifiable before the channel is submitted to UAGNotificationManager::CreateNotificationChannel.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	UAGNotificationChannel* SetSound(FString FilePath, FAGAudioAttributes Attributes);

	/**
	* Get what group this channel belongs to.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	FString GetGroupId();

	/**
	* Set what group this channel belongs to.
	* This is used only for visually grouping channels in the UI.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	UAGNotificationChannel* SetGroup(FString GroupId);

	void Init(TSharedPtr<IAndroidGoodiesNotificationChannel> Channel);
	TSharedPtr<IAndroidGoodiesNotificationChannel> GetNativeNotificationChannel() const;
	bool IsValid() const;

private:
	TSharedPtr<IAndroidGoodiesNotificationChannel> NativeNotificationChannel = nullptr;
};
