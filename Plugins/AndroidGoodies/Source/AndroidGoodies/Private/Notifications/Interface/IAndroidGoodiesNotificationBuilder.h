#pragma once

#include "Notifications/Enums/AGNotificationPriority.h"
#include "Notifications/Enums/AGNotificationBadgeIconType.h"
#include "Notifications/Enums/AGNotificationCategory.h"
#include "Notifications/AGNotificationDefaults.h"
#include "Notifications/Enums/AGNotificationGroupAlert.h"
#include "Notifications/Enums/AGNotificationVisibility.h"
#include "Notifications/Interface/IAndroidGoodiesNotificationBigPictureStyle.h"
#include "Notifications/Interface/IAndroidGoodiesNotificationBigTextStyle.h"
#include "Notifications/Interface/IAndroidGoodiesNotificationInboxStyle.h"
#include "Notifications/Interface/IAndroidGoodiesNotificationMessageStyle.h"
#include "Notifications/Interface/IAndroidGoodiesNotification.h"
#include "Templates/SharedPointer.h"
#include "Containers/UnrealString.h"

class IAndroidGoodiesNotificationBuilder
{
public:
	virtual ~IAndroidGoodiesNotificationBuilder() = default;

	virtual TSharedPtr<IAndroidGoodiesNotification> Build() = 0;
	virtual void SetTitle(FString Title) = 0;
	virtual void SetText(FString Text) = 0;
	virtual void SetSmallIcon(FString FileName) = 0;
	virtual void SetAutoCancel(bool bAutoCancel) = 0;
	virtual void SetBadgeIconType(NotificationBadgeIconType BadgeIconType) = 0;
	virtual void SetCategory(NotificationCategory Category) = 0;
	virtual void SetColor(FColor Color) = 0;
	virtual void SetColorized(bool bColorized) = 0;
	virtual void SetContentInfo(FString Text) = 0;
	virtual void SetDefaults(FAGNotificationDefaults Defaults) = 0;
	virtual void SetGroup(FString GroupKey) = 0;
	virtual void SetGroupAlertBehaviour(NotificationGroupAlert Behaviour) = 0;
	virtual void SetGroupSummary(bool bSummary) = 0;
	virtual void SetLargeIcon(UTexture2D* Icon) = 0;
	virtual void SetLights(FColor Color, int InMilliSeconds, int OutMilliSeconds) = 0;
	virtual void SetLocalOnly(bool bLocalOnly) = 0;
	virtual void SetNumber(int Number) = 0;
	virtual void SetOngoing(bool bOngoing) = 0;
	virtual void SetAlertOnce(bool bAlertOnce) = 0;
	virtual void SetPriority(NotificationPriority Priority) = 0;
	virtual void SetProgress(int Current, int Max, bool bIndeterminate) = 0;
	virtual void SetPublicVersion(TSharedPtr<IAndroidGoodiesNotification> Notification) = 0;
	virtual void SetShortcutId(FString ID) = 0;
	virtual void SetShowWhen(bool bShowWhen) = 0;
	virtual void SetSortKey(FString Key) = 0;
	virtual void SetSound(FString Path) = 0;
	virtual void SetSubText(FString Text) = 0;
	virtual void SetTicker(FString Text) = 0;
	virtual void SetTimeoutAfter(int MilliSeconds) = 0;
	virtual void SetUsesChronometer(bool bUsesChronometer) = 0;
	virtual void SetVibrate(TArray<float> Pattern) = 0;
	virtual void SetVisibility(NotificationVisibility Visibility) = 0;
	virtual void SetWhen(FDateTime DateTime) = 0;
	virtual void SetBigTextStyle(TSharedPtr<IAndroidGoodiesNotificationBigTextStyle> Style) = 0;
	virtual void SetMessagingStyle(TSharedPtr<IAndroidGoodiesNotificationMessageStyle> Style) = 0;
	virtual void SetBigPictureStyle(TSharedPtr<IAndroidGoodiesNotificationBigPictureStyle> Style) = 0;
	virtual void SetInboxStyle(TSharedPtr<IAndroidGoodiesNotificationInboxStyle> Style) = 0;
	virtual void AddOpenUrlAction(FString IconName, FString Title, FString URL) = 0;
};
