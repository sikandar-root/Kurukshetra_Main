// Copyright (c) 2020 Nineva Studios

#pragma once
#include "Containers/Array.h"
#include "HAL/Platform.h"

class UTexture2D;

namespace GPUtils
{
	UTexture2D* TextureFromByteArray(const TArray<uint8>& Bytes, int Width, int Height);
};
