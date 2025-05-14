// Fill out your copyright notice in the Description page of Project Settings.


#include "FirebaseIdentity_Subsystem.h"

//#include <rapidjson/document.h>

#include "FirebaseData_SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "FirebaseDatabasePath_Library.h"
#include "CloudMessaging/FGRemoteMessage.h"
#include "Database/FGDataSnapshot.h"
#include "Common/FGValueVariantAccess.h"
#include "Runtime/UMG/Public/Blueprint/AsyncTaskDownloadImage.h"
//#include "RuntimeImageLoader/Public/RuntimeGifReader.h"


UPROPERTY()
UFirebaseData_SaveGame* SaveGame;


void UFirebaseIdentity_Subsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	// // Create a save game object
	// UFirebaseData_SaveGame* SaveGameInstance = Cast<UFirebaseData_SaveGame>(UGameplayStatics::CreateSaveGameObject(UFirebaseData_SaveGame::StaticClass()));
	// SaveGame = SaveGameInstance;
	//
	// FString slot;
	//
	// bool Test = UGameplayStatics::DoesSaveGameExist(slot,0);
	// if (Test)
	// {
	// 	SaveGame = Cast<UFirebaseData_SaveGame>(UGameplayStatics::LoadGameFromSlot(slot,0));
	// 	SaveGame->UserProfile;
	// }
	
}

bool UFirebaseIdentity_Subsystem::IsProfileExistInLocal(const FString UID, FUserProfile& Profile)
{
	if (UGameplayStatics::DoesSaveGameExist(UID,0))
	{
		SaveGame = Cast<UFirebaseData_SaveGame>(UGameplayStatics::LoadGameFromSlot(UID,0));
		Profile=SaveGame->UserProfile;
		return true;
	}
	
		return false;
	
}

bool UFirebaseIdentity_Subsystem::SaveProfileToLocal(FString UID, FUserProfile Profile)
{
	// Create a save game object
	UFirebaseData_SaveGame* SaveGameInstance = Cast<UFirebaseData_SaveGame>(UGameplayStatics::CreateSaveGameObject(UFirebaseData_SaveGame::StaticClass()));
	SaveGameInstance->UserProfile=Profile;
	bool Result = UGameplayStatics::SaveGameToSlot(SaveGameInstance,UID,0);
	return Result;
	
}

bool UFirebaseIdentity_Subsystem::IsProfileExistInMemory(const FString UID, FUserProfile& Profile)
{
	if (UGameplayStatics::DoesSaveGameExist(UID, 0))
	{
		
	}
	return false;
}

// Async function to retrieve a user's profile
UGetProfile* UGetProfile::GetProfile(const FString UID)
{
	// Create an async action object
	UGetProfile* AsyncAction = NewObject<UGetProfile>();
	UE_LOG(LogTemp, Log, TEXT("Async action created"));

	// Store the provided UID for use in other methods
	AsyncAction->UID = UID;

	// Return the async function object so it can be activated
	return AsyncAction;
}

void UGetProfile::Activate()
{
	// Construct the save slot name using the UID
	const FString SlotName = UID + TEXT("Profile");

	// Check if a saved game file exists locally
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		// Load the saved profile from the save slot
		UFirebaseData_SaveGame* SaveGameInstance = Cast<UFirebaseData_SaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
		if (SaveGameInstance)
		{
			Profile = SaveGameInstance->UserProfile;
			On_Sucess.Broadcast(Profile,"Success");
			return;
		}
	}

	// If no local save exists, fetch data from the Firebase database
	OnCancelled.BindDynamic(this, &UGetProfile::OnCancelledOperation);
	OnCompleted.BindDynamic(this, &UGetProfile::OnDataRecived);

	UFGDatabaseRef* Database = UFirebaseDatabasePath_Library::PlayerProfileDBPath(UID);
	if (Database)
	{
		Database->GetValue(OnCompleted, OnCancelled);
	}
	else
	{
		On_Error.Broadcast(Profile,"Failed");
	}
}

void UGetProfile::OnDataRecived(UFGDataSnapshot* Data)
{
	// Construct the save slot name using the UID
	const FString SlotName = UID + TEXT("Profile");

	// Check if the data exists
	if (Data && Data->Exists())
	{
		// Extract the result map from the data
		TMap<FString, FFGValueVariant> Result = UFGValueVariantAccess::GetMap(Data->GetValue());

		// Safely extract profile data from the map
		Profile.Name      = UFGValueVariantAccess::GetString(Result.FindRef(TEXT("Name")));
		Profile.UserID    = UFGValueVariantAccess::GetInteger(Result.FindRef(TEXT("UserID")));
		Profile.AvatarURL = UFGValueVariantAccess::GetString(Result.FindRef(TEXT("PhotoURL")));

		// Save the profile locally
		UFirebaseIdentity_Subsystem::SaveProfileToLocal(SlotName, Profile);

		// Broadcast the success delegate
		On_Sucess.Broadcast(Profile,"Success");
	}
	else
	{
		On_Error.Broadcast(Profile,"Failed");
	}
}

void UGetProfile::OnCancelledOperation(int ErrorCode, FString ErrorMessage)
{
	// Broadcast the error delegate with the provided message
	On_Error.Broadcast(Profile,FString::Printf(TEXT("Operation cancelled: %s (Error Code: %d)"), *ErrorMessage, ErrorCode));
}

//ULoadImage_GIF* ULoadImage_GIF::LoadImage_GIF(const FString URL)
//{
//	// Create an async action object
//	ULoadImage_GIF* AsyncAction = NewObject<ULoadImage_GIF>();
//	UE_LOG(LogTemp, Log, TEXT("Async action created"));
//
//	// Store the provided UID for use in other methods
//	AsyncAction->URL = URL;
//
//	// Return the async function object so it can be activated
//	return AsyncAction;
//}
//
//void ULoadImage_GIF::Activate()
//{
//
//	UAsyncTaskDownloadImage* mDownloadTask = NewObject<UAsyncTaskDownloadImage>();
//	mDownloadTask->OnFail.AddDynamic(this, &ULoadImage_GIF::OnFailed);
//	//mDownloadTask->OnSuccess.AddDynamic(this, &ULoadImage_GIF::OnDownloadedImage);
//	mDownloadTask->Start(URL);
//	
//}
//
////void ULoadImage_GIF::OnDownloadedImage(UAnimatedTexture2D* Texture)
////{
////	On_Sucess.Broadcast(Texture);
////}
//
//void ULoadImage_GIF::OnFailed(UTexture2DDynamic* Texture)
//{
//	//URuntimeGifReader* GifReader = NewObject<URuntimeGifReader>();
//	// GifReader->OnSuccess.AddDynamic(this, &ULoadImage_GIF::OnDownloadedImage);
//	// GifReader->LoadGIF(URL,TextureFilter::TF_Trilinear);
//	//On_Error.Broadcast(Texture);
//}
