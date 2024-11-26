// Copyright (c) 2020 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "GPPlayerStats.generated.h"

USTRUCT(BlueprintType)
struct GOOGLEPLAYGOODIES_API FGPPlayerStats
{
	GENERATED_BODY()

	/**
	* The approximate number of days since the player last played.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Google Play Goodies|Player Stats")
	int DaysSinceLastPlayed = 0;

	/**
	* The approximate number of sessions of the player.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Google Play Goodies|Player Stats")
	int NumberOfSessions = 0;

	/**
	* The average session length of the player in minutes
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Google Play Goodies|Player Stats")
	float AverageSessionLength = 0;

	/**
	* The approximation of sessions percentile for the player, given as a decimal value between 0 to 1 inclusive.
	* Higher numbers indicate that this player has played more sessions.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Google Play Goodies|Player Stats")
	float SessiaonPercentile = 0;

	/**
	* The approximate number of in-app purchases for the player.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Google Play Goodies|Player Stats")
	int NumberOfPurchases = 0;

	/**
	* The approximate spend percentile of the player, given as a decimal value between 0 to 1 inclusive.
	* Higher numbers indicate that this player has spent more.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Google Play Goodies|Player Stats")
	float SpendPercentile = 0;
};

UCLASS()
class GOOGLEPLAYGOODIES_API UGPPlayerStatsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGPLoadStatsDelegate, FGPPlayerStats, PlayerStats);

	/**
	* Retrieve player stats.
	*
	* @param OnLoadStats - Called when player stats where successfully loaded
	* @param ForceRefresh - If true, this call will clear any locally cached data and attempt to fetch the latest data from the server
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Player Stats")
	static void LoadPlayerStats(const FGPLoadStatsDelegate& OnLoadStats, bool ForceRefresh);

	static FGPLoadStatsDelegate OnLoadStatsDelegate;
};
