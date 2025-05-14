// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "FirebaseData_SaveGame.h"
#include "Database/FGDatabaseRef.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FirebaseIdentity_Subsystem.generated.h"

// Forward declaration if necessary
//struct FUserProfile;

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRecivedUserProfile, bool, IsSuccess, FUserProfile, Profile);


USTRUCT(BlueprintType)
struct FUserProfile
{
	GENERATED_BODY()

	// User's name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserProfile")
	FString Name;

	// User's unique ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserProfile")
	int32 UserID;

	// User's profile picture (dynamic texture)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserProfile")
	FString AvatarURL;
	
};

/**
 * 
 */

UCLASS()
class ONLINESUBSYSTEM_FIREBASE_API UFirebaseIdentity_Subsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// User profile to be saved
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame")
	FUserProfile UserProfile;

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	static bool IsProfileExistInLocal(const FString UID, FUserProfile& Profile );

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	static bool SaveProfileToLocal(FString UID, FUserProfile Profile );

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	static bool IsProfileExistInMemory(const FString UID, FUserProfile& Profile );

protected:

private:
	// UPROPERTY()
	// UFirebaseData_SaveGame* SaveGame;
	
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRecivedUserProfile, FUserProfile, Profile,FString, Message);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDownloadImageDelegate, UTexture2DDynamic*, Texture);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLoadImage, UObject*, Texture);



// GetProfile Friend Request.
/**
 * 
 *
 *
**/

UCLASS()
class UGetProfile : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// This function will be called to Accept the friend request
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UGetProfile* GetProfile(const FString UID );

	// Function to activate the async task
	virtual void Activate() override;

private:
	// Internal storage for input and output values
	
	//UFGDatabaseRef* DatabaseRef;
	FString UID;
	FUserProfile Profile;
	FFGValueVariant Values;
	
	
	// Delegate to handle completion

	UPROPERTY(BlueprintAssignable)
	FOnRecivedUserProfile On_Sucess;

	UPROPERTY(BlueprintAssignable)
	FOnRecivedUserProfile On_Error;

	UPROPERTY()
	FOnDataChangedDelegate OnCompleted;

	// Delegate to handle cancellation
	UPROPERTY()
	FOnCancelledDelegate OnCancelled;

	UFUNCTION()
	void OnDataRecived(UFGDataSnapshot* Data);

	UFUNCTION()
	void OnCancelledOperation(int ErrorCode, FString ErrorMessage);
	
	
};


//UCLASS()
//class ULoadImage_GIF : public UBlueprintAsyncActionBase
//{
//	GENERATED_BODY()
//
//public:
//	// This function will be called to Accept the friend request
//	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
//	static ULoadImage_GIF* LoadImage_GIF(const FString URL );
//
//	// Function to activate the async task
//	virtual void Activate() override;
//
//	
//
//private:
//	// Internal storage for input and output values
//	
//	//UFGDatabaseRef* DatabaseRef;
//	FString URL;
//	FUserProfile Profile;
//	FFGValueVariant Values;
//	UObject Data;
//	
//	
//	// Delegate to handle completion
//
//	UPROPERTY(BlueprintAssignable)
//	FLoadImage On_Sucess;
//
//	UPROPERTY(BlueprintAssignable)
//	FLoadImage On_Error;
//
//	UPROPERTY()
//	FOnDataChangedDelegate OnCompleted;
//
//	// Delegate to handle cancellation
//	UPROPERTY()
//	FOnDataChangedDelegate OnCancelled;
//
//	/*UFUNCTION()
//	void OnDownloadedImage(UAnimatedTexture2D* Texture);*/
//
//	UFUNCTION()
//	void OnFailed(UTexture2DDynamic* Texture);
//	
//	
//};