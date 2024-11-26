// Copyright (c) 2019 Nineva Studios

#include "Notifications/AGNotificationMessageStyle.h"
#include "Notifications/Interface/IAndroidGoodiesNotificationMessageStyle.h"

void UAGNotificationMessageStyle::Init(TSharedPtr<IAndroidGoodiesNotificationMessageStyle> Style)
{
	NativeStyle = Style;
}

TSharedPtr<IAndroidGoodiesNotificationMessageStyle> UAGNotificationMessageStyle::GetNativeStyle()
{
	return NativeStyle;
}

bool UAGNotificationMessageStyle::IsValid() const
{
	return NativeStyle != nullptr;
}

UAGNotificationMessageStyle::~UAGNotificationMessageStyle()
{
}


UAGNotificationMessageStyle* UAGNotificationMessageStyle::AddMessage(FString Text, FDateTime TimeStamp, FString Sender)
{
	if (!IsValid())
	{
		return this;
	}
	NativeStyle->AddMessage(Text, TimeStamp, Sender);
	return this;
}

UAGNotificationMessageStyle* UAGNotificationMessageStyle::SetConversationTitle(FString Title)
{
	if (!IsValid())
	{
		return this;
	}
	NativeStyle->SetConversationTitle(Title);
	return this;
}

UAGNotificationMessageStyle* UAGNotificationMessageStyle::SetGroupConversation(bool bIsGroupConversation)
{
	if (!IsValid())
	{
		return this;
	}
	NativeStyle->SetGroupConversation(bIsGroupConversation);
	return this;
}
