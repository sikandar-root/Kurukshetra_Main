// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGAudioAttributesFlags.h"
#include "Enums/AGAudioAttributesUsage.h"
#include "Enums/AGAudioAttributesContentType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGAudioAttributes.generated.h"

USTRUCT(BlueprintType)
struct ANDROIDGOODIES_API FAGAudioAttributes
{
	GENERATED_BODY()
public:
	/**
	* Flags.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	FAGAudioAttributesFlags Flags;

	/**
	* Usage.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	TEnumAsByte<AudioAttributesUsage> Usage = AudioAttributesUsage::NotSpecified;

	/**
	* Content type.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	TEnumAsByte<AudioAttributesContentType> ContentType = AudioAttributesContentType::AudioAttributesContentTypeUnknown;
};
