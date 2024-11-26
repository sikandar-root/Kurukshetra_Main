#include "AndroidGoodiesNotification.h"

#include "Android/AndroidApplication.h"

AndroidGoodiesNotification::~AndroidGoodiesNotification()
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->DeleteGlobalRef(NativeNotification);
	NativeNotification = nullptr;
}

AndroidGoodiesNotification::AndroidGoodiesNotification(jobject Notification)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	NativeNotification = Env->NewGlobalRef(Notification);
}

jobject AndroidGoodiesNotification::GetNativeNotification()
{
	return NativeNotification;
}
