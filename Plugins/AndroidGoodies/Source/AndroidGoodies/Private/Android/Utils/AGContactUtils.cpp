// Copyright (c) 2019 Nineva Studios

#include "AGContactUtils.h"
#include "AGArrayConvertor.h"

TArray<FAGContact> AGContactUtils::ContactsFromJavaArray(jobjectArray javaArray)
{
	TArray<FAGContact> result;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	int length = Env->GetArrayLength(javaArray);

	for (int i = 0; i < length; i++)
	{
		jobject javaContact = Env->GetObjectArrayElement(javaArray, i);

		FAGContact contact = ContactFromJavaObject(javaContact);

		result.Add(contact);
	}

	return result;
}

FAGContact AGContactUtils::ContactFromJavaObject(jobject javaContact)
{
	FAGContact contact;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jclass AGContactClass = FAndroidApplication::FindJavaClass("com/ninevastudios/androidgoodies/AGContact");

	jfieldID nameFieldID = Env->GetFieldID(AGContactClass, "DisplayName", "Ljava/lang/String;");
	jstring displayName = static_cast<jstring>(Env->GetObjectField(javaContact, nameFieldID));
	contact.DisplayName = AGArrayConvertor::FromJavaString(displayName);

	jfieldID numbersFieldID = Env->GetFieldID(AGContactClass, "PhoneNumbers", "[Ljava/lang/String;");
	jobjectArray javaNumbersArray = static_cast<jobjectArray>(Env->GetObjectField(javaContact, numbersFieldID));
	contact.Numbers = AGArrayConvertor::ConvertToStringArray(javaNumbersArray);

	Env->DeleteLocalRef(javaContact);
	Env->DeleteLocalRef(AGContactClass);

	return contact;
}

jobject AGContactUtils::ConvertToJavaContact(FAGContact contact)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jclass AGContactClass = FAndroidApplication::FindJavaClass("com/ninevastudios/androidgoodies/AGContact");
	FJavaClassObject* javaClassObject = new FJavaClassObject("com/ninevastudios/androidgoodies/AGContact", "()V");
	jobject javaContact = javaClassObject->GetJObject();

	jfieldID nameFieldID = Env->GetFieldID(AGContactClass, "DisplayName", "Ljava/lang/String;");
	Env->SetObjectField(javaContact, nameFieldID, *FJavaClassObject::GetJString(contact.DisplayName));
	
	jfieldID numbersFieldID = Env->GetFieldID(AGContactClass, "PhoneNumbers", "[Ljava/lang/String;");
	Env->SetObjectField(javaContact, numbersFieldID, AGArrayConvertor::ConvertToJStringArray(contact.Numbers));

	Env->DeleteLocalRef(AGContactClass);

	return javaContact;
}
