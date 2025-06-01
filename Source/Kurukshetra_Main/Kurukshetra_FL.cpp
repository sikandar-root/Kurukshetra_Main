// Fill out your copyright notice in the Description page of Project Settings.


#include "Kurukshetra_FL.h"
#include "GameFramework/GameUserSettings.h"
#include "HAL/PlatformFileManager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"

#if PLATFORM_ANDROID
#include "Android/AndroidPlatform.h"
#include "Android/AndroidJavaEnv.h"
#include "Android/AndroidApplication.h"
#endif

EPlatformType UKurukshetra_FL::GetPlatformType()
{
#if WITH_EDITOR
	return EPlatformType::PT_Editor;
#elif PLATFORM_WINDOWS
	return EPlatformType::PT_Windows;
#elif PLATFORM_ANDROID
	return EPlatformType::PT_Android;
#elif PLATFORM_MAC
	return EPlatformType::PT_Mac;
#elif PLATFORM_LINUX
	return EPlatformType::PT_Linux;
#else
	return EPlatformType::PT_Unknown;
#endif
}

bool UKurukshetra_FL::IsAndroid()
{
#if PLATFORM_ANDROID
	return true;
#else
	return false;
#endif
}

void UKurukshetra_FL::SetGraphicsQuality(EGraphicsQuality Quality)
{
	UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();

	switch (Quality)
	{
	case EGraphicsQuality::Smooth:
		UserSettings->ScalabilityQuality.SetFromSingleQualityLevelRelativeToMax(0);
		break;
	case EGraphicsQuality::Balance:
		UserSettings->ScalabilityQuality.SetFromSingleQualityLevelRelativeToMax(2);
		break;
	case EGraphicsQuality::HD:
		UserSettings->ScalabilityQuality.SetFromSingleQualityLevelRelativeToMax(3);
		break;
	default:
		break;
	}

	UserSettings->ApplySettings(false);
}

void UKurukshetra_FL::SetFrameRate(EFrameRate FrameRate)
{
	UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();

	switch (FrameRate)
	{
	case EFrameRate::FPS_30:
		UserSettings->SetFrameRateLimit(30.0f);
		break;
	case EFrameRate::FPS_60:
		UserSettings->SetFrameRateLimit(60.0f);
		break;
	case EFrameRate::FPS_90:
		UserSettings->SetFrameRateLimit(90.0f);
		break;
	default:
		break;
	}

	UserSettings->ApplySettings(false);
}

void UKurukshetra_FL::GetGridPosition(int32 Index, int32& Row, int32& Column)
{
	const int32 MaxColumns = 1; // Maximum number of columns in the grid

	// Calculate the row and column based on the index
	Column = Index % MaxColumns; // Always 0 in this case since MaxColumns is 1
	Row = Index / MaxColumns;
}

bool UKurukshetra_FL::CreateDirectoryOnAndroid(const FString& DirectoryPath, bool bInternalStorage)
{
#if PLATFORM_ANDROID
	// Get the base storage path
	FString BasePath = GetAndroidStoragePath(bInternalStorage);
	if (BasePath.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get Android storage path"));
		return false;
	}

	// Combine with requested directory path
	FString FullPath = FPaths::Combine(BasePath, DirectoryPath);
    
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    
	// Check if directory already exists
	if (PlatformFile.DirectoryExists(*FullPath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Directory already exists: %s"), *FullPath);
		return true;
	}
    
	// Create directory and all parent directories if needed
	bool bSuccess = PlatformFile.CreateDirectoryTree(*FullPath);
    
	if (!bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create directory: %s"), *FullPath);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Created directory: %s"), *FullPath);
	}
    
	return bSuccess;
#else
	UE_LOG(LogTemp, Warning, TEXT("CreateDirectoryOnAndroid is only supported on Android platform"));
	return false;
#endif
}

bool UKurukshetra_FL::WriteFileToAndroid(const FString& FileName, const FString& Content, bool bInternalStorage)
{
#if PLATFORM_ANDROID
	FString FullPath = GetAndroidStoragePath(bInternalStorage);
	if (FullPath.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get Android storage path"));
		return false;
	}

	FullPath = FPaths::Combine(FullPath, FileName);
    
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    
	// Create directory if it doesn't exist
	FString Directory = FPaths::GetPath(FullPath);
	if (!PlatformFile.DirectoryExists(*Directory))
	{
		PlatformFile.CreateDirectoryTree(*Directory);
	}
    
	// Write the file
	return FFileHelper::SaveStringToFile(Content, *FullPath);
#else
	UE_LOG(LogTemp, Warning, TEXT("WriteFileToAndroid is only supported on Android platform"));
	return false;
#endif
}

bool UKurukshetra_FL::ReadFileFromAndroid(const FString& FileName, FString& OutContent, bool bInternalStorage)
{
#if PLATFORM_ANDROID
	FString FullPath = FPaths::Combine(GetAndroidStoragePath(bInternalStorage), FileName);
    
	if (!FFileHelper::LoadFileToString(OutContent, *FullPath))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to read file: %s"), *FullPath);
		return false;
	}
	return true;
#else
	UE_LOG(LogTemp, Warning, TEXT("ReadFileFromAndroid is only supported on Android platform"));
	return false;
#endif
}

bool UKurukshetra_FL::FileExistsOnAndroid(const FString& FileName, bool bInternalStorage)
{
#if PLATFORM_ANDROID
	FString FullPath = FPaths::Combine(GetAndroidStoragePath(bInternalStorage), FileName);
	return FPlatformFileManager::Get().GetPlatformFile().FileExists(*FullPath);
#else
	UE_LOG(LogTemp, Warning, TEXT("FileExistsOnAndroid is only supported on Android platform"));
	return false;
#endif
}

FString UKurukshetra_FL::GetAndroidStoragePath(bool bInternalStorage)
{
#if PLATFORM_ANDROID
	if (bInternalStorage)
	{
		// Internal storage path
		return FString(FPlatformMisc::GamePersistentDownloadDir());
	}
	else
	{
		// External storage path
		JNIEnv* Env = FAndroidApplication::GetJavaEnv();
		if (!Env)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to get JNIEnv"));
			return FString();
		}

		jclass Class = FAndroidApplication::FindJavaClass("android/os/Environment");
		if (!Class)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to find Environment class"));
			return FString();
		}

		jmethodID Method = Env->GetStaticMethodID(Class, "getExternalStorageDirectory", "()Ljava/io/File;");
		if (!Method)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to find getExternalStorageDirectory method"));
			return FString();
		}

		jobject FileObj = Env->CallStaticObjectMethod(Class, Method);
		if (!FileObj)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to call getExternalStorageDirectory"));
			return FString();
		}

		jclass FileClass = FAndroidApplication::FindJavaClass("java/io/File");
		jmethodID GetPathMethod = Env->GetMethodID(FileClass, "getAbsolutePath", "()Ljava/lang/String;");
		jstring PathObj = (jstring)Env->CallObjectMethod(FileObj, GetPathMethod);

		const char* PathChars = Env->GetStringUTFChars(PathObj, 0);
		FString Result = FString(UTF8_TO_TCHAR(PathChars));
		Env->ReleaseStringUTFChars(PathObj, PathChars);
		Env->DeleteLocalRef(FileObj);
		Env->DeleteLocalRef(PathObj);

		return Result;
	}
#else
	UE_LOG(LogTemp, Warning, TEXT("GetAndroidStoragePath is only supported on Android platform"));
	return FString();
#endif
}

