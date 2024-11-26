// Copyright (c) 2020 Nineva Studios

#include "Social/GPEvent.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"
#include "Async/Async.h"
#include "Android/Utils/GPJavaConvertor.h"
#endif

#include "Utils/GPUtils.h"

UGPEvent::~UGPEvent()
{
#if PLATFORM_ANDROID
	if (Event)
	{
		JNIEnv* Env = FAndroidApplication::GetJavaEnv();
		Env->DeleteGlobalRef(Event);
	}
#endif
}

#if PLATFORM_ANDROID
void UGPEvent::Init(jobject EventObject)
{

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Event = Env->NewGlobalRef(EventObject);

	jclass EventClass = FAndroidApplication::FindJavaClass("com/ninevastudios/googleplay/GPEvent");

	GetIdMethod = FJavaWrapper::FindMethod(Env, EventClass, "getEventId", "()Ljava/lang/String;", false);
	GetNameMethod = FJavaWrapper::FindMethod(Env, EventClass, "getEventName", "()Ljava/lang/String;", false);
	GetDescriptionMethod = FJavaWrapper::FindMethod(Env, EventClass, "getEventDescription", "()Ljava/lang/String;", false);
	GetValueMethod = FJavaWrapper::FindMethod(Env, EventClass, "getEventValue", "()J", false);
	GetFormattedValueMethod = FJavaWrapper::FindMethod(Env, EventClass, "getEventFormattedValue", "()Ljava/lang/String;", false);
	GetIconImageMethod = FJavaWrapper::FindMethod(Env, EventClass, "getEventIconImage", "(Landroid/app/Activity;J)V", false);
}
#endif

FString UGPEvent::EventId() const
{
	FString Result;
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jstring JString = static_cast<jstring>(Env->CallObjectMethod(Event, GetIdMethod));
	Result = FJavaHelper::FStringFromLocalRef(Env, JString);
#endif
	return Result;
}

FString UGPEvent::EventName() const
{
	FString Result;
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jstring JString = static_cast<jstring>(Env->CallObjectMethod(Event, GetNameMethod));
	Result = FJavaHelper::FStringFromLocalRef(Env, JString);
#endif
	return Result;
}

FString UGPEvent::EventDescription() const
{
	FString Result;
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jstring JString = static_cast<jstring>(Env->CallObjectMethod(Event, GetDescriptionMethod));
	Result = FJavaHelper::FStringFromLocalRef(Env, JString);
#endif
	return Result;
}

int UGPEvent::EventValue() const
{
	int Result = 0;
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Result = Env->CallLongMethod(Event, GetValueMethod);
#endif
	return Result;
}

FString UGPEvent::EventFormattedValue() const
{
	FString Result;
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jstring JString = static_cast<jstring>(Env->CallObjectMethod(Event, GetFormattedValueMethod));
	Result = FJavaHelper::FStringFromLocalRef(Env, JString);
#endif
	return Result;
}

void UGPEvent::GetIconImage(const FGPOnImageReadyDelegate& OnImageReady)
{
	OnIconImageReadyDelegate = OnImageReady;

#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->CallVoidMethod(Event, GetIconImageMethod, FJavaWrapper::GameActivityThis, (jlong)this);
#endif
}

#if PLATFORM_ANDROID

JNI_METHOD void Java_com_ninevastudios_googleplay_GPEvent_onEventIconReady(JNIEnv* env, jclass clazz,
	jlong objAddr, jbyteArray buffer, int Width, int Height)
{
	UGPEvent* Event = reinterpret_cast<UGPEvent*>(objAddr);
	TArray<uint8> ByteArray = GPJavaConvertor::ToByteArray(static_cast<jbyteArray>(buffer));
	AsyncTask(ENamedThreads::GameThread, [=]() {
		Event->OnIconImageReady(GPUtils::TextureFromByteArray(ByteArray, Width, Height));
	});
}

#endif
