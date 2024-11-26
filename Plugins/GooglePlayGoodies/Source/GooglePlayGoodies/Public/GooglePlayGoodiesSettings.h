// Copyright (c) 2020 Nineva Studios

#pragma once

#include "Engine/EngineTypes.h"
#include "GooglePlayGoodiesSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class GOOGLEPLAYGOODIES_API UGooglePlayGoodiesSettings : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	FString ClientID;
};
