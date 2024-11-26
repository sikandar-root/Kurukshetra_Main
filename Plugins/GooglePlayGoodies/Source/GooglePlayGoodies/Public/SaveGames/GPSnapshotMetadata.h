// Copyright (c) 2020 Nineva Studios

#pragma once

#include "CoreMinimal.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#endif

#include "GPSnapshotMetadata.generated.h"


UCLASS(BlueprintType)
class GOOGLEPLAYGOODIES_API UGPSnapshotMetadata : public UObject
{
	GENERATED_BODY()

public:
#if PLATFORM_ANDROID
	void Init(jobject SnapshotMetadata);

	jobject GetSnapshotMetadataObject();
#endif

	UGPSnapshotMetadata() = default;
	virtual ~UGPSnapshotMetadata();

	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|SnapshotMetadata")
	FString GetDescription();

	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|SnapshotMetadata")
	FString GetDeviceName();

	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|SnapshotMetadata")
	FString GetSnapshotId();

	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|SnapshotMetadata")
	FString GetUniqueName();
	
	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|SnapshotMetadata")
	FString GetCoverImageUri();

	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|SnapshotMetadata")
	float GetCoverImageAspectRatio();

	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|SnapshotMetadata")
	void GetLastModifiedTimestamp(int64& LastModifiedTimestamp);
	
	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|SnapshotMetadata")
	void GetPlayedTime(int64& SnapshotPlayedTime);

	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|SnapshotMetadata")
	void GetProgressValue(int64& ProgressValue);



private:

#if PLATFORM_ANDROID

	jobject SnapshotMetadata;
	jmethodID GetDescriptionMethod;
	jmethodID GetDeviceNameMethod;
	jmethodID GetSnapshotIdMethod;
	jmethodID GetUniqueNameMethod;
	jmethodID GetCoverImageUriMethod;
	jmethodID GetCoverImageAspectRatioMethod;
	jmethodID GetLastModifiedTimestampMethod;
	jmethodID GetPlayedTimeMethod;
	jmethodID GetProgressValueMethod;

#endif
};
