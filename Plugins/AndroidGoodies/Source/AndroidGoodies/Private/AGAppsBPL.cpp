// Copyright (c) 2018 Nineva Studios

#include "AGAppsBPL.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJava.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/Utils/AGMethodCallUtils.h"
#include "Android/Utils/AGArrayConvertor.h"
#endif

static const ANSICHAR* AGAppsClassName = "com/ninevastudios/androidgoodies/AGApps";

FOnApkErrorDelegate UAGApps::OnApkInstallErrorDelegate;

void UAGApps::OpenYoutubeVideo(FString videoId)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGAppsClassName, "watchYoutubeVideo", "(Landroid/app/Activity;Ljava/lang/String;)V", 
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(videoId));

#endif
}

void UAGApps::OpenTwitterProfile(FString profileId)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGAppsClassName, "openTwitterProfile", "(Landroid/app/Activity;Ljava/lang/String;)V", 
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(profileId));

#endif
}

void UAGApps::OpenInstagramProfile(FString profileId)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGAppsClassName, "openInstagramProfile", "(Landroid/app/Activity;Ljava/lang/String;)V", 
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(profileId));

#endif
}

void UAGApps::OpenFacebookProfile(FString profileId)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGAppsClassName, "openFacebookProfile", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(profileId));

#endif
}

void UAGApps::OpenAnotherApplication(FString packageName)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGAppsClassName, "openAnotherApplication", "(Landroid/app/Activity;Ljava/lang/String;)V", 
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(packageName));

#endif
}

void UAGApps::UninstallPackage(FString packageName)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGAppsClassName, "uninstallPackage", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(packageName));

#endif
}

void UAGApps::InstallApkFromFile(FString filePath, const FOnApkErrorDelegate& OnError)
{
	OnApkInstallErrorDelegate = OnError;

#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGAppsClassName, "installApkFromFile", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(filePath));

#endif
}

bool UAGApps::HasPhoneApp()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticBoolMethod(AGAppsClassName, "hasPhoneApp", "(Landroid/app/Activity;)Z", FJavaWrapper::GameActivityThis);
#endif

	return false;
}

void UAGApps::DialPhoneNumber(FString number)
{
#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(AGAppsClassName, "dialPhoneNumber", "(Landroid/app/Activity;Ljava/lang/String;)V", 
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(number));
#endif
}

void UAGApps::CallPhoneNumber(FString number)
{
#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(AGAppsClassName, "callPhoneNumber", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(number));
#endif
}

void UAGApps::DownloadAndInstallApk(FString DownloadUrl, FString DownloadTitle, FString DownloadDescription, const FOnApkErrorDelegate& OnError)
{
	OnApkInstallErrorDelegate = OnError;

#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(AGAppsClassName, "downloadApkToFile", "(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(DownloadTitle), *FJavaClassObject::GetJString(DownloadDescription), *FJavaClassObject::GetJString(DownloadUrl));
#endif
}

#if PLATFORM_ANDROID

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGApps_onApkInstallError(JNIEnv* env, jclass clazz, jstring error)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => onApkInstallError callback caught in C++!"));

	const char * UTFString = env->GetStringUTFChars(error, nullptr);
	FString result = UTF8_TO_TCHAR(UTFString);
	env->ReleaseStringUTFChars(error, UTFString);

	UAGApps::OnApkInstallErrorDelegate.ExecuteIfBound(result);
}

#endif
