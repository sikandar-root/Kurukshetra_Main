// Copyright (c) 2020 Nineva Studios

#include "VideoRecording/GPVideoRecordingLibrary.h"

#include "Async/Async.h"
#include "Auth/GPPlayer.h"
#include "GooglePlayGoodies.h"
#include "GooglePlayGoodiesSettings.h"
#include "GooglePlayLog.h"

#include "VideoRecording/GPVideoCapabilities.h"
#include "VideoRecording/GPCaptureState.h"

#if PLATFORM_ANDROID
#include "Android/Utils/GPMethodCallUtils.h"
#endif


UGPVideoRecordingLibrary::FGPOnErrorDelegate UGPVideoRecordingLibrary::OnVideoRecordingErrorDelegate;

// Get Capture Capabilities  
UGPVideoRecordingLibrary::FGPOnGetCaptureCapabilitiesSuccessDelegate UGPVideoRecordingLibrary::OnGetCaptureCapabilitiesSuccessDelegate;
UGPVideoRecordingLibrary::FGPOnErrorDelegate UGPVideoRecordingLibrary::OnGetCaptureCapabilitiesErrorDelegate;

// Is Capture Supported
UGPVideoRecordingLibrary::FGPOnIsCaptureSupportedSuccessDelegate UGPVideoRecordingLibrary::OnIsCaptureSupportedSuccessDelegate;
UGPVideoRecordingLibrary::FGPOnErrorDelegate UGPVideoRecordingLibrary::OnIsCaptureSupportedErrorDelegate;

// Get Capture State
UGPVideoRecordingLibrary::FGPOnGetCaptureStateSuccessDelegate UGPVideoRecordingLibrary::OnGetCaptureStateSuccessDelegate;
UGPVideoRecordingLibrary::FGPOnErrorDelegate UGPVideoRecordingLibrary::OnGetCaptureStateErrorDelegate;

//Register On Capture Overlay State Changed
UGPVideoRecordingLibrary::FGPOnCaptureOverlayStateChangedDelegate UGPVideoRecordingLibrary::OnCaptureOverlayStateChangedDelegate;
UGPVideoRecordingLibrary::FGPOnErrorDelegate UGPVideoRecordingLibrary::OnRegisterCaptureOverlayStateFailureListenerDelegate;

//Unregister On Capture Overlay State Changed
UGPVideoRecordingLibrary::FGPOnErrorDelegate UGPVideoRecordingLibrary::OnUnregisterCaptureOverlayStateFailureListenerDelegate;

