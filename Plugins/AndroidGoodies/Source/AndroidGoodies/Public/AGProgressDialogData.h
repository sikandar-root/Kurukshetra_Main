// Copyright (c) 2018 Nineva Studios

#pragma once

#include "AGDialogTheme.h"
#include "AGProgressDialogStyle.h"
#include "AGProgressDialogData.generated.h"

USTRUCT(BlueprintType)
struct ANDROIDGOODIES_API FAGProgressDialogData
{
	GENERATED_BODY()

	/** Progress dialog message title text. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	FString Title;

	/** Progress dialog message text. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	FString Message;

	/** Progress dialog theme. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	TEnumAsByte<DialogTheme> Theme = TEnumAsByte<DialogTheme>(DefaultTheme);

	/** Maximum allowed progress value. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	int MaxValue = 0;

	/** Current progress (value between 0 and MaxValue). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	int Progress = 0;

	/** Flag that determines whether progress dialog shows infinite animation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	bool IsIndeterminate = false;

	/** Flag that determines whether progress dialog is cancelable with the back key. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	bool IsCancellable = false;

	/** Progress dialog style. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	TEnumAsByte<ProgressDialogStyle> Style = TEnumAsByte<ProgressDialogStyle>(Spinner);
};