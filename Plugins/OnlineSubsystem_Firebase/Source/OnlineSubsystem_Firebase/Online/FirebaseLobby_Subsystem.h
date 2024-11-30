// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Database/FGDatabaseRef.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "FirebaseDatabase_Subsystem.h"

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FirebaseLobby_Subsystem.generated.h"

USTRUCT(BlueprintType)
struct FCarInputData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	AActor* CarActor;          // Reference to the car actor
	UPROPERTY(BlueprintReadWrite)
	int32 StartPosition;       // Starting position of the car
	UPROPERTY(BlueprintReadWrite)
	int32 FinishRank;          // Finish rank of the car
	UPROPERTY(BlueprintReadWrite)
	float GameTime;            // Game time for the car
};

USTRUCT(BlueprintType)
struct FCarOutputData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	AActor* CarActor;          // Reference to the car actor
	UPROPERTY(BlueprintReadWrite)
	int32 SplineIndex;         // Assigned spline index (0-3)
	UPROPERTY(BlueprintReadWrite)
	float DistanceAlongSpline; // Distance traveled along the spline
};

USTRUCT(BlueprintType)
struct FAllCarsOutput
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<FCarOutputData> CarsData; // Array of all cars at this game time
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnComplated ,UFGDataSnapshot*, Snapshot,FString ,Message);

/**
 * 
 */
UCLASS()
class ONLINESUBSYSTEM_FIREBASE_API UFirebaseLobby_Subsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Race")
	static void CalculateRaceData(const TMap<AActor*, FCarInputData>& CarInputMap, float RaceEndTime, float SplineLength, TMap<float, FAllCarsOutput>& OutRaceData);


	// UFUNCTION(BlueprintCallable,BlueprintPure, Category="Database")
	// UFGDatabaseRef* GetDatabase_ref(const FString UserID);
	//
	// UFUNCTION(BlueprintCallable,BlueprintPure, Category="Database")
	// UFGDatabaseRef* GetLobbyStatusDatabaseRef(const FString UserID);
	//
	// UFUNCTION(BlueprintCallable,BlueprintPure, Category="Database")
	// UFGDatabaseRef* LobbyStatus(const FString UserID);
	//
	// UFUNCTION(BlueprintCallable, Category="Database")
	// void GetLobbyValue(const UFGDataSnapshot* Data, bool& InLobby, int32& LobbyID);
	//
	//




	

protected:

	

	
};


// UCLASS()
// class ULobbyStatus : public UBlueprintAsyncActionBase
// {
// 	GENERATED_BODY()
//
// 	// This function will be called to start the async task
// 	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
// 	static ULobbyStatus* LobbyStatus(UFirebaseLobby_Subsystem* Subsystem, FString UserID);
//
// 	// Function to activate the async task
// 	virtual void Activate() override;
//
//
// 	UFUNCTION()
// 	void OnDataChanged(UFGDataSnapshot* Data);
//
// 	
//
// private:
// 	// Internal storage for input and output values
// 	UPROPERTY()
// 	UFGDatabaseRef* DatabaseRef;
//
// 	UPROPERTY()
// 	UFGDataSnapshot* Data;
//
// 	// Make Subsystem a pointer
// 	UPROPERTY()
// 	UFirebaseLobby_Subsystem* Subsystem;
//
// 	UPROPERTY()
// 	FString UserID;
//
//
// 	// Delegates for completion and cancellation
// 	UPROPERTY()
// 	FOnDataChangedDelegate OnCompleted;
//
// 	UPROPERTY()
// 	FOnCancelledDelegate OnCancelled;
// 	
// };
//
//
//
//
//
// UCLASS()
// class UCreateLobby : public UBlueprintAsyncActionBase
// {
// 	GENERATED_BODY()
//
// 	// This function will be called to start the async task
// 	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
// 	static UCreateLobby* CreateLobby(UFirebaseLobby_Subsystem* Subsystem, FString UserID);
//
// 	// Function to activate the async task
// 	virtual void Activate() override;
//
// 	// Delegate to handle completion
// 	UPROPERTY(BlueprintAssignable)
// 	FOnComplated OnSuccess;
//
// 	UPROPERTY(BlueprintAssignable)
// 	FOnComplated OnCancled;
//
// 	UFUNCTION()
// 	void OnDataChanged(UFGDataSnapshot* Data);
//
// 	UFUNCTION()
// 	void OnCancelledOperation(int ErrorCode, FString ErrorMessage);
//
// 	// Function to initiate the lobby creation process
// 	UFUNCTION(BlueprintCallable)
// 	void CheckLobbyAlreadyExist();
//
//
//
// private:
// 	// Internal storage for input and output values
// 	UPROPERTY()
// 	UFGDatabaseRef* DatabaseRef;
//
// 	// Make Subsystem a pointer
// 	UPROPERTY()
// 	UFirebaseLobby_Subsystem* Subsystem;
//
// 	UPROPERTY()
// 	UFGDataSnapshot* DataSnapshot;
//
// 	UPROPERTY()
// 	FString UserID;
//
// 	UPROPERTY()
// 	int32 ErrorCode;
//
// 	UPROPERTY()
// 	FString ErrorMessage;
//
// 	UPROPERTY()
// 	int32 LobbyID;
//
// 	UPROPERTY()
// 	FString LobbyKey = "IsInLobby";
//
// 	
//
// 	// Delegates for completion and cancellation
// 	UPROPERTY()
// 	FOnDataChangedDelegate OnCompleted;
//
// 	UPROPERTY()
// 	FOnCancelledDelegate OnCancelled;
//
// 	
//
// 	// Function to join an existing lobby with a given Lobby ID
// 	void JoinLobby(UFGDataSnapshot* Data);
// };
