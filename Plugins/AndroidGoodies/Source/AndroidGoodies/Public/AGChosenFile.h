// Copyright (c) 2020 Nineva Studios

#pragma once
#include "HAL/Platform.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJava.h"
#endif

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGChosenFile.generated.h"

UCLASS(BlueprintType)
class UAGChosenFile : public UObject
{
	GENERATED_BODY()

public:
	virtual ~UAGChosenFile();

	/**
	* If this file has been successfully processed.
	*/
	UFUNCTION(BlueprintPure, Category = "AndroidGoodies|FilePicker")
	bool IsSuccess();

	/**
	* Display name of the file.
	*/
	UFUNCTION(BlueprintPure, Category = "AndroidGoodies|FilePicker")
	FString GetDisplayName();

	/**
	* Path to the processed file. This will always be a local path on the device.
	*/
	UFUNCTION(BlueprintPure, Category = "AndroidGoodies|FilePicker")
	FString GetOriginalPath();

	/**
	* Get mime type of the processed file.
	*/
	UFUNCTION(BlueprintPure, Category = "AndroidGoodies|FilePicker")
	FString GetMimeType();

	/**
	* Get the size of the processed file in bytes.
	*/
	UFUNCTION(BlueprintPure, Category = "AndroidGoodies|FilePicker")
	int64 GetSize();

	/**
	* Get creation date and time of the processed file.
	*/
	UFUNCTION(BlueprintPure, Category = "AndroidGoodies|FilePicker")
	FDateTime GetCreatedAt();

	/**
	* Get the extension of the processed file. (Ex. .pdf, .jpeg, .mp4) 
	*/
	UFUNCTION(BlueprintPure, Category = "AndroidGoodies|FilePicker")
	FString GetFileExtensionFromMimeType();

	/**
	* Get only the file extension (Ex. jpg, mp4, pdf etc)
	*/
	UFUNCTION(BlueprintPure, Category = "AndroidGoodies|FilePicker")
	FString GetFileExtensionFromMimeTypeWithoutDot();

	/**
	* Get File size in a pretty format.
	* @param bytesRounded - flag that indicates whether to use 1024 Bytes as a size of Kilobyte or round to 1000.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|FilePicker")
	FString GetHumanReadableSize(bool bytesRounded);

#if PLATFORM_ANDROID
	void Init(jobject javaChosenFile);
	jobject JavaChosenFileObject;
#endif
};
