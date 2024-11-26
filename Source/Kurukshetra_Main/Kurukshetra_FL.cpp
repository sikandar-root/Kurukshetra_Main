// Fill out your copyright notice in the Description page of Project Settings.


#include "Kurukshetra_FL.h"
#include "GameFramework/GameUserSettings.h"


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


