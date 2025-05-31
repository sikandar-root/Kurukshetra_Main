// Copyright Epic Games, Inc. All Rights Reserved.

#include "FirebaseIdentity_Subsystem.h"
#include "FirebaseDatabasePath_Library.h"
#include "Kismet/GameplayStatics.h"
#include "Database/FGDataSnapshot.h"
#include "Common/FGValueVariantAccess.h"
#include "Auth/FGAuthLibrary.h"
#include "FirebaseData_SaveGame.h"

void UFirebaseIdentity_Subsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}

bool UFirebaseIdentity_Subsystem::IsProfileExistInLocal(const FString& UID, FUserProfile& Profile)
{
    if (UGameplayStatics::DoesSaveGameExist(UID, 0))
    {
        if (UFirebaseData_SaveGame* SaveGameInstance = Cast<UFirebaseData_SaveGame>(UGameplayStatics::LoadGameFromSlot(UID, 0)))
        {
            Profile = SaveGameInstance->UserProfile;
            return true;
        }
    }
    return false;
}

bool UFirebaseIdentity_Subsystem::SaveProfileToLocal(const FString& UID, const FUserProfile& Profile)
{
    if (UFirebaseData_SaveGame* SaveGameInstance = Cast<UFirebaseData_SaveGame>(UGameplayStatics::CreateSaveGameObject(UFirebaseData_SaveGame::StaticClass())))
    {
        SaveGameInstance->UserProfile = Profile;
        return UGameplayStatics::SaveGameToSlot(SaveGameInstance, UID, 0);
    }
    return false;
}

void UFirebaseIdentity_Subsystem::OnLoginSuccessInternal(UFGFirebaseUser* User)
{
    CurrentUser = User;
    CurrentUID = User->GetUid();
    OnLoginSuccess.Broadcast(User);
}

UGetProfileAsync* UGetProfileAsync::GetProfile(UObject* WorldContextObject, const FString& UID)
{
    UGetProfileAsync* Action = NewObject<UGetProfileAsync>();
    Action->TargetUID = UID;
    Action->RegisterWithGameInstance(WorldContextObject);
    return Action;
}

void UGetProfileAsync::Activate()
{
    const FString SlotName = TargetUID + TEXT("Profile");

    // First try to load from local storage
    if (UFirebaseIdentity_Subsystem::IsProfileExistInLocal(SlotName, Profile))
    {
        OnSuccess.Broadcast(Profile, TEXT("Loaded from local storage"));
        return;
    }

    // If not found locally, query Firebase database
    OnDataChangedDelegate.BindDynamic(this, &UGetProfileAsync::OnDataReceived);
    OnCancelledDelegate.BindDynamic(this, &UGetProfileAsync::OnOperationCancelled);

    if (UFGDatabaseRef* Database = UFirebaseDatabasePath_Library::PlayerProfileDBPath(TargetUID))
    {
        Database->GetValue(OnDataChangedDelegate, OnCancelledDelegate);
    }
    else
    {
        OnError.Broadcast(Profile, TEXT("Failed to create database reference"));
    }
}

void UGetProfileAsync::OnDataReceived(UFGDataSnapshot* Data)
{
    if (Data && Data->Exists())
    {
        const TMap<FString, FFGValueVariant> Result = UFGValueVariantAccess::GetMap(Data->GetValue());
        
        // Extract profile data from database result
        Profile.Name = UFGValueVariantAccess::GetString(Result.FindRef(TEXT("Name")));
        Profile.UserID = UFGValueVariantAccess::GetInteger(Result.FindRef(TEXT("UserID")));
        Profile.AvatarURL = UFGValueVariantAccess::GetString(Result.FindRef(TEXT("PhotoURL")));

        // Save the loaded profile locally
        const FString SlotName = TargetUID + TEXT("Profile");
        UFirebaseIdentity_Subsystem::SaveProfileToLocal(SlotName, Profile);

        OnSuccess.Broadcast(Profile, TEXT("Success"));
    }
    else
    {
        OnError.Broadcast(Profile, TEXT("Profile data not found"));
    }
}

