// Copyright (c) 2019 Nineva Studios

#include "Notifications/AGNotificationManager.h"

#include "Interface/IAndroidGoodiesNotificationManager.h"

#if PLATFORM_ANDROID
#include "Notifications/Android/AndroidNotificationManager.h"
#endif

#if PLATFORM_ANDROID
TSharedPtr<IAndroidGoodiesNotificationManager> UAGNotificationManager::NotificationManagerImpl = MakeShareable(new AndroidNotificationManager());
#else
TSharedPtr<IAndroidGoodiesNotificationManager> UAGNotificationManager::NotificationManagerImpl = nullptr;
#endif

bool UAGNotificationManager::IsValid()
{
	return NotificationManagerImpl != nullptr;
}

void UAGNotificationManager::Notify(UAGNotification* Notification, int ID)
{
	if (!IsValid())
	{
		return;
	}

	NotificationManagerImpl->Notify(Notification->GetNativeNotification(), ID);
}

void UAGNotificationManager::CreateNotificationChannel(UAGNotificationChannel* Channel)
{
	if (!IsValid())
	{
		return;
	}

	if (AreNotificationChannelsSupported())
	{
		NotificationManagerImpl->CreateNotificationChannel(Channel->GetNativeNotificationChannel());
	}
}

void UAGNotificationManager::CreateNotificationChannelGroup(UAGNotificationChannelGroup* Group)
{
	if (!IsValid())
	{
		return;
	}

	if (AreNotificationChannelsSupported())
	{
		NotificationManagerImpl->CreateNotificationChannelGroup(Group->GetNativeNotificationChannelGroup());
	}
}

bool UAGNotificationManager::WasApplicationOpenViaNotification()
{
	if (!IsValid())
	{
		return false;
	}

	return NotificationManagerImpl->WasApplicationOpenViaNotification();
}

void UAGNotificationManager::CancelNotification(int ID)
{
	if (!IsValid())
	{
		return;
	}

	NotificationManagerImpl->CancelNotification(ID);
}

void UAGNotificationManager::CancelAllNotifications()
{
	if (!IsValid())
	{
		return;
	}

	NotificationManagerImpl->CancelAllNotifications();
}

TEnumAsByte<ChannelImportance> UAGNotificationManager::GetCurrentImportance()
{
	if (!IsValid())
	{
		return ImportanceUnspecified;
	}

	return NotificationManagerImpl->GetCurrentImportance();
}

TEnumAsByte<InterruptionFilter> UAGNotificationManager::GetCurrentInterruptionFilter()
{
	if (!IsValid())
	{
		return FilterUnknown;
	}

	return NotificationManagerImpl->GetCurrentInterruptionFilter();
}

void UAGNotificationManager::SetCurrentInterruptionFilter(InterruptionFilter Filter)
{
	if (!IsValid())
	{
		return;
	}

	NotificationManagerImpl->SetCurrentInterruptionFilter(Filter);
}

bool UAGNotificationManager::CanScheduleExactNotifications()
{
	if (!IsValid())
	{
		return false;
	}

	return NotificationManagerImpl->CanScheduleExactNotifications();
}

void UAGNotificationManager::OpenExactAlarmSettingPage()
{
	if (!IsValid())
	{
		return;
	}

	NotificationManagerImpl->OpenExactAlarmSettingPage();
}

void UAGNotificationManager::ScheduleNotification(UAGNotification* Notification, int ID, FTimespan NotifyAfter)
{
	if (!IsValid())
	{
		return;
	}

	NotificationManagerImpl->ScheduleNotification(Notification->GetNativeNotification(), ID, NotifyAfter);
}

void UAGNotificationManager::ScheduleRepeatingNotification(UAGNotification* Notification, int ID, FTimespan NotifyAfter, FTimespan RepeatAfter)
{
	if (!IsValid())
	{
		return;
	}

	NotificationManagerImpl->ScheduleRepeatingNotification(Notification->GetNativeNotification(), ID, NotifyAfter, RepeatAfter);
}

void UAGNotificationManager::CancelScheduledNotification(int ID)
{
	if (!IsValid())
	{
		return;
	}

	NotificationManagerImpl->CancelScheduledNotification(ID);
}

FString UAGNotificationManager::GetNotificationDataForKey(FString Key)
{
	if (!IsValid())
	{
		FString Result;
		return Result;
	}

	return NotificationManagerImpl->GetNotificationDataForKey(Key);
}

UAGNotificationChannel* UAGNotificationManager::GetNotificationChannel(FString ChannelId)
{
	UAGNotificationChannel* Channel = NewObject<UAGNotificationChannel>();

	if (!IsValid())
	{
		return Channel;
	}

	if (AreNotificationChannelsSupported())
	{
		Channel->Init(NotificationManagerImpl->GetNotificationChannel(ChannelId));
	}

	return Channel;
}

TArray<UAGNotificationChannel*> UAGNotificationManager::GetNotificationChannels()
{
	TArray<UAGNotificationChannel*> Result;

	if (!IsValid())
	{
		return Result;
	}

	if (AreNotificationChannelsSupported())
	{
		for (const auto& NativeChannel : NotificationManagerImpl->GetNotificationChannels())
		{
			UAGNotificationChannel* Channel = NewObject<UAGNotificationChannel>();
			Channel->Init(NativeChannel);
			Result.Add(Channel);
		}
	}

	return Result;
}

