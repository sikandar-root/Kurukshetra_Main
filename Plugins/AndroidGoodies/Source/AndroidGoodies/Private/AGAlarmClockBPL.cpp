// Copyright (c) 2018 Nineva Studios

#include "AGAlarmClockBPL.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJava.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/Utils/AGArrayConvertor.h"
#include "AGDeviceInfoBPL.h"
#include "Android/Utils/AGMethodCallUtils.h"
#endif

static const ANSICHAR* AGAlarmClockClassName = "com/ninevastudios/androidgoodies/AGAlarmClock";

UAGAlarmClock::UAGAlarmClock(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UAGAlarmClock::SetAlarm(int hour, int minute, FString message, FAGAlarmDaysData days, bool vibrate, bool skipUi)
{
#if PLATFORM_ANDROID
	
	AGMethodCallUtils::CallStaticVoidMethod(AGAlarmClockClassName, "setAlarm", "(Landroid/app/Activity;IILjava/lang/String;[IZZ)V",
		FAndroidApplication::GetGameActivityThis(), hour, minute, *FJavaClassObject::GetJString(message), AGArrayConvertor::ConvertToJIntArray(days.ToIntArray()), vibrate, skipUi);

#endif
}

void UAGAlarmClock::SetTimer(int lengthSeconds, FString message, bool skipUi)
{
#if PLATFORM_ANDROID
	
	AGMethodCallUtils::CallStaticVoidMethod(AGAlarmClockClassName, "setTimer", "(Landroid/app/Activity;ILjava/lang/String;Z)V",
			FAndroidApplication::GetGameActivityThis(), lengthSeconds, *FJavaClassObject::GetJString(message), skipUi);
	
#endif
}

void UAGAlarmClock::ShowAllAlarms()
{
#if PLATFORM_ANDROID
	
	AGMethodCallUtils::CallStaticVoidMethod(AGAlarmClockClassName, "showAllAlarms", "(Landroid/app/Activity;)V",
			FAndroidApplication::GetGameActivityThis());
	
#endif
}

void UAGAlarmClock::ShowAllTimers()
{
#if PLATFORM_ANDROID
	
	AGMethodCallUtils::CallStaticVoidMethod(AGAlarmClockClassName, "showAllTimers", "(Landroid/app/Activity;)V", 
		FAndroidApplication::GetGameActivityThis());
	
#endif
}

bool UAGAlarmClock::CanSetAlarm()
{
#if PLATFORM_ANDROID

	return AGMethodCallUtils::CallStaticBoolMethod(AGAlarmClockClassName, "canSetAlarm", "(Landroid/app/Activity;)Z", 
		FAndroidApplication::GetGameActivityThis());

#endif
	return false;
}

bool UAGAlarmClock::CanSetTimer()
{
#if PLATFORM_ANDROID
	
	return AGMethodCallUtils::CallStaticBoolMethod(AGAlarmClockClassName, "canSetTimer", "(Landroid/app/Activity;)Z",
			FAndroidApplication::GetGameActivityThis());
	
#endif
	return false;
}

void UAGAlarmClock::SnoozeAlarm(int snoozeDurationMinutes)
{
#if PLATFORM_ANDROID
	
	AGMethodCallUtils::CallStaticVoidMethod(AGAlarmClockClassName, "snoozeAlarm", "(Landroid/app/Activity;I)V", FAndroidApplication::GetGameActivityThis(), snoozeDurationMinutes);
	
#endif
}