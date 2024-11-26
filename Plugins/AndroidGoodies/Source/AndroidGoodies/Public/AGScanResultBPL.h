// Copyright (c) 2019 Nineva Studios

#pragma once
#include "HAL/Platform.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#endif
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGScanResultBPL.generated.h"

UCLASS(BlueprintType)
class ANDROIDGOODIES_API UAGScanResultBPL : public UObject
{
	GENERATED_BODY()

public:
#if PLATFORM_ANDROID
	void Init(jobject ScanResultObject);
#endif

	/**
	* The address of the access point.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "AndroidGoodies|Hardware")
	FString BSSID;
	
	/**
	* The network name.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "AndroidGoodies|Hardware")
	FString SSID;
	
	/**
	* Describes the authentication, key management, and encryption schemes supported by the access point.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "AndroidGoodies|Hardware")
	FString Capabilities;
	
	/**
	* This field was deprecated in API level 31. - Use WifiInfo#getPasspointProviderFriendlyName()
	*/
	UPROPERTY(BlueprintReadOnly, Category = "AndroidGoodies|Hardware")
	FString OperatorFriendlyName;
	
	/**
	* This field was deprecated in API level 31. - This information is not provided
	*/
	UPROPERTY(BlueprintReadOnly, Category = "AndroidGoodies|Hardware")
	FString VenueName;
	
	/**
	* Not used if the AP bandwidth is 20 MHz If the AP use 40, 80 or 160 MHz, this is the center frequency (in MHz) if the AP use 80 + 80 MHz, this is the center frequency of the first segment (in MHz)
	*/
	UPROPERTY(BlueprintReadOnly, Category = "AndroidGoodies|Hardware")
	int CenterFreq0;
	
	/**
	* Only used if the AP bandwidth is 80 + 80 MHz if the AP use 80 + 80 MHz, this is the center frequency of the second segment (in MHz)
	*/
	UPROPERTY(BlueprintReadOnly, Category = "AndroidGoodies|Hardware")
	int CenterFreq1;
	
	/**
	* AP Channel bandwidth; 
	* One of CHANNEL_WIDTH_20MHZ, CHANNEL_WIDTH_40MHZ, CHANNEL_WIDTH_80MHZ, CHANNEL_WIDTH_160MHZ or CHANNEL_WIDTH_80MHZ_PLUS_MHZ.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "AndroidGoodies|Hardware")
	int ChannelWidth;
	
	/**
	* The primary 20 MHz frequency (in MHz) of the channel over which the client is communicating with the access point.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "AndroidGoodies|Hardware")
	int Frequency;
	
	/**
	* The detected signal level in dBm, also known as the RSSI.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "AndroidGoodies|Hardware")
	int Level;
	
	/**
	* Timestamp in microseconds (since boot) when this result was last seen.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "AndroidGoodies|Hardware")
	int64 Timestamp;
};