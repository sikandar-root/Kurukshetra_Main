// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGBatteryPluggedState.generated.h"

UENUM(BlueprintType)
enum BatteryPluggedState
{
	OnBattery = 0 UMETA(DisplayName = "OnBattery"),
	Ac = 1 UMETA(DisplayName = "Ac"),
	Usb = 2 UMETA(DisplayName = "Usb"),
	Wireless = 4 UMETA(DisplayName = "Wireless"),
};