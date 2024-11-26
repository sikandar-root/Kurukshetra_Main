// Copyright (c) 2019 Nineva Studios

#pragma once
#include "HAL/Platform.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJava.h"
#endif

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGVibrationEffect.generated.h"

UCLASS(BlueprintType)
class ANDROIDGOODIES_API UAGVibrationEffect : public UObject
{
	GENERATED_BODY()

public:
	virtual ~UAGVibrationEffect();

	/**
	* Create a one shot vibration. One shot vibrations will vibrate constantly
	* for the specified period of time at the specified amplitude, and then stop.
	*
	* @param seconds - the number of seconds to vibrate. This must be a positive number.
	* @param amplitude - the strength of the vibration. This must be a value between 1 and 255.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static UAGVibrationEffect* VibrationEffectOneShot(float seconds, int amplitude);

	/**
	* Create a waveform vibration. 
	*
	* @param timings - The pattern of alternating on-off timings, starting with off. Timing values of 0 will cause the timing to be ignored.
	* @param repeat - the index of the element in the intervals array, from which to repeat the sequence, or -1 for a single playback.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static UAGVibrationEffect* VibrationEffectWaveForm(TArray<float> timings, int repeat);

	/**
	* Create a waveform vibration. Waveform vibrations are a potentially repeating series of
	* timing and amplitude pairs. For each pair, the value in the amplitude array determines
	* the strength of the vibration and the value in the timing array determines how long
	* it vibrates for.
	*
	* @param timings - The pattern of alternating on-off timings, starting with off. Timing values of 0 will cause the timing/amplitude pair to be ignored.
	* @param amplitudes - The amplitude values of the timing/amplitude pairs. Amplitude values
	* must be between 0 and 255. An amplitude value of 0 implies the motor is off.
	* @param repeat - the index of the element in the intervals array, from which to repeat the sequence, or -1 for a single playback.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static UAGVibrationEffect* VibrationEffectWaveFormWithAmplitudes(TArray<float> timings, TArray<int> amplitudes, int repeat);

#if PLATFORM_ANDROID
	jobject JavaObject;
#endif
};
