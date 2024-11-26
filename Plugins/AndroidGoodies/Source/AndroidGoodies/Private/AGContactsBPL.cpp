// Copyright (c) 2019 Nineva Studios

#include "AGContactsBPL.h"
#include "Async/Async.h"

#if PLATFORM_ANDROID
#include "Android/Utils/AGMethodCallUtils.h"
#include "Android/Utils/AGArrayConvertor.h"
#include "Android/Utils/AGContactUtils.h"
#endif

static const ANSICHAR* AGContactsClassName = "com/ninevastudios/androidgoodies/AGContacts";

FString UAGContactsBPL::GetUserPhoneNumber()
{
	FString result;

#if PLATFORM_ANDROID
	result = AGMethodCallUtils::CallStaticStringMethod(AGContactsClassName, "getSimPhoneNumber", "(Landroid/app/Activity;)Ljava/lang/String;", FJavaWrapper::GameActivityThis);
#endif

	return result;
}

TArray<FAGContact> UAGContactsBPL::GetContactsWithName(FString name)
{
	TArray<FAGContact> result;

#if PLATFORM_ANDROID
	jobjectArray contactsArray = static_cast<jobjectArray>(AGMethodCallUtils::CallStaticObjectMethod(AGContactsClassName, "fetchContactsWithName", 
		"(Landroid/app/Activity;Ljava/lang/String;)[Lcom/ninevastudios/androidgoodies/AGContact;", 
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(name)));

	result = AGContactUtils::ContactsFromJavaArray(contactsArray);
#endif

	return result;
}

TArray<FAGContact> UAGContactsBPL::GetContactsWithNumber(FString number)
{
	TArray<FAGContact> result;

#if PLATFORM_ANDROID
	jobjectArray contactsArray = static_cast<jobjectArray>(AGMethodCallUtils::CallStaticObjectMethod(AGContactsClassName, "fetchContactsWithNumber", 
		"(Landroid/app/Activity;Ljava/lang/String;)[Lcom/ninevastudios/androidgoodies/AGContact;", 
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(number)));

	result = AGContactUtils::ContactsFromJavaArray(contactsArray);
#endif

	return result;
}

TArray<FAGContact> UAGContactsBPL::GetAllContacts()
{
	TArray<FAGContact> result;

#if PLATFORM_ANDROID
	jobjectArray contactsArray = static_cast<jobjectArray>(AGMethodCallUtils::CallStaticObjectMethod(AGContactsClassName, "fetchAllContacts", 
		"(Landroid/app/Activity;)[Lcom/ninevastudios/androidgoodies/AGContact;", FJavaWrapper::GameActivityThis));

	result = AGContactUtils::ContactsFromJavaArray(contactsArray);
#endif

	return result;
}

bool UAGContactsBPL::AddContact(FAGContact contact)
{
	TArray<FString> dataArray;

	dataArray.Add(contact.DisplayName);
	dataArray.Append(contact.Numbers);

#if PLATFORM_ANDROID
	jobject javaContact = AGContactUtils::ConvertToJavaContact(contact);

	return AGMethodCallUtils::CallStaticBoolMethod(AGContactsClassName, "addContact", "(Landroid/app/Activity;Lcom/ninevastudios/androidgoodies/AGContact;)Z", 
		FJavaWrapper::GameActivityThis, javaContact);
#endif

	return false;
}