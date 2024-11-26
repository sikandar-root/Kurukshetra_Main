#include "AndroidGoodiesNotificationChannelGroup.h"

#include "Notifications/Android/AndroidGoodiesNotificationChannel.h"
#include "Android/AndroidApplication.h"
#include "Android/Utils/AGArrayConvertor.h"
#include "Android/Utils/AGMethodCallUtils.h"
#include "Notifications/Interface/IAndroidGoodiesNotificationChannel.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"

AndroidGoodiesNotificationChannelGroup::~AndroidGoodiesNotificationChannelGroup()
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->DeleteGlobalRef(NativeChannelGroup);
	NativeChannelGroup = nullptr;
}

AndroidGoodiesNotificationChannelGroup::AndroidGoodiesNotificationChannelGroup(jobject ChannelGroup)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	NativeChannelGroup = Env->NewGlobalRef(ChannelGroup);
}

jobject AndroidGoodiesNotificationChannelGroup::GetNativeChannelGroup()
{
	return NativeChannelGroup;
}

FString AndroidGoodiesNotificationChannelGroup::GetId()
{
	return AGMethodCallUtils::CallStringMethod(NativeChannelGroup, "getId", "()Ljava/lang/String;");
}

FString AndroidGoodiesNotificationChannelGroup::GetName()
{
	return AGMethodCallUtils::CallStringMethod(NativeChannelGroup, "getName", "()Ljava/lang/CharSequence;");
}

FString AndroidGoodiesNotificationChannelGroup::GetDescription()
{
	return AGMethodCallUtils::CallStringMethod(NativeChannelGroup, "getDescription", "()Ljava/lang/String;");
}

void AndroidGoodiesNotificationChannelGroup::SetDescription(const FString Description)
{
	AGMethodCallUtils::CallVoidMethod(NativeChannelGroup, "setDescription", "(Ljava/lang/String;)V", *FJavaClassObject::GetJString(Description));
}

bool AndroidGoodiesNotificationChannelGroup::IsBlocked()
{
	return AGMethodCallUtils::CallBoolMethod(NativeChannelGroup, "isBlocked", "()Z");
}

TArray<TSharedPtr<IAndroidGoodiesNotificationChannel>> AndroidGoodiesNotificationChannelGroup::GetChannels()
{
	TArray<TSharedPtr<IAndroidGoodiesNotificationChannel>> Result;

	jobject ChannelList = AGMethodCallUtils::CallObjectMethod(NativeChannelGroup, "getChannels", "()Ljava/util/List;");

	//TODO: make util method for working with java lists?
	int Count = AGMethodCallUtils::CallIntMethod(ChannelList, "size", "()I");
	for (int i = 0; i < Count; i++)
	{
		jobject JavaNotificationChannelObject = AGMethodCallUtils::CallObjectMethod(ChannelList, "get", "(I)Ljava/lang/Object;", i);
		Result.Add(MakeShareable(new AndroidGoodiesNotificationChannel(JavaNotificationChannelObject)));
	}

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->DeleteLocalRef(ChannelList);
	
	return Result;
}
