// Copyright (c) 2019 Nineva Studios

#include "Notifications/AGNotificationBigTextStyle.h"
#include "Notifications/Interface/IAndroidGoodiesNotificationBigTextStyle.h"

void UAGNotificationBigTextStyle::Init(TSharedPtr<IAndroidGoodiesNotificationBigTextStyle> Style)
{
	NativeStyle = Style;
}

TSharedPtr<IAndroidGoodiesNotificationBigTextStyle> UAGNotificationBigTextStyle::GetNativeStyle()
{
	return NativeStyle;
}

bool UAGNotificationBigTextStyle::IsValid() const
{
	return NativeStyle != nullptr;
}

UAGNotificationBigTextStyle::~UAGNotificationBigTextStyle()
{
}

UAGNotificationBigTextStyle* UAGNotificationBigTextStyle::SetBigContentTitle(FString Title)
{
	if (!IsValid())
	{
		return this;
	}
	NativeStyle->SetBigContentTitle(Title);
	return this;
}

UAGNotificationBigTextStyle* UAGNotificationBigTextStyle::SetSummaryText(FString Summary)
{
	if (!IsValid())
	{
		return this;
	}
	NativeStyle->SetSummaryText(Summary);
	return this;
}
