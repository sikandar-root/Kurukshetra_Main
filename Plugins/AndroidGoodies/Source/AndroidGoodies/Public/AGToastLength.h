// Copyright (c) 2018 Nineva Studios

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

UENUM(BlueprintType)
enum ToastLength
{
	/** Short toast duration. */
	Short = 0 UMETA(DisplayName = "Short"),
	/** Long toast duration. */
	Long = 1 UMETA(DisplayName = "Long"),
};
