// Copyright (c) 2022 Nineva Studios

#pragma once

#include "FGAuthCredentials.h"
#include "FGFirebaseUserInfo.h"

class IFirebaseUser;
class UFGGetTokenResult;

#include "FGFirebaseUser.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnUserVoidTaskCompleted, FString, uid);

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnUserUpdated, UFGFirebaseUser*, user);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnUserOperationError, FString, uid, FString, error);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnUserStringTaskCompleted, FString, uid, FString, result);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetTokenResultCompleted, FString, uid, UFGGetTokenResult*, result);

UCLASS(BlueprintType)
class FIREBASEGOODIES_API UFGFirebaseUser : public UFGFirebaseUserInfo
{
	GENERATED_BODY()

public:
	virtual ~UFGFirebaseUser() override;

	/**
	* @return true if user signed in anonymously.
	*/
	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Auth|Firebase User")
	bool IsAnonymous() const;

	/**
	 * If the user's email is verified
	 */
	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Auth|Firebase User")
	bool IsEmailVerified() const;

	/**
	* Convenience method to check if the native iOS/Android user object is valid.
	*/
	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Auth|Firebase User")
	bool IsUserValid() const;

	/**
	* Delete the user account.
	*
	* @param OnSuccess - callback to be invoked upon successful user deletion.
	* @param OnError - callback to be invoked when user deletion failed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Auth|Firebase User", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	void Delete(const FOnUserVoidTaskCompleted& OnSuccess, const FOnUserOperationError& OnError);

	/**
	* Link the user with the given 3rd party credentials.
	*
	* @param Credentials - credentials to link with.
	* @param OnSuccess - callback to be invoked upon successful linking.
	* @param OnError - callback to be invoked when linking failed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Auth|Firebase User", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	void LinkWithCredentials(UFGAuthCredentials* Credentials, const FOnUserUpdated& OnSuccess, const FOnUserOperationError& OnError);

	/**
	* Convenience function for ReauthenticateAndRetrieveData that discards the returned UFGFirebaseUser data.
	*
	* @param Credentials - credentials to reauthenticate with.
	* @param OnSuccess - callback to be invoked upon successful reauthentication.
	* @param OnError - callback to be invoked when reauthentication failed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Auth|Firebase User", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	void Reauthenticate(UFGAuthCredentials* Credentials, const FOnUserVoidTaskCompleted& OnSuccess, const FOnUserOperationError& OnError);

	/**
	* Refresh the data for this user.
	*
	* @param OnSuccess - callback to be invoked upon successful refresh.
	* @param OnError - callback to be invoked when refresh failed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Auth|Firebase User", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	void Reload(const FOnUserVoidTaskCompleted& OnSuccess, const FOnUserOperationError& OnError);

	/**
	* Initiate email verification for the user.
	*
	* @param OnSuccess - callback to be invoked upon successful email sending.
	* @param OnError - callback to be invoked when task failed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Auth|Firebase User", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	void SendEmailVerification(const FOnUserVoidTaskCompleted& OnSuccess, const FOnUserOperationError& OnError);

	/**
	* Unlink the current user from the provider specified.
	*
	* @param Provider - provider ID to unlink (For example, "Facebook").
	* @param OnSuccess - callback to be invoked upon successful unlinking.
	* @param OnError - callback to be invoked when task failed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Auth|Firebase User", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	void UnlinkProvider(const FString& Provider, const FOnUserUpdated& OnSuccess, const FOnUserOperationError& OnError);

	/**
	* Set the email address for the user.
	*
	* @param Email - new email address.
	* @param OnSuccess - callback to be invoked upon successful change.
	* @param OnError - callback to be invoked when task failed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Auth|Firebase User", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	void UpdateEmail(const FString& Email, const FOnUserVoidTaskCompleted& OnSuccess, const FOnUserOperationError& OnError);

	/**
	* Set the password for the user.
	*
	* @param Password - new password.
	* @param OnSuccess - callback to be invoked upon successful change.
	* @param OnError - callback to be invoked when task failed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Auth|Firebase User", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	void UpdatePassword(const FString& Password, const FOnUserVoidTaskCompleted& OnSuccess, const FOnUserOperationError& OnError);

	/**
	* Set the phone number for the user.
	*
	* @param Credentials - phone number credentials. Can be obtained after successful VerifyPhoneNumber task.
	* @param OnSuccess - callback to be invoked upon successful change.
	* @param OnError - callback to be invoked when task failed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Auth|Firebase User", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	void UpdatePhoneNumber(UFGAuthCredentials* Credentials, const FOnUserVoidTaskCompleted& OnSuccess, const FOnUserOperationError& OnError);

	/**
	* Update a subset of user profile information.
	*
	* @param DisplayName - User display name
	* @param AvatarUrl - URL to user avatar
	* @param OnSuccess - callback to be invoked upon successful change.
	* @param OnError - callback to be invoked when task failed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Auth|Firebase User", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	void UpdateProfile(const FString& DisplayName, const FString& AvatarUrl, const FOnUserVoidTaskCompleted& OnSuccess,
	                   const FOnUserOperationError& OnError);

	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Auth|Firebase User", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	void GetToken(bool ForceRefresh, const FOnUserStringTaskCompleted& OnSuccess, const FOnUserOperationError& OnError);

	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Auth|Firebase User")
	TArray<UFGFirebaseUserInfo*> GetProviderData() const;
	
	/**
	* Get ID token data. Works only on IOS and Android. For desktop platforms use GetToken.
	*
	* @param ForceRefresh - Whether to force generation of the new token data..
	* @param OnSuccess - callback to be invoked with the token data.
	* @param OnError - callback to be invoked when task failed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Auth|Firebase User", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	void GetIdToken(bool ForceRefresh, const FOnGetTokenResultCompleted& OnSuccess, const FOnUserOperationError& OnError);

	static FOnUserVoidTaskCompleted OnUserVoidTaskCompletedCallback;
	static FOnUserUpdated OnUserUpdatedCallback;
	static FOnUserOperationError OnUserOperationErrorCallback;
	static FOnUserStringTaskCompleted OnUserStringTaskCompletedCallback;
	static FOnGetTokenResultCompleted OnGetTokenResultCompletedCallback;

	void Init(const TSharedPtr<IFirebaseUser>& User);

private:
	TSharedPtr<IFirebaseUser> UserImpl;
};
