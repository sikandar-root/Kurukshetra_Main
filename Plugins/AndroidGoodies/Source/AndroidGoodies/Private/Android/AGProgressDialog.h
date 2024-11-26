// Copyright (c) 2018 Nineva Studios

#pragma once

#include "AGProgressDialogInterface.h"
#include "AGProgressDialogData.h"

#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJava.h"

#include "AGProgressDialog.generated.h"

UCLASS()
class UAGProgressDialog : public UObject, public IAGProgressDialogInterface
{
	GENERATED_UCLASS_BODY()

public:

	virtual void PostInitProperties() override;
	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	virtual void Show(FAGProgressDialogData dialogData) override;

	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	virtual void Dismiss() override;

	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	virtual void SetProgress(int progress) override;

private:

	TSharedPtr<FJavaClassObject> ProgressDialogJavaObject;

	// Java methods
	FJavaClassMethod ShowMethod;
	FJavaClassMethod DismissMethod;
	FJavaClassMethod SetProgressMethod;
	FJavaClassMethod PauseMethod;
	FJavaClassMethod ResumeMethod;

	bool WasDissmised() const;

	// Flag indicating if map view was dismissed.
	// Map view CAN'T be used after it was dismissed.
	bool WasDismissed;

	/**
	* Handle map view when GameActivity is suspended.
	* (e.g., due to switching to another app or closing it via the home button)
	*/
	UFUNCTION()
	void OnApplicationSuspended();

	/**
	* Handle map view when GameActivity is resumed.
	*/
	UFUNCTION()
	void OnApplicationResumed();
};