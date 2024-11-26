// Copyright (c) 2020 Nineva Studios

#pragma once

#include "CoreMinimal.h"
#include "GPSnapshot.h"
#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#endif

#include "GPConflict.generated.h"


UCLASS(BlueprintType)
class GOOGLEPLAYGOODIES_API UGPConflict : public UObject
{
	GENERATED_BODY()

public:
	UGPConflict() = default;
	virtual ~UGPConflict();

#if PLATFORM_ANDROID
	void Init(jobject ConflictObject);

	jobject GetConflictObject();
#endif

	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Conflict")
	FString GetSnapshotconflictId() const;

	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Conflict")
	UGPSnapshot* GetLocalSnapshot() const;

	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Conflict")
	UGPSnapshot* GetServerSnapshot() const;

private:

#if PLATFORM_ANDROID
	jobject ConflictObject;
	jmethodID GetSnapshotConflictIdMethod;
	jmethodID GetLocalSnapshotMethod;
	jmethodID GetServerSnapshotMethod;
#endif
};
