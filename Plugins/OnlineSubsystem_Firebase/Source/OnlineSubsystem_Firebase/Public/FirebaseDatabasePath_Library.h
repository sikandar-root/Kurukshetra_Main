// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Database/FGDatabaseRef.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FirebaseDatabasePath_Library.generated.h"

/**
 * 
 */

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTest, UFGDataSnapshot*, DataSnap);

UCLASS()
class ONLINESUBSYSTEM_FIREBASE_API UFirebaseDatabasePath_Library : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category = "Firebase")
	static UFGDatabaseRef* PlayerProfileDBPath(const FString& UID);

	UFUNCTION(BlueprintCallable, Category = "Firebase")
	static UFGDatabaseRef* UserIdsDBPath(const FString& UserId);

	UFUNCTION(BlueprintCallable, Category = "Firebase")
	static UFGDatabaseRef* FriendRequestsDBPath(const FString& UID,const FString& FriendId, bool IsSender );

	UFUNCTION(BlueprintCallable, Category = "Firebase")
	static UFGDatabaseRef* FriendsDBPath(const FString& UID );

	// Add these to FirebaseDatabasePath_Library.h
	UFUNCTION(BlueprintPure, Category = "Firebase|Database|Paths|Chat")
	static UFGDatabaseRef* WorldChatDBPath(const FString& UID);

	UFUNCTION(BlueprintPure, Category = "Firebase|Database|Paths|Chat")
	static UFGDatabaseRef* PrivateChatDBPath(const FString ChatID,const FString& UID);

	UFUNCTION(BlueprintPure, Category = "Firebase|Database|Paths|Chat")
	static UFGDatabaseRef* WorldChatListenerDBPath();

	UFUNCTION(BlueprintPure, Category = "Firebase|Database|Paths|Chat")
	static UFGDatabaseRef* PrivateChatListenerDBPath(const FString& ChatID);

	
};


