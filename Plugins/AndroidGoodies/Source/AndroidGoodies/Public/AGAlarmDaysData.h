// Copyright (c) 2018 Nineva Studios

#pragma once

#include "AGAlarmDaysData.generated.h"

USTRUCT(BlueprintType)
struct ANDROIDGOODIES_API FAGAlarmDaysData
{
	GENERATED_USTRUCT_BODY()

	/** Sunday. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	bool Sunday = false;

	/** Monday. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	bool Monday = false;

	/** Tuesday. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	bool Tuesday = false;

	/** Wednesday. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	bool Wednesday = false;

	/** Thursday. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	bool Thursday = false;

	/** Friday. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	bool Friday = false;

	/** Saturday. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	bool Saturday = false;

	TArray<int> ToIntArray()
	{
		constexpr int SundayIntValue = 1;
		constexpr int MondayIntValue = 2;
		constexpr int TuesdayIntValue = 3;
		constexpr int WednesdayIntValue = 4;
		constexpr int ThursdayIntValue = 5;
		constexpr int FridayIntValue = 6;
		constexpr int SaturdayIntValue = 7;

		TArray<int> intArray;

		if (Sunday)
		{
			intArray.Add(SundayIntValue);
		}
		if (Monday)
		{
			intArray.Add(MondayIntValue);
		}
		if (Tuesday)
		{
			intArray.Add(TuesdayIntValue);
		}
		if (Wednesday)
		{
			intArray.Add(WednesdayIntValue);
		}
		if (Thursday)
		{
			intArray.Add(ThursdayIntValue);
		}
		if (Friday)
		{
			intArray.Add(FridayIntValue);
		}
		if (Saturday)
		{
			intArray.Add(SaturdayIntValue);
		}

		return intArray;
	};
};