// Copyright (c) 2020 Nineva Studios

#pragma once

#include "GPPermissionFlags.generated.h"

USTRUCT(BlueprintType)
struct GOOGLEPLAYGOODIES_API FGPPermissionFlags
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Google Play Goodies")
	bool bId = false;

	UPROPERTY(BlueprintReadWrite, Category = "Google Play Goodies")
	bool bIdToken = false;

	UPROPERTY(BlueprintReadWrite, Category = "Google Play Goodies")
	bool bServerAuthCode = false;

	UPROPERTY(BlueprintReadWrite, Category = "Google Play Goodies")
	bool bProfile = false;

	UPROPERTY(BlueprintReadWrite, Category = "Google Play Goodies")
	bool bEmail = false;

	UPROPERTY(BlueprintReadWrite, Category = "Google Play Goodies")
	bool bCloudSave = false;
};
