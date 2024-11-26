// Copyright (c) 2018 Nineva Studios

#include "AGArrayConvertor.h"

jobjectArray AGArrayConvertor::ConvertToJStringArray(const TArray<FString>& stringArray)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jobjectArray javaStringArray = (jobjectArray)Env->NewObjectArray(stringArray.Num(), FJavaWrapper::JavaStringClass, nullptr);

	for (int i = 0; i < stringArray.Num(); i++)
	{
		Env->SetObjectArrayElement(javaStringArray, i, *FJavaClassObject::GetJString(stringArray[i]));
	}

	return javaStringArray;
}

jbooleanArray AGArrayConvertor::ConvertToJBooleanArray(const TArray<bool>& boolArray)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jbooleanArray javaBooleanArray = (jbooleanArray)Env->NewBooleanArray(boolArray.Num());

	jboolean* javaBooleanArrayPtr = Env->GetBooleanArrayElements(javaBooleanArray, 0);

	for (int i = 0; i < boolArray.Num(); i++)
	{
		javaBooleanArrayPtr[i] = boolArray[i];
	}

	return javaBooleanArray;
}

jintArray AGArrayConvertor::ConvertToJIntArray(const TArray<int>& intArray)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jintArray javaIntArray = (jintArray)Env->NewIntArray(intArray.Num());

	jint* javaIntArrayPtr = (jint*)malloc(intArray.Num() * sizeof(jint));

	for (int i = 0; i < intArray.Num(); i++)
	{
		javaIntArrayPtr[i] = (jint) intArray[i];
	}

	Env->SetIntArrayRegion(javaIntArray, 0, intArray.Num(), javaIntArrayPtr);

	free(javaIntArrayPtr);

	return javaIntArray;
}

jbyteArray AGArrayConvertor::ConvertToJByteArray(const TArray<uint8>& byteArray)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jbyteArray javaByteArray = (jbyteArray)Env->NewByteArray(byteArray.Num());

	jbyte* javaByteArrayPtr = (jbyte*)malloc(byteArray.Num() * sizeof(jbyte));

	for (int i = 0; i < byteArray.Num(); i++)
	{
		javaByteArrayPtr[i] = byteArray[i];
	}

	Env->SetByteArrayRegion(javaByteArray, 0, byteArray.Num(), javaByteArrayPtr);

	free(javaByteArrayPtr);

	return javaByteArray;
}

jlongArray AGArrayConvertor::ConvertToJLongArray(const TArray<long>& longArray)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jlongArray javaLongArray = (jlongArray)Env->NewLongArray(longArray.Num());

	jlong* javaLongArrayPtr = (jlong*)malloc(longArray.Num() * sizeof(jlong));

	for (int i = 0; i < longArray.Num(); i++)
	{
		javaLongArrayPtr[i] = longArray[i];
	}

	Env->SetLongArrayRegion(javaLongArray, 0, longArray.Num(), javaLongArrayPtr);

	free(javaLongArrayPtr);

	return javaLongArray;
}

TArray<uint8> AGArrayConvertor::ConvertToByteArray(jbyteArray javaArray)
{
	TArray<uint8> byteArray;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jbyte* javaByte = Env->GetByteArrayElements(javaArray, 0);

	int length = Env->GetArrayLength(javaArray);

	for (int i = 0; i < length; i++)
	{
		byteArray.Add(javaByte[i]);
	}

	return byteArray;
}

TArray<long> AGArrayConvertor::ConvertToLongArray(jlongArray javaArray)
{
	TArray<long> longArray;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jlong* javaLong = Env->GetLongArrayElements(javaArray, 0);

	int length = Env->GetArrayLength(javaArray);

	for (int i = 0; i < length; i++)
	{
		longArray.Add((long) javaLong[i]);
	}

	return longArray;
}

TArray<FString> AGArrayConvertor::ConvertToStringArray(jobjectArray javaStringArray)
{
	TArray<FString> stringArray;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	int length = Env->GetArrayLength(javaStringArray);

	for (int i = 0; i < length; i++)
	{
		jstring javaString = static_cast<jstring>(Env->GetObjectArrayElement(javaStringArray, i));

		stringArray.Add(FromJavaString(javaString));
	}

	return stringArray;
}

FString AGArrayConvertor::FromJavaString(jstring javaString)
{
	JNIEnv*	Env = AndroidJavaEnv::GetJavaEnv();
	const char * UTFString = Env->GetStringUTFChars(javaString, nullptr);
	FString Result(UTF8_TO_TCHAR(UTFString));
	Env->ReleaseStringUTFChars(javaString, UTFString);
	Env->DeleteLocalRef(javaString);

	return Result;
}
