// Copyright (c) 2018 Nineva Studios

#include "AGProgressDialog.h"
#include "JavaEntities/JavaAGProgressDialogData.h"
#include "Misc/CoreDelegates.h"

UAGProgressDialog::UAGProgressDialog(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ProgressDialogJavaObject(nullptr)
	, WasDismissed(false)
{
}

void UAGProgressDialog::PostInitProperties()
{
	Super::PostInitProperties();

	if (UAGProgressDialog::StaticClass()->GetDefaultObject() != this)
	{
		// create dialog Java object
		ProgressDialogJavaObject = MakeShareable(new FJavaClassObject("com/ninevastudios/androidgoodies/AGProgressDialog", "(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis));

		// get references to Java methods
		ShowMethod = ProgressDialogJavaObject->GetClassMethod("show", "(Lcom/ninevastudios/androidgoodies/AGProgressDialogData;)V");
		DismissMethod = ProgressDialogJavaObject->GetClassMethod("dismiss", "()V");
		SetProgressMethod = ProgressDialogJavaObject->GetClassMethod("setProgress", "(I)V");
		PauseMethod = ProgressDialogJavaObject->GetClassMethod("pause", "()V");
		ResumeMethod = ProgressDialogJavaObject->GetClassMethod("resume", "()V");

		// add dialog to root to avoid GC issues
		AddToRoot();

		FCoreDelegates::ApplicationWillEnterBackgroundDelegate.AddUObject(this, &UAGProgressDialog::OnApplicationSuspended);
		FCoreDelegates::ApplicationHasEnteredForegroundDelegate.AddUObject(this, &UAGProgressDialog::OnApplicationResumed);
	}
}

void UAGProgressDialog::BeginDestroy()
{
	if (UAGProgressDialog::StaticClass()->GetDefaultObject() != this)
	{
		FCoreDelegates::ApplicationWillEnterBackgroundDelegate.RemoveAll(this);
		FCoreDelegates::ApplicationHasEnteredForegroundDelegate.RemoveAll(this);

		// remove dialog from root so now it can be safely destroyed by GC
		RemoveFromRoot();
	}

	Super::BeginDestroy();
}

void UAGProgressDialog::Show(FAGProgressDialogData dialogData)
{
	if (WasDissmised())
	{
		return;
	}

	ProgressDialogJavaObject->CallMethod<void>(ShowMethod, FJavaAGProgressDialogData(dialogData).GetJObject());
}

void UAGProgressDialog::Dismiss()
{
	if (WasDissmised())
	{
		return;
	}

	ProgressDialogJavaObject->CallMethod<void>(DismissMethod);

	ConditionalBeginDestroy();

	// restrict possibility of further work with this dialog
	WasDismissed = true;
}

void UAGProgressDialog::SetProgress(int progress)
{
	ProgressDialogJavaObject->CallMethod<void>(SetProgressMethod, progress);
}

bool UAGProgressDialog::WasDissmised() const
{
	if (WasDismissed)
	{
		UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Impossible to call method on dialog that was dismissed!"));
	}

	return WasDismissed;
}

void UAGProgressDialog::OnApplicationSuspended()
{
	if (WasDissmised())
	{
		return;
	}

	ProgressDialogJavaObject->CallMethod<void>(PauseMethod);
}

void UAGProgressDialog::OnApplicationResumed()
{
	if (WasDissmised())
	{
		return;
	}

	ProgressDialogJavaObject->CallMethod<void>(ResumeMethod);
}
