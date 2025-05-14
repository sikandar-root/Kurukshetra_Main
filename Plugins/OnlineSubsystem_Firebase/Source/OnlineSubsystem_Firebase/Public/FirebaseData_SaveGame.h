// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "OnlineSubsystem_Firebase/Online/FirebaseIdentity_Subsystem.h"
#include "FirebaseData_SaveGame.generated.h"



/**
 * 
 */
UCLASS()
class ONLINESUBSYSTEM_FIREBASE_API UFirebaseData_SaveGame : public USaveGame
{
	GENERATED_BODY()

	public:
	//User profile to be saved
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame")
	FUserProfile UserProfile;

	// // Constructor
	// UFirebaseData_SaveGame();
	
};
