// Copyright (c) 2018 Nineva Studios

#include "AGMethodCallUtils.h"

#include "Android/AndroidJava.h"
#include "AGDeviceInfoBPL.h"

FString AGMethodCallUtils::CallStaticStringMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Method call CallStaticStringMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = FAndroidApplication::FindJavaClass(ClassName);

	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	jstring Return = static_cast<jstring>(Env->CallStaticObjectMethodV(Class, Method, Args));
	va_end(Args);

	const char * UTFString = Env->GetStringUTFChars(Return, nullptr);
	FString Result(UTF8_TO_TCHAR(UTFString));
	Env->ReleaseStringUTFChars(Return, UTFString);

	Env->DeleteLocalRef(Class);

	return Result;
}

bool AGMethodCallUtils::CallStaticBoolMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Method call CallStaticBoolMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = FAndroidApplication::FindJavaClass(ClassName);

	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	bool Result = Env->CallStaticBooleanMethodV(Class, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}

int AGMethodCallUtils::CallStaticIntMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Method call CallStaticIntMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = FAndroidApplication::FindJavaClass(ClassName);

	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	int Result = Env->CallStaticIntMethodV(Class, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}

long AGMethodCallUtils::CallStaticLongMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Method call CallStaticIntMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = FAndroidApplication::FindJavaClass(ClassName);

	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	long Result = Env->CallStaticLongMethodV(Class, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}

jobject AGMethodCallUtils::CallStaticObjectMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Method call CallStaticObjectMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = FAndroidApplication::FindJavaClass(ClassName);

	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	jobject Result = Env->CallStaticObjectMethodV(Class, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}

void AGMethodCallUtils::CallStaticVoidMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Method call CallStaticVoidMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = FAndroidApplication::FindJavaClass(ClassName);

	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	Env->CallStaticVoidMethodV(Class, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);
}

FString AGMethodCallUtils::CallStringMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Method call CallStringMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = Env->GetObjectClass(object);

	jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	jstring Return = static_cast<jstring>(Env->CallObjectMethodV(object, Method, Args));
	va_end(Args);

	const char* UTFString = Env->GetStringUTFChars(Return, nullptr);
	FString Result(UTF8_TO_TCHAR(UTFString));
	Env->ReleaseStringUTFChars(Return, UTFString);

	Env->DeleteLocalRef(Class);

	return Result;
}

bool AGMethodCallUtils::CallBoolMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Method call CallBoolMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = Env->GetObjectClass(object);

	jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	bool Result = Env->CallBooleanMethodV(object, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}

int AGMethodCallUtils::CallIntMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Method call CallIntMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = Env->GetObjectClass(object);

	jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	int Result = Env->CallIntMethodV(object, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}
jobject AGMethodCallUtils::CallObjectMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Method call CallObjectMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = Env->GetObjectClass(object);

	jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	jobject Result = Env->CallObjectMethodV(object, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}

void AGMethodCallUtils::CallVoidMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Method call CallVoidMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = Env->GetObjectClass(object);

	jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	Env->CallVoidMethodV(object, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);
}

long AGMethodCallUtils::CallLongMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = Env->GetObjectClass(object);

	jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	long Result = Env->CallLongMethodV(object, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}