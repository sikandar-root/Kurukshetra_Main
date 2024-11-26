// Copyright (c) 2018 Nineva Studios

#include "JavaAGDeviceInfo.h"
#include "Android/Utils/AGMethodCallUtils.h"
#include "Android/AndroidApplication.h"

static const ANSICHAR* AGDeviceInfoClassName = "com/ninevastudios/androidgoodies/AGDeviceInfo";

int FJavaAGDeviceInfo::GetSdkInt()
{
	return AGMethodCallUtils::CallStaticIntMethod(AGDeviceInfoClassName, "getSdkInt", "()I");
}

FString FJavaAGDeviceInfo::GetApplicationPackageName()
{
	return AGMethodCallUtils::CallStaticStringMethod(AGDeviceInfoClassName, "getApplicationPackageName", "(Landroid/app/Activity;)Ljava/lang/String;", FJavaWrapper::GameActivityThis);
}

FString FJavaAGDeviceInfo::GetAndroidId()
{
	return AGMethodCallUtils::CallStaticStringMethod(AGDeviceInfoClassName, "getAndroidId", "(Landroid/app/Activity;)Ljava/lang/String;", FJavaWrapper::GameActivityThis);
}

FString FJavaAGDeviceInfo::GetBaseOs()
{
	return AGMethodCallUtils::CallStaticStringMethod(AGDeviceInfoClassName, "getBaseOs", "()Ljava/lang/String;");
}

FString FJavaAGDeviceInfo::GetCodeName()
{
	return AGMethodCallUtils::CallStaticStringMethod(AGDeviceInfoClassName, "getCodeName", "()Ljava/lang/String;");
}

FString FJavaAGDeviceInfo::GetRelease()
{
	return AGMethodCallUtils::CallStaticStringMethod(AGDeviceInfoClassName, "getRelease", "()Ljava/lang/String;");
}

FString FJavaAGDeviceInfo::GetBoard()
{
	return AGMethodCallUtils::CallStaticStringMethod(AGDeviceInfoClassName, "getBoard", "()Ljava/lang/String;");
}

FString FJavaAGDeviceInfo::GetBootloader()
{
	return AGMethodCallUtils::CallStaticStringMethod(AGDeviceInfoClassName, "getBootloader", "()Ljava/lang/String;");
}

FString FJavaAGDeviceInfo::GetBrand()
{
	return AGMethodCallUtils::CallStaticStringMethod(AGDeviceInfoClassName, "getBrand", "()Ljava/lang/String;");
}

FString FJavaAGDeviceInfo::GetDevice()
{
	return AGMethodCallUtils::CallStaticStringMethod(AGDeviceInfoClassName, "getDevice", "()Ljava/lang/String;");
}

FString FJavaAGDeviceInfo::GetDisplay()
{
	return AGMethodCallUtils::CallStaticStringMethod(AGDeviceInfoClassName, "getDisplay", "()Ljava/lang/String;");
}

FString FJavaAGDeviceInfo::GetHardware()
{
	return AGMethodCallUtils::CallStaticStringMethod(AGDeviceInfoClassName, "getHardware", "()Ljava/lang/String;");
}

FString FJavaAGDeviceInfo::GetManufacturer()
{
	return AGMethodCallUtils::CallStaticStringMethod(AGDeviceInfoClassName, "getManufacturer", "()Ljava/lang/String;");
}

FString FJavaAGDeviceInfo::GetModel()
{
	return AGMethodCallUtils::CallStaticStringMethod(AGDeviceInfoClassName, "getModel", "()Ljava/lang/String;");
}

FString FJavaAGDeviceInfo::GetProduct()
{
	return AGMethodCallUtils::CallStaticStringMethod(AGDeviceInfoClassName, "getProduct", "()Ljava/lang/String;");
}

FString FJavaAGDeviceInfo::GetRadio()
{
	return AGMethodCallUtils::CallStaticStringMethod(AGDeviceInfoClassName, "getRadio", "()Ljava/lang/String;");
}

FString FJavaAGDeviceInfo::GetSerial()
{
	return AGMethodCallUtils::CallStaticStringMethod(AGDeviceInfoClassName, "getSerial", "()Ljava/lang/String;");
}

FString FJavaAGDeviceInfo::GetTags()
{
	return AGMethodCallUtils::CallStaticStringMethod(AGDeviceInfoClassName, "getTags", "()Ljava/lang/String;");
}

FString FJavaAGDeviceInfo::GetType()
{
	return AGMethodCallUtils::CallStaticStringMethod(AGDeviceInfoClassName, "getType", "()Ljava/lang/String;");
}

bool FJavaAGDeviceInfo::IsPackageInstalled(FString packageName)
{
	return AGMethodCallUtils::CallStaticBoolMethod(AGDeviceInfoClassName, "isPackageInstalled", "(Landroid/app/Activity;Ljava/lang/String;)Z", FJavaWrapper::GameActivityThis,
	                                               *FJavaClassObject::GetJString(packageName));
}

bool FJavaAGDeviceInfo::HasSystemFeature(FString featureName)
{
	return AGMethodCallUtils::CallStaticBoolMethod(AGDeviceInfoClassName, "hasSystemFeature", "(Landroid/app/Activity;Ljava/lang/String;)Z", FJavaWrapper::GameActivityThis,
	                                               *FJavaClassObject::GetJString(featureName));
}

FString FJavaAGDeviceInfo::GetInstallSourceAndroid()
{
	return AGMethodCallUtils::CallStaticStringMethod(AGDeviceInfoClassName, "GetInstallSourceAndroid", "(Landroid/content/Context;)Ljava/lang/String;", FJavaWrapper::GameActivityThis);
}
