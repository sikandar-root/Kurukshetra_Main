// Copyright (c) 2018 Nineva Studios

#include "AGDialogBPL.h"
#include "Async/Async.h"

#if PLATFORM_ANDROID
#include "Android/JavaEntities/JavaAGDialogData.h"
#include "Android/Utils/AGMethodCallUtils.h"
#endif

FOnPositiveButtonClickedDelegate UAGDialogBPL::OnPositiveButtonClickedDelegate;
FOnNegativeButtonClickedDelegate UAGDialogBPL::OnNegativeButtonClickedDelegate;
FOnNeutralButtonClickedDelegate UAGDialogBPL::OnNeutralButtonClickedDelegate;
FOnListItemChoosedDelegate UAGDialogBPL::OnListItemChoosedDelegate;
FOnSingleChoiceItemClickDelegate UAGDialogBPL::OnSingleChoiceItemClickDelegate;
FOnMultiChoiceItemClickDelegate UAGDialogBPL::OnMultiChoiceItemClickDelegate;
FOnDialogCancelledDelegate UAGDialogBPL::OnDialogCancelledDelegate;

static const ANSICHAR* AGDialogClassName = "com/ninevastudios/androidgoodies/AGDialog";

UAGDialogBPL::UAGDialogBPL(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UAGDialogBPL::ShowSingleButtonDialog(FString messageTitle, FString message, FString positiveButtonText,
	const FOnPositiveButtonClickedDelegate& onPositiveButtonClickedCallback, const FOnDialogCancelledDelegate& onDialogCancelledCallback, DialogTheme theme)
{
	OnPositiveButtonClickedDelegate = onPositiveButtonClickedCallback;
	OnDialogCancelledDelegate = onDialogCancelledCallback;

#if PLATFORM_ANDROID

	FAGDialogData DialogData;
	DialogData.Title = messageTitle;
	DialogData.Message = message;
	DialogData.Theme = theme;
	DialogData.PositiveButtonText = positiveButtonText;

	FJavaAGDialogData JavaDialogData(DialogData);

	AGMethodCallUtils::CallStaticVoidMethod(AGDialogClassName, "showDialog", "(Landroid/app/Activity;Lcom/ninevastudios/androidgoodies/AGDialogData;)V",
		FJavaWrapper::GameActivityThis, JavaDialogData.GetJObject());	

#endif
}

void UAGDialogBPL::ShowTwoButtonsDialog(FString messageTitle, FString message, FString positiveButtonText, FString negativeButtonText, 
	const FOnPositiveButtonClickedDelegate& onPositiveButtonClickedCallback, const FOnNegativeButtonClickedDelegate& onNegativeButtonClickedCallback, 
	const FOnDialogCancelledDelegate& onDialogCancelledCallback, DialogTheme theme)
{
	OnPositiveButtonClickedDelegate = onPositiveButtonClickedCallback;
	OnNegativeButtonClickedDelegate = onNegativeButtonClickedCallback;
	OnDialogCancelledDelegate = onDialogCancelledCallback;

#if PLATFORM_ANDROID

	FAGDialogData DialogData;
	DialogData.Title = messageTitle;
	DialogData.Message = message;
	DialogData.Theme = theme;
	DialogData.PositiveButtonText = positiveButtonText;
	DialogData.NegativeButtonText = negativeButtonText;

	FJavaAGDialogData JavaDialogData(DialogData);

	AGMethodCallUtils::CallStaticVoidMethod(AGDialogClassName, "showDialog", "(Landroid/app/Activity;Lcom/ninevastudios/androidgoodies/AGDialogData;)V",
		FJavaWrapper::GameActivityThis, JavaDialogData.GetJObject());

#endif
}

void UAGDialogBPL::ShowThreeButtonsDialog(FString messageTitle, FString message, FString positiveButtonText, FString negativeButtonText, FString neutralButtonText, 
	const FOnPositiveButtonClickedDelegate& onPositiveButtonClickedCallback, const FOnNegativeButtonClickedDelegate& onNegativeButtonClickedCallback, 
	const FOnNeutralButtonClickedDelegate& onNeutralButtonClickedCallback, const FOnDialogCancelledDelegate& onDialogCancelledCallback, DialogTheme theme)
{
	OnPositiveButtonClickedDelegate = onPositiveButtonClickedCallback;
	OnNegativeButtonClickedDelegate = onNegativeButtonClickedCallback;
	OnNeutralButtonClickedDelegate = onNeutralButtonClickedCallback;
	OnDialogCancelledDelegate = onDialogCancelledCallback;

#if PLATFORM_ANDROID

	FAGDialogData DialogData;
	DialogData.Title = messageTitle;
	DialogData.Message = message;
	DialogData.Theme = theme;
	DialogData.PositiveButtonText = positiveButtonText;
	DialogData.NegativeButtonText = negativeButtonText;
	DialogData.NeutralButtonText = neutralButtonText;

	FJavaAGDialogData JavaDialogData(DialogData);

	AGMethodCallUtils::CallStaticVoidMethod(AGDialogClassName, "showDialog", "(Landroid/app/Activity;Lcom/ninevastudios/androidgoodies/AGDialogData;)V",
		FJavaWrapper::GameActivityThis, JavaDialogData.GetJObject());

#endif
}

void UAGDialogBPL::ShowChooserDialog(FString listTitle, TArray<FString> listItems, 
	const FOnListItemChoosedDelegate& onItemChoosedCallback, const FOnDialogCancelledDelegate& onDialogCancelledCallback, DialogTheme theme)
{
	OnListItemChoosedDelegate = onItemChoosedCallback;
	OnDialogCancelledDelegate = onDialogCancelledCallback;

#if PLATFORM_ANDROID

	FAGDialogData DialogData;
	DialogData.Title = listTitle;
	DialogData.Items = listItems;
	DialogData.Theme = theme;

	FJavaAGDialogData JavaDialogData(DialogData);

	AGMethodCallUtils::CallStaticVoidMethod(AGDialogClassName, "showDialog", "(Landroid/app/Activity;Lcom/ninevastudios/androidgoodies/AGDialogData;)V", 
		FJavaWrapper::GameActivityThis, JavaDialogData.GetJObject());

#endif
}

void UAGDialogBPL::ShowSingleItemChoiceDialog(FString listTitle, TArray<FString> listItems, FString positiveButtonText, int selectedItemIndex, 
	const FOnSingleChoiceItemClickDelegate& onSingleChoiceItemClickedCallback, const FOnPositiveButtonClickedDelegate& onPositiveButtonClickedCallback, 
	const FOnDialogCancelledDelegate& onDialogCancelledCallback, DialogTheme theme)
{
	OnSingleChoiceItemClickDelegate = onSingleChoiceItemClickedCallback;
	OnPositiveButtonClickedDelegate = onPositiveButtonClickedCallback;
	OnDialogCancelledDelegate = onDialogCancelledCallback;

#if PLATFORM_ANDROID

	FAGDialogData DialogData;
	DialogData.Title = listTitle;
	DialogData.SingleChoiceItems = listItems;
	DialogData.SingleChoiceCheckedItem = selectedItemIndex;
	DialogData.PositiveButtonText = positiveButtonText;
	DialogData.Theme = theme;

	FJavaAGDialogData JavaDialogData(DialogData);

	AGMethodCallUtils::CallStaticVoidMethod(AGDialogClassName, "showDialog", "(Landroid/app/Activity;Lcom/ninevastudios/androidgoodies/AGDialogData;)V",
		FJavaWrapper::GameActivityThis, JavaDialogData.GetJObject());

#endif
}

void UAGDialogBPL::ShowMultipleItemChoiceDialog(FString listTitle, TArray<FString> listItems, FString positiveButtonText, TArray<bool> checkedListItems,
	const FOnMultiChoiceItemClickDelegate& onMultipleChoiceItemClickedCallback, const FOnPositiveButtonClickedDelegate& onPositiveButtonClickedCallback, 
	const FOnDialogCancelledDelegate& onDialogCancelledCallback, DialogTheme theme)
{
	OnMultiChoiceItemClickDelegate = onMultipleChoiceItemClickedCallback;
	OnPositiveButtonClickedDelegate = onPositiveButtonClickedCallback;
	OnDialogCancelledDelegate = onDialogCancelledCallback;

#if PLATFORM_ANDROID

	FAGDialogData DialogData;
	DialogData.Title = listTitle;
	DialogData.MultiChoiceItems = listItems;
	DialogData.MultiChoiceCheckedItems = checkedListItems;
	DialogData.PositiveButtonText = positiveButtonText;
	DialogData.Theme = theme;

	FJavaAGDialogData JavaDialogData(DialogData);

	AGMethodCallUtils::CallStaticVoidMethod(AGDialogClassName, "showDialog", "(Landroid/app/Activity;Lcom/ninevastudios/androidgoodies/AGDialogData;)V",
		FJavaWrapper::GameActivityThis, JavaDialogData.GetJObject());

#endif
}

void UAGDialogBPL::OnPositiveButtonClicked()
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnPositiveButtonClickedDelegate.ExecuteIfBound();
	});
}

