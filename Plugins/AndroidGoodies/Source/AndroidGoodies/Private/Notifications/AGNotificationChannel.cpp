// Copyright (c) 2019 Nineva Studios

#include "Notifications/AGNotificationChannel.h"
#include "Notifications/AGNotificationManager.h"
#include "Interface/IAndroidGoodiesNotificationChannel.h"

UAGNotificationChannel::~UAGNotificationChannel()
{
}

FString UAGNotificationChannel::GetId()
{
	FString Result;

	if (!IsValid())
	{
		return Result;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		return NativeNotificationChannel->GetId();
	}

	return Result;
}

UAGNotificationChannel* UAGNotificationChannel::SetBypassDnd(bool Bypass)
{
	if (!IsValid())
	{
		return this;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		NativeNotificationChannel->SetBypassDnd(Bypass);
	}

	return this;
}

bool UAGNotificationChannel::CanBypassDnd()
{
	if (!IsValid())
	{
		return false;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		return NativeNotificationChannel->CanBypassDnd();
	}

	return false;
}

UAGNotificationChannel* UAGNotificationChannel::SetShowBadge(bool bShow)
{
	if (!IsValid())
	{
		return this;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		NativeNotificationChannel->SetShowBadge(bShow);
	}

	return this;
}

bool UAGNotificationChannel::CanShowBadge()
{
	if (!IsValid())
	{
		return false;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		return NativeNotificationChannel->CanShowBadge();
	}

	return false;
}

UAGNotificationChannel* UAGNotificationChannel::SetEnableLights(bool bEnable)
{
	if (!IsValid())
	{
		return this;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		NativeNotificationChannel->SetEnableLights(bEnable);
	}

	return this;
}

bool UAGNotificationChannel::ShouldShowLights()
{
	if (!IsValid())
	{
		return false;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		return NativeNotificationChannel->ShouldShowLights();
	}

	return false;
}

UAGNotificationChannel* UAGNotificationChannel::SetEnableVibration(bool bEnable)
{
	if (!IsValid())
	{
		return this;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		NativeNotificationChannel->SetEnableVibration(bEnable);
	}

	return this;
}

bool UAGNotificationChannel::ShouldVibrate()
{
	if (!IsValid())
	{
		return false;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		return NativeNotificationChannel->ShouldVibrate();
	}

	return false;
}

FAGAudioAttributes UAGNotificationChannel::GetAudioAttributes()
{
	const FAGAudioAttributes Attributes;

	if (!IsValid())
	{
		return Attributes;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		return NativeNotificationChannel->GetAudioAttributes();
	}

	return Attributes;
}

UAGNotificationChannel* UAGNotificationChannel::SetDescription(FString Description)
{
	if (!IsValid())
	{
		return this;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		NativeNotificationChannel->SetDescription(Description);
	}

	return this;
}

FString UAGNotificationChannel::GetDescription()
{
	FString Result;

	if (!IsValid())
	{
		return Result;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		return NativeNotificationChannel->GetDescription();
	}

	return Result;
}

UAGNotificationChannel* UAGNotificationChannel::SetImportance(ChannelImportance Importance)
{
	if (!IsValid())
	{
		return this;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		NativeNotificationChannel->SetImportance(Importance);
	}

	return this;
}

ChannelImportance UAGNotificationChannel::GetImportance()
{
	if (!IsValid())
	{
		return ImportanceDefault;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		return NativeNotificationChannel->GetImportance();
	}

	return ImportanceDefault;
}

UAGNotificationChannel* UAGNotificationChannel::SetLightColor(FColor Color)
{
	if (!IsValid())
	{
		return this;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		NativeNotificationChannel->SetLightColor(Color);
	}

	return this;
}

FColor UAGNotificationChannel::GetLightColor()
{
	const FColor Color = FColor::Magenta;

	if (!IsValid())
	{
		return Color;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		return NativeNotificationChannel->GetLightColor();
	}

	return Color;
}

UAGNotificationChannel* UAGNotificationChannel::SetLockScreenVisibility(NotificationVisibility Visibility)
{
	if (!IsValid())
	{
		return this;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		NativeNotificationChannel->SetLockScreenVisibility(Visibility);
	}

	return this;
}

NotificationVisibility UAGNotificationChannel::GetLockScreenVisibility()
{
	if (!IsValid())
	{
		return VisibilityPrivate;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		return NativeNotificationChannel->GetLockScreenVisibility();
	}

	return VisibilityPrivate;
}

FString UAGNotificationChannel::GetName()
{
	FString Result;
	if (!IsValid())
	{
		return Result;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		return NativeNotificationChannel->GetName();
	}

	return Result;
}

FString UAGNotificationChannel::GetSoundPath()
{
	FString result;
	if (!IsValid())
	{
		return result;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		return NativeNotificationChannel->GetSoundPath();
	}

	return result;
}

UAGNotificationChannel* UAGNotificationChannel::SetVibrationPattern(TArray<float> Pattern)
{
	if (!IsValid())
	{
		return this;
	}


	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		NativeNotificationChannel->SetVibrationPattern(Pattern);
	}

	return this;
}

TArray<float> UAGNotificationChannel::GetVibrationPattern()
{
	TArray<float> Result;
	if (!IsValid())
	{
		return Result;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		return NativeNotificationChannel->GetVibrationPattern();
	}

	return Result;
}

UAGNotificationChannel* UAGNotificationChannel::SetSound(FString FilePath, FAGAudioAttributes Attributes)
{
	if (!IsValid())
	{
		return this;
	}


	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		NativeNotificationChannel->SetSound(FilePath, Attributes);
	}

	return this;
}

FString UAGNotificationChannel::GetGroupId()
{
	FString Result;
	if (!IsValid())
	{
		return Result;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		return NativeNotificationChannel->GetGroupId();
	}

	return Result;
}

UAGNotificationChannel* UAGNotificationChannel::SetGroup(FString GroupId)
{
	if (!IsValid())
	{
		return this;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		NativeNotificationChannel->SetGroup(GroupId);
	}

	return this;
}

TSharedPtr<IAndroidGoodiesNotificationChannel> UAGNotificationChannel::GetNativeNotificationChannel() const
{
	return NativeNotificationChannel;
}

bool UAGNotificationChannel::IsValid() const
{
	return NativeNotificationChannel != nullptr;
}

void UAGNotificationChannel::Init(TSharedPtr<IAndroidGoodiesNotificationChannel> Channel)
{
	NativeNotificationChannel = Channel;
}
