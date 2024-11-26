// Copyright (c) 2018 Nineva Studios

#pragma once

#include "AGAudioAttributesFlags.generated.h"

USTRUCT(BlueprintType)
struct ANDROIDGOODIES_API FAGAudioAttributesFlags
{
	GENERATED_BODY()
public:
	/** Flag defining a behavior where the audibility of the sound will be ensured by the system. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	bool AudibilityEnforced = false;

	/** Flag requesting the use of an output stream supporting hardware A/V synchronization. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	bool HwAvSync = false;

	/** Flag requesting a low latency path when creating an AudioTrack.  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	bool LowLatency = false;
};
