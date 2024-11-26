// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGNotificationCategory.generated.h"

UENUM(BlueprintType)
enum NotificationCategory
{
	/** Alarm. */
	CategoryAlarm = 0 UMETA(DisplayName = "Alarm"),
	/** Call. */
	CategoryCall = 1 UMETA(DisplayName = "Call"),
	/** Email. */
	CategoryEmail = 2 UMETA(DisplayName = "Email"),
	/** Error. */
	CategoryError = 3 UMETA(DisplayName = "Error"),
	/** Event. */
	CategoryEvent = 4 UMETA(DisplayName = "Event"),
	/** Message. */
	CategoryMessage = 5 UMETA(DisplayName = "Message"),
	/** Navigation. */
	CategoryNavigation = 6 UMETA(DisplayName = "Navigation"),
	/** Progress. */
	CategoryProgress = 7 UMETA(DisplayName = "Progress"),
	/** Promo. */
	CategoryPromo = 8 UMETA(DisplayName = "Promo"),
	/** Recommendation. */
	CategoryRecommendation = 9 UMETA(DisplayName = "Recommendation"),
	/** Reminder. */
	CategoryReminder = 10 UMETA(DisplayName = "Reminder"),
	/** Service. */
	CategoryService = 11 UMETA(DisplayName = "Service"),
	/** Social. */
	CategorySocial = 12 UMETA(DisplayName = "Social"),
	/** Status. */
	CategoryStatus = 13 UMETA(DisplayName = "Status"),
	/** System. */
	CategorySystem = 14 UMETA(DisplayName = "System"),
	/** Transport. */
	CategoryTransport = 15 UMETA(DisplayName = "Transport"),
};