void UAGNotificationManager::DeleteNotificationChannel(FString ChannelId)
{
	if (!IsValid())
	{
		return;
	}

	if (AreNotificationChannelsSupported())
	{
		NotificationManagerImpl->DeleteNotificationChannel(ChannelId);
	}
}

UAGNotificationChannelGroup* UAGNotificationManager::GetNotificationChannelGroup(FString GroupId)
{
	UAGNotificationChannelGroup* Group = NewObject<UAGNotificationChannelGroup>();

	if (!IsValid())
	{
		return Group;
	}

	if (AreNotificationChannelsSupported() && UAGDeviceInfo::GetSdkInt() >= 28)
	{
		const auto NativeGroup = NotificationManagerImpl->GetNotificationChannelGroup(GroupId);
		Group->Init(NativeGroup);
	}

	return Group;
}

TArray<UAGNotificationChannelGroup*> UAGNotificationManager::GetNotificationChannelGroups()
{
	TArray<UAGNotificationChannelGroup*> Result;

	if (!IsValid())
	{
		return Result;
	}

	if (AreNotificationChannelsSupported())
	{
		for (auto const& NativeGroup : NotificationManagerImpl->GetNotificationChannelGroups())
		{
			UAGNotificationChannelGroup* Group = NewObject<UAGNotificationChannelGroup>();
			Group->Init(NativeGroup);
			Result.Add(Group);
		}
	}

	return Result;
}

void UAGNotificationManager::DeleteNotificationChannelGroup(FString GroupId)
{
	if (!IsValid())
	{
		return;
	}

	if (AreNotificationChannelsSupported())
	{
		NotificationManagerImpl->DeleteNotificationChannelGroup(GroupId);
	}
}

void UAGNotificationManager::OpenNotificationChannelSettings(FString ChannelId)
{
	if (!IsValid())
	{
		return;
	}

	if (AreNotificationChannelsSupported())
	{
		NotificationManagerImpl->OpenNotificationChannelSettings(ChannelId);
	}
}

UAGNotificationBuilder* UAGNotificationManager::NewNotificationBuilder(FString ChannelId, TMap<FString, FString> AdditionalData)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => UAGNotificationBuilder::InitializeWithChannel()"));

	UAGNotificationBuilder* Builder = NewObject<UAGNotificationBuilder>();
	if (!IsValid())
	{
		return Builder;
	}

	Builder->Init(NotificationManagerImpl->NewNotificationBuilder(ChannelId, AdditionalData));
	return Builder;
}

UAGNotificationChannel* UAGNotificationManager::NewNotificationChannel(const FString ID, const FString Name, ChannelImportance Importance)
{
	UAGNotificationChannel* Channel = NewObject<UAGNotificationChannel>();
	if (!IsValid())
	{
		return Channel;
	}

	if (AreNotificationChannelsSupported())
	{
		const auto NativeChannel = NotificationManagerImpl->NewNotificationChannel(ID, Name, Importance);
		Channel->Init(NativeChannel);
	}

	return Channel;
}

UAGNotificationMessageStyle* UAGNotificationManager::CreateMessageStyle(FString UserDisplayName)
{
	UAGNotificationMessageStyle* Style = NewObject<UAGNotificationMessageStyle>();
	if (!IsValid())
	{
		return Style;
	}


	Style->Init(NotificationManagerImpl->CreateMessageStyle(UserDisplayName));
	return Style;
}

UAGNotificationInboxStyle* UAGNotificationManager::CreateInboxStyle()
{
	UAGNotificationInboxStyle* style = NewObject<UAGNotificationInboxStyle>();
	if (!IsValid())
	{
		return style;
	}

	style->Init(NotificationManagerImpl->CreateInboxStyle());
	// #if PLATFORM_ANDROID
	// 	style->JavaObject = AGMethodCallUtils::CallStaticObjectMethod(UAGNotificationManager::NotificationHelperClassName, "getInboxStyle",
	// 		"()Landroidx/core/app/NotificationCompat$InboxStyle;");
	// #endif
	return style;
}

UAGNotificationBigTextStyle* UAGNotificationManager::CreateBigTextStyle(FString BigText)
{
	UAGNotificationBigTextStyle* Style = NewObject<UAGNotificationBigTextStyle>();
	if (!IsValid())
	{
		return Style;
	}
	Style->Init(NotificationManagerImpl->CreateBigTextStyle(BigText));
	return Style;
}

UAGNotificationBigPictureStyle* UAGNotificationManager::CreateBigPictureStyle(UTexture2D* BigPicture)
{
	UAGNotificationBigPictureStyle* style = NewObject<UAGNotificationBigPictureStyle>();
	if (!IsValid())
	{
		return style;
	}

	style->Init(NotificationManagerImpl->CreateBigPictureStyle(BigPicture));
	return style;
}

UAGNotificationChannelGroup* UAGNotificationManager::NewNotificationChannelGroup(FString ID, FString Name)
{
	UAGNotificationChannelGroup* Group = NewObject<UAGNotificationChannelGroup>();
	if (!IsValid())
	{
		return Group;
	}

	if (AreNotificationChannelsSupported())
	{
		Group->Init(NotificationManagerImpl->NewNotificationChannelGroup(ID, Name));
	}

	return Group;
}
