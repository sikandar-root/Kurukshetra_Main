// Copyright (c) 2019 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGNotification.h"
#include "AGNotificationChannel.h"
#include "AGNotificationChannelGroup.h"
#include "AGNotificationBuilder.h"
#include "Enums/AGChannelImportance.h"
#include "Enums/AGInterruptionFilter.h"
#include "AGDeviceInfoBPL.h"

class IAndroidGoodiesNotificationManager;

#include "AGNotificationManager.generated.h"

UCLASS()
class ANDROIDGOODIES_API UAGNotificationManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Constructor.
	*
	* @param ChannelId - the constructed Notification will be posted on this NotificationChannel.
	* @param AdditionalData - custom user notification data to be later retrieved with 
	* UAGNotificationManager.GetNotificationDataForKey() if app was launched from notification.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications", meta = (AutoCreateRefTerm = "additionalData"))
	static UAGNotificationBuilder* NewNotificationBuilder(FString ChannelId, TMap<FString, FString> AdditionalData);

	/**
	* Constructor.
	*
	* @param ID - the id of the channel. Must be unique per package. The value may be truncated if it is too long.
	* @param Name - the user visible name of the channel. The recommended maximum length is 40 characters; the value may be truncated if it is too long.
	* @param Importance - the importance of the channel. This controls how interruptive notifications posted to this channel are.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static UAGNotificationChannel* NewNotificationChannel(FString ID, FString Name, ChannelImportance Importance);

	/**
	* Post a notification to be shown in the status bar, stream, etc.
	*
	* @param Notification - the notification to post to the system.
	* @param ID - the ID of the notification.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static void Notify(UAGNotification* Notification, int ID);

	/**
	* Creates a notification channel that notifications can be posted to.
	* This can also be used to restore a deleted channel and to update an existing channel's name,
	* description, group, and/or importance. The name and description should only be changed
	* if the locale changes or in response to the user renaming this channel.
	* For example, if a user has a channel named 'John Doe' that represents messages from a 'John Doe',
	* and 'John Doe' changes his name to 'John Smith,' the channel can be renamed to match.
	* The importance of an existing channel will only be changed if the new importance is lower
	* than the current value and the user has not altered any settings on this channel.
	* The group an existing channel will only be changed if the channel does not already
	* belong to a group. All other fields are ignored for channels that already exist.
	*
	* @param Channel - the channel to create. Note that the created channel may differ from this value.
	* If the provided channel is malformed, a RemoteException will be thrown.
	* This value must never be null.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static void CreateNotificationChannel(UAGNotificationChannel* Channel);

	/**
	* Create a group container for NotificationChannel objects. This can be used to rename an existing group.
	* Group information is only used for presentation, not for behavior. Groups are optional for channels,
	* and you can have a mix of channels that belong to groups and channels that do not.
	* For example, if your application supports multiple accounts, and those accounts will have similar channels,
	* you can create a group for each account with account specific labels instead of appending account
	* information to each channel's label.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static void CreateNotificationChannelGroup(UAGNotificationChannelGroup* Group);

	/**
	* Convenience property to check if the app was opened from notification.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static bool WasApplicationOpenViaNotification();

	/**
	* Cancel a previously shown notification. If it's transient, the view will be hidden.
	* If it's persistent, it will be removed from the status bar.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static void CancelNotification(int ID);

	/**
	* Cancel all previously shown notifications.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static void CancelAllNotifications();

	/**
	* Get the user specified importance for notifications from the calling package.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static TEnumAsByte<ChannelImportance> GetCurrentImportance();

	/**
	* Get the current notification interruption filter. The interruption filter defines which notifications
	* are allowed to interrupt the user (e.g. via sound & vibration) and is applied globally.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static TEnumAsByte<InterruptionFilter> GetCurrentInterruptionFilter();

	/**
	* Set the current notification interruption filter. The interruption filter defines which notifications
	* are allowed to interrupt the user (e.g. via sound & vibration) and is applied globally.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static void SetCurrentInterruptionFilter(InterruptionFilter Filter);

	/**
	* Property to check if the new notification channels API is supported on the current device.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static bool AreNotificationChannelsSupported()
	{
		return UAGDeviceInfo::GetSdkInt() >= 26;
	}

	/**
	* Whether the user has permission to schedule exact notifications.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static bool CanScheduleExactNotifications();

	/**
	* Open a screen where the user can grant permission to schedule exact alarms (For Android 12+).
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static void OpenExactAlarmSettingPage();

	/**
	* Schedule a notification to be shown in the status bar, stream, etc. after the specified time.
	*
	* @param Notification - the notification to post to the system.
	* @param ID - the ID of the notification.
	* @param NotifyAfter - timespan to pass before the actual notifying.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static void ScheduleNotification(UAGNotification* Notification, int ID, FTimespan NotifyAfter);

	/**
	* Schedule a repeating notification to be shown in the status bar, stream, etc. after the specified time.
	*
	* @param Notification - the notification to post to the system.
	* @param ID - the ID of the notification.
	* @param NotifyAfter - timespan to pass before the actual notifying.
	* @param RepeatAfter - timespan to pass before the next notifying.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static void ScheduleRepeatingNotification(UAGNotification* Notification, int ID, FTimespan NotifyAfter, FTimespan RepeatAfter);

	/**
	* Cancel previously scheduled notification.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static void CancelScheduledNotification(int ID);

	/**
	* Try to retrieve extra data, provided with the NewNotificationBuilder additional data dictionary.
	* This data can only be retrieved if the application was open by tapping the respective notification.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static FString GetNotificationDataForKey(FString Key);

	/**
	* Return the notification channel settings for a given channel id.
	* The channel must belong to your package, or it will not be returned.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static UAGNotificationChannel* GetNotificationChannel(FString ChannelId);

	/**
	* Return all notification channels belonging to the calling package.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static TArray<UAGNotificationChannel*> GetNotificationChannels();

	/**
	* Delete the given notification channel.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static void DeleteNotificationChannel(FString ChannelId);

	/**
	* Get the notification channel group settings for a given channel group id.
	* The channel group must belong to your package, or null will be returned.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static UAGNotificationChannelGroup* GetNotificationChannelGroup(FString GroupId);

	/**
	* Return all notification channel groups belonging to the calling package.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static TArray<UAGNotificationChannelGroup*> GetNotificationChannelGroups();

	/**
	* Constructor.
	*
	* @param ID - the id of the group. Must be unique per package. The value may be truncated if it is too long.
	* @param Name - the user visible name of the group. The recommended maximum length is 40 characters; the value may be truncated if it is too long.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static UAGNotificationChannelGroup* NewNotificationChannelGroup(FString ID, FString Name);

	/**
	* Delete the given notification channel group, and all notification channels that belong to it.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static void DeleteNotificationChannelGroup(FString GroupId);

	/**
	* Open system settings window for the selected channel.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static void OpenNotificationChannelSettings(FString ChannelId);

	/**
	* Create a MessageStyle object.
	*
	* @param UserDisplayName - the displayed user name.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static UAGNotificationMessageStyle* CreateMessageStyle(FString UserDisplayName);


	/**
	* Create an InboxStyle object.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static UAGNotificationInboxStyle* CreateInboxStyle();

	/**
	* Create a BigTextStyle object with the big text.
	*
	* @param BigText - the longer text to be displayed in the big form of the template in place of the content text.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static UAGNotificationBigTextStyle* CreateBigTextStyle(FString BigText);

	/**
	* Create a BigPictureStyle object with the big image.
	*
	* @param BigPicture - image to be shown in the big picture view of the notification.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	static UAGNotificationBigPictureStyle* CreateBigPictureStyle(UTexture2D* BigPicture);

private:
	static bool IsValid();
	static TSharedPtr<IAndroidGoodiesNotificationManager> NotificationManagerImpl;
};
