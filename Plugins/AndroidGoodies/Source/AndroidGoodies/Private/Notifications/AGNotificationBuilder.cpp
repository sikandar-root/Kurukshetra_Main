// Copyright (c) 2019 Nineva Studios

#include "Notifications/AGNotificationBuilder.h"

#include "Interface/IAndroidGoodiesNotificationBuilder.h"
#include "Notifications/AGNotificationManager.h"

UAGNotificationBuilder::~UAGNotificationBuilder()
{
}

UAGNotification* UAGNotificationBuilder::Build()
{
	UAGNotification* Notification = NewObject<UAGNotification>();
	if (!IsValid())
	{
		return Notification;
	}
	Notification->Init(NativeBuilder->Build());
	return Notification;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetTitle(FString Title)
{
	if (!IsValid())
	{
		return this;
	}
	NativeBuilder->SetTitle(Title);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetText(FString Text)
{
	if (!IsValid())
	{
		return this;
	}
	NativeBuilder->SetText(Text);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetSmallIcon(FString FileName)
{
	if (!IsValid())
	{
		return this;
	}
	NativeBuilder->SetSmallIcon(FileName);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetAutoCancel(bool bAutoCancel)
{
	if (!IsValid())
	{
		return this;
	}
	NativeBuilder->SetAutoCancel(bAutoCancel);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetBadgeIconType(NotificationBadgeIconType BadgeIconType)
{
	if (!IsValid())
	{
		return this;
	}
	NativeBuilder->SetBadgeIconType(BadgeIconType);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetCategory(NotificationCategory Category)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetCategory(Category);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetColor(FColor Color)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetColor(Color);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetColorized(bool bColorized)
{
	if (!IsValid())
	{
		return this;
	}
	NativeBuilder->SetColorized(bColorized);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetContentInfo(FString text)
{
	if (!IsValid())
	{
		return this;
	}
	NativeBuilder->SetContentInfo(text);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetDefaults(FAGNotificationDefaults Defaults)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetDefaults(Defaults);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetGroup(FString GroupKey)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetGroup(GroupKey);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetGroupAlertBehaviour(NotificationGroupAlert Behaviour)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetGroupAlertBehaviour(Behaviour);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetGroupSummary(bool bSummary)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetGroupSummary(bSummary);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetLargeIcon(UTexture2D* Icon)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetLargeIcon(Icon);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetLights(FColor Color, int InMilliSeconds, int OutMilliSeconds)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetLights(Color, InMilliSeconds, OutMilliSeconds);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetLocalOnly(bool bLocalOnly)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetLocalOnly(bLocalOnly);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetNumber(int Number)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetNumber(Number);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetOngoing(bool bOngoing)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetOngoing(bOngoing);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetAlertOnce(bool bAlertOnce)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetAlertOnce(bAlertOnce);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetPriority(NotificationPriority Priority)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetPriority(Priority);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetProgress(int Current, int Max, bool bIndeterminate)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetProgress(Current, Max, bIndeterminate);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetPublicVersion(UAGNotification* Notification)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetPublicVersion(Notification->GetNativeNotification());
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetShortcutId(FString ID)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetShortcutId(ID);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetShowWhen(bool bShowWhen)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetShowWhen(bShowWhen);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetSortKey(FString Key)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetSortKey(Key);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetSound(FString Path)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetSound(Path);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetSubText(FString Text)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetSubText(Text);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetTicker(FString Text)
{
	if (!IsValid())
	{
		return this;
	}
	NativeBuilder->SetTicker(Text);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetTimeoutAfter(int MilliSeconds)
{
	if (!IsValid())
	{
		return this;
	}
	NativeBuilder->SetTimeoutAfter(MilliSeconds);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetUsesChronometer(bool bUsesChronometer)
{
	if (!IsValid())
	{
		return this;
	}
	NativeBuilder->SetUsesChronometer(bUsesChronometer);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetVibrate(TArray<float> Pattern)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetVibrate(Pattern);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetVisibility(NotificationVisibility Visibility)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetVisibility(Visibility);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetWhen(FDateTime DateTime)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetWhen(DateTime);
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetBigTextStyle(UAGNotificationBigTextStyle* Style)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetBigTextStyle(Style->GetNativeStyle());
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetMessagingStyle(UAGNotificationMessageStyle* Style)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetMessagingStyle(Style->GetNativeStyle());
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetBigPictureStyle(UAGNotificationBigPictureStyle* Style)
{
	if (!IsValid())
	{
		return this;
	}
	NativeBuilder->SetBigPictureStyle(Style->GetNativeStyle());
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetInboxStyle(UAGNotificationInboxStyle* Style)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->SetInboxStyle(Style->GetNativeStyle());
	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::AddOpenUrlAction(FString IconName, FString Title, FString URL)
{
	if (!IsValid())
	{
		return this;
	}

	NativeBuilder->AddOpenUrlAction(IconName, Title, URL);
	return this;
}

void UAGNotificationBuilder::Init(TSharedPtr<IAndroidGoodiesNotificationBuilder> Builder)
{
	NativeBuilder = Builder;
}

TSharedPtr<IAndroidGoodiesNotificationBuilder> UAGNotificationBuilder::GetNativeBuilder() const
{
	return NativeBuilder;
}

bool UAGNotificationBuilder::IsValid() const
{
	return NativeBuilder != nullptr;
}
