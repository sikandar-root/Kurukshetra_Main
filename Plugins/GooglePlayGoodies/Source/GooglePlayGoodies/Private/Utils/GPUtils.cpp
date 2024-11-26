// Copyright (c) 2020 Nineva Studios

#include "GPUtils.h"

#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "Runtime/Launch/Resources/Version.h"

namespace GPUtils
{
UTexture2D* TextureFromByteArray(const TArray<uint8>& Bytes, int Width, int Height)
{
	UTexture2D* Tex = UTexture2D::CreateTransient(Width, Height, PF_R8G8B8A8);
	
	FTexturePlatformData* texturePlatformData;

#if ENGINE_MAJOR_VERSION == 4
	texturePlatformData = Tex->PlatformData;
#elif ENGINE_MAJOR_VERSION == 5
	texturePlatformData = Tex->GetPlatformData();
#endif

	FColor* MipData = (FColor*)texturePlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	for (int i = 0; i < Bytes.Num() / 4; i++)
	{
		MipData[i].A = Bytes[4 * i];
		MipData[i].B = Bytes[4 * i + 1];
		MipData[i].G = Bytes[4 * i + 2];
		MipData[i].R = Bytes[4 * i + 3];
	}
	texturePlatformData->Mips[0].BulkData.Unlock();

	Tex->UpdateResource();

	return Tex;
}
}
