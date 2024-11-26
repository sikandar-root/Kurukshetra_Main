// Copyright (c) 2023 Nineva Studios

#include "AnalyticsAndroid.h"

#include "Analytics/FGAnalyticsParameter.h"
#include "FirebaseGoodiesLog.h"

#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"
#include "Android/Utils/FGJavaConvertor.h"
#include "Android/Utils/FGMethodCallUtils.h"

static const ANSICHAR* FGAnalyticsClassName = "com/ninevastudios/unrealfirebase/FGAnalytics";

AnalyticsAndroid::~AnalyticsAndroid()
{
}

void AnalyticsAndroid::SetAnalyticsCollectionEnabled(bool bEnabled)
{
	FGMethodCallUtils::CallStaticVoidMethod(FGAnalyticsClassName, "SetAnalyticsCollectionEnabled", "(Landroid/app/Activity;Z)V",
	FJavaWrapper::GameActivityThis, bEnabled);
}

void AnalyticsAndroid::ResetAnalyticsData()
{
	FGMethodCallUtils::CallStaticVoidMethod(FGAnalyticsClassName, "ResetAnalyticsData", "(Landroid/app/Activity;)V",
	FJavaWrapper::GameActivityThis);
}

void AnalyticsAndroid::SetSessionTimeoutDuration(int64 Milliseconds)
{
	FGMethodCallUtils::CallStaticVoidMethod(FGAnalyticsClassName, "SetSessionTimeoutDuration", "(Landroid/app/Activity;J)V",
	FJavaWrapper::GameActivityThis, Milliseconds);
}

void AnalyticsAndroid::SetUserId(const FString& Id)
{
	auto JId = FJavaClassObject::GetJString(Id);
	FGMethodCallUtils::CallStaticVoidMethod(FGAnalyticsClassName, "SetUserId", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *JId);
}

void AnalyticsAndroid::SetUserProperty(const FString& Name, const FString& Value)
{
	FGMethodCallUtils::CallStaticVoidMethod(FGAnalyticsClassName, "SetUserProperty", "(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;)V",
	FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(Name), *FJavaClassObject::GetJString(Value));
}

void AnalyticsAndroid::SetCurrentScreen(const FString& ScreenName, const FString& ScreenClassName)
{
	FGMethodCallUtils::CallStaticVoidMethod(FGAnalyticsClassName, "SetCurrentScreen", "(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;)V",
	FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(ScreenName), *FJavaClassObject::GetJString(ScreenClassName));
}

UFGAnalyticsParameter* AnalyticsAndroid::CreateIntegerParameter(const FString& Name, int64 Value)
{
	UFGAnalyticsParameter* parameter = NewObject<UFGAnalyticsParameter>();
	parameter->SetName(Name);
	parameter->SetInt(Value);

	return parameter;
}

UFGAnalyticsParameter* AnalyticsAndroid::CreateFloatParameter(const FString& Name, float Value)
{
	UFGAnalyticsParameter* parameter = NewObject<UFGAnalyticsParameter>();
	parameter->SetName(Name);
	parameter->SetFloat(Value);

	return parameter;
}

UFGAnalyticsParameter* AnalyticsAndroid::CreateStringParameter(const FString& Name, const FString& Value)
{
	UFGAnalyticsParameter* parameter = NewObject<UFGAnalyticsParameter>();
	parameter->SetName(Name);
	parameter->SetString(Value);

	return parameter;
}

void AnalyticsAndroid::LogEvent(const FString& EventName)
{
	FGMethodCallUtils::CallStaticVoidMethod(FGAnalyticsClassName, "LogEvent", "(Landroid/app/Activity;Ljava/lang/String;)V",
	FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(EventName));
}

void AnalyticsAndroid::LogEventWithParameter(const FString& EventName, UFGAnalyticsParameter* Parameter)
{
	TArray<UFGAnalyticsParameter*> parameters;
	parameters.Add(Parameter);
	LogEventWithParameters(EventName, parameters);
}

void AnalyticsAndroid::LogEventWithParameters(const FString& EventName,
	const TArray<UFGAnalyticsParameter*>& Parameters)
{
	// TODO wrap this in a separate class
	JNIEnv* env = FAndroidApplication::GetJavaEnv();
	jclass bundleClass = FJavaWrapper::FindClass(env, "android/os/Bundle", false);
	jmethodID bundleCtor = FJavaWrapper::FindMethod(env, bundleClass, "<init>", "()V", false);
	jmethodID putLongMethod = FJavaWrapper::FindMethod(env, bundleClass, "putLong", "(Ljava/lang/String;J)V", false);
	jmethodID putDoubleMethod = FJavaWrapper::FindMethod(env, bundleClass, "putDouble", "(Ljava/lang/String;D)V", false);
	jmethodID putStringMethod = FJavaWrapper::FindMethod(env, bundleClass, "putString", "(Ljava/lang/String;Ljava/lang/String;)V", false);
	jobject bundle = env->NewObject(bundleClass, bundleCtor);

	for (const auto parameter : Parameters)
	{
		switch (parameter->GetType())
		{
		case EParameterType::Integer:
			{
				env->CallVoidMethod(bundle, putLongMethod,
					*FJavaClassObject::GetJString(parameter->GetName()), parameter->GetInt());
				break;
			}
		case EParameterType::Float:
			{
				env->CallVoidMethod(bundle, putDoubleMethod,
					*FJavaClassObject::GetJString(parameter->GetName()), parameter->GetFloat());
				break;
			}
		case EParameterType::String:
			{
				env->CallVoidMethod(bundle, putStringMethod,
					*FJavaClassObject::GetJString(parameter->GetName()),
					*FJavaClassObject::GetJString(parameter->GetString()));
				break;
			}
		default:
			{
				UE_LOG(LogFirebaseGoodies, Error, TEXT("Trying to log an event with an undefined parameter"));
				break;
			}
		}
	}

	FGMethodCallUtils::CallStaticVoidMethod(FGAnalyticsClassName, "LogEvent",
		"(Landroid/app/Activity;Ljava/lang/String;Landroid/os/Bundle;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(EventName), bundle);
}
