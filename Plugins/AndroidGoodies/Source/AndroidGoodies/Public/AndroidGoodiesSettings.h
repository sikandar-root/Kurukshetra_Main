// Copyright (c) 2019 Nineva Studios

#pragma once

#include "Engine/EngineTypes.h"
#include "AndroidGoodiesSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class ANDROIDGOODIES_API UAndroidGoodiesSettings : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	/** Folder, files from which should be copied to the "../Android/res/drawable" folder */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings|Drawables")
	FDirectoryPath AndroidDrawablesFolder;

	/** Add send SMS permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings|Permissions")
	bool sendSmsPermission = false;

	/** Add set alarm permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings|Permissions")
	bool setAlarmPermission = false;

	/** Add camera permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings|Permissions")
	bool cameraPermission = false;

	/** Add READ_MEDIA_IMAGES permission to Android Manifest  Required for file pickers to works on Android 13+ */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings|Permissions")
	bool readMediaImagesPermission = false;

	/** Add flashlight permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings|Permissions")
	bool flashlightPermission = false;

	/** Add vibrate permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings|Permissions")
	bool vibratePermission = false;

	/** Add call phone permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings|Permissions")
	bool callPhonePermission = false;

	/** Add read phone state permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings|Permissions")
	bool readPhoneStatePermission = false;

	/** Add read contact permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings|Permissions")
	bool readContactsPermission = false;

	/** Add write contact permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings|Permissions")
	bool writeContactsPermission = false;

	/** Add install packages permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings|Permissions")
	bool installPackagesPermission = false;

	/** Add coarse location permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings|Permissions")
	bool coarseLocationPermission = false;

	/** Add fine location permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings|Permissions")
	bool fineLocationPermission = false;

	/** Add change WI-FI state permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings|Permissions")
	bool changeWifiStatePermission = false;

	/** You must add this permission if you are using scheduling notifications */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings|Permissions")
	bool setExactAlarmsPermission = true;

	/** You must add this permission if you are using notifications on Android 13+ */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings|Permissions")
	bool sendPushNotificationsPermission = true;
};
