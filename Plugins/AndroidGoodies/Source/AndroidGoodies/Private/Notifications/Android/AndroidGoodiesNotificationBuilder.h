#pragma once
#include "Containers/UnrealString.h"
#include "Notifications/Interface/IAndroidGoodiesNotificationBuilder.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"

class AndroidGoodiesNotificationBuilder : public IAndroidGoodiesNotificationBuilder
{
public:
	virtual ~AndroidGoodiesNotificationBuilder() override;
	AndroidGoodiesNotificationBuilder(jobject Builder);
	virtual TSharedPtr<IAndroidGoodiesNotification> Build() override;
	virtual void SetTitle(FString Title) override;
	virtual void SetText(FString Text) override;
	virtual void SetSmallIcon(FString FileName) override;
	virtual void SetAutoCancel(bool bAutoCancel) override;
	virtual void SetBadgeIconType(NotificationBadgeIconType BadgeIconType) override;
	virtual void SetCategory(NotificationCategory Category) override;
	virtual void SetColor(FColor Color) override;
	virtual void SetColorized(bool bColorized) override;
	virtual void SetContentInfo(FString Text) override;
	virtual void SetDefaults(FAGNotificationDefaults Defaults) override;
	virtual void SetGroup(FString GroupKey) override;
	virtual void SetGroupAlertBehaviour(NotificationGroupAlert Behaviour) override;
	virtual void SetGroupSummary(bool bSummary) override;
	virtual void SetLargeIcon(UTexture2D* Icon) override;
	virtual void SetLights(FColor Color, int InMilliSeconds, int OutMilliSeconds) override;
	virtual void SetLocalOnly(bool bLocalOnly) override;
	virtual void SetNumber(int Number) override;
	virtual void SetOngoing(bool bOngoing) override;
	virtual void SetAlertOnce(bool bAlertOnce) override;
	virtual void SetPublicVersion(TSharedPtr<IAndroidGoodiesNotification> Notification) override;
	virtual void SetShortcutId(FString ID) override;
	virtual void SetShowWhen(bool bShowWhen) override;
	virtual void SetSortKey(FString Key) override;
	virtual void SetSound(FString Path) override;
	virtual void SetSubText(FString Text) override;
	virtual void SetTicker(FString Text) override;
	virtual void SetTimeoutAfter(int MilliSeconds) override;
	virtual void SetUsesChronometer(bool bUsesChronometer) override;
	virtual void SetVibrate(TArray<float> Pattern) override;
	virtual void SetVisibility(NotificationVisibility Visibility) override;
	virtual void SetWhen(FDateTime DateTime) override;
	virtual void SetBigTextStyle(TSharedPtr<IAndroidGoodiesNotificationBigTextStyle> Style) override;
	virtual void SetMessagingStyle(TSharedPtr<IAndroidGoodiesNotificationMessageStyle> Style) override;
	virtual void SetBigPictureStyle(TSharedPtr<IAndroidGoodiesNotificationBigPictureStyle> Style) override;
	virtual void SetInboxStyle(TSharedPtr<IAndroidGoodiesNotificationInboxStyle> Style) override;
	virtual void AddOpenUrlAction(FString IconName, FString Title, FString URL) override;
	virtual void SetPriority(NotificationPriority Priority) override;
	virtual void SetProgress(int Current, int Max, bool bIndeterminate) override;

private:
	jobject NativeBuilder;
};
