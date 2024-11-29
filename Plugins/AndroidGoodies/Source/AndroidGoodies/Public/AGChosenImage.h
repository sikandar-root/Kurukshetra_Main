// Copyright (c) 2020 Nineva Studios

#pragma once
#include "HAL/Platform.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJava.h"
#endif

#include "AGChosenFile.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGChosenImage.generated.h"

UCLASS(BlueprintType)
class UAGChosenImage : public UAGChosenFile
{
	GENERATED_BODY()

public:
	/**
	* Get orientation of the actual image.
	*/
	UFUNCTION(BlueprintPure, Category = "AndroidGoodies|ImagePicker")
	int GetOrientation();

	/**
	* Get the path to the thumbnail(big) of the image.
	*/
	UFUNCTION(BlueprintPure, Category = "AndroidGoodies|ImagePicker")
	FString GetThumbnailPath();

	/**
	* Get the path to the thumbnail(small) of the image.
	*/
	UFUNCTION(BlueprintPure, Category = "AndroidGoodies|ImagePicker")
	FString GetThumbnailSmallPath();

	/**
	* Get the image width.
	*/
	UFUNCTION(BlueprintPure, Category = "AndroidGoodies|ImagePicker")
	int GetWidth();

	/**
	* Get the image height.
	*/
	UFUNCTION(BlueprintPure, Category = "AndroidGoodies|ImagePicker")
	int GetHeight();

	/**
	* Get Orientation user friendly label.
	*/
	UFUNCTION(BlueprintPure, Category = "AndroidGoodies|ImagePicker")
	FString GetOrientationName();
};
