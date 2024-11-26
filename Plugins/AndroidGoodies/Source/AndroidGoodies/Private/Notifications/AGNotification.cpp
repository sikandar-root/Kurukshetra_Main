// Copyright (c) 2019 Nineva Studios

#include "Notifications/AGNotification.h"


UAGNotification::~UAGNotification()
{
}

void UAGNotification::Init(const TSharedPtr<IAndroidGoodiesNotification> Notification)
{
	NativeNotification = Notification;
}

TSharedPtr<IAndroidGoodiesNotification> UAGNotification::GetNativeNotification()
{
	return NativeNotification;
}