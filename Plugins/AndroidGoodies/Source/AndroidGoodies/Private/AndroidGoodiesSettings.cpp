#include "AndroidGoodiesSettings.h"

// Copyright (c) 2020 Nineva Studios

UAndroidGoodiesSettings::UAndroidGoodiesSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	sendSmsPermission = false;
	setAlarmPermission = false;
	cameraPermission = false;
	flashlightPermission = false;
	vibratePermission = false;
	callPhonePermission = false;
	readPhoneStatePermission = false;
	readContactsPermission = false;
	writeContactsPermission = false;
	installPackagesPermission = false;
}