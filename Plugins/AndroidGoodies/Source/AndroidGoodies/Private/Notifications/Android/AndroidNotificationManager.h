#pragma once

#include "Notifications/Interface/IAndroidGoodiesNotificationManager.h"

class AndroidNotificationManager : public IAndroidGoodiesNotificationManager
{
public:
	virtual TSharedPtr<IAndroidGoodiesNotificationMessageStyle> CreateMessageStyle(FString UserDisplayName) override;
	virtual TSharedPtr<IAndroidGoodiesNotificationInboxStyle> CreateInboxStyle() override;
	virtual TSharedPtr<IAndroidGoodiesNotificationBigTextStyle> CreateBigTextStyle(FString BigText) override;
	virtual TSharedPtr<IAndroidGoodiesNotificationBigPictureStyle> CreateBigPictureStyle(UTexture2D* BigPicture) override;
	virtual TSharedPtr<IAndroidGoodiesNotificationBuilder> NewNotificationBuilder(FString ChannelId, TMap<FString, FString> AdditionalData) override;
	virtual TSharedPtr<IAndroidGoodiesNotificationChannel> NewNotificationChannel(FString ID, FString Name, ChannelImportance Importance) override;
	virtual TSharedPtr<IAndroidGoodiesNotificationChannelGroup> NewNotificationChannelGroup(FString ID, FString Name) override;

	virtual ~AndroidNotificationManager() override;
	virtual void Notify(TSharedPtr<IAndroidGoodiesNotification> Notification, int ID) override;
	virtual void CreateNotificationChannel(TSharedPtr<IAndroidGoodiesNotificationChannel> Channel) override;
	virtual void CreateNotificationChannelGroup(TSharedPtr<IAndroidGoodiesNotificationChannelGroup> Group) override;
	virtual void OpenExactAlarmSettingPage() override;
	virtual bool CanScheduleExactNotifications() override;
	virtual bool WasApplicationOpenViaNotification() override;
	virtual void CancelNotification(int ID) override;
	virtual void CancelAllNotifications() override;
	virtual TEnumAsByte<ChannelImportance> GetCurrentImportance() override;
	virtual TEnumAsByte<InterruptionFilter> GetCurrentInterruptionFilter() override;
	virtual void SetCurrentInterruptionFilter(InterruptionFilter Filter) override;
	virtual void ScheduleNotification(TSharedPtr<IAndroidGoodiesNotification> Notification, int ID, FTimespan NotifyAfter) override;
	virtual void ScheduleRepeatingNotification(TSharedPtr<IAndroidGoodiesNotification> Notification, int ID, FTimespan NotifyAfter, FTimespan RepeatAfter) override;
	virtual void CancelScheduledNotification(int ID) override;
	virtual FString GetNotificationDataForKey(FString Key) override;
	virtual TSharedPtr<IAndroidGoodiesNotificationChannel> GetNotificationChannel(FString ChannelId) override;
	virtual TArray<TSharedPtr<IAndroidGoodiesNotificationChannel>> GetNotificationChannels() override;
	virtual void DeleteNotificationChannel(FString ChannelId) override;
	virtual TSharedPtr<IAndroidGoodiesNotificationChannelGroup> GetNotificationChannelGroup(FString GroupId) override;
	virtual TArray<TSharedPtr<IAndroidGoodiesNotificationChannelGroup>> GetNotificationChannelGroups() override;
	virtual void DeleteNotificationChannelGroup(FString GroupId) override;
	virtual void OpenNotificationChannelSettings(FString ChannelId) override;

	static const ANSICHAR* NotificationHelperClassName;
};
