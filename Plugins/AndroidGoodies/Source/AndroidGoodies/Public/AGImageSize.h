// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGImageSize.generated.h"

UENUM(BlueprintType)
enum ImageSize
{
	Original = 0 UMETA(DisplayName = "Original"),
	Max256 = 256 UMETA(DisplayName = "Maximum 256"),
	Max512 = 512 UMETA(DisplayName = "Maximum 512"),
	Max1024 = 1024 UMETA(DisplayName = "Maximum 1024"),
	Max2048 = 2048 UMETA(DisplayName = "Maximum 2048"),
};
