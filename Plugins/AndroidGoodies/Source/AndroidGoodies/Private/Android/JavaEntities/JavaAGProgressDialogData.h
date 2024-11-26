// Copyright (c) 2018 Nineva Studios

#pragma once

#include "Android/AndroidJava.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"

#include "AGProgressDialogData.h"

// Wrapper for com/ninevastudios/androidgoodies/AGProgressDialogData*.java.
class FJavaAGProgressDialogData : public FJavaClassObject
{
public:

	FJavaAGProgressDialogData(FAGProgressDialogData progressDialogData);

private:

	jfieldID titleTextFieldID;
	jfieldID messageTextFieldID;

	jfieldID themeFieldID;

	jfieldID maxValueFieldID;
	jfieldID progressFieldID;

	jfieldID isIndeterminateFieldID;
	jfieldID isCancellableFieldID;

	jfieldID styleFieldID;

	static FName GetClassName();
};