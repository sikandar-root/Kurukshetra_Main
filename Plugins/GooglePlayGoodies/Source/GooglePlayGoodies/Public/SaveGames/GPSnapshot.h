// Copyright (c) 2020 Nineva Studios

#pragma once

#include "CoreMinimal.h"
#include "GPSnapshotMetadata.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#endif

#include "GPSnapshot.generated.h"


UCLASS(BlueprintType)
class GOOGLEPLAYGOODIES_API UGPSnapshot : public UObject
{
	GENERATED_BODY()

public:
	UGPSnapshot() = default;
	virtual ~UGPSnapshot();

#if PLATFORM_ANDROID
	void Init(jobject SnapshotObject);

	jobject GetSnapshotObject();
#endif
	
	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Snapshot")
	UGPSnapshotMetadata* GetMetadata() const;

private:

#if PLATFORM_ANDROID
		jobject SnapshotObject;
		jmethodID GetMetadataMethod;
#endif
};
