// Copyright (c) 2018 Nineva Studios

#include "AGDateTimePickerBPL.h"
#include "Async/Async.h"

#if PLATFORM_ANDROID
#include "Android/Utils/AGMediaUtils.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/Utils/AGMethodCallUtils.h"
#endif

FOnDateSetDelegate UAGDateTimePickerBPL::OnDateSetDelegate;
FOnTimeSetDelegate UAGDateTimePickerBPL::OnTimeSetDelegate;
FOnCancelDelegate UAGDateTimePickerBPL::OnCancelDelegate;

static const ANSICHAR* AGDateTimePickerClassName = "com/ninevastudios/androidgoodies/AGDateTimePicker";

UAGDateTimePickerBPL::UAGDateTimePickerBPL(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UAGDateTimePickerBPL::ShowDatePicker(FDateTime initialDate, const FOnDateSetDelegate& onDateSetCallback, const FOnCancelDelegate& onCancelCallback, DialogTheme theme)
{
	OnDateSetDelegate = onDateSetCallback;
	OnCancelDelegate = onCancelCallback;
	
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGDateTimePickerClassName, "showDatePicker", "(Landroid/app/Activity;IIII)V",
		FJavaWrapper::GameActivityThis, initialDate.GetYear(), initialDate.GetMonth()-1, initialDate.GetDay(), AGMediaUtils::GetDialogTheme(theme));

#endif
}

void UAGDateTimePickerBPL::ShowDatePickerWithLimits(FDateTime initialDate, const FOnDateSetDelegate& onDateSetCallback, const FOnCancelDelegate& onCancelCallback,
	FDateTime fromDate, FDateTime toDate, DialogTheme theme)
{
	OnDateSetDelegate = onDateSetCallback;
	OnCancelDelegate = onCancelCallback;

	int64 fromLimitMils = fromDate.ToUnixTimestamp() * 1000;
	int64 toLimitsMils = toDate.ToUnixTimestamp() * 1000;

#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGDateTimePickerClassName, "showDatePickerWithLimits", "(Landroid/app/Activity;IIIJJI)V",
		FJavaWrapper::GameActivityThis, initialDate.GetYear(), initialDate.GetMonth()-1, initialDate.GetDay(), fromLimitMils, toLimitsMils, AGMediaUtils::GetDialogTheme(theme));

#endif
}

void UAGDateTimePickerBPL::ShowTimePicker(int hour, int minute, const FOnTimeSetDelegate& onTimeSetCallback, const FOnCancelDelegate& onCancelCallback, DialogTheme theme, bool is24HourView)
{
	OnTimeSetDelegate = onTimeSetCallback;
	OnCancelDelegate = onCancelCallback;

#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGDateTimePickerClassName, "showTimePicker", "(Landroid/app/Activity;IIIZ)V",
		FJavaWrapper::GameActivityThis, hour, minute, AGMediaUtils::GetDialogTheme(theme), is24HourView);

#endif
}

void UAGDateTimePickerBPL::OnDateSet(int year, int month, int day)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnDateSetDelegate.ExecuteIfBound(year, month, day);
	});
}

void UAGDateTimePickerBPL::OnTimeSet(int hour, int minute)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnTimeSetDelegate.ExecuteIfBound(hour, minute);
	});
}

void UAGDateTimePickerBPL::OnCancel()
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnCancelDelegate.ExecuteIfBound();
	});
}

#if PLATFORM_ANDROID

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGDateTimePicker_onDateSet(JNIEnv* env, jclass clazz, int year, int month, int day)
{
	UAGDateTimePickerBPL::OnDateSet(year, month, day);
}

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGDateTimePicker_onTimeSet(JNIEnv* env, jclass clazz, int hour, int minute)
{
	UAGDateTimePickerBPL::OnTimeSet(hour, minute);
}

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGDateTimePicker_onCancel(JNIEnv* env, jclass clazz)
{
	UAGDateTimePickerBPL::OnCancel();
}

#endif
