// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Database/FGDatabaseRef.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FirebaseDatabase_Subsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnSuccess, bool , IsSuccess, UFGDataSnapshot*, Snapshot,FString ,Message);
/**
 * 
 */
UCLASS()
class ONLINESUBSYSTEM_FIREBASE_API UFirebaseDatabase_Subsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 LobbyID;
	
	
	
};



UCLASS()
class USetValue_Async : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// This function will be called to start the async task
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static USetValue_Async* SetValueWithResponce(UFGDatabaseRef* DatabaseRef,
		const FFGValueVariant& Value );

	// Function to activate the async task
	virtual void Activate() override;

	// Delegate to handle completion
	/**
	 * 
	 */

	UPROPERTY(BlueprintAssignable)
	FOnSuccess On_Completed;
	

	UFUNCTION()
	void OnDataChanged(UFGDataSnapshot* Data);

	UFUNCTION()
	void OnCancelledOperation(int ErrorCode, FString ErrorMessage);

private:
	// Internal storage for input and output values
	UFGDatabaseRef* DatabaseRef;
	FFGValueVariant Values;
	FFGValueVariant Prioritys;
	UFGDataSnapshot* DataSnapshot;

	UPROPERTY()
	FOnDataChangedDelegate OnCompleted;

	// Delegate to handle cancellation
	UPROPERTY()
	FOnCancelledDelegate OnCancelled;
};



UCLASS()
class UUpdateChildren_Async : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnSuccess On_Completed;

	// This function will be called to start the async task
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UUpdateChildren_Async* UpdateChildrenWithResponce(UFGDatabaseRef* DatabaseRef,
	 const TMap<FString, FFGValueVariant>& Value );

	// Function to activate the async task
	virtual void Activate() override;

	UFUNCTION()
	void OnDataChanged(EChileEventType EventType, UFGDataSnapshot* Data, FString PreviousChildName);

	UFUNCTION()
	void OnCancelledOperation(int ErrorCode, FString ErrorMessage);

private:
	// Internal storage for input and output values
	UFGDatabaseRef* DatabaseRef;
	TMap<FString, FFGValueVariant> Values;
	UFGDataSnapshot* DataSnapshot;

	UPROPERTY()
	FOnChildEventDelegate OnCompleted;

	// Delegate to handle cancellation
	UPROPERTY()
	FOnCancelledDelegate OnCancelled;
	
};


UCLASS()
class UListenValue_Async : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FOnSuccess On_Completed;

	// This function will be called to start the async task
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UListenValue_Async* ActivateValueListner(UFGDatabaseRef* DatabaseRef);

	// Function to activate the async task
	virtual void Activate() override;

	UFUNCTION()
	void OnDataChanged(UFGDataSnapshot* Data);

	UFUNCTION()
	void OnCancelledOperation(int ErrorCode, FString ErrorMessage);

private:
	// Internal storage for input and output values
	UFGDatabaseRef* DatabaseRef;
	UFGDataSnapshot* DataSnapshot;

	UPROPERTY()
	FOnDataChangedDelegate OnCompleted;

	// Delegate to handle cancellation
	UPROPERTY()
	FOnCancelledDelegate OnCancelled;
};


UCLASS()
class UListenChildren_Async : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FOnSuccess On_Completed;

	// This function will be called to start the async task
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UListenChildren_Async* ActivateChildListner(UFGDatabaseRef* DatabaseRef);

	// Function to activate the async task
	virtual void Activate() override;

	UFUNCTION()
	void OnDataChanged(EChileEventType EventType, UFGDataSnapshot* Data, FString PreviousChildName);

	UFUNCTION()
	void OnCancelledOperation(int ErrorCode, FString ErrorMessage);

private:
	// Internal storage for input and output values
	UFGDatabaseRef* DatabaseRef;
	UFGDataSnapshot* DataSnapshot;

	UPROPERTY()
	FOnChildEventDelegate OnCompleted;

	// Delegate to handle cancellation
	UPROPERTY()
	FOnCancelledDelegate OnCancelled;
};


UCLASS()
class UGetValue_Async : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FOnSuccess On_Completed;

	// This function will be called to start the async task
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UGetValue_Async* GetValue_Async(UFGDatabaseRef* DatabaseRef);

	// Function to activate the async task
	virtual void Activate() override;

	UFUNCTION()
	void OnDataChanged(UFGDataSnapshot* Data);

	UFUNCTION()
	void OnCancelledOperation(int ErrorCode, FString ErrorMessage);

private:
	// Internal storage for input and output values
	UFGDatabaseRef* DatabaseRef;
	UFGDataSnapshot* DataSnapshot;

	UPROPERTY()
	FOnDataChangedDelegate OnCompleted;

	// Delegate to handle cancellation
	UPROPERTY()
	FOnCancelledDelegate OnCancelled;
};