void UGetProfileAsync::OnOperationCancelled(int32 ErrorCode, const FString ErrorMessage)
{
    OnError.Broadcast(Profile, FString::Printf(TEXT("Operation cancelled: %s (Code: %d)"), *ErrorMessage, ErrorCode));
}

UFirebaseAuthAsync* UFirebaseAuthAsync::SignInWithEmailAndPassword(UObject* WorldContextObject, UFirebaseIdentity_Subsystem* IdentitySubsystem, const FString& Email, const FString& Password)
{
    UFirebaseAuthAsync* Action = NewObject<UFirebaseAuthAsync>();
    Action->Email = Email;
    Action->Password = Password;
    Action->FirebaseIdentity = IdentitySubsystem;
    Action->AuthAction = EAuthAction::SignIn;
    Action->RegisterWithGameInstance(WorldContextObject);
    return Action;
}

UFirebaseAuthAsync* UFirebaseAuthAsync::SignUpWithEmailAndPassword(UObject* WorldContextObject, UFirebaseIdentity_Subsystem* IdentitySubsystem, const FString& Email, const FString& Password)
{
    UFirebaseAuthAsync* Action = NewObject<UFirebaseAuthAsync>();
    Action->Email = Email;
    Action->Password = Password;
    Action->FirebaseIdentity = IdentitySubsystem;
    Action->AuthAction = EAuthAction::Signup;
    Action->RegisterWithGameInstance(WorldContextObject);
    return Action;
}

UFirebaseAuthAsync* UFirebaseAuthAsync::SignInWithCredential(UObject* WorldContextObject, UFirebaseIdentity_Subsystem* IdentitySubsystem, UFGAuthCredentials* Credentials)
{
    UFirebaseAuthAsync* Action = NewObject<UFirebaseAuthAsync>();
    Action->Credentials = Credentials;
    Action->FirebaseIdentity = IdentitySubsystem;
    Action->AuthAction = EAuthAction::SignInWithCredential;
    Action->RegisterWithGameInstance(WorldContextObject);
    return Action;
}

void UFirebaseAuthAsync::Activate()
{
    if (!FirebaseIdentity)
    {
        HandleError(TEXT("Invalid identity subsystem"));
        return;
    }

    // Use the static UFGAuthLibrary functions for authentication
    FAuthUserDelegate SuccessDelegate;
    SuccessDelegate.BindDynamic(this, &UFirebaseAuthAsync::HandleSuccess);
    
    FAuthStringDelegate ErrorDelegate;
    ErrorDelegate.BindDynamic(this, &UFirebaseAuthAsync::HandleError);

    switch (AuthAction)
    {
    case EAuthAction::Signup:
        if (Email.IsEmpty() || Password.IsEmpty())
        {
            HandleError(TEXT("Email and password required"));
            return;
        }
        UFGAuthLibrary::CreateUser(Email, Password, SuccessDelegate, ErrorDelegate);
        break;
        
    case EAuthAction::SignIn:
        if (Email.IsEmpty() || Password.IsEmpty())
        {
            HandleError(TEXT("Email and password required"));
            return;
        }
        UFGAuthLibrary::SignInWithEmailAndPassword(Email, Password, SuccessDelegate, ErrorDelegate);
        break;
        
    case EAuthAction::SignInWithCredential:
        if (!Credentials)
        {
            HandleError(TEXT("Invalid credentials"));
            return;
        }
        // Convert credentials to proper type
        // TSharedPtr<IFirebaseAuthCredentials> NativeCredentials = Credentials->GetCredentials();
        UFGAuthLibrary::SignInWithCredentials(Credentials, SuccessDelegate, ErrorDelegate);
        break;
        
    default:
        HandleError(TEXT("Unknown auth action"));
        break;
    }
}

void UFirebaseAuthAsync::HandleSuccess(UFGFirebaseUser* User)
{
    if (FirebaseIdentity)
    {
        FirebaseIdentity->CurrentUser = User;
        FirebaseIdentity->CurrentUID = User->GetUid();
        FirebaseIdentity->OnLoginSuccess.Broadcast(User);
    }
    OnAuthResponse.Broadcast(true, User, TEXT("Success"));
}

void UFirebaseAuthAsync::HandleError(const FString ErrorMessage)
{
    OnAuthResponse.Broadcast(false, nullptr, ErrorMessage);
}