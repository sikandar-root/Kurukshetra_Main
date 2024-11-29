// Copyright (c) 2019 Nineva Studios

#include "AGScreenShotHelper.h"
#include "AGPickersBPL.h"
#include "Runtime/Engine/Classes/Engine/GameViewportClient.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Public/UnrealClient.h"
#include "Runtime/Launch/Resources/Version.h"

#if PLATFORM_ANDROID
#include "Android/Utils/AGMediaUtils.h"
#endif

void UScreenShotHelper::ProcessScreenShot(int InSizeX, int InSizeY, const TArray<FColor>& InImageData)
{
#if PLATFORM_ANDROID
	TArray<uint8> bytes;
	bytes.SetNumZeroed(InSizeX * InSizeY * 4);

	for (int Row = 0; Row < InSizeY; Row++)
	{
		for (int Col = 0; Col < InSizeX; Col++)
		{
			const auto ColorArrIndex = Row * InSizeX + Col;
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 2
			const auto ByteArrIndex = (InSizeY - 1 - Row) * InSizeX + Col;
#else
			const auto ByteArrIndex = ColorArrIndex;
#endif
			bytes[4 * ByteArrIndex] = InImageData[ColorArrIndex].A;
			bytes[4 * ByteArrIndex + 1] = InImageData[ColorArrIndex].R;
			bytes[4 * ByteArrIndex + 2] = InImageData[ColorArrIndex].G;
			bytes[4 * ByteArrIndex + 3] = InImageData[ColorArrIndex].B;
		}
	}

	UAGPickersBPL::OnImageReady(AGMediaUtils::TextureFromByteArray(bytes, InSizeX, InSizeY));

	GEngine->GameViewport->OnScreenshotCaptured().RemoveAll(this);

	ConditionalBeginDestroy();
#endif
}
