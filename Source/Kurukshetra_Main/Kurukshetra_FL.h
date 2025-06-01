// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kurukshetra_FL.generated.h"

// Add Android platform detection
#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#endif

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPermissionResult, bool, bGranted);

UENUM(BlueprintType)
enum class EPlatformType : uint8
{
	PT_Editor UMETA(DisplayName = "Editor"),
	PT_Windows UMETA(DisplayName = "Windows"),
	PT_Android UMETA(DisplayName = "Android"),
	PT_Mac UMETA(DisplayName = "Mac"),
	PT_Linux UMETA(DisplayName = "Linux"),
	PT_Unknown UMETA(DisplayName = "Unknown")
};

UENUM(BlueprintType)
enum class EGraphicsQuality : uint8
{
	Smooth UMETA(DisplayName = "Smooth"),
	Balance UMETA(DisplayName = "Balance"),
	HD UMETA(DisplayName = "HD")
};

UENUM(BlueprintType)
enum class EFrameRate : uint8
{
	FPS_30 UMETA(DisplayName = "30 FPS"),
	FPS_60 UMETA(DisplayName = "60 FPS"),
	FPS_90 UMETA(DisplayName = "90 FPS")
};
/**
 * 
 */
UCLASS()
class KURUKSHETRA_MAIN_API UKurukshetra_FL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Platform Check")
	static EPlatformType GetPlatformType();

	UFUNCTION(BlueprintCallable, Category = "Platform Check")
	static bool IsAndroid();
	
	// graphics Settings
	UFUNCTION(BlueprintCallable, Category = "Graphics Settings")
	void SetGraphicsQuality(EGraphicsQuality Quality);

	UFUNCTION(BlueprintCallable, Category = "Graphics Settings")
	void SetFrameRate(EFrameRate FrameRate);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	static void GetGridPosition(int32 Index, int32& Row, int32& Column);

	// Create a directory
	UFUNCTION(BlueprintCallable, Category = "File Operations", meta = (DisplayName = "Create Directory (Android)"))
	static bool CreateDirectoryOnAndroid(const FString& DirectoryPath, bool bInternalStorage = true);
	
	// Write a string to a file
	UFUNCTION(BlueprintCallable, Category = "File Operations", meta = (DisplayName = "Write File (Android)"))
	static bool WriteFileToAndroid(const FString& FileName, const FString& Content, bool bInternalStorage = true);

	// Read a string from a file
	UFUNCTION(BlueprintCallable, Category = "File Operations", meta = (DisplayName = "Read File (Android)"))
	static bool ReadFileFromAndroid(const FString& FileName, FString& OutContent, bool bInternalStorage = true);

	// Check if file exists
	UFUNCTION(BlueprintCallable, Category = "File Operations", meta = (DisplayName = "File Exists (Android)"))
	static bool FileExistsOnAndroid(const FString& FileName, bool bInternalStorage = true);

	// Get the Android storage path
	UFUNCTION(BlueprintCallable, Category = "File Operations", meta = (DisplayName = "Get Android Storage Path"))
	static FString GetAndroidStoragePath(bool bInternalStorage = true);

	
};
