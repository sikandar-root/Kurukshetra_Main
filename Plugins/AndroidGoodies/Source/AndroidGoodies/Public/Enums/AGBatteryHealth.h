// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGBatteryHealth.generated.h"

UENUM(BlueprintType)
enum class BatteryHealth : uint8
{
	UnknownHealth = 0 UMETA(DisplayName = "UnknownHealth"),
	Good UMETA(DisplayName = "Good"),
	Overheat UMETA(DisplayName = "Overheat"),
	Dead UMETA(DisplayName = "Dead"),
	OverVoltage UMETA(DisplayName = "OverVoltage"),
	UnspecifiedFailure UMETA(DisplayName = "UnspecifiedFailure"),
	Cold UMETA(DisplayName = "Cold"),
};