void UGPVideoRecordingLibrary::ShowVideoRecordingOverlay(const FGPOnErrorDelegate& OnVideoRecordingError)
{
	UGPVideoRecordingLibrary::OnVideoRecordingErrorDelegate = OnVideoRecordingError;
#if PLATFORM_ANDROID
	GPMethodCallUtils::CallStaticVoidMethod("com/ninevastudios/googleplay/GPVideoRecordingLibrary", "showVideoRecordingOverlay", "(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis);
#endif
}

void UGPVideoRecordingLibrary::IsCaptureSupported(
	const FGPOnIsCaptureSupportedSuccessDelegate& OnIsCaptureSupportedSuccess,
	const FGPOnErrorDelegate& OnIsCaptureSupportedError)
{
	UGPVideoRecordingLibrary::OnIsCaptureSupportedSuccessDelegate = OnIsCaptureSupportedSuccess;
	UGPVideoRecordingLibrary::OnIsCaptureSupportedErrorDelegate = OnIsCaptureSupportedError;
	#if PLATFORM_ANDROID
	GPMethodCallUtils::CallStaticVoidMethod("com/ninevastudios/googleplay/GPVideoRecordingLibrary", "isCaptureSupported", "(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis);
#endif
}

void UGPVideoRecordingLibrary::GetCaptureCapabilities(
	const FGPOnGetCaptureCapabilitiesSuccessDelegate& OnGetCaptureCapabilitiesSuccess,
	const FGPOnErrorDelegate& OnGetCaptureCapabilitiesError)
{
	UGPVideoRecordingLibrary::OnGetCaptureCapabilitiesSuccessDelegate = OnGetCaptureCapabilitiesSuccess;
	UGPVideoRecordingLibrary::OnGetCaptureCapabilitiesErrorDelegate = OnGetCaptureCapabilitiesError;
#if PLATFORM_ANDROID
	GPMethodCallUtils::CallStaticVoidMethod("com/ninevastudios/googleplay/GPVideoRecordingLibrary", "getCaptureCapabilities", "(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis);
#endif
}

void UGPVideoRecordingLibrary::GetCaptureState(
	const FGPOnGetCaptureStateSuccessDelegate& OnGetCaptureStateSuccess,
	const FGPOnErrorDelegate& OnGetCaptureStateError)
{
	UGPVideoRecordingLibrary::OnGetCaptureStateSuccessDelegate = OnGetCaptureStateSuccess;
	UGPVideoRecordingLibrary::OnGetCaptureStateErrorDelegate = OnGetCaptureStateError;
#if PLATFORM_ANDROID
	GPMethodCallUtils::CallStaticVoidMethod("com/ninevastudios/googleplay/GPVideoRecordingLibrary", "getCaptureState", "(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis);
#endif
}

void UGPVideoRecordingLibrary::RegisterOnCaptureOverlayStateChanged(
	const FGPOnCaptureOverlayStateChangedDelegate& OnCaptureOverlayStateChanged,
	const FGPOnErrorDelegate& OnRegisterCaptureOverlayStateFailureListener)
{
	UGPVideoRecordingLibrary::OnCaptureOverlayStateChangedDelegate = OnCaptureOverlayStateChanged;
	UGPVideoRecordingLibrary::OnRegisterCaptureOverlayStateFailureListenerDelegate = OnRegisterCaptureOverlayStateFailureListener;

#if PLATFORM_ANDROID
	GPMethodCallUtils::CallStaticVoidMethod("com/ninevastudios/googleplay/GPVideoRecordingLibrary", "registerOnCaptureOverlayStateChangedListener", "(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis);
#endif
}

void UGPVideoRecordingLibrary::UnregisterOnCaptureOverlayStateChanged(const FGPOnErrorDelegate& OnUnregisterCaptureOverlayStateFailureListener)
{
	UGPVideoRecordingLibrary::OnUnregisterCaptureOverlayStateFailureListenerDelegate = OnUnregisterCaptureOverlayStateFailureListener;
#if PLATFORM_ANDROID
	GPMethodCallUtils::CallStaticVoidMethod("com/ninevastudios/googleplay/GPVideoRecordingLibrary", "unregisterOnCaptureOverlayStateChangedListener", "(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis);
#endif
}

#if PLATFORM_ANDROID

JNI_METHOD void Java_com_ninevastudios_googleplay_GPVideoRecordingLibrary_onVideoRecordingFailureCallback(JNIEnv* env, jclass clazz, jstring errorMessage)
{
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, errorMessage);
	UE_LOG(LogGooglePlayGoodies, Error, TEXT("%s"), *ErrorMessage);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UGPVideoRecordingLibrary::OnVideoRecordingErrorDelegate.ExecuteIfBound(ErrorMessage);
	});

}

// Get Capture Capabilities
JNI_METHOD void Java_com_ninevastudios_googleplay_GPVideoRecordingLibrary_onGetCaptureCapabilitiesSuccessCallback(JNIEnv* env, jclass clazz, jobject videoCapabilitiesObject)
{
	UGPVideoCapabilities* VideoCapabilities = NewObject<UGPVideoCapabilities>();
	VideoCapabilities->Init(videoCapabilitiesObject);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UGPVideoRecordingLibrary::OnGetCaptureCapabilitiesSuccessDelegate.ExecuteIfBound(VideoCapabilities);
	});
}

JNI_METHOD void Java_com_ninevastudios_googleplay_GPVideoRecordingLibrary_onGetCaptureCapabilitiesFailureCallback(JNIEnv* env, jclass clazz, jstring errorMessage)
{
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, errorMessage);
	UE_LOG(LogGooglePlayGoodies, Error, TEXT("%s"), *ErrorMessage);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UGPVideoRecordingLibrary::OnGetCaptureCapabilitiesErrorDelegate.ExecuteIfBound(ErrorMessage);
	});
}