void UAGDialogBPL::OnNegativeButtonClicked()
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnNegativeButtonClickedDelegate.ExecuteIfBound();
	});
}

void UAGDialogBPL::OnNeutralButtonClicked()
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnNeutralButtonClickedDelegate.ExecuteIfBound();
	});
}

void UAGDialogBPL::OnListItemChoosed(int index)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnListItemChoosedDelegate.ExecuteIfBound(index);
	});
}

void UAGDialogBPL::OnSingleChoiceItemClicked(int index)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnSingleChoiceItemClickDelegate.ExecuteIfBound(index);
	});
}

void UAGDialogBPL::OnMultiChoiceItemClicked(int index, bool isChosen)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnMultiChoiceItemClickDelegate.ExecuteIfBound(index, isChosen);
	});
}

void UAGDialogBPL::OnDialogCancelled()
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnDialogCancelledDelegate.ExecuteIfBound();
	});
}

#if PLATFORM_ANDROID

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGDialog_positiveButtonCallback(JNIEnv* env, jclass clazz)
{
	UAGDialogBPL::OnPositiveButtonClicked();
}

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGDialog_negativeButtonCallback(JNIEnv* env, jclass clazz)
{
	UAGDialogBPL::OnNegativeButtonClicked();
}

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGDialog_neutralButtonCallback(JNIEnv* env, jclass clazz)
{
	UAGDialogBPL::OnNeutralButtonClicked();
}

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGDialog_itemClickCallback(JNIEnv* env, jclass clazz, jint index)
{
	UAGDialogBPL::OnListItemChoosed(index);
}

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGDialog_singleChoiceItemClickCallback(JNIEnv* env, jclass clazz, jint index)
{
	UAGDialogBPL::OnSingleChoiceItemClicked(index);
}

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGDialog_multiChoiceItemClickCallback(JNIEnv* env, jclass clazz, jint index, jboolean isChosen)
{
	UAGDialogBPL::OnMultiChoiceItemClicked(index, isChosen);
}

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGDialog_onCancelCallback(JNIEnv* env, jclass clazz)
{
	UAGDialogBPL::OnDialogCancelled();
}

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGDialog_onDismissCallback(JNIEnv* env, jclass clazz)
{
	
}

#endif