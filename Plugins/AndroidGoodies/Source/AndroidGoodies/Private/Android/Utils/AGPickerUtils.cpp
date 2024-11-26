// Copyright (c) 2019 Nineva Studios

#include "AGPickerUtils.h"
#include "AGArrayConvertor.h"

TArray<UAGChosenImage*> AGPickerUtils::ChosenImagesFromJavaArray(jobjectArray javaArray)
{
	TArray<UAGChosenImage*> result;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	int length = Env->GetArrayLength(javaArray);

	for (int i = 0; i < length; i++)
	{
		jobject javaChosenImage = Env->GetObjectArrayElement(javaArray, i);

		UAGChosenImage* chosenImage = NewObject<UAGChosenImage>();
		chosenImage->Init(javaChosenImage);

		Env->DeleteLocalRef(javaChosenImage);

		result.Add(chosenImage);
	}
	
	Env->DeleteLocalRef(javaArray);

	return result;
}

TArray<UAGChosenFile*> AGPickerUtils::ChosenFilesFromJavaArray(jobjectArray javaArray)
{
	TArray<UAGChosenFile*> result;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	int length = Env->GetArrayLength(javaArray);

	for (int i = 0; i < length; i++)
	{
		jobject javaChosenFile = Env->GetObjectArrayElement(javaArray, i);

		UAGChosenFile* chosenFile = NewObject<UAGChosenFile>();
		chosenFile->Init(javaChosenFile);

		Env->DeleteLocalRef(javaChosenFile);

		result.Add(chosenFile);
	}

	Env->DeleteLocalRef(javaArray);

	return result;
}
