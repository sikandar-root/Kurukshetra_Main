// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGNotificationPriority.generated.h"

UENUM(BlueprintType)
enum NotificationPriority
{
	/** Minimum. */
	PriorityMinimum = -2 UMETA(DisplayName = "Minimum"),
	/** Low. */
	PriorityLow = -1 UMETA(DisplayName = "Low"),
	/** Default. */
	PriorityDefault = 0 UMETA(DisplayName = "Default"),
	/** High. */
	PriorityHigh = 1 UMETA(DisplayName = "High"),
	/** Maximum. */
	PriorityMaximum = 2 UMETA(DisplayName = "Maximum"),	
};
