// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGInterruptionFilter.generated.h"

UENUM(BlueprintType)
enum InterruptionFilter
{
	/** Unknown. */
	FilterUnknown = 0 UMETA(DisplayName = "Unknown"),
	/** All. */
	FIlterAll = 1 UMETA(DisplayName = "All"),
	/** Priority. */
	FilterPriority = 2 UMETA(DisplayName = "Priority"),
	/** None. */
	FilterNone = 3 UMETA(DisplayName = "None"),
	/** Alarms. */
	FilterAlarms = 4 UMETA(DisplayName = "Alarms"),
};
