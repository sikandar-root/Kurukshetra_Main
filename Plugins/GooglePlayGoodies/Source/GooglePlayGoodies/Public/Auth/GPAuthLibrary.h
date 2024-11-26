// Copyright (c) 2020 Nineva Studios

#pragma once

#include "Auth/GPPermissionFlags.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "GPAuthLibrary.generated.h"

class UGPAccount;
class UGPPlayer;

UCLASS()
class GOOGLEPLAYGOODIES_API UGPAuthLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_DELEGATE(FGPDelegate);
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FGPLoginDelegate, UGPAccount*, Account, UGPPlayer*, Player);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGPErrorDelegate, FString, ErrorMessage);

	/**
	* Log in via Google Play.
	*
	* @param bDoSilentLogin - If set to true the user will be silently logged in with his default account, UI will appear only if silent login fails
	* @param OnLoginSuccess - Called in case of successful login
	* @param OnLoginCancel - Called if the login process is canceled by the user
	* @param OnLoginError - Called in case an error occurs
	* @param PermissionFlags - Specify which permissions should be requested upon login
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Auth", meta = (AutoCreateRefTerm = "OnLoginSuccess, OnLoginCancel, OnLoginError, PermissionFlags", AdvancedDisplay = "PermissionFlags"))
	static void Login(bool bDoSilentLogin, const FGPLoginDelegate& OnLoginSuccess, const FGPDelegate& OnLoginCancel, 
		const FGPErrorDelegate& OnLoginError, const FGPPermissionFlags& PermissionFlags);

	/**
	* Log out the current user.
	*
	* @param OnLogoutSuccess - Called in case of successful logout
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Auth", meta = (AutoCreateRefTerm = "OnLogoutSuccess"))
	static void Logout(const FGPDelegate& OnLogoutSuccess);

	/**
	* Log out the current user and revokes all granted permission.
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Auth")
	static void RevokeAccess();

	/**
	* Check if a user is logged in.
	*
	* @returns True if a user is logged in, false otherwise
	*/
	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Auth")
	static bool IsLoggedIn();

	static FGPLoginDelegate OnLoginSuccessDelegate;
	static FGPDelegate OnLoginCancelDelegate;
	static FGPDelegate OnLogoutSuccessDelegate;
	static FGPErrorDelegate OnLoginErrorDelegate;
};
