// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGNotificationDefaults.generated.h"

USTRUCT(BlueprintType)
struct ANDROIDGOODIES_API FAGNotificationDefaults
{
	GENERATED_BODY()

	/**
	* Use the default notification lights. This will ignore the FLAG_SHOW_LIGHTS bit, and ledARGB, ledOffMS, or ledOnMS.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies|Notifications")
	bool Lights = false;

	/**
	* Use the default notification sound. This will ignore any given sound.
	* A notification that is noisy is more likely to be presented as a heads-up notification.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies|Notifications")
	bool Sound = false;

	/**
	* Use the default notification vibrate. This will ignore any given vibrate.
	* Using phone vibration requires the VIBRATE permission.
	* A notification that vibrates is more likely to be presented as a heads-up notification.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies|Notifications")
	bool Vibrate = false;
};
