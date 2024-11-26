// Copyright (c) 2020 Nineva Studios

#include "Social/GPEventLibrary.h"

#include "GooglePlayLog.h"
#include "Social/GPEvent.h"

#if PLATFORM_ANDROID
#include "Android/Utils/GPJavaConvertor.h"
#include "Android/Utils/GPMethodCallUtils.h"
#include "Async/Async.h"
#endif

static const ANSICHAR* GPEventClassName = "com/ninevastudios/googleplay/GPEvent";

UGPEventLibrary::FGPLoadEventsDelegate UGPEventLibrary::OnLoadEventsDelegate;

void UGPEventLibrary::IncrementEvent(const FString& EventID, int Value /*= 1*/)
{
#if PLATFORM_ANDROID
	auto JIdString = FJavaClassObject::GetJString(EventID);
	GPMethodCallUtils::CallStaticVoidMethod(GPEventClassName, "incrementEvent", "(Landroid/app/Activity;Ljava/lang/String;I)V",
		FJavaWrapper::GameActivityThis, *JIdString, Value);
#endif
}

void UGPEventLibrary::LoadEvents(const FGPLoadEventsDelegate& OnLoadEvents, bool ForceRefresh, const TArray<FString>& EventIds)
{
	OnLoadEventsDelegate = OnLoadEvents;
#if PLATFORM_ANDROID
	GPMethodCallUtils::CallStaticVoidMethod(GPEventClassName, "loadEvents", "(Landroid/app/Activity;Z[Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, ForceRefresh, GPJavaConvertor::ToJavaStringArray(EventIds));
#endif
}

#if PLATFORM_ANDROID
JNI_METHOD void Java_com_ninevastudios_googleplay_GPEvent_onLoadEventsCallback(
	JNIEnv* env, jclass clazz, jobject eventArrayObject)
{
	TArray<UGPEvent*> Events;
	jobjectArray eventArray = static_cast<jobjectArray>(eventArrayObject);
	const int ArrayLength = env->GetArrayLength(eventArray);
	for (int i = 0; i < ArrayLength; i++)
	{
		jobject EventObject = env->GetObjectArrayElement(eventArray, i);
		UGPEvent* Event = NewObject<UGPEvent>();
		Event->Init(EventObject);
		Events.Add(Event);
	}

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UGPEventLibrary::OnLoadEventsDelegate.ExecuteIfBound(Events);
	});
}

#endif
