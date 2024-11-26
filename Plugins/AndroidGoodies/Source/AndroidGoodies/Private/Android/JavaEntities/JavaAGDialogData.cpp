// Copyright (c) 2018 Nineva Studios

#include "JavaAGDialogData.h"
#include "Android/Utils/AGArrayConvertor.h"
#include "Android/Utils/AGMediaUtils.h"
#include "Android/AndroidApplication.h"

FJavaAGDialogData::FJavaAGDialogData(FAGDialogData dialogData)
	: FJavaClassObject(GetClassName(), "()V")
{
	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	titleTextFieldID = FJavaWrapper::FindField(Env, Class, "title", "Ljava/lang/String;", bIsOptional);
	messageTextFieldID = FJavaWrapper::FindField(Env, Class, "message", "Ljava/lang/String;", bIsOptional);

	themeFieldID = FJavaWrapper::FindField(Env, Class, "theme", "I", bIsOptional);

	positiveButtonTextFieldID = FJavaWrapper::FindField(Env, Class, "positiveButtonText", "Ljava/lang/String;", bIsOptional);
	negativeButtonTextFieldID = FJavaWrapper::FindField(Env, Class, "negativeButtonText", "Ljava/lang/String;", bIsOptional);
	neutralButtonTextFieldID = FJavaWrapper::FindField(Env, Class, "neutralButtonText", "Ljava/lang/String;", bIsOptional);

	itemsFieldID = FJavaWrapper::FindField(Env, Class, "items", "[Ljava/lang/String;", bIsOptional);

	singleChoiceItemsFieldID = FJavaWrapper::FindField(Env, Class, "singleChoiceItems", "[Ljava/lang/String;", bIsOptional);
	singleChoiceCheckedItemFieldID = FJavaWrapper::FindField(Env, Class, "singleChoiceCheckedItem", "I", bIsOptional);

	multiChoiceItemsFieldID = FJavaWrapper::FindField(Env, Class, "multiChoiceItems", "[Ljava/lang/String;", bIsOptional);
	multiChoiceCheckedItemsFieldID = FJavaWrapper::FindField(Env, Class, "multiChoiceCheckedItems", "[Z", bIsOptional);

	Env->SetObjectField(Object, titleTextFieldID, *FJavaClassObject::GetJString(dialogData.Title));
	Env->SetObjectField(Object, messageTextFieldID, *FJavaClassObject::GetJString(dialogData.Message));
	Env->SetIntField(Object, themeFieldID, AGMediaUtils::GetDialogTheme(dialogData.Theme));
	Env->SetObjectField(Object, positiveButtonTextFieldID, *FJavaClassObject::GetJString(dialogData.PositiveButtonText));
	Env->SetObjectField(Object, negativeButtonTextFieldID, *FJavaClassObject::GetJString(dialogData.NegativeButtonText));
	Env->SetObjectField(Object, neutralButtonTextFieldID, *FJavaClassObject::GetJString(dialogData.NeutralButtonText));
	Env->SetObjectField(Object, itemsFieldID, AGArrayConvertor::ConvertToJStringArray(dialogData.Items));
	Env->SetObjectField(Object, singleChoiceItemsFieldID, AGArrayConvertor::ConvertToJStringArray(dialogData.SingleChoiceItems));
	Env->SetIntField(Object, singleChoiceCheckedItemFieldID, dialogData.SingleChoiceCheckedItem);
	Env->SetObjectField(Object, multiChoiceItemsFieldID, AGArrayConvertor::ConvertToJStringArray(dialogData.MultiChoiceItems));
	Env->SetObjectField(Object, multiChoiceCheckedItemsFieldID, AGArrayConvertor::ConvertToJBooleanArray(dialogData.MultiChoiceCheckedItems));
}

FName FJavaAGDialogData::GetClassName()
{
	return FName("com/ninevastudios/androidgoodies/AGDialogData");
}