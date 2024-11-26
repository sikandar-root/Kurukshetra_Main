// Copyright (c) 2019 Nineva Studios

#include "Notifications/AGNotificationBigPictureStyle.h"
#include "Notifications/Interface/IAndroidGoodiesNotificationBigPictureStyle.h"

void UAGNotificationBigPictureStyle::Init(TSharedPtr<IAndroidGoodiesNotificationBigPictureStyle> Style)
{
	NativeStyle = Style;
}

TSharedPtr<IAndroidGoodiesNotificationBigPictureStyle> UAGNotificationBigPictureStyle::GetNativeStyle()
{
	return NativeStyle;
}

bool UAGNotificationBigPictureStyle::IsValid() const
{
	return NativeStyle != nullptr;
}

UAGNotificationBigPictureStyle::~UAGNotificationBigPictureStyle()
{
}

UAGNotificationBigPictureStyle* UAGNotificationBigPictureStyle::SetBigLargeIcon(UTexture2D* Icon)
{
	if (!IsValid())
	{
		return this;
	}
	NativeStyle->SetBigLargeIcon(Icon);
	return this;
}

UAGNotificationBigPictureStyle* UAGNotificationBigPictureStyle::SetBigContentTitle(FString Title)
{
	if (!IsValid())
	{
		return this;
	}
	NativeStyle->SetBigContentTitle(Title);
	return this;
}

UAGNotificationBigPictureStyle* UAGNotificationBigPictureStyle::SetSummaryText(FString Text)
{
	if (!IsValid())
	{
		return this;
	}
	return this;
}
