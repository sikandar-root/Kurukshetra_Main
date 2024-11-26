// Copyright (c) 2018 Nineva Studios

#pragma once

#include "Android/AndroidJava.h"

// Wrapper for com/ninevastudios/androidgoodies/AGDeviceInfo*.java.
class FJavaAGDeviceInfo
{
public:

	static int GetSdkInt();

	static FString GetApplicationPackageName();
	static FString GetBaseOs();
	static FString GetCodeName();
	static FString GetRelease();	
	static FString GetBoard();
	static FString GetBootloader();
	static FString GetBrand();
	static FString GetDevice();
	static FString GetDisplay();
	static FString GetHardware();
	static FString GetManufacturer();
	static FString GetModel();
	static FString GetProduct();
	static FString GetRadio();
	static FString GetSerial();
	static FString GetTags();
	static FString GetType();
	static FString GetAndroidId();

	static bool IsPackageInstalled(FString packageName);
	static bool HasSystemFeature(FString featureName);
	static FString GetInstallSourceAndroid();
};