#pragma once

#include "ActionCodeSettings.generated.h"

USTRUCT(BlueprintType)
struct FIREBASEGOODIES_API FActionCodeSettings
{
	GENERATED_BODY()

	/**
	 * The default is false.
	 */
	UPROPERTY(BlueprintReadWrite, Category = "Firebase Goodies|Auth")
	bool bCanHandleCodeInApp = false;

	/**
	 * To be used if the email link that is sent might be opened on an iOS device.
	 */
	UPROPERTY(BlueprintReadWrite, Category = "Firebase Goodies|Auth")
	FString IosBundle = "";

	UPROPERTY(BlueprintReadWrite, Category = "Firebase Goodies|Auth")
	FString AndroidPackageName = "";

	/**
	 * Sets the optional FDL domain, overriding the default FDL domain that would be used.
	 */
	UPROPERTY(BlueprintReadWrite, Category = "Firebase Goodies|Auth")
	FString DynamicLinkDomain = "";

	/**
	 * Sets the URL, which has different meanings in different contexts.
	 */
	UPROPERTY(BlueprintReadWrite, Category = "Firebase Goodies|Auth")
	FString Url = "";

	UPROPERTY(BlueprintReadWrite, Category = "Firebase Goodies|Auth")
	bool bInstallIfNotAvailable = false;

	/**
	 * If the installed app is an older version, the user is taken to the Play Store to upgrade the app.
	 */
	UPROPERTY(BlueprintReadWrite, Category = "Firebase Goodies|Auth")
	FString MinimumAppVersion = "";
};
