// Copyright (c) 2018 Nineva Studios

#pragma once

#include "Engine/Texture2D.h"
#include "AGDialogTheme.h"

class AGMediaUtils
{
public:

	static FString SaveTextureToTempFile(UTexture2D* texture);
	static int GetDialogTheme(DialogTheme theme);
	static UTexture2D* TextureFromByteArray(TArray<uint8> bytes, int width, int height);
	static TArray<uint8> ByteArrayFromTexture(UTexture2D* image);

private:

	static FString GenerateTempImageFilePath();
};
