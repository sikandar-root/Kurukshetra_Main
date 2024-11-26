// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGNotificationVisibility.generated.h"

UENUM(BlueprintType)
enum NotificationVisibility
{
	/** Secret. */
	VisibilitySecret = -1 UMETA(DisplayName = "Secret"),
	/** Private. */
	VisibilityPrivate = 0 UMETA(DisplayName = "Private"),
	/** Public. */
	VisibilityPublic = 1 UMETA(DisplayName = "Public"),
};