//Is Capture Supported
JNI_METHOD void Java_com_ninevastudios_googleplay_GPVideoRecordingLibrary_onIsCaptureSupportedSuccessCallback(JNIEnv* env, jclass clazz, bool bCaptureSupported)
{
	bool IsCaptureSupported = bCaptureSupported;
		AsyncTask(ENamedThreads::GameThread, [=]() {
		UGPVideoRecordingLibrary::OnIsCaptureSupportedSuccessDelegate.ExecuteIfBound(IsCaptureSupported);
	});
}

JNI_METHOD void Java_com_ninevastudios_googleplay_GPVideoRecordingLibrary_onIsCaptureSupportedFailureCallback(JNIEnv* env, jclass clazz, jstring errorMessage)
{
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, errorMessage);
	UE_LOG(LogGooglePlayGoodies, Error, TEXT("%s"), *ErrorMessage);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UGPVideoRecordingLibrary::OnIsCaptureSupportedErrorDelegate.ExecuteIfBound(ErrorMessage);
	});
}

// Get Capture State
JNI_METHOD void Java_com_ninevastudios_googleplay_GPVideoRecordingLibrary_onGetCaptureStateSuccessCallback(JNIEnv* env, jclass clazz, jobject captureStateObject)
{
	UGPCaptureState* CaptureState = NewObject<UGPCaptureState>();
	CaptureState->Init(captureStateObject);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UGPVideoRecordingLibrary::OnGetCaptureStateSuccessDelegate.ExecuteIfBound(CaptureState);
	});
}

JNI_METHOD void Java_com_ninevastudios_googleplay_GPVideoRecordingLibrary_onGetCaptureStateFailureCallback(JNIEnv* env, jclass clazz, jstring errorMessage)
{
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, errorMessage);
	UE_LOG(LogGooglePlayGoodies, Error, TEXT("%s"), *ErrorMessage);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UGPVideoRecordingLibrary::OnGetCaptureStateErrorDelegate.ExecuteIfBound(ErrorMessage);
	});
}

//Register On Capture Overlay State Changed
JNI_METHOD void Java_com_ninevastudios_googleplay_GPVideoRecordingLibrary_onRegisterCaptureOverlayStateChangedListenerCallback(JNIEnv* env, jclass clazz, int captureOverlayState)
{
	ECaptureOverlayState CurrentOverlayState;
	switch (captureOverlayState)
	{
		case 1:
			CurrentOverlayState = ECaptureOverlayState::Shown;
			break;
		case 2:
			CurrentOverlayState = ECaptureOverlayState::CaptureStarted;
			break;
		case 3:
			CurrentOverlayState = ECaptureOverlayState::CaptureStopped;
			break;
		case 4:
			CurrentOverlayState = ECaptureOverlayState::Dismissed;
			break;
		default:
			CurrentOverlayState = ECaptureOverlayState::Unknown;
			break;
	}
	AsyncTask(ENamedThreads::GameThread, [=]() {
		UGPVideoRecordingLibrary::OnCaptureOverlayStateChangedDelegate.ExecuteIfBound(CurrentOverlayState);
	});
}

JNI_METHOD void Java_com_ninevastudios_googleplay_GPVideoRecordingLibrary_onRegisterCaptureOverlayStateFailureListenerCallback(JNIEnv* env, jclass clazz, jstring errorMessage)
{
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, errorMessage);
	UE_LOG(LogGooglePlayGoodies, Error, TEXT("%s"), *ErrorMessage);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UGPVideoRecordingLibrary::OnRegisterCaptureOverlayStateFailureListenerDelegate.ExecuteIfBound(ErrorMessage);
	});
}

//Unregister On Capture Overlay State Changed
JNI_METHOD void Java_com_ninevastudios_googleplay_GPVideoRecordingLibrary_onUnregisterCaptureOverlayStateFailureListenerCallback(JNIEnv* env, jclass clazz, jstring errorMessage)
{
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, errorMessage);
	UE_LOG(LogGooglePlayGoodies, Error, TEXT("%s"), *ErrorMessage);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UGPVideoRecordingLibrary::OnUnregisterCaptureOverlayStateFailureListenerDelegate.ExecuteIfBound(ErrorMessage);
		});
}
#endif