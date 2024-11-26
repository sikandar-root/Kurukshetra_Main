#include "CloudFunctionsAndroid.h"
#include "CloudFunctions/FGCloudFunctions.h"

#include "Async/Async.h"
#include "FirebaseGoodiesLog.h"
#include "Common/FGValueVariantAccess.h"

#include "Android/Utils/FGJavaConvertor.h"
#include "Android/Utils/FGMethodCallUtils.h"
#include "Android/Utils/FGValueVariantUtils.h"

#include "CloudFunctions/Callbacks/FGCloudFunctionsStringCallback.h"
#include "CloudFunctions/Callbacks/FGCloudFunctionsIntCallback.h"
#include "CloudFunctions/Callbacks/FGCloudFunctionsFloatCallback.h"
#include "CloudFunctions/Callbacks/FGCloudFunctionsBoolCallback.h"
#include "CloudFunctions/Callbacks/FGCloudFunctionsVoidCallback.h"
#include "CloudFunctions/Callbacks/FGCloudFunctionsMapCallback.h"
#include "CloudFunctions/Callbacks/FGCloudFunctionsArrayCallback.h"


const FString DefaultRegion = "us-central1";

const ANSICHAR* FGCloudFunctionsClassName = "com/ninevastudios/unrealfirebase/FGCloudFunctions";

CloudFunctionsAndroid::~CloudFunctionsAndroid()
{
}

void CloudFunctionsAndroid::CallStringFunction(const FString& MethodName, FString Region,
	const TMap<FString, FFGValueVariant>& Parameters, const FCloudFunctionsStringDelegate& OnSuccess,
	const FCloudFunctionsStringDelegate& OnError)
{
	UFGCloudFunctionsStringCallback* NativeCallback = NewObject<UFGCloudFunctionsStringCallback>();
	NativeCallback->BindSuccessDelegate(OnSuccess);
	NativeCallback->BindErrorDelegate(OnError);

	if (Region.IsEmpty())
	{
		Region = DefaultRegion;
	}
	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();

	FGMethodCallUtils::CallStaticVoidMethod(FGCloudFunctionsClassName, "callStringFunction",
	                                        "(JLjava/lang/String;Ljava/lang/String;Ljava/util/Map;)V",
	                                        (jlong) NativeCallback,
	                                        *FJavaClassObject::GetJString(MethodName), *FJavaClassObject::GetJString(Region),
	                                        ValueVariantUtils::VariantMapToJavaMap(JEnv, Parameters));
}

void CloudFunctionsAndroid::CallIntFunction(const FString& MethodName, FString Region,
	const TMap<FString, FFGValueVariant>& Parameters, const FCloudFunctionsIntDelegate& OnSuccess,
	const FCloudFunctionsStringDelegate& OnError)
{
	UFGCloudFunctionsIntCallback* NativeCallback = NewObject<UFGCloudFunctionsIntCallback>();
	NativeCallback->BindSuccessDelegate(OnSuccess);
	NativeCallback->BindErrorDelegate(OnError);

	if (Region.IsEmpty())
	{
		Region = DefaultRegion;
	}
	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();

	FGMethodCallUtils::CallStaticVoidMethod(FGCloudFunctionsClassName, "callIntFunction",
		"(JLjava/lang/String;Ljava/lang/String;Ljava/util/Map;)V",
		(jlong) NativeCallback,
		*FJavaClassObject::GetJString(MethodName), *FJavaClassObject::GetJString(Region),
		ValueVariantUtils::VariantMapToJavaMap(JEnv, Parameters));
}

void CloudFunctionsAndroid::CallFloatFunction(const FString& MethodName, FString Region,
	const TMap<FString, FFGValueVariant>& Parameters, const FCloudFunctionsFloatDelegate& OnSuccess,
	const FCloudFunctionsStringDelegate& OnError)
{
	UFGCloudFunctionsFloatCallback* NativeCallback = NewObject<UFGCloudFunctionsFloatCallback>();
	NativeCallback->BindSuccessDelegate(OnSuccess);
	NativeCallback->BindErrorDelegate(OnError);
	
	if (Region.IsEmpty())
	{
		Region = DefaultRegion;
	}
	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();

	FGMethodCallUtils::CallStaticVoidMethod(FGCloudFunctionsClassName, "callFloatFunction",
		"(JLjava/lang/String;Ljava/lang/String;Ljava/util/Map;)V",
		(jlong) NativeCallback,
		*FJavaClassObject::GetJString(MethodName), *FJavaClassObject::GetJString(Region),
		ValueVariantUtils::VariantMapToJavaMap(JEnv, Parameters));
}

