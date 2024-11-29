// Copyright (c) 2019 Nineva Studios

#include "AGHardwareBPL.h"
#include "AGDeviceInfoBPL.h"
#include "Async/Async.h"

#if PLATFORM_ANDROID
#include "Android/Utils/AGMethodCallUtils.h"
#include "Android/Utils/AGArrayConvertor.h"
#endif

static const ANSICHAR* AGHardwareClassName = "com/ninevastudios/androidgoodies/AGHardware";


FIntPoint UAGHardwareBPL::GetDeviceViewportSizeFullScreen()
{
	FIntPoint viewportSize(0, 0);
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jobject viewportArray = AGMethodCallUtils::CallStaticObjectMethod(AGHardwareClassName, "getDeviceViewportSizeFullScreen", "(Landroid/app/Activity;)[I", FJavaWrapper::GameActivityThis);
	jintArray* intArray = reinterpret_cast<jintArray*>(&viewportArray);
	jsize length = Env->GetArrayLength(*intArray);
	jint* viewportValues = Env->GetIntArrayElements(*intArray, 0);
	if (length == 2)
	{
		viewportSize.X = viewportValues[0];
		viewportSize.Y = viewportValues[1];
	}
	Env->ReleaseIntArrayElements(*intArray, viewportValues, 0);
#endif
	return viewportSize;
}

FIntPoint UAGHardwareBPL::GetDeviceViewportSizeAdjusted()
{
	FIntPoint viewportSize(0, 0);
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jobject viewportArray = AGMethodCallUtils::CallStaticObjectMethod(AGHardwareClassName, "getDeviceViewportSizeAdjusted", "(Landroid/app/Activity;)[I", FJavaWrapper::GameActivityThis);
	jintArray* intArray = reinterpret_cast<jintArray*>(&viewportArray);
	jsize length = Env->GetArrayLength(*intArray);
	jint* viewportValues = Env->GetIntArrayElements(*intArray, 0);
	if (length == 2)
	{
		viewportSize.X = viewportValues[0];
		viewportSize.Y = viewportValues[1];
	}
	Env->ReleaseIntArrayElements(*intArray, viewportValues, 0);
#endif
	return viewportSize;
}

bool UAGHardwareBPL::HasNotch()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticBoolMethod(AGHardwareClassName, "hasNotch", "(Landroid/app/Activity;)Z", FJavaWrapper::GameActivityThis);
#endif
	return false;
}

bool UAGHardwareBPL::HasRoundedCorners()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticBoolMethod(AGHardwareClassName, "hasRoundedCorners", "(Landroid/app/Activity;)Z", FJavaWrapper::GameActivityThis);
#endif
	return false;
}
int32 UAGHardwareBPL::GetVolumeLevel()
{
	int32 volumeLevel = 0;
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jclass AGHardwareClass = FAndroidApplication::FindJavaClass(AGHardwareClassName);
	jmethodID Method = Env->GetStaticMethodID(AGHardwareClass, "getVolumeLevel", "(Landroid/app/Activity;)I");
	volumeLevel = Env->CallStaticIntMethod(AGHardwareClass, Method, FJavaWrapper::GameActivityThis);
	Env->DeleteLocalRef(AGHardwareClass);
#endif
	return volumeLevel;
}

void UAGHardwareBPL::SetVolumeLevel(int32 VolumeLevel)
{
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jclass AGHardwareClass = FAndroidApplication::FindJavaClass(AGHardwareClassName);
	jmethodID Method = Env->GetStaticMethodID(AGHardwareClass, "setVolumeLevel", "(Landroid/app/Activity;I)V");
	Env->CallStaticVoidMethod(AGHardwareClass, Method, FJavaWrapper::GameActivityThis, VolumeLevel);
	Env->DeleteLocalRef(AGHardwareClass);
#endif
}

int32 UAGHardwareBPL::GetMaxVolumeLevel()
{
	int32 maxVolumeLevel = 0;
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jclass AGHardwareClass = FAndroidApplication::FindJavaClass(AGHardwareClassName);
	jmethodID Method = Env->GetStaticMethodID(AGHardwareClass, "getMaxVolumeLevel", "(Landroid/app/Activity;)I");
	maxVolumeLevel = Env->CallStaticIntMethod(AGHardwareClass, Method, FJavaWrapper::GameActivityThis);
	Env->DeleteLocalRef(AGHardwareClass);
#endif
	return maxVolumeLevel;
}

void UAGHardwareBPL::EnableFlashlight(bool enable)
{
#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(AGHardwareClassName, "enableFlashlight", "(Landroid/app/Activity;Z)V", FJavaWrapper::GameActivityThis, enable);
#endif
}

bool UAGHardwareBPL::HasVibrator()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticBoolMethod(AGHardwareClassName, "hasVibrator", "(Landroid/app/Activity;)Z", FJavaWrapper::GameActivityThis);
#endif

	return false;
}

