// Copyright 2024 Gdy Development, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#if PLATFORM_ANDROID
#include "AndroidPermissionFunctionLibrary.h" 
#endif

#include "FixAndroidPermissionBPLibrary.generated.h"


UENUM(BlueprintType)
enum class EOnSuccess : uint8
{
	None UMETA(DisplayName = "None"),
	OnSuccess UMETA(DisplayName = "OnSuccess"),
	OnUnsuccess UMETA(DisplayName = "OnUnsuccess")
};


UCLASS()
class UFixAndroidPermissionBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	//Get SDK Version
	static int32 GetSDKVersion();

public:

	//Check And Request Android Storage Permissions
	UFUNCTION(BlueprintCallable, Category = "FixAndroidPermissionBPLibrary")
	static UAndroidPermissionCallbackProxy* CheckAndRequestAndroidStoragePermissions();

	//Check Android Storage Permissions  granted
	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "OnSuccess"), Category = "FixAndroidPermissionBPLibrary")
	static void CheckAndroidStoragePermissionsGranted(EOnSuccess & OnSuccess , const TArray<bool>& BoolArray);


};
