// Copyright (c) 2019 Nineva Studios

#include "AGContactsBPL.h"
#include "Async/Async.h"

#if PLATFORM_ANDROID
#include "Android/Utils/AGMethodCallUtils.h"
#include "Android/Utils/AGArrayConvertor.h"
#include "Android/Utils/AGContactUtils.h"
#include "Android/Utils/AGAndroidGoodiesScopedObject.h"
#endif


FOnPickContactSuccessDelegate UAGContactsBPL::OnPickContactSuccess;
FOnPickContactErrorelegate UAGContactsBPL::OnPickContactError;

static const ANSICHAR* AGContactsClassName = "com/ninevastudios/androidgoodies/AGContacts";

FString UAGContactsBPL::GetUserPhoneNumber()
{
	FString result;

#if PLATFORM_ANDROID
	result = AGMethodCallUtils::CallStaticStringMethod(AGContactsClassName, "getSimPhoneNumber", "(Landroid/app/Activity;)Ljava/lang/String;", FJavaWrapper::GameActivityThis);
#endif

	return result;
}

TArray<FAGContact> UAGContactsBPL::GetContactsWithName(FString Name)
{
	TArray<FAGContact> result;

#if PLATFORM_ANDROID
	jobjectArray contactsArray = static_cast<jobjectArray>(AGMethodCallUtils::CallStaticObjectMethod(AGContactsClassName, "fetchContactsWithName", 
		"(Landroid/app/Activity;Ljava/lang/String;)[Lcom/ninevastudios/androidgoodies/AGContact;", 
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(Name)));

	result = AGContactUtils::ContactsFromJavaArray(contactsArray);
#endif

	return result;
}

TArray<FAGContact> UAGContactsBPL::GetContactsWithNumber(FString Number)
{
	TArray<FAGContact> result;

#if PLATFORM_ANDROID
	jobjectArray contactsArray = static_cast<jobjectArray>(AGMethodCallUtils::CallStaticObjectMethod(AGContactsClassName, "fetchContactsWithNumber", 
		"(Landroid/app/Activity;Ljava/lang/String;)[Lcom/ninevastudios/androidgoodies/AGContact;", 
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(Number)));

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

bool UAGContactsBPL::AddContact(FAGContact Contact)
{
	TArray<FString> dataArray;

	dataArray.Add(Contact.DisplayName);
	dataArray.Append(Contact.Numbers);

#if PLATFORM_ANDROID
	jobject javaContact = AGContactUtils::ConvertToJavaContact(Contact);

	return AGMethodCallUtils::CallStaticBoolMethod(AGContactsClassName, "addContact", "(Landroid/app/Activity;Lcom/ninevastudios/androidgoodies/AGContact;)Z", 
		FJavaWrapper::GameActivityThis, javaContact);
#endif

	return false;
}

void UAGContactsBPL::PickContact(const FOnPickContactSuccessDelegate& OnContactPickedCallback, const FOnPickContactErrorelegate& OnContactPickErrorCallback)
{
	OnPickContactSuccess = OnContactPickedCallback;
	OnPickContactError = OnContactPickErrorCallback;

#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(AGContactsClassName, "pickContact", "(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis);
#endif
}

#if PLATFORM_ANDROID

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGContacts_onContactPicked(JNIEnv* env, jclass clazz, jobject contact)
{
	AsyncTask(ENamedThreads::GameThread, [Data = NewGlobalJavaObject(contact)]()
	{
		FAGContact Contact;
		Contact.DisplayName = AGMethodCallUtils::CallStringMethod(*Data, "getDisplayName", "()Ljava/lang/String;");
		Contact.PhotoUri = AGMethodCallUtils::CallStringMethod(*Data, "getPhotoUri", "()Ljava/lang/String;");
		Contact.Numbers = AGArrayConvertor::ConvertToStringArray(static_cast<jobjectArray>(AGMethodCallUtils::CallObjectMethod(*Data, "getPhones", "()[Ljava/lang/String;")));
		Contact.Emails = AGArrayConvertor::ConvertToStringArray(static_cast<jobjectArray>(AGMethodCallUtils::CallObjectMethod(*Data, "getEmails", "()[Ljava/lang/String;")));

		UAGContactsBPL::OnPickContactSuccess.ExecuteIfBound(Contact); 
	});
}

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGContacts_onContactPickError(JNIEnv* env, jclass clazz, jstring error)
{
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, error);
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UAGContactsBPL::OnPickContactError.ExecuteIfBound(ErrorMessage); 
	});
}
#endif
