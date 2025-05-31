// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Auth/FGAuthCredentials.h"
#include "Auth/FGAuthLibrary.h"
#include "Database/FGDatabaseRef.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "FirebaseIdentity_Subsystem.generated.h"

class UFGFirebaseUser;
class UFirebaseData_SaveGame;

/**
 * Enum defining different authentication actions
 */
UENUM(BlueprintType)
enum class EAuthAction : uint8
{
    Signup,
    SignIn,
    SignInWithCredential
};

/**
 * Structure containing user profile data
 */
USTRUCT(BlueprintType)
struct FUserProfile
{
    GENERATED_BODY()

    /** User's display name */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserProfile")
    FString Name;

    /** Unique user identifier */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserProfile")
    int32 UserID;

    /** URL to user's avatar image */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserProfile")
    FString AvatarURL;
};

/** Delegate for login success events */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoginSuccess, UFGFirebaseUser*, User);

/** Delegate for profile received events */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserProfileReceived, FUserProfile, Profile, FString, Message);

/** Delegate for authentication response events */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAuthResponse, bool, bWasSuccessful, UFGFirebaseUser*, User, FString, Message);

/**
 * Subsystem for managing Firebase authentication and user identity
 */
UCLASS()
class ONLINESUBSYSTEM_FIREBASE_API UFirebaseIdentity_Subsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    /** Called when user successfully logs in */
    UPROPERTY(BlueprintAssignable, Category = "Firebase")
    FOnLoginSuccess OnLoginSuccess;

    /** Currently logged in user */
    UPROPERTY(BlueprintReadOnly, Category = "Firebase")
    UFGFirebaseUser* CurrentUser;

    /** Currently logged in user's ID */
    UPROPERTY(BlueprintReadOnly, Category = "Firebase")
    FString CurrentUID;

    /**
     * Checks if a user profile exists in local storage
     * @param UID - User ID to check
     * @param Profile - Output parameter for found profile
     * @return True if profile exists
     */
    UFUNCTION(BlueprintCallable, Category = "UserProfile")
    static bool IsProfileExistInLocal(const FString& UID, FUserProfile& Profile);

    /**
     * Saves user profile to local storage
     * @param UID - User ID to save under
     * @param Profile - Profile data to save
     * @return True if save was successful
     */
    UFUNCTION(BlueprintCallable, Category = "UserProfile")
    static bool SaveProfileToLocal(const FString& UID, const FUserProfile& Profile);

private:
    /** Internal handler for login success */
    UFUNCTION()
    void OnLoginSuccessInternal(UFGFirebaseUser* User);
};

/**
 * Async action for retrieving user profiles
 */
UCLASS()
class UGetProfileAsync : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    /**
     * Creates an async action to get user profile
     * @param WorldContextObject - World context
     * @param UID - User ID to get profile for
     */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"))
    static UGetProfileAsync* GetProfile(UObject* WorldContextObject, const FString& UID);

    virtual void Activate() override;

    /** Called when profile is successfully retrieved */
    UPROPERTY(BlueprintAssignable)
    FOnUserProfileReceived OnSuccess;

    /** Called when profile retrieval fails */
    UPROPERTY(BlueprintAssignable)
    FOnUserProfileReceived OnError;

private:
    /** Handles successful database response */
    UFUNCTION()
    void OnDataReceived(UFGDataSnapshot* Data);

    /** Handles cancelled database operation */
    UFUNCTION()
    void OnOperationCancelled(int32 ErrorCode, const FString ErrorMessage);

    FString TargetUID;
    FUserProfile Profile;
    FOnDataChangedDelegate OnDataChangedDelegate;
    FOnCancelledDelegate OnCancelledDelegate;
};

/**
 * Async action for authentication operations
 */
UCLASS()
class UFirebaseAuthAsync : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    /**
     * Creates an async action for email/password sign in
     * @param WorldContextObject - World context
     * @param IdentitySubsystem - Identity subsystem instance
     * @param Email - User's email
     * @param Password - User's password
     */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"))
    static UFirebaseAuthAsync* SignInWithEmailAndPassword(UObject* WorldContextObject, UFirebaseIdentity_Subsystem* IdentitySubsystem, const FString& Email, const FString& Password);

    /**
     * Creates an async action for email/password sign up
     * @param WorldContextObject - World context
     * @param IdentitySubsystem - Identity subsystem instance
     * @param Email - User's email
     * @param Password - User's password
     */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"))
    static UFirebaseAuthAsync* SignUpWithEmailAndPassword(UObject* WorldContextObject, UFirebaseIdentity_Subsystem* IdentitySubsystem, const FString& Email, const FString& Password);

    /**
     * Creates an async action for credential sign in
     * @param WorldContextObject - World context
     * @param IdentitySubsystem - Identity subsystem instance
     * @param Credentials - Authentication credentials
     */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"))
    static UFirebaseAuthAsync* SignInWithCredential(UObject* WorldContextObject, UFirebaseIdentity_Subsystem* IdentitySubsystem, UFGAuthCredentials* Credentials);

    virtual void Activate() override;

    /** Called with authentication result */
    UPROPERTY(BlueprintAssignable)
    FAuthResponse OnAuthResponse;

private:
    /** Handles successful authentication */
    UFUNCTION()
    void HandleSuccess(UFGFirebaseUser* User);

    /** Handles authentication error */
    UFUNCTION()
    void HandleError(const FString ErrorMessage);

    FString Email;
    FString Password;
    UFirebaseIdentity_Subsystem* FirebaseIdentity;
    UFGAuthCredentials* Credentials;
    EAuthAction AuthAction;
};