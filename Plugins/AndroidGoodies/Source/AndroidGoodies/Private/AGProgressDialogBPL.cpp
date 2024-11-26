// Copyright (c) 2018 Nineva Studios

#include "AGProgressDialogBPL.h"

#if PLATFORM_ANDROID
#include "Android/AGProgressDialog.h"
#include "Android/AndroidJava.h"
#endif

UAGProgressDialogBPL::UAGProgressDialogBPL(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

TScriptInterface<IAGProgressDialogInterface> UAGProgressDialogBPL::CreateProgressDialog()
{
#if PLATFORM_ANDROID
	UAGProgressDialog* ProgressDialog = NewObject<UAGProgressDialog>();
	TScriptInterface<IAGProgressDialogInterface> ProgressDialogInterface;
	ProgressDialogInterface.SetObject(ProgressDialog);
	ProgressDialogInterface.SetInterface(Cast<IAGProgressDialogInterface>(ProgressDialog));
	return ProgressDialogInterface;
#endif

	return nullptr;
}