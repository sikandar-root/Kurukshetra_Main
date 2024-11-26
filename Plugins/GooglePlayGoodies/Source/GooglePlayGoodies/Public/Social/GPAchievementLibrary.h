// Copyright (c) 2020 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "GPAchievementLibrary.generated.h"

UCLASS()
class GOOGLEPLAYGOODIES_API UGPAchievementLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	* Unlock an achievement.
	*
	* @param AchievementID - ID of the achievement to unlock
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Achievements")
	static void UnlockAchievement(const FString& AchievementID);

	/**
	* Increment an achievement.
	*
	* @param AchievementID - ID of the achievement to increment
	* @param Value - Amount to be incremented by
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Achievements")
	static void IncrementAchievement(const FString& AchievementID, int Value = 1);

	/**
	* Show the default Google Play Games achievement UI.
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Achievements")
	static void ShowAchievementUI();

};
