// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGVibrationEffect.h"
#include "AGAudioAttributes.h"
#include "AGScanResultBPL.h"
#include "Enums/AGBatteryStatus.h"
#include "Enums/AGBatteryHealth.h"
#include "Enums/AGBatteryPluggedState.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGHardwareBPL.generated.h"


DECLARE_DYNAMIC_DELEGATE_OneParam(FOnWifiScanSuccessDelegate, const TArray<UAGScanResultBPL*>&, ScanResult);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnWifiScanFailureDelegate, const FString&, ErrorMessage);


USTRUCT(BlueprintType)
struct FRect
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 MinX;

	UPROPERTY(BlueprintReadOnly)
	int32 MinY;

	UPROPERTY(BlueprintReadOnly)
	int32 MaxX;

	UPROPERTY(BlueprintReadOnly)
	int32 MaxY;

	FRect() : MinX(0), MinY(0), MaxX(0), MaxY(0) {}
};


UCLASS()
class ANDROIDGOODIES_API UAGHardwareBPL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


	/**
	* Toggle flashlight ON/OFF
	*
	* @param enable - whether to turn the flashlight ON or OFF.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void EnableFlashlight(bool enable);

	/**
	* Check whether the device has a vibrator.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasVibrator();

	/**
	* Check whether the vibrator has amplitude control.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasAmplitudeControl();

	/**
	* Vibrate constantly for the specified period of time.
	*
	* @param duration - duration in seconds.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void Vibrate(float duration);

	/**
	* Vibrate with a given pattern.
	*
	* @param pattern - an array of the floating point values that are the durations for which to turn on or off the vibrator in seconds. 
	* The first value indicates the number of seconds to wait before turning the vibrator on. The next value indicates the number of seconds 
	* for which to keep the vibrator on before turning it off. Subsequent values alternate between durations in seconds to turn the vibrator off or to turn the vibrator on.
	* @param repeatFrom - the index of the element in the intervals array, from which to repeat the sequence, or -1 for a single playback.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void VibrateWithPattern(TArray<float> pattern, int repeatFrom);

	/**
	* Check if device's OS supports new vibration effects
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool AreVibrationEffectsSupported();

	/**
	* Vibrate with custom vibration effect.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void VibrateWithEffect(UAGVibrationEffect* vibrationEffect);

	/**
	* Vibrate with custom vibration effect and audio attributes.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void VibrateWithEffectAndAttributes(UAGVibrationEffect* vibrationEffect, FAGAudioAttributes audioAttributes);

	/**
	* Cancel the current vibration.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void StopVibration();

	/**
	* Return callback with the results of the latest access point scan, else return callback with error message.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Hardware")
	static void StartWifiScan(const FOnWifiScanSuccessDelegate& OnWifiScanSuccess, const FOnWifiScanFailureDelegate& OnWifiScanFailure);

	/**
	* Attempt to connect to a Wifi network using the given credentials. 
	* Requires android.permission.ACCESS_FINE_LOCATION permission.
	* 
	* On Android 29 and higher you can only suggest the system to do it. 
	* The decision whether to actually connect to the given network is made by the operating system.
	* 
	* https://developer.android.com/guide/topics/connectivity/wifi-suggest
	* 
	* @param SSID - name of the network.
	* @param Password - passphrase of the network. Leave empty for open networks.
	* @param IsWpa2 - true if the network is WPA2-encrypted. Otherwise, assumes it's WPA3.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Hardware", meta = (AutoCreateRefTerm = "Password"))
	static void ConnectToWifiNetwork(const FString& SSID, const FString& Password, bool IsWpa2);

	/**
	* Enable/disable Wifi.
	* Requires android.permission.CHANGE_WIFI_STATE permission.
	* 
	* On Android 29 and higher this will only open system dialog where the user can do it.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Hardware")
	static void ToggleWifiState(bool Enabled);

	/**
	* Returns whether Wifi is enabled on the device.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Hardware")
	static bool IsWifiEnabled();

	/**
	* The remaining battery charge time in seconds.
	* Returns -1, on OS version <28 and if something went wrong.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static int ComputeRemainingChargeTime();

	/**
	* The current battery capacity (0 - 100 %). Returns -1, if something went wrong.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static int GetBatteryCapacity();

	/**
	* The battery capacity in micro ampere-hours, as an integer.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static int GetBatteryChargeCounter();

	/**
	* The average battery current in micro amperes, as an integer.
	* Positive values indicate net current entering the battery from a charge source,
	* negative values indicate net current discharging from the battery.
	* The time period over which the average is computed may depend on the fuel gauge hardware and its configuration.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static int GetAverageBatteryCurrent();

	/**
	* Instantaneous battery current in micro amperes, as an integer.
	* Positive values indicate net current entering the battery from a charge source,
	* negative values indicate net current discharging from the battery.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static int GetImmediateBatteryCurrent();

	/**
	* Battery remaining energy in nano watt-hours. -1 if not supported.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static int GetBatteryEnergyCounter();

	/**
	* Battery charge status.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static BatteryStatus GetBatteryStatus();

	/**
	* Whether the battery is currently considered to be low,
	* that is whether an Intent.ActionBatteryLow broadcast has been sent.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool IsBatteryLow();

	/**
	* Current health constant.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static BatteryHealth GetBatteryHealth();

	/**
	* The current battery level, from 0 to Scale. -1 if something went wrong.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static int GetBatteryLevel();

	/**
	* One of the BatteryPluggedState values indicating whether the device is plugged in to a power source.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static BatteryPluggedState GetBatteryPluggedState();

	/**
	* Whether a battery is present.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool IsBatteryPresent();

	/**
	* The maximum battery level. -1 if something went wrong.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static int GetBatteryScale();

	/**
	* The technology of the current battery.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static FString GetBatteryTechnology();

	/**
	* The current battery temperature in the tenth parts of a Celcius degree.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static int GetBatteryTemperature();

	/**
	* The current battery voltage level in mV.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static int GetBatteryVoltage();

	/**
	* Get the device viewport size in full screen mode.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Hardware")
	static FIntPoint GetDeviceViewportSizeFullScreen();

	/**
	* Get the device viewport size after reducing the notch and corner.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Hardware")
	static FIntPoint GetDeviceViewportSizeAdjusted();

	/**
	* Check if the device has a notch.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Hardware")
	static bool HasNotch();

	/**
	* Check if the device has rounded corners.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Hardware")
	static bool HasRoundedCorners();
	/**
	* Get the current volume level.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Hardware")
	static int32 GetVolumeLevel();

	/**
	* Set the volume level.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Hardware")
	static void SetVolumeLevel(int32 VolumeLevel);

	/**
	* Get the maximum volume level.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Hardware")
	static int32 GetMaxVolumeLevel();

	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Hardware")
	static void SendNotification(const FString& Title, const FString& Text);

	

public:
	static FOnWifiScanSuccessDelegate OnWifiScanSuccessDelegate;
	static FOnWifiScanFailureDelegate OnWifiScanFailureDelegate;

};