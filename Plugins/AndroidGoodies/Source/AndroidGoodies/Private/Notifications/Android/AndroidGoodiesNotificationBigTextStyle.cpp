#include "AndroidGoodiesNotificationBigTextStyle.h"

#include "Android/AndroidApplication.h"
#include "Android/Utils/AGMethodCallUtils.h"

AndroidGoodiesNotificationBigTextStyle::~AndroidGoodiesNotificationBigTextStyle()
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->DeleteLocalRef(NativeStyle);
	NativeStyle = nullptr;
}

AndroidGoodiesNotificationBigTextStyle::AndroidGoodiesNotificationBigTextStyle(jobject Style)
{
	NativeStyle = Style;
}

jobject AndroidGoodiesNotificationBigTextStyle::GetNativeStyle()
{
	return NativeStyle;
}

void AndroidGoodiesNotificationBigTextStyle::SetBigContentTitle(FString Title)
{
	NativeStyle = AGMethodCallUtils::CallObjectMethod(NativeStyle, "setBigContentTitle",
	                                                  "(Ljava/lang/CharSequence;)Landroidx/core/app/NotificationCompat$BigTextStyle;", *FJavaClassObject::GetJString(Title));
}

void AndroidGoodiesNotificationBigTextStyle::SetSummaryText(FString Summary)
{
	NativeStyle = AGMethodCallUtils::CallObjectMethod(NativeStyle, "setSummaryText",
	                                                  "(Ljava/lang/CharSequence;)Landroidx/core/app/NotificationCompat$BigTextStyle;", *FJavaClassObject::GetJString(Summary));
}
