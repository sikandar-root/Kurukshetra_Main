#pragma once

#include "Notifications/AGNotificationChannelGroup.h"
#include "Notifications/Enums/AGInterruptionFilter.h"
#include "Notifications/AGNotificationChannel.h"
#include "Notifications/AGNotification.h"
#include "Engine/Texture2D.h"

class IAndroidGoodiesNotificationChannelGroup;
class IAndroidGoodiesNotificationChannel;
class IAndroidGoodiesNotification;
class IAndroidGoodiesNotificationBuilder;
class IAndroidGoodiesNotificationMessageStyle;
class IAndroidGoodiesNotificationInboxStyle;
class IAndroidGoodiesNotificationBigTextStyle;
class IAndroidGoodiesNotificationBigPictureStyle;

class IAndroidGoodiesNotificationManager
{
public:
	virtual ~IAndroidGoodiesNotificationManager() = default;

	// Constructors
	virtual TSharedPtr<IAndroidGoodiesNotificationMessageStyle> CreateMessageStyle(FString UserDisplayName) = 0;
	virtual TSharedPtr<IAndroidGoodiesNotificationInboxStyle> CreateInboxStyle() = 0;
	virtual TSharedPtr<IAndroidGoodiesNotificationBigTextStyle> CreateBigTextStyle(FString BigText) = 0;
	virtual TSharedPtr<IAndroidGoodiesNotificationBigPictureStyle> CreateBigPictureStyle(UTexture2D* BigPicture) = 0;
	virtual TSharedPtr<IAndroidGoodiesNotificationBuilder> NewNotificationBuilder(FString ChannelId, TMap<FString, FString> AdditionalData) = 0;
	virtual TSharedPtr<IAndroidGoodiesNotificationChannel> NewNotificationChannel(FString ID, FString Name, ChannelImportance Importance) = 0;
	virtual TSharedPtr<IAndroidGoodiesNotificationChannelGroup> NewNotificationChannelGroup(FString ID, FString Name) = 0;

	virtual void Notify(TSharedPtr<IAndroidGoodiesNotification> Notification, int ID) = 0;
	virtual void CreateNotificationChannel(TSharedPtr<IAndroidGoodiesNotificationChannel> Channel) = 0;
	virtual void CreateNotificationChannelGroup(TSharedPtr<IAndroidGoodiesNotificationChannelGroup> Group) = 0;
	virtual bool WasApplicationOpenViaNotification() = 0;
	virtual void OpenExactAlarmSettingPage() = 0;
	virtual bool CanScheduleExactNotifications() = 0;
	virtual void CancelNotification(int ID) = 0;
	virtual void CancelAllNotifications() = 0;
	virtual TEnumAsByte<ChannelImportance> GetCurrentImportance() = 0;
	virtual TEnumAsByte<InterruptionFilter> GetCurrentInterruptionFilter() = 0;
	virtual void SetCurrentInterruptionFilter(InterruptionFilter Filter) = 0;
	virtual void ScheduleNotification(TSharedPtr<IAndroidGoodiesNotification> Notification, int ID, FTimespan NotifyAfter) = 0;
	virtual void ScheduleRepeatingNotification(TSharedPtr<IAndroidGoodiesNotification> Notification, int ID, FTimespan NotifyAfter, FTimespan RepeatAfter) = 0;
	virtual void CancelScheduledNotification(int ID) = 0;
	virtual FString GetNotificationDataForKey(FString Key) = 0;
	virtual TSharedPtr<IAndroidGoodiesNotificationChannel> GetNotificationChannel(FString ChannelId) = 0;
	virtual TArray<TSharedPtr<IAndroidGoodiesNotificationChannel>> GetNotificationChannels() = 0;
	virtual void DeleteNotificationChannel(FString ChannelId) = 0;
	virtual TSharedPtr<IAndroidGoodiesNotificationChannelGroup> GetNotificationChannelGroup(FString GroupId) = 0;
	virtual TArray<TSharedPtr<IAndroidGoodiesNotificationChannelGroup>> GetNotificationChannelGroups() = 0;
	virtual void DeleteNotificationChannelGroup(FString GroupId) = 0;
	virtual void OpenNotificationChannelSettings(FString ChannelId) = 0;
};

