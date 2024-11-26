// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGBatteryStatus.generated.h"

UENUM(BlueprintType)
enum class BatteryStatus : uint8
{
	UnknownStatus = 0 UMETA(DisplayName = "UnknownStatus"),
	Charging UMETA(DisplayName = "Charging"),
	Discharging UMETA(DisplayName = "Discharging"),
	NotCharging UMETA(DisplayName = "NotCharging"),
	Full UMETA(DisplayName = "Full"),
};
