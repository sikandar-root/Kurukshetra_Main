// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGImageSize.generated.h"

UENUM(BlueprintType)
enum class ImageSize: uint8
{
	Original = 0 UMETA(DisplayName = "Original"),
	Max256 = 1 UMETA(DisplayName = "Maximum 256"),
	Max512 = 2 UMETA(DisplayName = "Maximum 512"),
	Max1024 = 3 UMETA(DisplayName = "Maximum 1024"),
	Max2048 = 4 UMETA(DisplayName = "Maximum 2048"),
};
