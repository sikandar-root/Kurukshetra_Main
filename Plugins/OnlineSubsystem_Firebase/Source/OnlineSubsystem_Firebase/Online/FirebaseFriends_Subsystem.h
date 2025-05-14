// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Database/FGDatabaseRef.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FirebaseFriends_Subsystem.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EGetExes : uint8
{
	Then,
	Success,
	Failed
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOntest, bool , IsSuccess, FString ,FriendUID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSucessGetFriendLists, const TArray<FString>&, Friends, bool,Result);



UCLASS()
class ONLINESUBSYSTEM_FIREBASE_API UFirebaseFriends_Subsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UPROPERTY()
	TArray<FString> Friends;

	UFUNCTION(BlueprintCallable, Category = "Firebase")
	static void SetNetID( APlayerState* playerstete, FUniqueNetIdRepl Ptr);

	UFUNCTION(BlueprintCallable, Category = "Firebase")
	FUniqueNetIdRepl CreateUniqueIdFromString(const FString& StringId);

};



UCLASS()
class UGetFriendLists : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FOnSucessGetFriendLists On_Completed;

	// This function will be called to start the async task
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UGetFriendLists* Get_Friend_List(UFirebaseFriends_Subsystem* Subsystem, FString UID);

	// Function to activate the async task
	virtual void Activate() override;

	UFUNCTION()
	void OnDataRecived(UFGDataSnapshot* Data);

	UFUNCTION()
	void OnCancelledOperation(int ErrorCode, FString ErrorMessage);

private:
	// Internal storage for input and output values
	UFirebaseFriends_Subsystem* Subsystem;
	FString UID;
	

	UPROPERTY()
	FOnDataChangedDelegate OnCompleted;

	// Delegate to handle cancellation
	UPROPERTY()
	FOnCancelledDelegate OnCancelled;
};


UCLASS()
class UFindUser : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// This function will be called to start the async task
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UFindUser* FindUser(
		const FString Value );

	// Function to activate the async task
	virtual void Activate() override;

	// Delegate to handle completion
	/**
	 * 
	 */

	UPROPERTY(BlueprintAssignable)
	FOntest On_Completed;

	UPROPERTY()
	FOnDataChangedDelegate OnRecived;
	

	// UFUNCTION()
	// void OnDataChanged(UFGDataSnapshot* Data);

	UFUNCTION()
	void OnCancelledOperation(int ErrorCode, FString ErrorMessage);

	UFUNCTION()
	void OnRecivedOperation(UFGDataSnapshot* Data);

private:
	// Internal storage for input and output values
	UFGDatabaseRef* DatabaseRef;
	FFGValueVariant Values;
	UFGDataSnapshot* DataSnapshot;

	UPROPERTY()
	FOnDataChangedDelegate OnCompleted;

	// Delegate to handle cancellation
	UPROPERTY()
	FOnCancelledDelegate OnCancelled;
};







// Send Friend Request.
/**
 *
 *
 *
**/

UCLASS()
class UsendFriendRequest : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// This function will be called to Send the friend request
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UsendFriendRequest* SendFriendRequest(
		const FString FriendID, const FString UID );

	// Function to activate the async task
	virtual void Activate() override;

private:
	// Internal storage for input and output values
	
	UFGDatabaseRef* DatabaseRef;
	FFGValueVariant Values;
	UFGDataSnapshot* DataSnapshot;
	FString FriendID;
	FString UID;
	
	

	// Delegate to handle completion

	UPROPERTY(BlueprintAssignable)
	FOntest On_Completed;

	UPROPERTY()
	FOnDataChangedDelegate OnFoundPlayerData;

	// Delegate to handle cancellation
	UPROPERTY()
	FOnCancelledDelegate OnCancelled;
	

	UFUNCTION()
	void FoundedPlayerProfile(UFGDataSnapshot* Data);

	UFUNCTION()
	TMap<FString,FFGValueVariant> GetDatabaseValue( FString UIDParam,  FString FriendUID, bool IsSender);

	UFUNCTION()
	void SetValueDatabase(FString UIDparam, FString FriendUIDparam);
};




// Accept Friend Request.
/**
 *
 *
 *
**/

UCLASS()
class UAcceptFriendRequest : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// This function will be called to Accept the friend request
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UAcceptFriendRequest* AcceptFriendRequest(
		const FString FriendUID, const FString UID );

	// Function to activate the async task
	virtual void Activate() override;

private:
	// Internal storage for input and output values
	
	//UFGDatabaseRef* DatabaseRef;
	FString FriendUID;
	FString UID;
	
	
	// Delegate to handle completion

	UPROPERTY(BlueprintAssignable)
	FOntest On_Completed;
	

	UFUNCTION()
	TMap<FString,FFGValueVariant> GetDatabaseValue( FString UIDParam,  FString FriendUIDParam, bool IsFriend);

	
};



// Reject / Widraw Friend Request.
/**
 *
 *
 *
**/

UCLASS()
class URejectFriendRequest : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// This function will be called to Accept the friend request
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static URejectFriendRequest* RejectFriendRequest(
		const FString FriendUID, const FString UID );

	// Function to activate the async task
	virtual void Activate() override;

private:
	// Internal storage for input and output values
	
	//UFGDatabaseRef* DatabaseRef;
	FString FriendUID;
	FString UID;
	
	
	// Delegate to handle completion

	UPROPERTY(BlueprintAssignable)
	FOntest On_Completed;
	
	
};