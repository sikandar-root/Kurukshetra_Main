// Copyright (c) 2020 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "GPLeaderboardScore.h"

#include "GPLeaderboardLibrary.generated.h"

UENUM()
enum class LeaderboardTimeSpan : uint8
{
	Daily,
	Weekly,
	AllTime
};

UENUM()
enum class LeaderboardCollection : uint8
{
	Public,
	Friends = 3
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FGPOnScoresLoadedDelegate, const TArray<FGPLeaderboardScore>&, Scores);

DECLARE_DYNAMIC_DELEGATE_OneParam(FGPOnScoresLoadErrorDelegate, FString, Error);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FGPOnScoreHolderImageReadyDelegate, UTexture2D*, ImageTexture, FString, ImageUri);

UCLASS()
class GOOGLEPLAYGOODIES_API UGPLeaderboardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Submit a score to a leaderboard.
	*
	* @param LeaderboardID - ID of the leaderboard to submit to
	* @param Score - Score to be submitted (milliseconds for time e. g. 240000 = 4 minutes, for currency use 1/1,000,000th fractions e. g. 19,950,000 = $19.95)
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Leaderboards")
	static void SubmitScore(const FString& LeaderboardID, int Score);

	/**
	* Show a leaderboard.
	*
	* @param LeaderboardID - ID of the leaderboard to show
	* @param TimeSpan - Time span of the leeaderboard (daily, weekly, all time)
	* @param Collection - Type of leaderboard entries (public, friends)
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Leaderboards")
	static void ShowLeaderboardUI(const FString& LeaderboardID,
	                              LeaderboardTimeSpan TimeSpan = LeaderboardTimeSpan::AllTime, LeaderboardCollection Collection = LeaderboardCollection::Public);

	/**
	* Load the player-centered page of scores for the leaderboard specified by LeaderboardId. 
	* If the player does not have a score on this leaderboard, this call will return the top page instead.
	*
	* @param LeaderboardID - ID of the leaderboard to show
	* @param OnSuccess - action to perform with the scores
	* @param OnError - action to perform with the error message
	* @param MaxResults - maximum results to be shown (between 1 and 25)
	* @param TimeSpan - Time span of the leeaderboard (daily, weekly, all time)
	* @param Collection - Type of leaderboard entries (public, friends)
	* @param ForceReload - If true, this call will clear any locally cached data and attempt to fetch the latest data from the server. 
	* This would commonly be used for something like a user-initiated refresh. Normally, this should be set to false to gain advantages of data caching.
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Leaderboards", Meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void LoadPlayerCenteredScores(const FString& LeaderboardID, const FGPOnScoresLoadedDelegate& OnSuccess, const FGPOnScoresLoadErrorDelegate& OnError,
	                                     int MaxResults = 25, LeaderboardTimeSpan TimeSpan = LeaderboardTimeSpan::AllTime, LeaderboardCollection Collection = LeaderboardCollection::Public,
	                                     bool ForceReload = true);

	/**
	* Load the top page of scores for the leaderboard specified by leaderboardId
	* 
	* @param LeaderboardID - ID of the leaderboard to show
	* @param OnSuccess - action to perform with the scores
	* @param OnError - action to perform with the error message
	* @param MaxResults - The maximum number of scores to fetch per page. Must be between 1 and 25.
	* @param TimeSpan - Time span to retrieve data for.
	* @param Collection - The leaderboard collection to retrieve scores for. 
	* @param ForceReload - If true, this call will clear any locally cached data and attempt to fetch the latest data from the server.
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Leaderboards", Meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void LoadTopScores(const FString& LeaderboardID,
	                          const FGPOnScoresLoadedDelegate& OnSuccess, const FGPOnScoresLoadErrorDelegate& OnError,
	                          int MaxResults = 25, LeaderboardTimeSpan TimeSpan = LeaderboardTimeSpan::AllTime, LeaderboardCollection Collection = LeaderboardCollection::Public,
	                          bool ForceReload = true);

	/**
	* Get score holder image.
	*
	* @param ScoreHolderImageUri - Uri of the score holder image
	* @param onImageReady - Called when the image is ready for use
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Leaderboards")
	static void GetScoreHolderImage(const FString& ScoreHolderImageUri, const FGPOnScoreHolderImageReadyDelegate& onImageReady);

	static FGPOnScoresLoadedDelegate OnScoresLoadedCallback;
	static FGPOnScoresLoadErrorDelegate OnScoresLoadErrorCallback;

	static FGPOnScoresLoadedDelegate OnTopScoresLoadedCallback;
	static FGPOnScoresLoadErrorDelegate OnTopScoresLoadErrorCallback;
};
