// Copyright (c) 2018 Nineva Studios

#pragma once

#include "AGDialogTheme.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGDateTimePickerBPL.generated.h"

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDateSetDelegate, int, Year, int, Month, int, Day);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnTimeSetDelegate, int, Hour, int, Minute);
DECLARE_DYNAMIC_DELEGATE(FOnCancelDelegate);

UCLASS()
class ANDROIDGOODIES_API UAGDateTimePickerBPL : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/**
	* Show the default Android date picker.
	* @param initialDate - initial date value for date picker dialog
	* @param onDateSetCallback - callback function that is called when user is done setting a new date and date picker dialog has closed
	* @param onCancelCallback - callback function that is called when user cancelled date picker dialog
	* @param theme - date picker dialog theme
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void ShowDatePicker(FDateTime initialDate, const FOnDateSetDelegate& onDateSetCallback, const FOnCancelDelegate& onCancelCallback, DialogTheme theme = DialogTheme::LightTheme);

	/**
	* Show the default Android date picker, but with limited date range.
	* @param initialDate - initial date value for date picker dialog
	* @param fromDate - minimum value in date picker dialog that can be selected
	* @param toDate - maximum value in date picker dialog that can be selected
	* @param onDateSetCallback - callback function that is called when user is done setting a new date and date picker dialog has closed
	* @param onCancelCallback - callback function that is called when user cancelled date picker dialog
	* @param theme - date picker dialog theme
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void ShowDatePickerWithLimits(FDateTime initialDate, const FOnDateSetDelegate& onDateSetCallback, const FOnCancelDelegate& onCancelCallback,
		FDateTime fromDate, FDateTime toDate, DialogTheme theme = DialogTheme::LightTheme);

	/**
	* Show the default Android time picker.
	* @param hour - initial hour value for time picker dialog
	* @param minute - initial minute value for time picker dialog
	* @param onTimeSetCallback - callback function that is called when user is done setting a new time and time picker dialog has closed
	* @param onCancelCallback - callback function that is called when user cancelled time picker dialog
	* @param theme - time picker dialog theme
	* @param is24HourView - flag that indicates which hour format to use
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void ShowTimePicker(int hour, int minute, const FOnTimeSetDelegate& onTimeSetCallback, const FOnCancelDelegate& onCancelCallback, DialogTheme theme = DialogTheme::LightTheme, bool is24HourView = true);

	// Callbacks interface methods to be called from Android
	static void OnDateSet(int year, int month, int day);
	static void OnTimeSet(int hour, int minute);
	static void OnCancel();

private:

	static FOnDateSetDelegate OnDateSetDelegate;
	static FOnTimeSetDelegate OnTimeSetDelegate;
	static FOnCancelDelegate OnCancelDelegate;
};
