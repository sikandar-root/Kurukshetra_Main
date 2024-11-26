// Copyright (c) 2020 Nineva Studios

#include "VideoRecording/GPCaptureState.h"

#if PLATFORM_ANDROID
#include "Android/Utils/GPMethodCallUtils.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"
#endif

#include "Utils/GPUtils.h"


UGPCaptureState::~UGPCaptureState()
{
#if PLATFORM_ANDROID
	if (CaptureStateObject)
	{
		JNIEnv* Env = FAndroidApplication::GetJavaEnv();
		Env->DeleteGlobalRef(CaptureStateObject);
	}
#endif
}

#if PLATFORM_ANDROID
void UGPCaptureState::Init(jobject CaptureState)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	CaptureStateObject = Env->NewGlobalRef(CaptureState);

	jclass CaptureStateClass = FAndroidApplication::FindJavaClass("com/ninevastudios/googleplay/GPCaptureState");

	GetCaptureModeMethod = FJavaWrapper::FindMethod(Env, CaptureStateClass, "getCaptureMode", "()I", false);
	GetCaptureQualityMethod = FJavaWrapper::FindMethod(Env, CaptureStateClass, "getCaptureQuality", "()I", false);
	IsCapturingMethod = FJavaWrapper::FindMethod(Env, CaptureStateClass, "isCapturing", "()Z", false);
	IsOverlayVisibleMethod = FJavaWrapper::FindMethod(Env, CaptureStateClass, "isOverlayVisible", "()Z", false);
	IsPausedMethod = FJavaWrapper::FindMethod(Env, CaptureStateClass, "isPaused", "()Z", false);
}

jobject UGPCaptureState::GetCaptureStateObject()
{
	return CaptureStateObject;
}
#endif

ECaptureMode UGPCaptureState::GetCaptureMode()
{
	int CaptureMode = 0;
#if PLATFORM_ANDROID
	CaptureMode = GPMethodCallUtils::CallIntMethod(CaptureStateObject, "getCaptureMode", "()I");
#endif
	switch (CaptureMode)
	{
		case 0:
			return ECaptureMode::File;
		case 1:
			return ECaptureMode::Stream;
		default:
			return ECaptureMode::Unknown;
	}
}

EQualityLevel UGPCaptureState::GetCaptureQuality()
{
	int CaptureQuality = 0;
#if PLATFORM_ANDROID
	CaptureQuality = GPMethodCallUtils::CallIntMethod(CaptureStateObject, "getCaptureMode", "()I");
#endif
	switch (CaptureQuality)
	{
		case -1:
			return EQualityLevel::Unknown;
		case 0:
			return EQualityLevel::SD;
		case 1:
			return EQualityLevel::HD;
		case 2:
			return EQualityLevel::XHD;
		case 3:
			return EQualityLevel::FullHD;
		default:
			return EQualityLevel::Unknown;
	}
}

bool UGPCaptureState::IsCapturing()
{
	bool Result = false;
#if PLATFORM_ANDROID
	Result = GPMethodCallUtils::CallBoolMethod(CaptureStateObject, "isCapturing", "()Z");
#endif
	return Result;
}

bool UGPCaptureState::IsOverlayVisible()
{
	bool Result = false;
#if PLATFORM_ANDROID
	Result = GPMethodCallUtils::CallBoolMethod(CaptureStateObject, "isOverlayVisible", "()Z");
#endif
	return Result;
}

bool UGPCaptureState::IsPaused()
{
	bool Result = false;
#if PLATFORM_ANDROID
	Result = GPMethodCallUtils::CallBoolMethod(CaptureStateObject, "isPaused", "()Z");
#endif
	return Result;
}
