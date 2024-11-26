// Copyright (c) 2018 Nineva Studios

#include "JavaAGProgressDialogData.h"
#include "Android/Utils/AGMediaUtils.h"
#include "Android/AndroidApplication.h"

FJavaAGProgressDialogData::FJavaAGProgressDialogData(FAGProgressDialogData progressDialogData)
	: FJavaClassObject(GetClassName(), "()V")
{
	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	titleTextFieldID = FJavaWrapper::FindField(Env, Class, "title", "Ljava/lang/String;", bIsOptional);
	messageTextFieldID = FJavaWrapper::FindField(Env, Class, "message", "Ljava/lang/String;", bIsOptional);

	themeFieldID = FJavaWrapper::FindField(Env, Class, "theme", "I", bIsOptional);

	maxValueFieldID = FJavaWrapper::FindField(Env, Class, "maxValue", "I", bIsOptional);
	progressFieldID = FJavaWrapper::FindField(Env, Class, "progress", "I", bIsOptional);

	isIndeterminateFieldID = FJavaWrapper::FindField(Env, Class, "isIndeterminate", "Z", bIsOptional);
	isCancellableFieldID = FJavaWrapper::FindField(Env, Class, "isCancellable", "Z", bIsOptional);

	styleFieldID = FJavaWrapper::FindField(Env, Class, "style", "I", bIsOptional);

	Env->SetObjectField(Object, titleTextFieldID, *FJavaClassObject::GetJString(progressDialogData.Title));
	Env->SetObjectField(Object, messageTextFieldID, *FJavaClassObject::GetJString(progressDialogData.Message));
	Env->SetIntField(Object, themeFieldID, AGMediaUtils::GetDialogTheme(progressDialogData.Theme));

	Env->SetIntField(Object, maxValueFieldID, progressDialogData.MaxValue);
	Env->SetIntField(Object, progressFieldID, progressDialogData.Progress);

	Env->SetBooleanField(Object, isIndeterminateFieldID, progressDialogData.IsIndeterminate);
	Env->SetBooleanField(Object, isCancellableFieldID, progressDialogData.IsCancellable);

	Env->SetIntField(Object, styleFieldID, progressDialogData.Style.GetValue());
}

FName FJavaAGProgressDialogData::GetClassName()
{
	return FName("com/ninevastudios/androidgoodies/AGProgressDialogData");
}