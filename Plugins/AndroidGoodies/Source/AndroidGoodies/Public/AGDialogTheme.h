// Copyright (c) 2018 Nineva Studios

#pragma once

#include "AGDialogTheme.generated.h"

UENUM(BlueprintType)
enum DialogTheme
{
	/** Light dialog theme. */
	LightTheme = 0 UMETA(DisplayName = "Light"),
	/** Dark dialog theme. */
	DarkTheme = 1 UMETA(DisplayName = "Dark"),
	/** Default dialog theme. */
	DefaultTheme = 2 UMETA(DisplayName = "Default"),
};