bool UAGHardwareBPL::HasAmplitudeControl()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticBoolMethod(AGHardwareClassName, "hasAmplitudeControl", "(Landroid/app/Activity;)Z", FJavaWrapper::GameActivityThis);
#endif

	return false;
}

void UAGHardwareBPL::Vibrate(float duration)
{
	long durationLong = (long) FMath::RoundHalfFromZero(duration * 1000);

	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Duration: %d"), durationLong);

#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(AGHardwareClassName, "vibrate", "(Landroid/app/Activity;J)V", FJavaWrapper::GameActivityThis, (jlong) durationLong);
#endif
}

void UAGHardwareBPL::VibrateWithPattern(TArray<float> pattern, int repeatFrom)
{
	TArray<long> longArray;
	for (int i = 0; i < pattern.Num(); i++)
	{
		longArray.Add((long) FMath::RoundHalfFromZero(pattern[i] * 1000));
	}

#if PLATFORM_ANDROID
	jlongArray jLongArray = AGArrayConvertor::ConvertToJLongArray(longArray);
	AGMethodCallUtils::CallStaticVoidMethod(AGHardwareClassName, "vibrate", "(Landroid/app/Activity;[JI)V", 
		FJavaWrapper::GameActivityThis, jLongArray, repeatFrom);
#endif
}

bool UAGHardwareBPL::AreVibrationEffectsSupported()
{
	return UAGDeviceInfo::GetSdkInt() >= 26;
}

void UAGHardwareBPL::VibrateWithEffect(UAGVibrationEffect* vibrationEffect)
{
#if PLATFORM_ANDROID
	if (!vibrationEffect->JavaObject)
	{
		UE_LOG(LogTemp, Error, TEXT("ANDROIDGOODIES => Vibration Effect was not created successfully, returning..."));
		return;
	}

	AGMethodCallUtils::CallStaticVoidMethod(AGHardwareClassName, "vibrate", "(Landroid/app/Activity;Landroid/os/VibrationEffect;)V", 
		FJavaWrapper::GameActivityThis, vibrationEffect->JavaObject);
#endif
}

void UAGHardwareBPL::VibrateWithEffectAndAttributes(UAGVibrationEffect* vibrationEffect, FAGAudioAttributes audioAttributes)
{
	int flagsInt = 0;
	if (audioAttributes.Flags.AudibilityEnforced)
	{
		flagsInt = flagsInt | 1;
	}
	if (audioAttributes.Flags.HwAvSync)
	{
		flagsInt = flagsInt | 16;
	}
	if (audioAttributes.Flags.LowLatency)
	{
		flagsInt = flagsInt | 256;
	}

	UE_LOG(LogTemp, Error, TEXT("ANDROIDGOODIES => Flags: %d"), flagsInt);

#if PLATFORM_ANDROID
	if (!vibrationEffect->JavaObject)
	{
		UE_LOG(LogTemp, Error, TEXT("ANDROIDGOODIES => Vibration Effect was not created successfully, returning..."));
		return;
	}

	AGMethodCallUtils::CallStaticVoidMethod(AGHardwareClassName, "vibrate", "(Landroid/app/Activity;Landroid/os/VibrationEffect;III)V",
		FJavaWrapper::GameActivityThis, vibrationEffect->JavaObject, flagsInt, (int) audioAttributes.Usage, (int) audioAttributes.ContentType);
#endif
}

void UAGHardwareBPL::StopVibration()
{
#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(AGHardwareClassName, "stopVibration", "(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis);
#endif
}

FOnWifiScanSuccessDelegate UAGHardwareBPL::OnWifiScanSuccessDelegate;
FOnWifiScanFailureDelegate UAGHardwareBPL::OnWifiScanFailureDelegate;

void UAGHardwareBPL::StartWifiScan(
	const FOnWifiScanSuccessDelegate& OnWifiScanSuccess,
	const FOnWifiScanFailureDelegate& OnWifiScanFailure)
{
	OnWifiScanSuccessDelegate = OnWifiScanSuccess;
	OnWifiScanFailureDelegate = OnWifiScanFailure;
#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(AGHardwareClassName, "startWifiScan", "(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis);
#endif
}

void UAGHardwareBPL::ConnectToWifiNetwork(const FString& SSID, const FString& Password, bool IsWpa2)
{
#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(AGHardwareClassName, "connectToWifiNetwork", "(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;Z)V", 
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(SSID), *FJavaClassObject::GetJString(Password), IsWpa2);
#endif
}

void UAGHardwareBPL::ToggleWifiState(bool Enabled)
{
#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(AGHardwareClassName, "enableWifi", "(Landroid/app/Activity;Z)V", FJavaWrapper::GameActivityThis, Enabled);
#endif
}

