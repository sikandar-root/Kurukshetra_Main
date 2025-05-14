// Fill out your copyright notice in the Description page of Project Settings.


#include "FirebaseDatabasePath_Library.h"

#include "Database/FGDatabaseRef.h"
#include "Database/FGDataSnapshot.h"
#include "Engine/Engine.h"


UFGDatabaseRef* UFirebaseDatabasePath_Library::PlayerProfileDBPath(const FString& UID)
{
	// Base path for the Firebase Database
	FString BasePath = TEXT("users");

	// Create a database reference from the base path
	UFGDatabaseRef* DatabaseRef = UFGDatabaseRef::MakeDatabaseRefFromPath(BasePath);
	if (!DatabaseRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create database reference from path: %s"), *BasePath);
		return nullptr;
	}

	// Add the UID as a child node
	UFGDatabaseRef* UIDRef = DatabaseRef->Child(UID);
	if (!UIDRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create child reference for UID: %s"), *UID);
		return nullptr;
	}

	// Add "Profile" as another child node
	UFGDatabaseRef* ProfileRef = UIDRef->Child(TEXT("Profile"));
	if (!ProfileRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create child reference for 'Profile'"));
		return nullptr;
	}

	return ProfileRef;
}

UFGDatabaseRef* UFirebaseDatabasePath_Library::UserIdsDBPath(const FString& UserId)
{
	// Base path for the Firebase Database
	FString BasePath = TEXT("userIds");

	// Create a database reference from the base path
	UFGDatabaseRef* DatabaseRef = UFGDatabaseRef::MakeDatabaseRefFromPath(BasePath);
	if (!DatabaseRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create database reference from path: %s"), *BasePath);
		return nullptr;
	}
	// Add the UserId as a child node
	UFGDatabaseRef* UserIdRef = DatabaseRef->Child(UserId);
	if (!UserIdRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create child reference for UID: %s"), *UserId);
		return nullptr;
	}
	return UserIdRef;
}

UFGDatabaseRef* UFirebaseDatabasePath_Library::FriendRequestsDBPath(const FString& UID, const FString& FriendId,
	bool IsSender)
{
	UFGDatabaseRef* FinalDatabaseRef = nullptr;

	FString BasePath = TEXT("users");
	// Create a database reference from the base path
	UFGDatabaseRef* DatabaseRef = UFGDatabaseRef::MakeDatabaseRefFromPath(BasePath);
		
	
	if (IsSender)
	{
		// Add the UID as a child node
		UFGDatabaseRef* UIDRef = DatabaseRef->Child(UID);
		UFGDatabaseRef* FriendReqRef = UIDRef->Child(FString("FriendRequests"));
		UFGDatabaseRef* FriendIdRef = FriendReqRef->Child(FriendId);
		FinalDatabaseRef =FriendIdRef;
	}
	else
	{
		// Add the UID as a child node
		UFGDatabaseRef* FriendIdRef = DatabaseRef->Child(FriendId);
		UFGDatabaseRef* FriendReqRef = FriendIdRef->Child(FString("FriendRequests"));
		UFGDatabaseRef* UIDRef = FriendReqRef->Child(UID);
		FinalDatabaseRef = UIDRef;
	}

	return FinalDatabaseRef;
}

UFGDatabaseRef* UFirebaseDatabasePath_Library::FriendsDBPath(const FString& UID)
{
	FString BasePath = TEXT("users");
	// Create a database reference from the base path
	UFGDatabaseRef* DatabaseRef = UFGDatabaseRef::MakeDatabaseRefFromPath(BasePath);
	// Add the UID as a child node
	UFGDatabaseRef* UIDRef = DatabaseRef->Child(UID);
	UFGDatabaseRef* FriendRef = UIDRef->Child(FString("Friends"));

	return FriendRef;
}



