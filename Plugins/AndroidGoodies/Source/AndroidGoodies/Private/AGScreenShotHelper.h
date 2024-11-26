// Copyright (c) 2019 Nineva Studios

#pragma once

#include "UObject/Object.h"
#include "AGScreenShotHelper.generated.h"

UCLASS()
class UScreenShotHelper : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void ProcessScreenShot(int InSizeX, int InSizeY, const TArray<FColor>& InImageData);
};