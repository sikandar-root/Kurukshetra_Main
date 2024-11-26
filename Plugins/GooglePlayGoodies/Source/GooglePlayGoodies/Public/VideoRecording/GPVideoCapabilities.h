// Copyright (c) 2020 Nineva Studios

#pragma once

#include "CoreMinimal.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#endif
#include "GPVideoRecordingLibrary.h"

#include "GPVideoCapabilities.generated.h"


UCLASS(BlueprintType)
class GOOGLEPLAYGOODIES_API UGPVideoCapabilities : public UObject
{
	GENERATED_BODY()

public:

	#if PLATFORM_ANDROID
		void Init(jobject VideoCapabilities);
	
		jobject GetVideoCapabilitiesObject();
	#endif

		UGPVideoCapabilities() = default;
		virtual ~UGPVideoCapabilities();

		UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Video Recording")
		TArray<ECaptureMode> GetSupportedCaptureModes();
		
		UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Video Recording")
		TArray<EQualityLevel> GetSupportedQualityLevels();

		UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Video Recording")
		bool IsCameraSupported();

		UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Video Recording")
		bool IsFullySupported(ECaptureMode CaptureMode, EQualityLevel QualityLevel);

		UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Video Recording")
		bool IsMicSupported();

		UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Video Recording")
		bool IsWriteStorageSupported();

		UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Video Recording")
		bool SupportsCaptureMode(ECaptureMode CaptureMode);

		UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Video Recording")
		bool SupportsQualityLevel(EQualityLevel QualityLevel);

private:
	int GetCaptureMode(ECaptureMode CaptureMode);
	int GetQualityLevel(EQualityLevel QualityLevel);

	#if PLATFORM_ANDROID
		jobject VideoCapabilitiesObject;
	#endif
};
