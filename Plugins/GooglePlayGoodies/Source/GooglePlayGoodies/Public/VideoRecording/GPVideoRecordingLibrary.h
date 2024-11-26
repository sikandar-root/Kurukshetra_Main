// Copyright (c) 2020 Nineva Studios

#pragma once

#include "CoreMinimal.h"
#include "Misc/EnumRange.h"
#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#endif

#include "GPVideoRecordingLibrary.generated.h"

UENUM()
enum class ECaptureMode : uint8
{
	/** An unknown value to return when capture mode is not available.*/
	Unknown,
	/** Capture device audio and video to a local file.*/
	File,
	/** Capture device audio and video, and stream it live.*/
	Stream
};
ENUM_RANGE_BY_COUNT(ECaptureMode, ECaptureMode::Stream);

UENUM()
enum class EQualityLevel : uint8
{
	/** An unknown value to return when quality level is not available.*/
	Unknown,
	/** SD quality: Standard def resolution (e.g. 480p) and a low bit rate (e.g. 1-2Mbps).*/
	SD,
	/** HD quality: DVD HD resolution (i.e. 720p) and a medium bit rate (e.g. 3-4Mbps).*/
	HD,
	/** Extreme HD quality: BluRay HD resolution (i.e. 1080p) and a high bit rate (e.g. 6-8Mbps).*/
	XHD,
	/** Full HD quality: 2160P resolution and high bit rate, e.g. 10-12Mbps.*/
	FullHD
};
ENUM_RANGE_BY_COUNT(EQualityLevel, EQualityLevel::FullHD);

UENUM()
enum class ECaptureOverlayState : uint8
{
	/** State used to indicate that the capture overlay is drawn on the screen and visible to the user.*/
	Shown,
	/** State used to indicate that the user has initiated capture via the capture overlay.*/
	CaptureStarted,
	/** State used to indicate that the user has stopped capturing via the capture overlay.*/
	CaptureStopped,
	/** State used to indicate that the user has dismissed the capture overlay and it is no longer visible.*/
	Dismissed,
	/** State used to indicate default value.*/
	Unknown
};

class UGPVideoCapabilities;
class UGPCaptureState;

UCLASS(BlueprintType)
class GOOGLEPLAYGOODIES_API UGPVideoRecordingLibrary : public UObject
{
	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_DELEGATE_OneParam(FGPOnErrorDelegate, const FString&, ErrorMessage);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGPOnGetCaptureCapabilitiesSuccessDelegate, const UGPVideoCapabilities*, CaptureCapabilities);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGPOnGetCaptureStateSuccessDelegate, const UGPCaptureState*, CaptureState);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGPOnIsCaptureSupportedSuccessDelegate, bool, IsCaptureSupported);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGPOnCaptureOverlayStateChangedDelegate, ECaptureOverlayState, OverlayState);

	
	/**
	* Initiate video recording for the currently signed-in player.
	*
	* @param OnVideoRecordingError - Called if snapshot reading is failed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Video Recording", meta = (AutoCreateRefTerm = "OnVideoRecordingError"))
	static void ShowVideoRecordingOverlay(const FGPOnErrorDelegate& OnVideoRecordingError);
	
	/**
	* Checks whether the device supports capture.
	*
	* @param OnIsCaptureSupportedSuccess - Called if capture supported success.
	* @param OnIsCaptureSupportedError - Called if capture supported is failed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Video Recording", meta = (AutoCreateRefTerm = "OnIsCaptureSupportedSuccess,OnIsCaptureSupportedError"))
	static void IsCaptureSupported(const FGPOnIsCaptureSupportedSuccessDelegate& OnIsCaptureSupportedSuccess, const FGPOnErrorDelegate& OnIsCaptureSupportedError);

	/**
	* Fetches the VideoCapabilities of the service, whether the mic or front-facing camera are supported, if the service can write to external storage, and what capture modes and quality levels are available.
	*
	* @param OnGetCaptureCapabilitiesSuccess - Called if it successfully got capture capabilities.
	* @param OnGetCaptureCapabilitiesError - Called if getting capture capabilities was failed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Video Recording", meta = (AutoCreateRefTerm = "OnGetCaptureCapabilitiesSuccess,OnGetCaptureCapabilitiesError"))
	static void GetCaptureCapabilities(const FGPOnGetCaptureCapabilitiesSuccessDelegate& OnGetCaptureCapabilitiesSuccess, const FGPOnErrorDelegate& OnGetCaptureCapabilitiesError);
	
	/**
	* Fetches the current CaptureState of the capture service.
	*
	* @param OnGetCaptureStateSuccess - Called if fetching capture state was successful.
	* @param OnGetCaptureStateError - Called if fetching capture state was failed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Video Recording", meta = (AutoCreateRefTerm = "OnGetCaptureStateSuccess,OnGetCaptureStateError"))
	static void GetCaptureState(const FGPOnGetCaptureStateSuccessDelegate& OnGetCaptureStateSuccess, const FGPOnErrorDelegate& OnGetCaptureStateError);
	
	/**
	*  Registers a Capture Overlay State Listener to listen for changes to the overlay state.
	*
	* @param OnCaptureOverlayStateChanged - Called if capture overlay state changed successfully.
	* @param OnRegisterCaptureOverlayStateFailureListener - Called if capture overlay state change was failed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Video Recording", meta = (AutoCreateRefTerm = "OnCaptureOverlayStateChanged,OnRegisterCaptureOverlayStateFailureListener"))
	static void RegisterOnCaptureOverlayStateChanged(const FGPOnCaptureOverlayStateChangedDelegate& OnCaptureOverlayStateChanged, const FGPOnErrorDelegate& OnRegisterCaptureOverlayStateFailureListener);

	/**
	* Unregisters this client's overlay state update listener, if any, and loads the result.
	*
	* @param OnUnregisterCaptureOverlayStateFailureListener - Called if unregister capture overlay state mode was failed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Video Recording", meta = (AutoCreateRefTerm = "OnUnregisterCaptureOverlayStateFailureListener"))
	static void UnregisterOnCaptureOverlayStateChanged(const FGPOnErrorDelegate& OnUnregisterCaptureOverlayStateFailureListener);

	static FGPOnErrorDelegate OnVideoRecordingErrorDelegate;
	
	//Get Capture Capabilities
	static FGPOnGetCaptureCapabilitiesSuccessDelegate OnGetCaptureCapabilitiesSuccessDelegate;
	static FGPOnErrorDelegate OnGetCaptureCapabilitiesErrorDelegate;
	
	//Is Capture Supported
	static FGPOnIsCaptureSupportedSuccessDelegate OnIsCaptureSupportedSuccessDelegate;
	static FGPOnErrorDelegate OnIsCaptureSupportedErrorDelegate;

	//Get Capture State 
	static FGPOnGetCaptureStateSuccessDelegate OnGetCaptureStateSuccessDelegate;
	static FGPOnErrorDelegate OnGetCaptureStateErrorDelegate;

	//Register Overlay State Changed
	static FGPOnCaptureOverlayStateChangedDelegate OnCaptureOverlayStateChangedDelegate;
	static FGPOnErrorDelegate OnRegisterCaptureOverlayStateFailureListenerDelegate;

	//Unregister Overlay State Changed
	static FGPOnErrorDelegate OnUnregisterCaptureOverlayStateFailureListenerDelegate;
};
