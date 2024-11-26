// Copyright (c) 2019 Nineva Studios

#include "AGPickersBPL.h"
#include "Async/Async.h"
#include "Runtime/Engine/Classes/Engine/GameViewportClient.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Public/UnrealClient.h"
#include "AGScreenShotHelper.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/Utils/AGMethodCallUtils.h"
#include "Android/Utils/AGArrayConvertor.h"
#include "Android/Utils/AGMediaUtils.h"
#include "Android/Utils/AGPickerUtils.h"
#endif

FOnImageReadyDelegate UAGPickersBPL::OnImageReadyDelegate;
FOnImageErrorDelegate UAGPickersBPL::OnImageErrorDelegate;
FOnImagesPickedDelegate UAGPickersBPL::OnImagesPickedDelegate;
FOnFilesPickedDelegate UAGPickersBPL::OnFilesPickedDelegate;
FOnFilesPickErrorDelegate UAGPickersBPL::OnFilesPickErrorDelegate;

#if PLATFORM_ANDROID
jbyteArray bufferRef = nullptr;
#endif

static const ANSICHAR* AGImagePickerClassName = "com/ninevastudios/androidgoodies/AGImagePicker";
static const ANSICHAR* AGFilePickerClassName = "com/ninevastudios/androidgoodies/AGFilePicker";

UAGPickersBPL::UAGPickersBPL(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UAGPickersBPL::PickImageFromGallery(int quality, ImageSize maxSize, bool shouldGenerateThumbnails, const FOnImageReadyDelegate& onImagePickedCallback, const FOnImageErrorDelegate& onImagePickErrorCallback)
{
	OnImageReadyDelegate = onImagePickedCallback;
	OnImageErrorDelegate = onImagePickErrorCallback;

#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGImagePickerClassName, "pickImage", "(Landroid/app/Activity;IIZZZ)V", FJavaWrapper::GameActivityThis, quality, (int)maxSize, shouldGenerateThumbnails, true, false);

#endif
}

void UAGPickersBPL::PickPhotoFromCamera(bool shouldGenerateThumbnails, const FOnImageReadyDelegate& onPhotoPickedCallback, const FOnImageErrorDelegate& onPhotoPickErrorCallback, ImageSize maxSize)
{
	OnImageReadyDelegate = onPhotoPickedCallback;
	OnImageErrorDelegate = onPhotoPickErrorCallback;

#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGImagePickerClassName, "takePhoto", "(Landroid/app/Activity;IZZ)V", FJavaWrapper::GameActivityThis, (int)maxSize, shouldGenerateThumbnails, true);

#endif
}

void UAGPickersBPL::SaveImageToGallery(UTexture2D* image, FString fileName)
{
#if PLATFORM_ANDROID

	int width = image->GetSizeX();
	int height = image->GetSizeY();

	TArray<uint8> byteArray = AGMediaUtils::ByteArrayFromTexture(image);
	jbyteArray jArray = AGArrayConvertor::ConvertToJByteArray(byteArray);

	AGMethodCallUtils::CallStaticVoidMethod(AGImagePickerClassName, "saveImageToGallery", "(Landroid/app/Activity;[BLjava/lang/String;II)V", FJavaWrapper::GameActivityThis, jArray, *FJavaClassObject::GetJString(fileName), width, height);

#endif
}

void UAGPickersBPL::TakeScreenShot(const FOnImageReadyDelegate& onScreenShotTakenCallback, const FOnImageErrorDelegate& onErrorCallback, bool showUI)
{
	OnImageReadyDelegate = onScreenShotTakenCallback;
	OnImageErrorDelegate = onErrorCallback;

#if PLATFORM_ANDROID

	if (!GEngine)
	{
		UAGPickersBPL::OnImageError("Default Engine was not found");
		return;
	}

	UGameViewportClient* GameViewport = GEngine->GameViewport;

	if (!GameViewport)
	{
		UAGPickersBPL::OnImageError("Default Game Viewport Client was not found");
		return;
	}

	UScreenShotHelper* Helper = NewObject<UScreenShotHelper>();

	GameViewport->OnScreenshotCaptured().AddUObject(Helper, &UScreenShotHelper::ProcessScreenShot);

	FScreenshotRequest::RequestScreenshot(showUI);

#endif
}

void UAGPickersBPL::PickFilesFromLocalStorage(bool allowMultiple, const FOnFilesPickedDelegate& OnFilesPickedCallback, const FOnFilesPickErrorDelegate& OnFilesPickErrorCallback)
{
	OnFilesPickedDelegate = OnFilesPickedCallback;
	OnFilesPickErrorDelegate = OnFilesPickErrorCallback;

#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(AGFilePickerClassName, "pickFile", "(Landroid/app/Activity;Z)V", FJavaWrapper::GameActivityThis, allowMultiple);
#endif
}

void UAGPickersBPL::GetChosenImagesData(int quality, ImageSize maxSize, bool shouldGenerateThumbnails, bool allowMultiple, const FOnImagesPickedDelegate& OnImagesPickedCallback, const FOnImageErrorDelegate& OnImagesPickErrorCallback)
{
	OnImagesPickedDelegate = OnImagesPickedCallback;
	OnImageErrorDelegate = OnImagesPickErrorCallback;

#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(AGImagePickerClassName, "pickImage", "(Landroid/app/Activity;IIZZZ)V", FJavaWrapper::GameActivityThis, quality, (int)maxSize, shouldGenerateThumbnails, false, allowMultiple);
#endif
}

void UAGPickersBPL::GetPhotoDataFromCamera(bool shouldGenerateThumbnails, const FOnImagesPickedDelegate& OnImagesPickedCallback, const FOnImageErrorDelegate& OnImagesPickErrorCallback, ImageSize maxSize)
{
	OnImagesPickedDelegate = OnImagesPickedCallback;
	OnImageErrorDelegate = OnImagesPickErrorCallback;

#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(AGImagePickerClassName, "takePhoto", "(Landroid/app/Activity;IZZ)V", FJavaWrapper::GameActivityThis, (int)maxSize,shouldGenerateThumbnails, false);
#endif
}



void UAGPickersBPL::GetTextureFromPath(FString imagePath, const FOnImageReadyDelegate& onTextureReadyCallback, const FOnImageErrorDelegate& onTextureErrorCallback)
{
	OnImageReadyDelegate = onTextureReadyCallback;
	OnImageErrorDelegate = onTextureErrorCallback;

#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGImagePickerClassName, "getTextureFromPath", "(Ljava/lang/String;)V", *FJavaClassObject::GetJString(imagePath));

#endif
}

void UAGPickersBPL::ClearTexture(UTexture2D* texture)
{
	if (texture != nullptr)
	{
		texture->ConditionalBeginDestroy();
	}
	texture = nullptr;
}

void UAGPickersBPL::OnImageReady(UTexture2D* texture)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnImageReadyDelegate.ExecuteIfBound(texture);
	});

