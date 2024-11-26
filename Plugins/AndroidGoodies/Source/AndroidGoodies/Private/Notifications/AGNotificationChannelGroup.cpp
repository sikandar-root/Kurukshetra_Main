// Copyright (c) 2019 Nineva Studios

#include "Notifications/AGNotificationChannelGroup.h"
#include "Notifications/AGNotificationManager.h"
#include "Notifications/Interface/IAndroidGoodiesNotificationChannelGroup.h"

UAGNotificationChannelGroup::~UAGNotificationChannelGroup()
{
}

FString UAGNotificationChannelGroup::GetId()
{
	FString Result;
	if (!IsValid())
	{
		return Result;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		return NativeNotificationChannelGroup->GetId();
	}

	return Result;
}

FString UAGNotificationChannelGroup::GetName()
{
	FString Result;
	if (!IsValid())
	{
		return Result;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		return NativeNotificationChannelGroup->GetName();
	}

	return Result;
}

FString UAGNotificationChannelGroup::GetDescription()
{
	FString Result;
	if (!IsValid())
	{
		return Result;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		return NativeNotificationChannelGroup->GetDescription();
	}

	return Result;
}

UAGNotificationChannelGroup* UAGNotificationChannelGroup::SetDescription(FString Description)
{
	if (!IsValid())
	{
		return this;
	}
	if (UAGDeviceInfo::GetSdkInt() >= 28)
	{
		NativeNotificationChannelGroup->SetDescription(Description);
	}

	return this;
}

bool UAGNotificationChannelGroup::IsBlocked()
{
	if (!IsValid())
	{
		return false;
	}
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		return NativeNotificationChannelGroup->IsBlocked();
	}

	return true;
}

TArray<UAGNotificationChannel*> UAGNotificationChannelGroup::GetChannels()
{
	TArray<UAGNotificationChannel*> Result;
	if (!IsValid())
	{
		return Result;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		const auto AndroidGoodiesNotificationChannels = NativeNotificationChannelGroup->GetChannels();
		for (const auto& NativeChannel : AndroidGoodiesNotificationChannels)
		{
			UAGNotificationChannel* Channel = NewObject<UAGNotificationChannel>();
			Channel->Init(NativeChannel);
			Result.Add(Channel);
		}
	}

	return Result;
}

void UAGNotificationChannelGroup::Init(TSharedPtr<IAndroidGoodiesNotificationChannelGroup> Group)
{
	NativeNotificationChannelGroup = Group;
}

TSharedPtr<IAndroidGoodiesNotificationChannelGroup> UAGNotificationChannelGroup::GetNativeNotificationChannelGroup()
{
	return NativeNotificationChannelGroup;
}

bool UAGNotificationChannelGroup::IsValid() const
{
	return NativeNotificationChannelGroup != nullptr;
}
