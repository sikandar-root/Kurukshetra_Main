// Copyright (c) 2023 Nineva Studios

#include "FirebaseGoodiesLog.h"
#include "Async/Async.h"
#include "Android/Utils/FGJavaConvertor.h"

#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"
#include "Android/AndroidJavaEnv.h"
#include "Android/AndroidPlatform.h"
#include "Android/Utils/FGValueVariantUtils.h"

#include "CloudFunctions/Callbacks/FGCloudFunctionsStringCallback.h"
#include "CloudFunctions/Callbacks/FGCloudFunctionsIntCallback.h"
#include "CloudFunctions/Callbacks/FGCloudFunctionsFloatCallback.h"
#include "CloudFunctions/Callbacks/FGCloudFunctionsBoolCallback.h"
#include "CloudFunctions/Callbacks/FGCloudFunctionsVoidCallback.h"
#include "CloudFunctions/Callbacks/FGCloudFunctionsMapCallback.h"
#include "CloudFunctions/Callbacks/FGCloudFunctionsArrayCallback.h"

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudFunctions_OnFunctionError(JNIEnv* env, jclass clazz, jlong objAddr, jstring error)
{
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, error);
	UE_LOG(LogFirebaseGoodies, Error, TEXT("Calling Cloud Function failed: %s"), *ErrorMessage);

	UFGCloudFunctionsCallback* callback = reinterpret_cast<UFGCloudFunctionsCallback*>(objAddr);
	if (IsValid(callback))
	{
		AsyncTask(ENamedThreads::GameThread, [=]() {
			callback->ExecuteError(ErrorMessage);
			callback->RemoveFromRoot();
		});
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid Error callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudFunctions_OnStringFunctionComplete(JNIEnv* env, jclass clazz, jlong objAddr, jstring string)
{
	FString StringResponse = FJavaHelper::FStringFromParam(env, string);

	UFGCloudFunctionsStringCallback* callback = reinterpret_cast<UFGCloudFunctionsStringCallback*>(objAddr);
	if (IsValid(callback))
	{
		AsyncTask(ENamedThreads::GameThread, [=]() {
			callback->ExecuteSuccess(StringResponse);
			callback->RemoveFromRoot();
		});
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid Success callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudFunctions_OnIntFunctionComplete(JNIEnv* env, jclass clazz, jlong objAddr, jint intRes)
{
	UFGCloudFunctionsIntCallback* callback = reinterpret_cast<UFGCloudFunctionsIntCallback*>(objAddr);
	if (IsValid(callback))
	{
		AsyncTask(ENamedThreads::GameThread, [=]() {
			callback->ExecuteSuccess(intRes);
			callback->RemoveFromRoot();
		});
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid Success callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudFunctions_OnFloatFunctionComplete(JNIEnv* env, jclass clazz, jlong objAddr, jfloat floatRes)
{
	UFGCloudFunctionsFloatCallback* callback = reinterpret_cast<UFGCloudFunctionsFloatCallback*>(objAddr);
	if (IsValid(callback))
	{
		AsyncTask(ENamedThreads::GameThread, [=]() {
			callback->ExecuteSuccess(floatRes);
			callback->RemoveFromRoot();
		});
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid Success callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudFunctions_OnBoolFunctionComplete(JNIEnv* env, jclass clazz, jlong objAddr, jboolean boolRes)
{
	UFGCloudFunctionsBoolCallback* callback = reinterpret_cast<UFGCloudFunctionsBoolCallback*>(objAddr);
	if (IsValid(callback))
	{
		AsyncTask(ENamedThreads::GameThread, [=]() {
			callback->ExecuteSuccess(boolRes);
			callback->RemoveFromRoot();
		});
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid Success callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudFunctions_OnVoidFunctionComplete(JNIEnv* env, jclass clazz, jlong objAddr)
{
	UFGCloudFunctionsVoidCallback* callback = reinterpret_cast<UFGCloudFunctionsVoidCallback*>(objAddr);
	if (IsValid(callback))
	{
		AsyncTask(ENamedThreads::GameThread, [=]() {
			callback->ExecuteSuccess();
			callback->RemoveFromRoot();
		});
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid Success callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudFunctions_OnMapFunctionComplete(JNIEnv* env, jclass clazz, jlong objAddr, jobject mapRes)
{
	FMapWrapper Result;
	Result.Map = ValueVariantUtils::JavaMapToVariantMap(env, mapRes);

	UFGCloudFunctionsMapCallback* callback = reinterpret_cast<UFGCloudFunctionsMapCallback*>(objAddr);
	if (IsValid(callback))
	{
		AsyncTask(ENamedThreads::GameThread, [=]() {
			callback->ExecuteSuccess(Result);
			callback->RemoveFromRoot();
		});
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid Success callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudFunctions_OnArrayFunctionComplete(JNIEnv* env, jclass clazz, jlong objAddr, jobject arrayRes)
{
	TArray<FFGValueVariant> Result = ValueVariantUtils::JavaListToVariantArray(env, arrayRes);

	UFGCloudFunctionsArrayCallback* callback = reinterpret_cast<UFGCloudFunctionsArrayCallback*>(objAddr);
	if (IsValid(callback))
	{
		AsyncTask(ENamedThreads::GameThread, [=]() {
			callback->ExecuteSuccess(Result);
			callback->RemoveFromRoot();
		});
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid Success callback"));
	}
}