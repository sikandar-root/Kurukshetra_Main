// Copyright (c) 2018 Nineva Studios

#include "AGDeviceInfoBPL.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJava.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/JavaEntities/JavaAGDeviceInfo.h"
#include "AGDeviceInfoBPL.h"
#endif

UAGDeviceInfo::UAGDeviceInfo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

int UAGDeviceInfo::GetSdkInt()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::GetSdkInt();
#endif
	return 0;
}

FString UAGDeviceInfo::GetApplicationPackageName()
{
	FString result;

#if PLATFORM_ANDROID
	result = FJavaAGDeviceInfo::GetApplicationPackageName();
#endif

	return result;
}

FString UAGDeviceInfo::GetBaseOs()
{
	FString result;

#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 23)
	{
		result = FJavaAGDeviceInfo::GetBaseOs();
	}
#endif

	return result;
}

FString UAGDeviceInfo::GetCodeName()
{
	FString result;

#if PLATFORM_ANDROID
	result = FJavaAGDeviceInfo::GetCodeName();
#endif

	return result;
}

FString UAGDeviceInfo::GetRelease()
{
	FString result;

#if PLATFORM_ANDROID
	result = FJavaAGDeviceInfo::GetRelease();
#endif

	return result;
}

FString UAGDeviceInfo::GetBoard()
{
	FString result;

#if PLATFORM_ANDROID
	result = FJavaAGDeviceInfo::GetBoard();
#endif

	return result;
}

FString UAGDeviceInfo::GetBootloader()
{
	FString result;

#if PLATFORM_ANDROID
	result = FJavaAGDeviceInfo::GetBootloader();
#endif

	return result;
}

FString UAGDeviceInfo::GetBrand()
{
	FString result;

#if PLATFORM_ANDROID
	result = FJavaAGDeviceInfo::GetBrand();
#endif

	return result;
}

FString UAGDeviceInfo::GetDevice()
{
	FString result;

#if PLATFORM_ANDROID
	result = FJavaAGDeviceInfo::GetDevice();
#endif

	return result;
}

FString UAGDeviceInfo::GetDisplay()
{
	FString result;

#if PLATFORM_ANDROID
	result = FJavaAGDeviceInfo::GetDisplay();
#endif

	return result;
}

FString UAGDeviceInfo::GetHardware()
{
	FString result;

#if PLATFORM_ANDROID
	result = FJavaAGDeviceInfo::GetHardware();
#endif

	return result;
}

FString UAGDeviceInfo::GetManufacturer()
{
	FString result;

#if PLATFORM_ANDROID
	result = FJavaAGDeviceInfo::GetManufacturer();
#endif

	return result;
}

FString UAGDeviceInfo::GetModel()
{
	FString result;

#if PLATFORM_ANDROID
	result = FJavaAGDeviceInfo::GetModel();
#endif

	return result;
}

FString UAGDeviceInfo::GetProduct()
{
	FString result;

#if PLATFORM_ANDROID
	result = FJavaAGDeviceInfo::GetProduct();
#endif

	return result;
}

FString UAGDeviceInfo::GetRadio()
{
	FString result;

#if PLATFORM_ANDROID
	result = FJavaAGDeviceInfo::GetRadio();
#endif

	return result;
}

FString UAGDeviceInfo::GetSerial()
{
	FString result;

#if PLATFORM_ANDROID
	result = FJavaAGDeviceInfo::GetSerial();
#endif

	return result;
}

FString UAGDeviceInfo::GetTags()
{
	FString result;

#if PLATFORM_ANDROID
	result = FJavaAGDeviceInfo::GetTags();
#endif

	return result;
}

FString UAGDeviceInfo::GetType()
{
	FString result;

#if PLATFORM_ANDROID
	result = FJavaAGDeviceInfo::GetType();
#endif

	return result;
}

FString UAGDeviceInfo::GetAndroidId()
{
	FString result;

#if PLATFORM_ANDROID
	result = FJavaAGDeviceInfo::GetAndroidId();
#endif

	return result;
}

