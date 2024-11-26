// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGNotificationBadgeIconType.generated.h"

UENUM(BlueprintType)
enum NotificationBadgeIconType
{
	/** No Badge. */
	NoBadge = 0 UMETA(DisplayName = "No Badge"),
	/** Small Badge. */
	SmallBadge = 1 UMETA(DisplayName = "Small Badge"),
	/** Large Badge. */
	LargeBadge = 2 UMETA(DisplayName = "Large Badge"),
};