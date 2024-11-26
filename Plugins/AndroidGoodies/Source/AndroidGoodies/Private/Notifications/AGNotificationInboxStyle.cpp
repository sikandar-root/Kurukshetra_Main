// Copyright (c) 2019 Nineva Studios

#include "Notifications/AGNotificationInboxStyle.h"
#include "Notifications/Interface/IAndroidGoodiesNotificationInboxStyle.h"

void UAGNotificationInboxStyle::Init(TSharedPtr<IAndroidGoodiesNotificationInboxStyle> Style)
{
	NativeStyle = Style;
}

TSharedPtr<IAndroidGoodiesNotificationInboxStyle> UAGNotificationInboxStyle::GetNativeStyle()
{
	return NativeStyle;
}

bool UAGNotificationInboxStyle::IsValid() const
{
	return NativeStyle != nullptr;
}

UAGNotificationInboxStyle::~UAGNotificationInboxStyle()
{
}


UAGNotificationInboxStyle* UAGNotificationInboxStyle::AddLine(FString Line)
{
	if (!IsValid())
	{
		return this;
	}

	NativeStyle->AddLine(Line);
	return this;
}

UAGNotificationInboxStyle* UAGNotificationInboxStyle::SetBigContentTitle(FString Title)
{
	if (!IsValid())
	{
		return this;
	}

	NativeStyle->SetBigContentTitle(Title);
	return this;
}

UAGNotificationInboxStyle* UAGNotificationInboxStyle::SetSummaryText(FString Summary)
{
	if (!IsValid())
	{
		return this;
	}
	NativeStyle->SetSummaryText(Summary);
	return this;
}
