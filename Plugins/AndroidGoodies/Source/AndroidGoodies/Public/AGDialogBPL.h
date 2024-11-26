// Copyright (c) 2018 Nineva Studios

#pragma once

#include "AGDialogTheme.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGDialogBPL.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnPositiveButtonClickedDelegate);
DECLARE_DYNAMIC_DELEGATE(FOnNegativeButtonClickedDelegate);
DECLARE_DYNAMIC_DELEGATE(FOnNeutralButtonClickedDelegate);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnListItemChoosedDelegate, int, index);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSingleChoiceItemClickDelegate, int, index);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnMultiChoiceItemClickDelegate, int, index, bool, isChosen);
DECLARE_DYNAMIC_DELEGATE(FOnDialogCancelledDelegate);

UCLASS()
class ANDROIDGOODIES_API UAGDialogBPL : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/**
	* Show the default Android message dialog with single positive button.
	* @param messageTitle - message title text to be displayed in dialog
	* @param message - message text to be displayed in dialog
	* @param positiveButtonText - text displayed in dialogs positive button
	* @param onPositiveButtonClickedCallback - callback function that is called after user clicked dialog positive button
	* @param onDialogCancelledCallback - callback function that is called after user cancelled dialog
	* @param theme - dialog theme
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void ShowSingleButtonDialog(FString messageTitle, FString message, FString positiveButtonText, 
		const FOnPositiveButtonClickedDelegate& onPositiveButtonClickedCallback, const FOnDialogCancelledDelegate& onDialogCancelledCallback, DialogTheme theme = DialogTheme::LightTheme);

	/**
	* Show the default Android message dialog with positive and negative buttons.
	* @param messageTitle - message title text to be displayed in dialog
	* @param message - message text to be displayed in dialog
	* @param positiveButtonText - text displayed in dialogs positive button
	* @param negativeButtonText - text displayed in dialogs negative button
	* @param onPositiveButtonClickedCallback - callback function that is called after user clicked dialog positive button
	* @param onNegativeButtonClickedCallback - callback function that is called after user clicked dialog negative button
	* @param onDialogCancelledCallback - callback function that is called after user cancelled dialog
	* @param theme - dialog theme
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void ShowTwoButtonsDialog(FString messageTitle, FString message, FString positiveButtonText, FString negativeButtonText,
		const FOnPositiveButtonClickedDelegate& onPositiveButtonClickedCallback, const FOnNegativeButtonClickedDelegate& onNegativeButtonClickedCallback,
		const FOnDialogCancelledDelegate& onDialogCancelledCallback, DialogTheme theme = DialogTheme::LightTheme);

	/**
	* Show the default Android message dialog with positive, negative and neutral buttons.
	* @param messageTitle - message title text to be displayed in dialog
	* @param message - message text to be displayed in dialog
	* @param positiveButtonText - text displayed in dialogs positive button
	* @param negativeButtonText - text displayed in dialogs negative button
	* @param neutralButtonText - text displayed in dialogs neutral button
	* @param onPositiveButtonClickedCallback - callback function that is called after user clicked dialog positive button
	* @param onNegativeButtonClickedCallback - callback function that is called after user clicked dialog negative button
	* @param onNeutralButtonClickedCallback - callback function that is called after user clicked dialog negative button
	* @param onDialogCancelledCallback - callback function that is called after user cancelled dialog
	* @param theme - dialog theme
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void ShowThreeButtonsDialog(FString messageTitle, FString message, FString positiveButtonText, FString negativeButtonText, FString neutralButtonText,
		const FOnPositiveButtonClickedDelegate& onPositiveButtonClickedCallback, const FOnNegativeButtonClickedDelegate& onNegativeButtonClickedCallback,
		const FOnNeutralButtonClickedDelegate& onNeutralButtonClickedCallback, const FOnDialogCancelledDelegate& onDialogCancelledCallback, DialogTheme theme = DialogTheme::LightTheme);

	/**
	* Show the default Android message dialog with choosable items list.
	* @param listTitle - items list title text to be displayed in dialog
	* @param listItems - list of choosable text items that are displayed in dialog
	* @param onItemChoosedCallback - callback function that is called after user choosed one of list items in dialog
	* @param onDialogCancelledCallback - callback function that is called after user cancelled dialog
	* @param theme - dialog theme
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void ShowChooserDialog(FString listTitle, TArray<FString> listItems,
		const FOnListItemChoosedDelegate& onItemChoosedCallback, const FOnDialogCancelledDelegate& onDialogCancelledCallback, DialogTheme theme = DialogTheme::LightTheme);

	/**
	* Show the default Android message dialog with single choice items list.
	* @param listTitle - items list title text to be displayed in dialog
	* @param listItems - list of choosable text items that are displayed in dialog
	* @param positiveButtonText - text displayed in dialogs positive button
	* @param selectedItemIndex - index of selected list item
	* @param onSingleChoiceItemClickedCallback - callback function that is called after user choosed one of list items in dialog
	* @param onPositiveButtonClickedCallback - callback function that is called after user clicked dialog positive button
	* @param onDialogCancelledCallback - callback function that is called after user cancelled dialog
	* @param theme - dialog theme
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void ShowSingleItemChoiceDialog(FString listTitle, TArray<FString> listItems, FString positiveButtonText, int selectedItemIndex,
		const FOnSingleChoiceItemClickDelegate& onSingleChoiceItemClickedCallback, const FOnPositiveButtonClickedDelegate& onPositiveButtonClickedCallback,
		const FOnDialogCancelledDelegate& onDialogCancelledCallback, DialogTheme theme = DialogTheme::LightTheme);

	/**
	* Show the default Android message dialog with multiple choice items list.
	* @param listTitle - items list title text to be displayed in dialog
	* @param listItems - list of choosable text items that are displayed in dialog
	* @param positiveButtonText - text displayed in dialogs positive button
	* @param checkedListItems - list of chosen list items
	* @param onMultipleChoiceItemClickedCallback - callback function that is called after user choosed another list item in dialog
	* @param onPositiveButtonClickedCallback - callback function that is called after user clicked dialog positive button
	* @param onDialogCancelledCallback - callback function that is called after user cancelled dialog
	* @param theme - dialog theme
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void ShowMultipleItemChoiceDialog(FString listTitle, TArray<FString> listItems, FString positiveButtonText, TArray<bool> checkedListItems,
		const FOnMultiChoiceItemClickDelegate& onMultipleChoiceItemClickedCallback, const FOnPositiveButtonClickedDelegate& onPositiveButtonClickedCallback,
		const FOnDialogCancelledDelegate& onDialogCancelledCallback, DialogTheme theme = DialogTheme::LightTheme);

	// Callbacks interface methods to be called from Android
	static void OnPositiveButtonClicked();
	static void OnNegativeButtonClicked();
	static void OnNeutralButtonClicked();
	static void OnListItemChoosed(int index);
	static void OnSingleChoiceItemClicked(int index);
	static void OnMultiChoiceItemClicked(int index, bool isChosen);
	static void OnDialogCancelled();

private:

	static FOnPositiveButtonClickedDelegate OnPositiveButtonClickedDelegate;
	static FOnNegativeButtonClickedDelegate OnNegativeButtonClickedDelegate;
	static FOnNeutralButtonClickedDelegate OnNeutralButtonClickedDelegate;
	static FOnListItemChoosedDelegate OnListItemChoosedDelegate;
	static FOnSingleChoiceItemClickDelegate OnSingleChoiceItemClickDelegate;
	static FOnMultiChoiceItemClickDelegate OnMultiChoiceItemClickDelegate;
	static FOnDialogCancelledDelegate OnDialogCancelledDelegate;
};