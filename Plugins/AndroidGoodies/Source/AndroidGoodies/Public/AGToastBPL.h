// Copyright (c) 2018 Nineva Studios

#pragma once

#include "AGToastLength.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGToastBPL.generated.h"

UCLASS()
class ANDROIDGOODIES_API UAGToastBPL : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/**
	* Show toast message.
	* @param message - toast message text
	* @param length - toast display duration
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void ShowToast(FString message, ToastLength length);
};