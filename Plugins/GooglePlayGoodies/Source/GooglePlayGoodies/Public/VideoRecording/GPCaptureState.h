// Copyright (c) 2020 Nineva Studios

#pragma once

#include "CoreMinimal.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#endif
#include "GPVideoRecordingLibrary.h"

#include "GPCaptureState.generated.h"


UCLASS(BlueprintType)
class GOOGLEPLAYGOODIES_API UGPCaptureState : public UObject
{
	GENERATED_BODY()

public:

#if PLATFORM_ANDROID
	void Init(jobject CaptureState);

	jobject GetCaptureStateObject();
#endif

	UGPCaptureState() = default;
	virtual ~UGPCaptureState();

	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Video Recording")
	ECaptureMode GetCaptureMode();

	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Video Recording")
	EQualityLevel GetCaptureQuality();
	
	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Video Recording")
	bool IsCapturing();	
	
	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Video Recording")
	bool IsOverlayVisible();
	
	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Video Recording")
	bool IsPaused();

private:
#if PLATFORM_ANDROID
	jobject CaptureStateObject;
	jmethodID GetCaptureModeMethod;
	jmethodID GetCaptureQualityMethod;
	jmethodID IsCapturingMethod;
	jmethodID IsOverlayVisibleMethod;
	jmethodID IsPausedMethod;
#endif
};
