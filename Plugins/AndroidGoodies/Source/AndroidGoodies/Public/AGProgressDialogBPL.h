// Copyright (c) 2018 Nineva Studios

#pragma once

#include "AGProgressDialogInterface.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGProgressDialogBPL.generated.h"

UCLASS()
class ANDROIDGOODIES_API UAGProgressDialogBPL : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/**
	* Show the default Android progress dialog.
	*
	* @return - reference to Android progress dialog interface
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static TScriptInterface<IAGProgressDialogInterface> CreateProgressDialog();
};