#include "AndroidGoodiesNotificationBigPictureStyle.h"

#include "Notifications/Android/AndroidNotificationManager.h"
#include "Android/AndroidApplication.h"
#include "Android/Utils/AGArrayConvertor.h"
#include "Android/Utils/AGMediaUtils.h"
#include "Android/Utils/AGMethodCallUtils.h"

AndroidGoodiesNotificationBigPictureStyle::~AndroidGoodiesNotificationBigPictureStyle()
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->DeleteLocalRef(NativeStyle);
	NativeStyle = nullptr;
}

AndroidGoodiesNotificationBigPictureStyle::AndroidGoodiesNotificationBigPictureStyle(jobject Style)
{
	NativeStyle = Style;
}

jobject AndroidGoodiesNotificationBigPictureStyle::GetNativeStyle()
{
	return NativeStyle;
}

void AndroidGoodiesNotificationBigPictureStyle::SetBigLargeIcon(UTexture2D* Icon)
{
	const TArray<uint8> ByteArray = AGMediaUtils::ByteArrayFromTexture(Icon);
	jbyteArray JavaArray = AGArrayConvertor::ConvertToJByteArray(ByteArray);

	NativeStyle = AGMethodCallUtils::CallStaticObjectMethod(AndroidNotificationManager::NotificationHelperClassName, "setBigLargeIcon",
	                                                        "(Landroidx/core/app/NotificationCompat$BigPictureStyle;[BII)Landroidx/core/app/NotificationCompat$BigPictureStyle;",
	                                                        NativeStyle, JavaArray, Icon->GetSizeX(), Icon->GetSizeY());
}

void AndroidGoodiesNotificationBigPictureStyle::SetBigContentTitle(FString Title)
{
	NativeStyle = AGMethodCallUtils::CallObjectMethod(NativeStyle, "setBigContentTitle", "(Ljava/lang/CharSequence;)Landroidx/core/app/NotificationCompat$BigPictureStyle;",
	                                                  *FJavaClassObject::GetJString(Title));
}

void AndroidGoodiesNotificationBigPictureStyle::SetSummaryText(FString Text)
{
	NativeStyle = AGMethodCallUtils::CallObjectMethod(NativeStyle, "setSummaryText", "(Ljava/lang/CharSequence;)Landroidx/core/app/NotificationCompat$BigPictureStyle;",
	                                                 *FJavaClassObject::GetJString(Text));
}
