// Copyright (c) 2019 Nineva Studios

#include "AGContact.h"

#include "Android/AndroidJava.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"

#pragma once

class AGContactUtils
{
public:

	static TArray<FAGContact> ContactsFromJavaArray(jobjectArray javaArray);

	static FAGContact ContactFromJavaObject(jobject javaContact);

	static jobject ConvertToJavaContact(FAGContact contact);
};
