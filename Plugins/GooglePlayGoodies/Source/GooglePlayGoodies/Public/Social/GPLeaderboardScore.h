// Copyright (c) 2021 Nineva Studios

#pragma once

#include "Misc/DateTime.h"
#include "Containers/UnrealString.h"

#include "GPLeaderboardScore.generated.h"

USTRUCT(BlueprintType)
struct GOOGLEPLAYGOODIES_API FGPLeaderboardScore
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Google Play Goodies|Leaderboards")
	FString DisplayRank = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Google Play Goodies|Leaderboards")
	FString DisplayScore = "";
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Google Play Goodies|Leaderboards")
	FString ScoreHolderDisplayName = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Google Play Goodies|Leaderboards")
	FString ScoreHolderHiResImageUri = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Google Play Goodies|Leaderboards")
	FString ScoreHolderIconImageUri = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Google Play Goodies|Leaderboards")
	int64 Rank = -1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Google Play Goodies|Leaderboards")
	FString ScoreTag = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Google Play Goodies|Leaderboards")
	FDateTime Timestamp = FDateTime::MinValue();
};
