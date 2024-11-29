// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGImageSize.h"
#include "AGChosenImage.h"
#include "AGChosenFile.h"
#include "Engine/Texture2D.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "AGPickersBPL.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnImageReadyDelegate, UTexture2D*, texture);

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnImageErrorDelegate, FString, error);

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnImagesPickedDelegate, const TArray<UAGChosenImage*>&, images);

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnFilesPickedDelegate, const TArray<UAGChosenFile*>&, files);

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnFilesPickErrorDelegate, FString, error);

UCLASS()
class ANDROIDGOODIES_API UAGPickersBPL : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
	/**
	* Pick image from gallery.
	* @param quality - quality of image to be picked (0 for minimum, 100 for maximum quality)
	* @param maxSize - size of the resulting image (pick smaller value to save memory)
	* @param shouldGenerateThumbnails - flag that indicates whether to generate thumbnails
	* @param onImagePickedCallback - callback function that is called when image picking completed successfully
	* @param onImagePickErrorCallback - callback function that is called when image picking from gallery resulted with an error
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void PickImageFromGallery(int quality, ImageSize maxSize, bool shouldGenerateThumbnails,
	                                 const FOnImageReadyDelegate& onImagePickedCallback, const FOnImageErrorDelegate& onImagePickErrorCallback);

	/**
	* Pick photo from camera.
	* @param shouldGenerateThumbnails - flag that indicates whether to generate thumbnails
	* @param onPhotoPickedCallback - callback function that is called when capturing image with camera completed successfully
	* @param onPhotoPickErrorCallback - callback function that is called when capturing image with camera resulted with an error
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void PickPhotoFromCamera(bool shouldGenerateThumbnails, const FOnImageReadyDelegate& onPhotoPickedCallback, const FOnImageErrorDelegate& onPhotoPickErrorCallback, ImageSize maxSize = ImageSize::Original);

	/**
	* Save image to gallery.
	* @param image - image to be saved
	* @param fileName - name of the created file
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void SaveImageToGallery(UTexture2D* image, FString fileName);

	/**
	* Take a screen shot of the game screen.
	* @param onScreenShotTakenCallback - callback function that is called when screen shot taking is completed successfully
	* @param onErrorCallback - callback function that is called when screen shot taking resulted with an error
	* @param showUI - whether to capture UI elements to a screen shot
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void TakeScreenShot(const FOnImageReadyDelegate& onScreenShotTakenCallback, const FOnImageErrorDelegate& onErrorCallback, bool showUI);

	/**
	* Pick files from local storage.
	* @param allowMultiple - flag that indicated wether to allow multiple file picking
	* @param OnFilesPickedCallback - callback function that is called when files were picked successfuly. Callback returns array of ChosenFile objects
	* @param OnFilesPickErrorCallback - callback function that is called when file picking from local storage resulted with an error
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void PickFilesFromLocalStorage(bool allowMultiple, const FOnFilesPickedDelegate& OnFilesPickedCallback, const FOnFilesPickErrorDelegate& OnFilesPickErrorCallback);

	/**
	* Get chosen images data.
	* @param quality - quality of image to be picked (0 for minimum, 100 for maximum quality)
	* @param maxSize - size of the resulting image (pick smaller value to save memory)
	* @param shouldGenerateThumbnails - flag that indicates whether to generate thumbnails
	* @param allowMultiple - flag that indicated wether to allow multiple file picking
	* @param OnImagesPickedCallback - callback function that is called when images were picked successfuly. Callback returns array of ChosenImage objects
	* @param OnImagesPickErrorCallback - callback function that is called when image picking from galery resulted with an error
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void GetChosenImagesData(int quality, ImageSize maxSize, bool shouldGenerateThumbnails, bool allowMultiple, const FOnImagesPickedDelegate& OnImagesPickedCallback, const FOnImageErrorDelegate& OnImagesPickErrorCallback);

	/**
	* Get photo data from camera.
	* @param shouldGenerateThumbnails - flag that indicates whether to generate thumbnails
	* @param OnPhotoTakenCallback - callback function that is called when photo was taken successfully. Callback returns a ChosenImage object
	* @param OnPhotoTakeErrorCallback - callback function that is called when taking photo resulted with an error
	* @param maxSize - size of the resulting image (pick smaller value to save memory)
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void GetPhotoDataFromCamera(bool shouldGenerateThumbnails, const FOnImagesPickedDelegate& OnPhotoTakenCallback, const FOnImageErrorDelegate& OnPhotoTakeErrorCallback, ImageSize maxSize = ImageSize::Original);

	/**
	* Get texture from path.
	* @param imagePath - path of existing image to retrieve a texture from
	* @param onTextureReadyCallback - callback function that is called when texture retrieval completed successfully
	* @param onTextureErrorCallback - callback function that is called when texture retrieval resulted with an error
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void GetTextureFromPath(FString imagePath, const FOnImageReadyDelegate& onTextureReadyCallback, const FOnImageErrorDelegate& onTextureErrorCallback);

	/**
	* Utility method for clearing memory dedicated to UTexture2D object.
	* Use this method in case UTexture2D object is no longer needed, as Unreal doesn't seem to automatically GC objects of this type for some reason.
	* @param texture - object of type UTexture2D to be cleared from memory.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void ClearTexture(UTexture2D* texture);

	// Callbacks interface methods to be called from Android
	static void OnImageReady(UTexture2D* texture);
	static void OnImageError(FString error);
	static void OnImagesPicked(const TArray<UAGChosenImage*>& images);
	static void OnFilesPicked(const TArray<UAGChosenFile*>& files);
	static void OnFilesPickError(FString error);

private:
	static FOnImageReadyDelegate OnImageReadyDelegate;
	static FOnImageErrorDelegate OnImageErrorDelegate;
	static FOnImagesPickedDelegate OnImagesPickedDelegate;
	static FOnFilesPickedDelegate OnFilesPickedDelegate;
	static FOnFilesPickErrorDelegate OnFilesPickErrorDelegate;
};