void CloudFunctionsAndroid::CallBoolFunction(const FString& MethodName, FString Region,
	const TMap<FString, FFGValueVariant>& Parameters, const FCloudFunctionsBoolDelegate& OnSuccess,
	const FCloudFunctionsStringDelegate& OnError)
{
	UFGCloudFunctionsBoolCallback* NativeCallback = NewObject<UFGCloudFunctionsBoolCallback>();
	NativeCallback->BindSuccessDelegate(OnSuccess);
	NativeCallback->BindErrorDelegate(OnError);
	
	if (Region.IsEmpty())
	{
		Region = DefaultRegion;
	}
	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();

	FGMethodCallUtils::CallStaticVoidMethod(FGCloudFunctionsClassName, "callBoolFunction",
		"(JLjava/lang/String;Ljava/lang/String;Ljava/util/Map;)V",
		(jlong) NativeCallback,
		*FJavaClassObject::GetJString(MethodName), *FJavaClassObject::GetJString(Region),
		ValueVariantUtils::VariantMapToJavaMap(JEnv, Parameters));
}

void CloudFunctionsAndroid::CallVoidFunction(const FString& MethodName, FString Region,
	const TMap<FString, FFGValueVariant>& Parameters, const FCloudFunctionsVoidDelegate& OnSuccess,
	const FCloudFunctionsStringDelegate& OnError)
{
	UFGCloudFunctionsVoidCallback* NativeCallback = NewObject<UFGCloudFunctionsVoidCallback>();
	NativeCallback->BindSuccessDelegate(OnSuccess);
	NativeCallback->BindErrorDelegate(OnError);
	
	if (Region.IsEmpty())
	{
		Region = DefaultRegion;
	}
	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();

	FGMethodCallUtils::CallStaticVoidMethod(FGCloudFunctionsClassName, "callVoidFunction",
		"(JLjava/lang/String;Ljava/lang/String;Ljava/util/Map;)V",
		(jlong) NativeCallback,
		*FJavaClassObject::GetJString(MethodName), *FJavaClassObject::GetJString(Region),
		ValueVariantUtils::VariantMapToJavaMap(JEnv, Parameters));
}

void CloudFunctionsAndroid::CallMapFunction(const FString& MethodName, FString Region,
	const TMap<FString, FFGValueVariant>& Parameters, const FCloudFunctionsMapDelegate& OnSuccess,
	const FCloudFunctionsStringDelegate& OnError)
{
	UFGCloudFunctionsMapCallback* NativeCallback = NewObject<UFGCloudFunctionsMapCallback>();
	NativeCallback->BindSuccessDelegate(OnSuccess);
	NativeCallback->BindErrorDelegate(OnError);
	
	if (Region.IsEmpty())
	{
		Region = DefaultRegion;
	}
	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();

	FGMethodCallUtils::CallStaticVoidMethod(FGCloudFunctionsClassName, "callMapFunction",
		"(JLjava/lang/String;Ljava/lang/String;Ljava/util/Map;)V",
		(jlong) NativeCallback,
		*FJavaClassObject::GetJString(MethodName), *FJavaClassObject::GetJString(Region),
		ValueVariantUtils::VariantMapToJavaMap(JEnv, Parameters));
}

void CloudFunctionsAndroid::CallArrayFunction(const FString& MethodName, FString Region,
	const TMap<FString, FFGValueVariant>& Parameters, const FCloudFunctionsArrayDelegate& OnSuccess,
	const FCloudFunctionsStringDelegate& OnError)
{
	UFGCloudFunctionsArrayCallback* NativeCallback = NewObject<UFGCloudFunctionsArrayCallback>();
	NativeCallback->BindSuccessDelegate(OnSuccess);
	NativeCallback->BindErrorDelegate(OnError);
	
	if (Region.IsEmpty())
	{
		Region = DefaultRegion;
	}
	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();

	FGMethodCallUtils::CallStaticVoidMethod(FGCloudFunctionsClassName, "callArrayFunction",
		"(JLjava/lang/String;Ljava/lang/String;Ljava/util/Map;)V",
		(jlong) NativeCallback,
		*FJavaClassObject::GetJString(MethodName), *FJavaClassObject::GetJString(Region),
		ValueVariantUtils::VariantMapToJavaMap(JEnv, Parameters));
}
