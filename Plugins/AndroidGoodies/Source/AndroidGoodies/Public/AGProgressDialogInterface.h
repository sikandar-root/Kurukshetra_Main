// Copyright (c) 2018 Nineva Studios

#pragma once

#include "UObject/Interface.h"
#include "AGProgressDialogData.h"
#include "AGProgressDialogInterface.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class ANDROIDGOODIES_API UAGProgressDialogInterface : public UInterface
{
	GENERATED_BODY()
};

class ANDROIDGOODIES_API IAGProgressDialogInterface
{
	GENERATED_BODY()

public:

	/**
	* Show native Android progress dialog
	* @param progressDialogData - configuration data for progress dialog.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	virtual void Show(FAGProgressDialogData progressDialogData) = 0;

	/**
	* Dismiss native Android progress dialog.
	* It can't be used after that.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	virtual void Dismiss() = 0;

	/**
	* Set native Android progress dialog value.
	* @param progress - new progress value
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	virtual void SetProgress(int progress) = 0;
};