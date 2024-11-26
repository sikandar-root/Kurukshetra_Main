// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kurukshetra_FL.generated.h"


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

	// WebRTC Connection


	
};
