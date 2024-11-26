// Copyright (c) 2018 Nineva Studios

#pragma once

#include "AGDialogTheme.h"
#include "AGDialogData.generated.h"

USTRUCT(BlueprintType)
struct ANDROIDGOODIES_API FAGDialogData
{
	GENERATED_BODY()

	/** Dialog message title text. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	FString Title;

	/** Dialog message text. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	FString Message;

	/** Dialog theme. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	TEnumAsByte<DialogTheme> Theme = TEnumAsByte<DialogTheme>(DefaultTheme);

	/** Dialog positive button text. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	FString PositiveButtonText;
	/** Dialog negative button text. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	FString NegativeButtonText;
	/** Dialog neutral button text. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	FString NeutralButtonText;
	
	/** List of items to be displayed in the dialog as the content. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	TArray<FString> Items;

	/** List of selectable items to be displayed in the dialog. Only one item can be selected! */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	TArray<FString> SingleChoiceItems;
	/** Number of single selected list item. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	int SingleChoiceCheckedItem = 0;

	/** List of selectable items to be displayed in the dialog. Multiple items can be selected! */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	TArray<FString> MultiChoiceItems;
	/** List of items checked states. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	TArray<bool> MultiChoiceCheckedItems;
};