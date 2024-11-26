#include "AndroidGoodiesNotificationInboxStyle.h"

#include "Android/AndroidApplication.h"
#include "Android/Utils/AGArrayConvertor.h"
#include "Android/Utils/AGMethodCallUtils.h"

AndroidGoodiesNotificationInboxStyle::~AndroidGoodiesNotificationInboxStyle()
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->DeleteLocalRef(NativeStyle);
	NativeStyle = nullptr;
}

AndroidGoodiesNotificationInboxStyle::AndroidGoodiesNotificationInboxStyle(jobject Style)
{
	NativeStyle = Style;
}

jobject AndroidGoodiesNotificationInboxStyle::GetNativeStyle()
{
	return NativeStyle;
}

void AndroidGoodiesNotificationInboxStyle::AddLine(FString Line)
{
	NativeStyle = AGMethodCallUtils::CallObjectMethod(NativeStyle, "addLine",
	                                                  "(Ljava/lang/CharSequence;)Landroidx/core/app/NotificationCompat$InboxStyle;", *FJavaClassObject::GetJString(Line));
}

void AndroidGoodiesNotificationInboxStyle::SetBigContentTitle(FString Title)
{
	NativeStyle = AGMethodCallUtils::CallObjectMethod(NativeStyle, "setBigContentTitle",
	                                                  "(Ljava/lang/CharSequence;)Landroidx/core/app/NotificationCompat$InboxStyle;", *FJavaClassObject::GetJString(Title));
}

void AndroidGoodiesNotificationInboxStyle::SetSummaryText(FString Summary)
{
	NativeStyle = AGMethodCallUtils::CallObjectMethod(NativeStyle, "setSummaryText",
	                                                 "(Ljava/lang/CharSequence;)Landroidx/core/app/NotificationCompat$InboxStyle;", *FJavaClassObject::GetJString(Summary));
}
