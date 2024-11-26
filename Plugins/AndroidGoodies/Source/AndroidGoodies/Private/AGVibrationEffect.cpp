// Copyright (c) 2019 Nineva Studios

#include "AGVibrationEffect.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJava.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/Utils/AGMethodCallUtils.h"
#include "Android/Utils/AGArrayConvertor.h"
#endif

static const ANSICHAR* HardwareClassName = "com/ninevastudios/androidgoodies/AGHardware";

UAGVibrationEffect::~UAGVibrationEffect()
{
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->DeleteGlobalRef(JavaObject);
	JavaObject = nullptr;
#endif
}

UAGVibrationEffect* UAGVibrationEffect::VibrationEffectOneShot(float seconds, int amplitude)
{
	UAGVibrationEffect* effect = NewObject<UAGVibrationEffect>();

	amplitude = FMath::Clamp(amplitude, 1, 255);

#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	effect->JavaObject = Env->NewGlobalRef(AGMethodCallUtils::CallStaticObjectMethod(HardwareClassName, "createVibrationEffect", "(JI)Landroid/os/VibrationEffect;", 
		(jlong)(long)FMath::RoundHalfFromZero(seconds * 1000), (jint) amplitude));
#endif

	return effect;
}

UAGVibrationEffect* UAGVibrationEffect::VibrationEffectWaveForm(TArray<float> timings, int repeat)
{
	UAGVibrationEffect* effect = NewObject<UAGVibrationEffect>();

	TArray<long> timingsArray;
	for (int i = 0; i < timings.Num(); i++)
	{
		timingsArray.Add((long)FMath::RoundHalfFromZero(timings[i] * 1000));
	}

#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	effect->JavaObject = Env->NewGlobalRef(AGMethodCallUtils::CallStaticObjectMethod(HardwareClassName, "createVibrationEffect", "([JI)Landroid/os/VibrationEffect;",
		AGArrayConvertor::ConvertToJLongArray(timingsArray), (jint) repeat));
#endif

	return effect;
}

UAGVibrationEffect* UAGVibrationEffect::VibrationEffectWaveFormWithAmplitudes(TArray<float> timings, TArray<int> amplitudes, int repeat)
{
	UAGVibrationEffect* effect = NewObject<UAGVibrationEffect>();

	TArray<long> timingsArray;
	for (int i = 0; i < timings.Num(); i++)
	{
		timingsArray.Add((long)FMath::RoundHalfFromZero(timings[i] * 1000));
		amplitudes[i] = FMath::Clamp(amplitudes[i], 0, 255);
	}

	if (timings.Num() != amplitudes.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("ANDROIDGOODIES => Timings and Amplitudes arrays have to be of equal length!"));
		return effect;
	}

#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	effect->JavaObject = Env->NewGlobalRef(AGMethodCallUtils::CallStaticObjectMethod(HardwareClassName, "createVibrationEffect", "([J[II)Landroid/os/VibrationEffect;",
		AGArrayConvertor::ConvertToJLongArray(timingsArray), AGArrayConvertor::ConvertToJIntArray(amplitudes), (jint) repeat));
#endif

	return effect;
}
