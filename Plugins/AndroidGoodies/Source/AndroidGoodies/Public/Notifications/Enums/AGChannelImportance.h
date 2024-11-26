// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGChannelImportance.generated.h"

UENUM(BlueprintType)
enum ChannelImportance
{
	/** None. */
	ImportanceNone = 0 UMETA(DisplayName = "None"),
	/** Min. */
	ImportanceMin = 1 UMETA(DisplayName = "Min"),
	/** Low. */
	ImportanceLow = 2 UMETA(DisplayName = "Low"),
	/** Default. */
	ImportanceDefault = 3 UMETA(DisplayName = "Default"),
	/** High. */
	ImportanceHigh = 4 UMETA(DisplayName = "High"),
	/** Max. */
	ImportanceMax = 5 UMETA(DisplayName = "Max"),
	/** Unspecified. */
	ImportanceUnspecified = -1000 UMETA(DisplayName = "Unspecified"),
};
