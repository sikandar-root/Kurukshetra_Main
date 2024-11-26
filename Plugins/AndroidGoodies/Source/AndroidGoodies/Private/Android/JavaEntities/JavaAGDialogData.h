// Copyright (c) 2018 Nineva Studios

#pragma once

#include "Android/AndroidJava.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"

#include "AGDialogData.h"

// Wrapper for com/ninevastudios/androidgoodies/AGDialogData*.java.
class FJavaAGDialogData : public FJavaClassObject
{
public:

	FJavaAGDialogData(FAGDialogData dialogData);

private:

	jfieldID titleTextFieldID;
	jfieldID messageTextFieldID;

	jfieldID themeFieldID;

	jfieldID positiveButtonTextFieldID;
	jfieldID negativeButtonTextFieldID;
	jfieldID neutralButtonTextFieldID;

	jfieldID itemsFieldID;

	jfieldID singleChoiceItemsFieldID;
	jfieldID singleChoiceCheckedItemFieldID;

	jfieldID multiChoiceItemsFieldID;
	jfieldID multiChoiceCheckedItemsFieldID;

	static FName GetClassName();
};