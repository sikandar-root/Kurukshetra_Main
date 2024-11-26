// Copyright (c) 2020 Nineva Studios

#include "Social/GPAchievementLibrary.h"

#include "GooglePlayLog.h"

#if PLATFORM_ANDROID
#include "Android/Utils/GPMethodCallUtils.h"
#endif

static const ANSICHAR* GPAchievementClassName = "com/ninevastudios/googleplay/GPAchievement";

void UGPAchievementLibrary::UnlockAchievement(const FString& AchievementID)
{
#if PLATFORM_ANDROID
	auto JIdString = FJavaClassObject::GetJString(AchievementID);
	GPMethodCallUtils::CallStaticVoidMethod(GPAchievementClassName, "unlock", "(Landroid/app/Activity;Ljava/lang/String;)V", 
		FJavaWrapper::GameActivityThis, *JIdString);
#endif
}

void UGPAchievementLibrary::IncrementAchievement(const FString& AchievementID, int Value)
{
#if PLATFORM_ANDROID
	auto JIdString = FJavaClassObject::GetJString(AchievementID);
	GPMethodCallUtils::CallStaticVoidMethod(GPAchievementClassName, "increment", "(Landroid/app/Activity;Ljava/lang/String;I)V", 
		FJavaWrapper::GameActivityThis, *JIdString, Value);
#endif
}

void UGPAchievementLibrary::ShowAchievementUI()
{
#if PLATFORM_ANDROID
	GPMethodCallUtils::CallStaticVoidMethod(GPAchievementClassName, "showUI", "(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis);
#endif
}