bool UAGDeviceInfo::IsPackageInstalled(FString packageName)
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::IsPackageInstalled(packageName);
#endif

	return false;
}

bool UAGDeviceInfo::SupportsActivitiesOnSecondaryDisplays()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 26)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.software.activities_on_secondary_displays");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsAppWidgets()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 18)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.software.app_widgets");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsAudioLowLatency()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.audio.low_latency");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsAudioOutput()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 21)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.audio.output");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsAudioPro()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 23)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.audio.pro");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsAutofill()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 26)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.software.autofill");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsAutomotive()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 23)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.type.automotive");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsBackup()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 20)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.software.backup");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsBluetooth()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.bluetooth");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsBluetoothLe()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 18)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.bluetooth_le");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasCamera()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.camera");
#endif
	return false;
}

bool UAGDeviceInfo::HasCameraAny()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 17)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.camera.any");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasCameraAr()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 28)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.camera.ar");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasCameraAutofocus()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.camera.autofocus");
#endif
	return false;
}

bool UAGDeviceInfo::HasCameraCapabilityManualPostprocessing()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 21)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.camera.capability.manual_post_processing");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasCameraCapabilityManualSensor()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.camera.capability.manual_sensor");
#endif
	return false;
}

bool UAGDeviceInfo::HasCameraCapabilityRaw()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 21)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.camera.capability.raw");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasCameraExternal()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 20)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.camera.external");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasCameraFlash()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.camera.flash");
#endif
	return false;
}

bool UAGDeviceInfo::HasCameraFront()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.camera.front");
#endif
	return false;
}

bool UAGDeviceInfo::HasCameraLevelFull()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 21)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.camera.level.full");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsCantSaveState()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.software.cant_save_state");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsCompanionDeviceSetup()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 26)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.software.companion_device_setup");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsConnectionService()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 21)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.software.connectionservice");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsConsumerIr()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 19)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.consumerir");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsDeviceAdmin()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 19)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.software.device_admin");
	}
#endif
	return false;
}

bool UAGDeviceInfo::IsEmbedded()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 26)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.type.embedded");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsEthernet()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 24)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.ethernet");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsFakeTouch()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.faketouch");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsFakeTouchMultiTouchDistinct()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.faketouch.multitouch.distinct");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsFakeTouchMultiTouchJazzHand()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.faketouch.multitouch.jazzhand");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsFingerprint()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 23)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.fingerprint");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsFreeFormWindowManagement()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 24)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.software.freeform_window_management");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasGamepad()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 21)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.gamepad");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsHifiSensors()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 23)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.sensor.hifi_sensors");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsHomeScreen()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 18)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.software.home_screen");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsInputMethods()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 18)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.software.input_methods");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsLeanback()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 21)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.software.leanback");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsLeanbackOnly()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 26)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.software.leanback_only");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsLiveTv()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 21)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.software.live_tv");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsLiveWallpaper()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.software.live_wallpaper");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsLocation()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.location");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsLocationGps()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.location.gps");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsLocationNetwork()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.location.network");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsManagedUsers()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 21)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.software.managed_users");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasMicrophone()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.microphone");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsMidi()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 23)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.software.midi");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsNfc()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.nfc");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsNfcHostCardEmulation()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 19)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.nfc.hce");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsNfcHostCardEmulationNfcf()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 24)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.nfc.hcef");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsOpenGlEsExtensionPack()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 21)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.opengles.aep");
	}
#endif
	return false;
}

bool UAGDeviceInfo::IsPc()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 27)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.type.pc");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsPictureInPicture()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 24)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.software.picture_in_picture");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsPrinting()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 20)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.software.print");
	}
#endif
		return false;
}

bool UAGDeviceInfo::HasRamLow()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 27)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.ram.low");
	}
#endif
		return false;
}

