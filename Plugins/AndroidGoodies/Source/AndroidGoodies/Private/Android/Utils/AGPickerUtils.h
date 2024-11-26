// Copyright (c) 2020 Nineva Studios

#include "AGChosenImage.h"
#include "AGChosenFile.h"
#include "Android/AndroidJava.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"

#pragma once

class AGPickerUtils
{
public:
	static TArray<UAGChosenImage*> ChosenImagesFromJavaArray(jobjectArray javaArray);
	
	static TArray<UAGChosenFile*> ChosenFilesFromJavaArray(jobjectArray javaArray);
};
