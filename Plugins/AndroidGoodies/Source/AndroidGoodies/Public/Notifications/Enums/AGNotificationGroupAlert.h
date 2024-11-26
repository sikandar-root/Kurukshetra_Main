// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGNotificationGroupAlert.generated.h"

UENUM(BlueprintType)
enum NotificationGroupAlert
{
	/** 
	* All notifications in a group with sound or vibration ought to make sound or vibrate (respectively),
	* so this notification will not be muted when it is in a group.
	*/
	GroupAlertAll = 0 UMETA(DisplayName = "All"),
	/** 
	* All children notifications in a group should be silenced (no sound or vibration) even if they are posted to a NotificationChannel
	* that has sound and/or vibration. Use this constant to mute this notification if this notification is a group child. 
	* This must be applied to all children notifications you want to mute.
	*
	* For example, you might want to use this constant if you post a number of children notifications at once
	* (say, after a periodic sync), and only need to notify the user audibly once.
	*/	
	GroupAlertSummary = 1 UMETA(DisplayName = "Summary"),
	/** 
	* The summary notification in a group should be silenced (no sound or vibration) even if they are posted to a NotificationChannel
	* that has sound and/or vibration. Use this constant to mute this notification if this notification is a group summary.
	*
	* For example, you might want to use this constant if only the children notifications in your group have content and the summary 
	* is only used to visually group notifications rather than to alert the user that new information is available.
	*/
	GroupAlertChildren = 2 UMETA(DisplayName = "Children"),
};