bool UAGDeviceInfo::HasRamNormal()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 27)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.ram.normal");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsScreenLandscape()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.screen.landscape");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsScreenPortrtait()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.screen.portrait");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsSecureUserRemoval()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 21)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.software.securely_removes_users");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasSensorAccelerometer()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.sensor.accelerometer");
#endif
	return false;
}

bool UAGDeviceInfo::HasSensorAmbientTemperature()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 21)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.sensor.ambient_temperature");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasSensorBarometer()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.sensor.barometer");
#endif
	return false;
}

bool UAGDeviceInfo::HasSensorCompass()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.sensor.compass");
#endif
	return false;
}

bool UAGDeviceInfo::HasSensorGyroscope()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.sensor.gyroscope");
#endif
	return false;
}

bool UAGDeviceInfo::HasSensorHeartRate()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 20)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.sensor.heartrate");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasSensorHeartRateEcg()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 21)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.sensor.heartrate.ecg");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasSensorLight()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.sensor.light");
#endif
	return false;
}

bool UAGDeviceInfo::HasSensorProximity()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.sensor.proximity");
#endif
	return false;
}

bool UAGDeviceInfo::HasSensorRelativeHumidity()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 21)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.sensor.relative_humidity");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasSensorStepCounter()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 19)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.sensor.stepcounter");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasSensorStepDetector()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 19)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.sensor.stepdetector");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasSip()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.software.sip");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsSipVoip()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.software.sip.voip");
#endif
	return false;
}

bool UAGDeviceInfo::HasStrongBoxKeyStore()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 28)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.strongbox_keystore");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasTelephony()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.telephony");
#endif
	return false;
}

bool UAGDeviceInfo::HasTelephonyCdma()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.telephony.cdma");
#endif
	return false;
}

bool UAGDeviceInfo::HasTelephonyEuicc()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 28)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.telephony.euicc");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasTelephonyGsm()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.telephony.gsm");
#endif
	return false;
}

bool UAGDeviceInfo::HasTelephonyMbms()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 28)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.telephony.mbms");
	}
#endif
	return false;
}

bool UAGDeviceInfo::IsTelevision()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 16)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.type.television");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasTouchScreen()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.touchscreen");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsTouchScreenMultiTouch()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.touchscreen.multitouch");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsTouchScreenMultiTouchDistinct()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.touchscreen.multitouch.distinct");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsTouchScreenMultiTouchJazzHand()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.touchscreen.multitouch.jazzhand");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsUsbAccessory()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.usb.accessory");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsUsbHost()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.usb.host");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsVerifiedBoot()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 21)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.software.verified_boot");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasVrHeadTracking()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 26)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.vr.headtracking");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasVrMode()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 24)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.vr.mode");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasVrModeHighPerformance()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 24)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.vr.high_performance");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsVulkanHardwareCompute()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 26)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.vulkan.compute");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsVulkanHardwareLevel()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 24)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.vulkan.level");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsVulkanHardwareVersion()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 24)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.vulkan.version");
	}
#endif
	return false;
}

bool UAGDeviceInfo::IsWatch()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 20)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.type.watch");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsWebView()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 20)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.software.webview");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsWifi()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.wifi");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsWifiAware()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 26)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.wifi.aware");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsWifiDirect()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.wifi.direct");
#endif
	return false;
}

bool UAGDeviceInfo::SupportsWifiPassPoint()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 27)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.wifi.passpoint");
	}
#endif
	return false;
}

bool UAGDeviceInfo::SupportsWifiRtt()
{
#if PLATFORM_ANDROID
	if (UAGDeviceInfo::GetSdkInt() >= 28)
	{
		return FJavaAGDeviceInfo::HasSystemFeature("android.hardware.wifi.rtt");
	}
#endif
	return false;
}

bool UAGDeviceInfo::HasSystemFeature(FString featureName)
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::HasSystemFeature(featureName);
#endif
	return false;
}

FString UAGDeviceInfo::GetInstallSourceAndroid()
{
#if PLATFORM_ANDROID
	return FJavaAGDeviceInfo::GetInstallSourceAndroid();
#endif

	return "";
}