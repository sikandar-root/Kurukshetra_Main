// Copyright (c) 2020 Nineva Studios

#pragma once

#include "HAL/Platform.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"
#endif

#include "CoreMinimal.h"
#include "Auth/GPPermissionFlags.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "GPFriends.generated.h"


UCLASS()
class GOOGLEPLAYGOODIES_API UGPFriends : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:

	DECLARE_DYNAMIC_DELEGATE(FGPDelegate);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGPOnFriendsLoad, const TArray<UGPPlayer*>&, FriendsList);
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FGPErrorDelegate, const FString&, ErrorMessage, int, ErrorCode);
	DECLARE_DYNAMIC_DELEGATE_ThreeParams(FGPCompareTwoFriends, const FString&, OtherPlayerId, const FString&, OtherPlayerInGameName, const FString&, CurrentPlayerInGameName);

	UGPFriends() = default;

#if PLATFORM_ANDROID

	void Init(jobject PlayerObject);
#endif

	/**
	* You can retrieve and display (in the game) a list of players who are friends with the current user
	* As a user, it is possible to control which games have access to the friends list. 
	* When you retrieve the friends list, you must handle the case where permission is required.
	* This is all encapsulated in the API to make requesting access and subsequently using the friends list a straightforward task.
	* 
	* @param PageSize - The number of entries to request for this initial page. Note that if cached data already exists, the returned buffer may contain more than this size, but it is guaranteed to contain at least this many if the collection contains enough records.
	* @param ForceReload - If true, this call will clear any locally-cached data and attempt to fetch the latest data from the server. This would commonly be used for something like a user-initiated refresh. Normally, this should be set to false to gain advantages of data caching.
	* @param OnSuccess - Called if load friends is successfull
	* @param OnFailure - Called if load friends is failed
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Friends", meta = (AutoCreateRefTerm = "OnSuccess, OnFailure"))
	static void LoadFriends(int PageSize, bool ForceReload, const FGPOnFriendsLoad& OnSuccess, const FGPErrorDelegate& OnFailure);
	
	/** 
	* You can display a view of another player�s Play Games profile from within your game.
	* This view allows players to send and accept friend invitations for the player being viewed.
	* This view does not require access to the friends list.
	* Additionally, if your game has its own concept of player names separate from Play Games Gamer IDs, you can pass these along to the profile view so that they can be included in any friend invitations for additional context.
	* 
	* @param OtherPlayerId - Id of your friend, whom you want to view account
	* @param OnSuccess - Called if view another player profile is successful
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Friends", meta = (AutoCreateRefTerm = "OnSuccess"))
	static void ViewAnotherPlayerProfile(const FString& OtherPlayerId, const FGPDelegate& OnSuccess);
	
	/** 
	* If the game has its own name for players, these can be added to the API call.
	* This enables Play Games to set the nickname of players who send friend invitations from within your game to "<game-specific-name> from <your-game-name>" 
	* 
	* @param OtherPlayerId - The player ID of the player to compare with.
	* @param OtherPlayerInGameName - The game's own display name of the player referred to by otherPlayerId.
	* @param CurrentPlayerInGameName - The game's own display name of the current player.
	* @param OnSuccess - Called if view another player profile with alternative hints is successful
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Friends", meta = (AutoCreateRefTerm = "OnSuccess"))
	static void ViewAnotherPlayerProfileWithAlternativeHints(const FString& OtherPlayerId, const FString& OtherPlayerInGameName, const FString& CurrentPlayerInGameName, const FGPCompareTwoFriends& OnSuccess);

	static FGPOnFriendsLoad OnFriendsLoadSuccessDelegate;
	static FGPErrorDelegate OnFriendsLoadFailureDelegate;
	static FGPCompareTwoFriends OnCompareTwoFriendsDelegate;
};