bool UAGHardwareBPL::IsWifiEnabled()
{
	bool Result = false;

#if PLATFORM_ANDROID
	Result = AGMethodCallUtils::CallStaticBoolMethod(AGHardwareClassName, "isWifiEnabled", "(Landroid/app/Activity;)Z", FJavaWrapper::GameActivityThis);
#endif

	return Result;
}

int UAGHardwareBPL::ComputeRemainingChargeTime()
{
#if PLATFORM_ANDROID
	return (int) (AGMethodCallUtils::CallStaticLongMethod(AGHardwareClassName, "computeRemainingChargeTime", "(Landroid/app/Activity;)J", FJavaWrapper::GameActivityThis) / 1000);
#endif

	return -1;
}

int UAGHardwareBPL::GetBatteryCapacity()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getBatteryCapacity", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
#endif

	return -1;
}

int UAGHardwareBPL::GetBatteryChargeCounter()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getBatteryChargeCounter", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
#endif

	return -1;
}

int UAGHardwareBPL::GetAverageBatteryCurrent()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getAverageBatteryCurrent", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
#endif

	return -1;
}

int UAGHardwareBPL::GetImmediateBatteryCurrent()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getImmediateBatteryCurrent", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
#endif

	return -1;
}

int UAGHardwareBPL::GetBatteryEnergyCounter()
{
#if PLATFORM_ANDROID
	return (int) AGMethodCallUtils::CallStaticLongMethod(AGHardwareClassName, "getBatteryEnergyCounter", "(Landroid/app/Activity;)J", FJavaWrapper::GameActivityThis);
#endif

	return -1;
}

BatteryStatus UAGHardwareBPL::GetBatteryStatus()
{
#if PLATFORM_ANDROID
	int jBatteryStatus = AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getBatteryStatus", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
	return static_cast<BatteryStatus>(jBatteryStatus - 1);
#endif

	return BatteryStatus::UnknownStatus;
}

bool UAGHardwareBPL::IsBatteryLow()
{
	if (UAGDeviceInfo::GetSdkInt() < 28)
	{
		return false;
	}

#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticBoolMethod(AGHardwareClassName, "isBatteryLow", "(Landroid/app/Activity;)Z", FJavaWrapper::GameActivityThis);
#endif

	return false;
}

BatteryHealth UAGHardwareBPL::GetBatteryHealth()
{
#if PLATFORM_ANDROID
	int jBatterHealthId = AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getBatteryHealth", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
	return static_cast<BatteryHealth>(jBatterHealthId - 1);
#endif

	return BatteryHealth::UnknownHealth;
}

int UAGHardwareBPL::GetBatteryLevel()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getBatteryLevel", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
#endif

	return -1;
}

BatteryPluggedState UAGHardwareBPL::GetBatteryPluggedState()
{
#if PLATFORM_ANDROID
	return (BatteryPluggedState)AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getBatteryPluggedState", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
#endif

	return BatteryPluggedState::OnBattery;
}

bool UAGHardwareBPL::IsBatteryPresent()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticBoolMethod(AGHardwareClassName, "isBatteryPresent", "(Landroid/app/Activity;)Z", FJavaWrapper::GameActivityThis);
#endif

	return false;
}

int UAGHardwareBPL::GetBatteryScale()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getBatteryScale", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
#endif

	return -1;
}

FString UAGHardwareBPL::GetBatteryTechnology()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticStringMethod(AGHardwareClassName, "getBatteryTechnology", "(Landroid/app/Activity;)Ljava/lang/String;", FJavaWrapper::GameActivityThis);
#endif

	return "Unknown";
}

int UAGHardwareBPL::GetBatteryTemperature()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getBatteryTemperature", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
#endif

	return INT32_MIN;
}

int UAGHardwareBPL::GetBatteryVoltage()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getBatteryVoltage", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
#endif

	return 0;
}

#if PLATFORM_ANDROID

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGHardware_onReceiverSuccessCallback(JNIEnv* env, jclass clazz, jobjectArray scanResultJArray)
{
	TArray<UAGScanResultBPL*> ScanResultArray;
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	int length = Env->GetArrayLength(scanResultJArray);
	for (int i = 0; i < length; i++)
	{
		auto javaScanRes = Env->GetObjectArrayElement(scanResultJArray, i);

		UAGScanResultBPL* Res = NewObject<UAGScanResultBPL>();
		Res->Init(javaScanRes);
		ScanResultArray.Add(Res);
	}
	AsyncTask(ENamedThreads::GameThread, [=]() {
		UAGHardwareBPL::OnWifiScanSuccessDelegate.ExecuteIfBound(ScanResultArray);
	});
}

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGHardware_onReceiverFailureCallback(JNIEnv* env, jclass clazz, jstring errorMessage)
{
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, errorMessage);
	UE_LOG(LogTemp, Error, TEXT("%s"), *ErrorMessage);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UAGHardwareBPL::OnWifiScanFailureDelegate.ExecuteIfBound(ErrorMessage);
	});
}

#endif