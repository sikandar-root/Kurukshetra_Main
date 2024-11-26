// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGContact.generated.h"

USTRUCT(BlueprintType)
struct ANDROIDGOODIES_API FAGContact
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies|Contacts")
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies|Contacts")
	TArray<FString> Numbers;
};