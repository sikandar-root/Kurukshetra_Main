// Fill out your copyright notice in the Description page of Project Settings.


#include "FirebaseDatabasePath_Library.h"

#include "Auth/FGAuthLibrary.h"
#include "Auth/FGFirebaseUser.h"
#include "Common/FGValueVariantAccess.h"
#include "Database/FGDatabaseRef.h"
#include "Database/FGDataSnapshot.h"
#include "Database/FGDatabaseLibrary.h"
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

UFGDatabaseRef* UFirebaseDatabasePath_Library::WorldChatDBPath(const FString& UID)
{
    FString BasePath = TEXT("chatRoom");
    // Create a database reference from the base path
    UFGDatabaseRef* DatabaseRef = UFGDatabaseRef::MakeDatabaseRefFromPath(BasePath);
    if (!DatabaseRef)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create database reference from path: %s"), *BasePath);
        return nullptr;
    }

    FFGValueVariant Datetime = UFGDatabaseLibrary::RealtimeDatabaseTimestamp();
    FDateTime date = UFGValueVariantAccess::GetDateTime(Datetime);
    int64 Timestamp = date.ToUnixTimestamp();
    
    FString Path = FString::Printf(TEXT("World/%d::%s"), Timestamp, *UID);
    UFGDatabaseRef* WorldChatRef = DatabaseRef->Child(Path);
	UE_LOG(LogTemp, Warning, TEXT("DatabasePath: %s"), *Path);
    if (!WorldChatRef)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create child reference for path: %s"), *Path);
        return nullptr;
    }

    return WorldChatRef;
}

UFGDatabaseRef* UFirebaseDatabasePath_Library::PrivateChatDBPath(const FString ChatID,const FString& UID)
{
	FString BasePath = TEXT("chatRoom");
	// Create a database reference from the base path
	UFGDatabaseRef* DatabaseRef = UFGDatabaseRef::MakeDatabaseRefFromPath(BasePath);
	FFGValueVariant Datetime = UFGDatabaseLibrary::RealtimeDatabaseTimestamp();
	FDateTime date = UFGValueVariantAccess::GetDateTime(Datetime);
	int64 Timestamp = date.ToUnixTimestamp();
    
	FString Path = FString::Printf(TEXT("Private/%s/%lld::%s"), *ChatID, Timestamp, *UID);
	return DatabaseRef->Child(Path);
}

// UFGDatabaseRef* UFirebaseDatabasePath_Library::PrivateChatDBPath(const FString& UserID1, const FString& UserID2)
// {
// 	FString BasePath = TEXT("chatRoom");
// 	// Create a database reference from the base path
// 	UFGDatabaseRef* DatabaseRef = UFGDatabaseRef::MakeDatabaseRefFromPath(BasePath);
// 	// Create a deterministic chat ID so both users use the same path
// 	FString ChatID = UserID1 < UserID2 ?
// 		FString::Printf(TEXT("%s_%s"), *UserID1, *UserID2) :
// 		FString::Printf(TEXT("%s_%s"), *UserID2, *UserID1);
// 	
// 	return DatabaseRef->Child("Private")->Child(ChatID);
// }

UFGDatabaseRef* UFirebaseDatabasePath_Library::WorldChatListenerDBPath()
{
	FString BasePath = TEXT("chatRoom");
	// Create a database reference from the base path
	UFGDatabaseRef* DatabaseRef = UFGDatabaseRef::MakeDatabaseRefFromPath(BasePath);
	return DatabaseRef->Child("World");
}

UFGDatabaseRef* UFirebaseDatabasePath_Library::PrivateChatListenerDBPath(const FString& ChatID)
{
	FString BasePath = TEXT("chatRoom");
	// Create a database reference from the base path
	UFGDatabaseRef* DatabaseRef = UFGDatabaseRef::MakeDatabaseRefFromPath(BasePath);
    
	FString Path = FString::Printf(TEXT("Private/%s"), *ChatID);
	return DatabaseRef->Child(Path);
}
