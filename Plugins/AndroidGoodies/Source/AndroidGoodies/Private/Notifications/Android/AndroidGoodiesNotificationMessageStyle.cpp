#include "AndroidGoodiesNotificationMessageStyle.h"

#include "Android/AndroidApplication.h"
#include "Android/Utils/AGMethodCallUtils.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"

AndroidGoodiesNotificationMessageStyle::~AndroidGoodiesNotificationMessageStyle()
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->DeleteLocalRef(NativeStyle);
	NativeStyle = nullptr;
}

AndroidGoodiesNotificationMessageStyle::AndroidGoodiesNotificationMessageStyle(jobject Style)
{
	NativeStyle = Style;
}

jobject AndroidGoodiesNotificationMessageStyle::GetNativeStyle()
{
	return NativeStyle;
}

void AndroidGoodiesNotificationMessageStyle::AddMessage(FString Text, FDateTime TimeStamp, FString Sender)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Add Message -> TimeStamp: %s"), *TimeStamp.ToString());
	long DateLong = TimeStamp.ToUnixTimestamp() * 1000;
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Add Message -> TimeStamp: %d"), DateLong);

	NativeStyle = AGMethodCallUtils::CallObjectMethod(NativeStyle, "addMessage", "(Ljava/lang/CharSequence;JLjava/lang/CharSequence;)Landroidx/core/app/NotificationCompat$MessagingStyle;",
	                                                  *FJavaClassObject::GetJString(Text), static_cast<jlong>(DateLong), *FJavaClassObject::GetJString(Sender));
}

void AndroidGoodiesNotificationMessageStyle::SetConversationTitle(FString Title)
{
	NativeStyle = AGMethodCallUtils::CallObjectMethod(NativeStyle, "setConversationTitle", "(Ljava/lang/CharSequence;)Landroidx/core/app/NotificationCompat$MessagingStyle;",
	                                                  *FJavaClassObject::GetJString(Title));
}

void AndroidGoodiesNotificationMessageStyle::SetGroupConversation(bool bIsGroupConversation)
{
	NativeStyle = AGMethodCallUtils::CallObjectMethod(NativeStyle, "setGroupConversation", "(Z)Landroidx/core/app/NotificationCompat$MessagingStyle;",
	                                                  bIsGroupConversation);
}
