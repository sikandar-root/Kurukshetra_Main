// Copyright (c) 2018 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGDeviceInfoBPL.generated.h"

UCLASS()
class ANDROIDGOODIES_API UAGDeviceInfo : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	/**
	* Get SDK version of the software currently running on device.
	*
	* @return - SDK version number.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static int GetSdkInt();

	/**
	* Get package name of currently running application.
	*
	* @return - application package name.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static FString GetApplicationPackageName();

	/**
	* Get base OS build the product is based on.
	*
	* @return - base OS build version.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static FString GetBaseOs();

	/**
	* Get current development codename or the string "REL" if this is a release build.
	*
	* @return - development codename.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static FString GetCodeName();

	/**
	* Get visible Android version string. E.g. "1.0" or "3.4b5".
	*
	* @return - Android version string.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static FString GetRelease();

	/**
	* Get name of the underlying board, like "goldfish".
	*
	* @return - board name.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static FString GetBoard();

	/**
	* Get system bootloader version number.
	*
	* @return - bootloader version number.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static FString GetBootloader();

	/**
	* Get consumer-visible brand with which the product/hardware will be associated, if any.
	*
	* @return - brand name.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static FString GetBrand();

	/**
	* Get name of the industrial design.
	*
	* @return - name of the industrial design.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static FString GetDevice();

	/**
	* Get build ID string meant for displaying to the user.
	*
	* @return - build ID.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static FString GetDisplay();

	/**
	* Get name of the hardware (from the kernel command line or /proc).
	*
	* @return - name of the hardware.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static FString GetHardware();

	/**
	* Get manufacturer of the product/hardware.
	*
	* @return - name of hardware manufacturer.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static FString GetManufacturer();

	/**
	* Get end-user-visible name for the end product.
	*
	* @return - model name.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static FString GetModel();

	/**
	* Get name of the overall product.
	*
	* @return - product name.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static FString GetProduct();

	/**
	* Get radio firmware version number.
	*
	* @return - radio firmware version number.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static FString GetRadio();

	/**
	* Get hardware serial number, if available.
	*
	* @return - serial number.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static FString GetSerial();

	/**
	* Get comma-separated tags describing the build, like "unsigned,debug".
	*
	* @return - string with tags.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static FString GetTags();

	/**
	* Get type of build, like "user" or "eng".
	*
	* @return - build type.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static FString GetType();
	
	/**
	* Get android ID.
	*
	* @return - android ID.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static FString GetAndroidId();

	/**
	* Check whether package with specified name installed on current device.
	*
	* @param packageName - package name
	*
	* @return - true if package installed, otherwise - false
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool IsPackageInstalled(FString packageName);

	/**
	* Check whether the device supports running activities on secondary displays. 
	* @note API level 26
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsActivitiesOnSecondaryDisplays();	

	/**
	* Check whether the device supports app widgets. 
	* @note API level 18
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsAppWidgets();
	
	/**
	* Check whether the device's audio pipeline is low-latency, more suitable for audio applications sensitive to delays or lag in sound input or output. 
	* @note API level 9
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsAudioLowLatency();
		
	/**
	* Check whether the device includes at least one form of audio output, as defined in the Android Compatibility Definition Document (CDD) section 7.8 Audio. 
	* @note API level 21
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsAudioOutput();
	
	/**
	* Check whether the device has professional audio level of functionality and performance.
	* @note API level 23
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsAudioPro();

	/**
	* Check whether the device supports autofill of user credentials, addresses, credit cards, etc via integration with autofill providers. 
	* @note API level 26
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsAutofill();

	/**
	* Check whether this is a device dedicated to showing UI on a vehicle headunit. A headunit here is defined to be inside a vehicle that may or may not be moving.
	* A headunit uses either a primary display in the center console and/or additional displays in the instrument cluster or elsewhere in the vehicle. 
	* Headunit display(s) have limited size and resolution. The user will likely be focused on driving so limiting driver distraction is a primary concern. 
	* User input can be a variety of hard buttons, touch, rotary controllers and even mouse- like interfaces. 
	* @note API level 23
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsAutomotive();

	/**
	* Check whether the device can perform backup and restore operations on installed applications. 
	* @note API level 20
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsBackup();

	/**
	* Check whether the device is capable of communicating with other devices via Bluetooth. 
	* @note API level 8
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsBluetooth();

	/**
	* Check whether the device is capable of communicating with other devices via Bluetooth Low Energy radio.
	* @note API level 18
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsBluetoothLe();

	/**
	* Check whether the device has a camera facing away from the screen. 
	* @note API level 7
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasCamera();

	/**
	* Check whether the device has at least one camera pointing in some direction, or can support an external camera being connected to it.
	* @note API level 17
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasCameraAny();

	/**
	* Check whether at least one of the cameras on the device supports the motion tracking capability level. 
	* @note API level 28
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasCameraAr();

	/**
	* Check whether the device's camera supports auto-focus. 
	* @note API level 7
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasCameraAutofocus();

	/**
	* Check whether at least one of the cameras on the device supports the manual post-processing capability level. 
	* @note API level 21
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasCameraCapabilityManualPostprocessing();

	/**
	* Check whether at least one of the cameras on the device supports the manual sensor capability level. 
	* @note API level 21
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasCameraCapabilityManualSensor();

	/**
	* Check whether at least one of the cameras on the device supports the raw capability level. 
	* @note API level 21
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasCameraCapabilityRaw();

	/**
	* Check whether the device can support having an external camera connected to it. 
	* The external camera may not always be connected or available to applications to use. 
	* @note API level 20
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasCameraExternal();

	/**
	* Check whether the device's camera supports flash. 
	* @note API level 7
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasCameraFlash();

	/**
	* Check whether the device has a front facing camera. 
	* @note API level 9
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasCameraFront();

	/**
	* Check whether at least one of the cameras on the device supports the full hardware capability level. 
	* @note API level 21
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasCameraLevelFull();

	/**
	* Check whether the device supports the cant save state API. 
	* @note API level 28
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsCantSaveState();

	/**
	* Check whether the device supports associating with devices via CompanionDeviceManager. 
	* @note API level 26
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsCompanionDeviceSetup();

	/**
	* Check whether the Connection Service API is enabled on the device. 
	* @note API level 21
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsConnectionService();

	/**
	* Check whether the device is capable of communicating with consumer IR devices. 
	* @note API level 19
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsConsumerIr();

	/**
	* Check whether the device supports device policy enforcement via device admins. 
	* @note API level 19
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsDeviceAdmin();

	/**
	* Check whether this is a device for IoT and may not have an UI. An embedded device is defined as a full stack 
	* Android device with or without a display and no user-installable apps. 
	* @note API level 26
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool IsEmbedded();

	/**
	* Check whether this device supports ethernet.
	* @note API level 24
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsEthernet();

	/**
	* Check whether this device does not have a touch screen, but does support touch emulation for basic events. 
	* For instance, the device might use a mouse or remote control to drive a cursor, and emulate basic touch pointer events like
	* down, up, drag, etc. All devices that support android.hardware.touchscreen or a sub-feature are presumed to also support fake touch.
	* @note API level 11
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsFakeTouch();

	/**
	* Check whether this device does not have a touch screen, but does support touch emulation for basic events 
	* that supports distinct tracking of two or more fingers. This is an extension of SupportsFakeTouch for input devices with this capability.
	* Note that unlike a distinct multi touch screen as defined by SupportsFakeTouchMultiTouchDistinct, 
	* these kinds of input devices will not actually provide full two-finger gestures 
	* since the input is being transformed to cursor movement on the screen. That is, single finger gestures will move a cursor; 
	* two-finger swipes will result in single-finger touch events; other two-finger gestures will result in the corresponding two-finger touch event.
	* @note API level 13
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsFakeTouchMultiTouchDistinct();

	/**
	* Check whether this device does not have a touch screen, but does support touch emulation for basic events 
	* that supports tracking a hand of fingers (5 or more fingers) fully independently. This is an extension of SupportsFakeTouch for input devices with this capability. 
	* Note that unlike a multi touch screen as defined by SupportsFakeTouchMultiTouchJazzHand, 
	* not all two finger gestures can be detected due to the limitations described for SupportsFakeTouchMultiTouchDistinct.
	* @note API level 13
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsFakeTouchMultiTouchJazzHand();

	/**
	* Check whether this device has biometric hardware to detect a fingerprint.
	* @note API level 23
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsFingerprint();

	/**
	* Check whether this device supports free form window management. Windows have title bars and can be moved and resized.
	* @note API level 24
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsFreeFormWindowManagement();

	/**
	* Check whether this device has all of the inputs necessary to be considered a compatible game controller, or includes a compatible game controller in the box.
	* @note API level 21
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasGamepad();

	/**
	* Check whether this device supports high fidelity sensor processing capabilities.
	* @note API level 23
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsHifiSensors();

	/**
	* Check whether this device supports a home screen that is replaceable by third party applications.
	* @note API level 18
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsHomeScreen();

	/**
	* Check whether this device supports adding new input methods implemented with the InputMethodService API.
	* @note API level 18
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsInputMethods();

	/**
	* Check whether this device supports lean back UI. This is typically used in a living room television experience, 
	* but is a software feature unlike IsTelevision. Devices running with this feature will use resources associated with the "television" UI mode.
	* @note API level 21
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsLeanback();

	/**
	* Check whether this device supports only lean back UI. Only applications designed for this experience should be run, 
	* though this is not enforced by the system.
	* @note API level 26
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsLeanbackOnly();

	/**
	* Check whether this device supports live TV and can display contents from TV inputs implemented with the TvInputService API.
	* @note API level 21
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsLiveTv();

	/**
	* Check whether this device supports live wallpapers.
	* @note API level 7
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsLiveWallpaper();

	/**
	* Check whether this device supports one or more methods of reporting current location.
	* @note API level 8
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsLocation();

	/**
	* Check whether this device has a Global Positioning System receiver and can report precise location.
	* @note API level 8
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsLocationGps();

	/**
	* Check whether this device can report location with coarse accuracy using a network-based geolocation system.
	* @note API level 8
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsLocationNetwork();

	/**
	* Check whether this device supports creating secondary users and managed profiles via DevicePolicyManager.
	* @note API level 21
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsManagedUsers();

	/**
	* Check whether this device can record audio via a microphone.
	* @note API level 8
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasMicrophone();

	/**
	* Check whether this device has a full implementation of the android.media.midi.* APIs.
	* @note API level 23
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsMidi();

	/**
	* Check whether this device can communicate using Near-Field Communications (NFC).
	* @note API level 9
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsNfc();

	/**
	* Check whether this device supports host-based NFC card emulation.
	* @note API level 19
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsNfcHostCardEmulation();

	/**
	* Check whether this device supports host-based NFC-F card emulation.
	* @note API level 24
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsNfcHostCardEmulationNfcf();

	/**
	* Check whether this device supports the OpenGL ES Android Extension Pack.
	* @note API level 21
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsOpenGlEsExtensionPack();

	/**
	* Check whether this is a device dedicated to be primarily used with keyboard, mouse or touch pad. 
	* This includes traditional desktop computers, laptops and variants such as convertibles or detachables. 
	* Due to the larger screen, the device will most likely use the SupportsFreeFormWindowManagement feature as well.
	* @note API level 27
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool IsPc();

	/**
	* Check whether this device supports picture-in-picture multi-window mode.
	* @note API level 24
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsPictureInPicture();

	/**
	* Check whether this device supports printing.
	* @note API level 20
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsPrinting();

	/**
	* Check whether this device's ActivityManager.isLowRamDevice() method returns true.
	* @note API level 27
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasRamLow();

	/**
	* Check whether this device's ActivityManager.isLowRamDevice() method returns false.
	* @note API level 27
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasRamNormal();

	/**
	* Check whether this device supports landscape orientation screens. For backwards compatibility, you can assume that if neither this 
	* nor SupportsScreenPortrait is set then the device supports both portrait and landscape.
	* @note API level 13
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsScreenLandscape();

	/**
	* Check whether this device supports portrait orientation screens. For backwards compatibility, you can assume that if neither this 
	* nor SupportsScreenLandscape is set then the device supports both portrait and landscape.
	* @note API level 13
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsScreenPortrtait();

	/**
	* Check whether this device supports secure removal of users. When a user is deleted the data associated with that user is securely deleted and no longer available.
	* @note API level 21
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsSecureUserRemoval();

	/**
	* Check whether this device includes an accelerometer.
	* @note API level 8
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasSensorAccelerometer();

	/**
	* Check whether this device includes an ambient temperature sensor.
	* @note API level 21
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasSensorAmbientTemperature();

	/**
	* Check whether this device includes a barometer (air pressure sensor).
	* @note API level 9
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasSensorBarometer();

	/**
	* Check whether this device includes a magnetometer (compass).
	* @note API level 8
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasSensorCompass();

	/**
	* Check whether this device includes a gyroscope.
	* @note API level 9
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasSensorGyroscope();

	/**
	* Check whether this device includes a heart rate monitor.
	* @note API level 20
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasSensorHeartRate();

	/**
	* Check whether heart rate sensor on this device is an Electrocardiogram.
	* @note API level 21
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasSensorHeartRateEcg();

	/**
	* Check whether this device includes a light sensor.
	* @note API level 7
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasSensorLight();

	/**
	* Check whether this device includes a proximity sensor.
	* @note API level 7
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasSensorProximity();

	/**
	* Check whether this device includes a relative humidity sensor.
	* @note API level 21
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasSensorRelativeHumidity();

	/**
	* Check whether this device includes a hardware step counter.
	* @note API level 19
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasSensorStepCounter();

	/**
	* Check whether this device includes a hardware step detector.
	* @note API level 19
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasSensorStepDetector();

	/**
	* Check whether SIP API is enabled on the device.
	* @note API level 9
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasSip();

	/**
	* Check whether this device supports SIP-based VOIP.
	* @note API level 9
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsSipVoip();

	/**
	* Check whether this device has a StrongBox hardware-backed Key store.
	* @note API level 28
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasStrongBoxKeyStore();

	/**
	* Check whether this device has a telephony radio with data communication support.
	* @note API level 7
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasTelephony();

	/**
	* Check whether this device has a CDMA telephony stack.
	* @note API level 7
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasTelephonyCdma();

	/**
	* Check whether this device supports embedded subscriptions on eUICCs.
	* @note API level 28
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasTelephonyEuicc();

	/**
	* Check whether this device has a GSM telephony stack.
	* @note API level 7
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasTelephonyGsm();

	/**
	* Check whether this device supports cell-broadcast reception using the MBMS APIs.
	* @note API level 28
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasTelephonyMbms();

	/**
	* Check whether this is a device dedicated to showing UI on a television. Television here is defined to be a typical living room television experience: 
	* displayed on a big screen, where the user is sitting far away from it, and the dominant form of input will be something like a DPAD, not through touch or mouse.
	* Was deprecated in API level 21. Use SupportsLeanback instead.
	* @note API level 16
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool IsTelevision();

	/**
	* Check whether this device's display has a touch screen.
	* @note API level 8
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasTouchScreen();

	/**
	* Check whether this device's touch screen supports multi touch sufficient for basic two-finger gesture detection.
	* @note API level 7
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsTouchScreenMultiTouch();

	/**
	* Check whether this device's touch screen is capable of tracking two or more fingers fully independently.
	* @note API level 8
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsTouchScreenMultiTouchDistinct();

	/**
	* Check whether this device's touch screen is capable of tracking a full hand of fingers fully independently - that is, 5 or more simultaneous independent pointers.
	* @note API level 9
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsTouchScreenMultiTouchJazzHand();

	/**
	* Check whether this device supports connecting to USB accessories.
	* @note API level 12
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsUsbAccessory();

	/**
	* Check whether this device supports connecting to USB devices as the USB host.
	* @note API level 12
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsUsbHost();

	/**
	* Check whether this device supports verified boot.
	* @note API level 21
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsVerifiedBoot();

	/**
	* Check whether this device implements head tracking suitable for a VR device.
	* @note API level 26
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasVrHeadTracking();

	/**
	* Check whether this device implements an optimized mode for virtual reality (VR) applications that handles stereoscopic rendering of notifications,
	* and disables most monocular system UI components while a VR application has user focus. 
	* Devices declaring this feature must include an application implementing a VrListenerService that can be targeted by VR applications via Activity.SetVrModeEnabled(static boolean, ComponentName).
	* Was deprecated in API level 28. Use HasVrModeHighPerformance instead.
	* @note API level 24
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasVrMode();

	/**Check whether this device implements an optimized mode for virtual reality (VR) applications that handles stereoscopic rendering of notifications, 
	disables most monocular system UI components while a VR application has user focus and meets extra CDD requirements to provide a high-quality VR experience. 
	Devices declaring this feature must include an application implementing a VrListenerService that can be targeted by VR applications via Activity.setVrModeEnabled(static boolean, ComponentName)
	and must meet CDD requirements to provide a high-quality VR experience.
	API level 24*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasVrModeHighPerformance();

	/**
	* Check whether this device's Vulkan native API will enumerate at least one VkPhysicalDevice, and the feature version will indicate 
	* what level of optional compute features that device supports beyond the Vulkan 1.0 requirements.
	* Compute level 0 indicates:
	* The VK_KHR_variable_pointers extension and VkPhysicalDeviceVariablePointerFeaturesKHR::variablePointers feature are supported.
	* VkPhysicalDeviceLimits::maxPerStageDescriptorStorageBuffers is at least 16.
	* @note API level 26
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsVulkanHardwareCompute();

	/**
	* Check whether this device's Vulkan native API will enumerate at least one VkPhysicalDevice, 
	* and the feature version will indicate what level of optional hardware features limits it supports.
	* Level 0 includes the base Vulkan requirements as well as:
	* VkPhysicalDeviceFeatures::textureCompressionETC2
	* Level 1 additionally includes:
	* VkPhysicalDeviceFeatures::fullDrawIndexUint32
	* VkPhysicalDeviceFeatures::imageCubeArray
	* VkPhysicalDeviceFeatures::independentBlend
	* VkPhysicalDeviceFeatures::geometryShader
	* VkPhysicalDeviceFeatures::tessellationShader
	* VkPhysicalDeviceFeatures::sampleRateShading
	* VkPhysicalDeviceFeatures::textureCompressionASTC_LDR
	* VkPhysicalDeviceFeatures::fragmentStoresAndAtomics
	* VkPhysicalDeviceFeatures::shaderImageGatherExtended
	* VkPhysicalDeviceFeatures::shaderUniformBufferArrayDynamicIndexing
	* VkPhysicalDeviceFeatures::shaderSampledImageArrayDynamicIndexing
	* @note API level 24
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsVulkanHardwareLevel();

	/**
	* Check whether this device version of this feature indicates the highest VkPhysicalDeviceProperties::apiVersion 
	* supported by the physical devices that support the hardware level indicated by FEATURE_VULKAN_HARDWARE_LEVEL. 
	* The feature version uses the same encoding as Vulkan version numbers:
	* Major version number in bits 31-22
	* Minor version number in bits 21-12
	* Patch version number in bits 11-0
	* A version of 1.1.0 or higher also indicates:
	* SYNC_FD external semaphore and fence handles are supported.
	* VkPhysicalDeviceSamplerYcbcrConversionFeatures::samplerYcbcrConversion is supported.
	* @note API level 24
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsVulkanHardwareVersion();

	/**
	* Check whether this is a device dedicated to showing UI on a watch. A watch here is defined to be a device worn on the body, perhaps on the wrist. 
	* The user is very close when interacting with the device.
	* @note API level 20
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool IsWatch();

	/**
	* Check whether this device has a full implementation of the android.webkit.* APIs. 
	* Devices lacking this feature will not have a functioning WebView implementation.
	* @note API level 20
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsWebView();

	/**
	* Check whether this device supports WiFi (802.11) networking.
	* @note API level 8
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsWifi();

	/**
	* Check whether this device supports WiFi Aware.
	* @note API level 26
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsWifiAware();

	/**
	* Check whether this device supports WiFi Direct networking.
	* @note API level 14
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsWifiDirect();

	/**
	* Check whether this device supports WiFi Pass point and all Pass point related APIs in WifiManager are supported. 
	* Refer to WifiManager.AddOrUpdatePasspointConfiguration(PasspointConfiguration) for more info.
	* @note API level 27
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsWifiPassPoint();

	/**
	* Check whether this device supports WiFi RTT (IEEE 802.11mc).
	* @note API level 28
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool SupportsWifiRtt();

	/**
	* Check whether this device supports the specified system feature.
	* Make sure this method is only called on devices with SDK level greater or equal the API level this feature was introduced.
	* Generic method.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasSystemFeature(FString featureName);
	
	/**
	*  Get the install source of the app.
	*  ex. if app is installed from Google Play Store it returns "com.android.vending")
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static FString GetInstallSourceAndroid();
};