#if PLATFORM_ANDROID
	if (bufferRef != nullptr)
	{
		JNIEnv* Env = FAndroidApplication::GetJavaEnv();
		Env->DeleteGlobalRef(bufferRef);
		bufferRef = nullptr;
	}
#endif
}

void UAGPickersBPL::OnImageError(FString error)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnImageErrorDelegate.ExecuteIfBound(error);
	});
}

void UAGPickersBPL::OnImagesPicked(const TArray<UAGChosenImage*>& images)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnImagesPickedDelegate.ExecuteIfBound(images);
	});
}

void UAGPickersBPL::OnFilesPicked(const TArray<UAGChosenFile*>& files)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnFilesPickedDelegate.ExecuteIfBound(files);
	});
}

void UAGPickersBPL::OnFilesPickError(FString error)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnFilesPickErrorDelegate.ExecuteIfBound(error);
	});
}

#if PLATFORM_ANDROID

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGImagePicker_onImageReady(JNIEnv* env, jclass clazz, jbyteArray buffer, int width, int height)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => onImageReady callback caught in C++!"));
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Image width: %d, height: %d"), width, height);

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	bufferRef = static_cast<jbyteArray>(Env->NewGlobalRef(buffer));

	Env->DeleteLocalRef(buffer);
	AsyncTask(ENamedThreads::GameThread, [=]() {
		TArray<uint8> byteArray = AGArrayConvertor::ConvertToByteArray(bufferRef);
		UTexture2D* result = AGMediaUtils::TextureFromByteArray(byteArray, width, height);		

		UAGPickersBPL::OnImageReady(result);
		
		byteArray.Empty();
	});
}

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGImagePicker_onImageError(JNIEnv* env, jclass clazz, jstring error)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => onImageError callback caught in C++!"));

	const char * UTFString = env->GetStringUTFChars(error, nullptr);
	FString result = UTF8_TO_TCHAR(UTFString);
	env->ReleaseStringUTFChars(error, UTFString);

	UAGPickersBPL::OnImageError(result);
}

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGImagePicker_onImagesPicked(JNIEnv* env, jclass clazz, jobjectArray images)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => onImagesPicked callback caught in C++!"));

	TArray<UAGChosenImage*> result = AGPickerUtils::ChosenImagesFromJavaArray(images);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UAGPickersBPL::OnImagesPicked(result);
	});
}

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGFilePicker_onFilesPickError(JNIEnv* env, jclass clazz, jstring error)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => onFilesPickError callback caught in C++!"));

	const char * UTFString = env->GetStringUTFChars(error, nullptr);
	FString result = UTF8_TO_TCHAR(UTFString);
	env->ReleaseStringUTFChars(error, UTFString);

	UAGPickersBPL::OnFilesPickError(result);
}

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGFilePicker_onFilesPicked(JNIEnv* env, jclass clazz, jobjectArray files)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => onFilesPicked callback caught in C++!"));

	TArray<UAGChosenFile*> result = AGPickerUtils::ChosenFilesFromJavaArray(files);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UAGPickersBPL::OnFilesPicked(result);
	});
}

#endif
