// Copyright (c) 2020 Nineva Studios

#include "VideoRecording/GPVideoCapabilities.h"


#if PLATFORM_ANDROID
#include "Android/Utils/GPMethodCallUtils.h"
#include "Android/Utils/GPJavaConvertor.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"
#endif
#include "Misc/EnumRange.h"
#include "Utils/GPUtils.h"


UGPVideoCapabilities::~UGPVideoCapabilities()
{
#if PLATFORM_ANDROID
	if (VideoCapabilitiesObject)
	{
		JNIEnv* Env = FAndroidApplication::GetJavaEnv();
		Env->DeleteGlobalRef(VideoCapabilitiesObject);
	}
#endif
}

#if PLATFORM_ANDROID
void UGPVideoCapabilities::Init(jobject VideoCapabilities)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	VideoCapabilitiesObject = Env->NewGlobalRef(VideoCapabilities);
}

jobject UGPVideoCapabilities::GetVideoCapabilitiesObject()
{
	return VideoCapabilitiesObject;
}
#endif

TArray<ECaptureMode> UGPVideoCapabilities::GetSupportedCaptureModes()
{
	TArray<bool> SupportedCaptureModesBArray;
	TArray<ECaptureMode> SupportedCaptureModeEArray;
#if PLATFORM_ANDROID
	jbooleanArray supportedCaptureModesArray = static_cast<jbooleanArray>(GPMethodCallUtils::CallObjectMethod(VideoCapabilitiesObject, "getSupportedCaptureModes", "()[Z"));
	SupportedCaptureModesBArray = GPJavaConvertor::ToBoolArray(supportedCaptureModesArray);
#endif
	int i = 0;
	for (ECaptureMode Val : TEnumRange<ECaptureMode>())
	{
		if (Val == ECaptureMode::Unknown)
		{
			continue;
		}
		if (SupportedCaptureModesBArray[i])
		{
			SupportedCaptureModeEArray.Add(Val);
		}
		i++;
	}
	return SupportedCaptureModeEArray;
}

TArray<EQualityLevel> UGPVideoCapabilities::GetSupportedQualityLevels()
{
	TArray<bool> SupportedQualityLevelsBArray;
	TArray<EQualityLevel> SupportedQualityLevelsEArray;
#if PLATFORM_ANDROID
	jbooleanArray supportedQualityLevelsArray = static_cast<jbooleanArray>(GPMethodCallUtils::CallObjectMethod(VideoCapabilitiesObject, "getSupportedQualityLevels", "()[Z"));
	SupportedQualityLevelsBArray = GPJavaConvertor::ToBoolArray(supportedQualityLevelsArray);
#endif
	int i = 0;
	for (EQualityLevel Val : TEnumRange<EQualityLevel>())
	{
		if (Val == EQualityLevel::Unknown)
		{
			continue;
		}
		if (SupportedQualityLevelsBArray[i])
		{
			SupportedQualityLevelsEArray.Add(Val);
		}
		i++;
	}
	return SupportedQualityLevelsEArray;
}

bool UGPVideoCapabilities::IsCameraSupported()
{
	bool Result = false;
#if PLATFORM_ANDROID
	Result = GPMethodCallUtils::CallBoolMethod(VideoCapabilitiesObject, "isCameraSupported", "()Z");
#endif
	return Result;
}

int UGPVideoCapabilities::GetCaptureMode(ECaptureMode CaptureMode)
{
	switch (CaptureMode)
	{
		case ECaptureMode::File:
			return 0;
		case ECaptureMode::Stream:
			return 1;
		default:
			return -1;
	}
}

int UGPVideoCapabilities::GetQualityLevel(EQualityLevel QualityLevel)
{
	switch (QualityLevel)
	{
		case EQualityLevel::SD:
			return 0;
		case EQualityLevel::HD:
			return 1;
		case EQualityLevel::XHD:
			return 2;
		case EQualityLevel::FullHD:
			return 3;
		default:
			return -1;
	}
}

bool UGPVideoCapabilities::IsFullySupported(ECaptureMode CaptureMode, EQualityLevel QualityLevel)
{
	bool Result = false;
#if PLATFORM_ANDROID
	Result = GPMethodCallUtils::CallBoolMethod(VideoCapabilitiesObject, "isFullySupported", "(II)Z", GetCaptureMode(CaptureMode), GetQualityLevel(QualityLevel));
#endif
	return Result;
}

bool UGPVideoCapabilities::IsMicSupported()
{
	bool Result = false;
#if PLATFORM_ANDROID
	Result = GPMethodCallUtils::CallBoolMethod(VideoCapabilitiesObject, "isMicSupported", "()Z");
#endif
	return Result;
}


bool UGPVideoCapabilities::IsWriteStorageSupported()
{
	bool Result = false;
#if PLATFORM_ANDROID
	Result = GPMethodCallUtils::CallBoolMethod(VideoCapabilitiesObject, "isWriteStorageSupported", "()Z");
#endif
	return Result;
}

bool UGPVideoCapabilities::SupportsCaptureMode(ECaptureMode CaptureMode)
{
	bool Result = false;
#if PLATFORM_ANDROID
	Result = GPMethodCallUtils::CallBoolMethod(VideoCapabilitiesObject, "supportsCaptureMode", "(I)Z", GetCaptureMode(CaptureMode));
#endif
	return Result;
}

bool UGPVideoCapabilities::SupportsQualityLevel(EQualityLevel QualityLevel)
{
	bool Result = false;
#if PLATFORM_ANDROID
	Result = GPMethodCallUtils::CallBoolMethod(VideoCapabilitiesObject, "supportsQualityLevel", "(I)Z", GetQualityLevel(QualityLevel));
#endif
	return Result;
}