#include "AndroidNotificationManager.h"

#include "Notifications/Android/AndroidGoodiesNotificationBigPictureStyle.h"
#include "Notifications/Android/AndroidGoodiesNotificationBigTextStyle.h"
#include "Notifications/Android/AndroidGoodiesNotificationInboxStyle.h"
#include "Notifications/Android/AndroidGoodiesNotificationMessageStyle.h"
#include "Notifications/AGNotificationManager.h"
#include "Notifications/Android/AndroidGoodiesNotificationBuilder.h"
#include "Notifications/Android/AndroidGoodiesNotificationChannelGroup.h"
#include "Notifications/Android/AndroidGoodiesNotification.h"
#include "Notifications/Android/AndroidGoodiesNotificationChannel.h"

#include "Android/Utils/AGMethodCallUtils.h"
#include "Android/Utils/AGArrayConvertor.h"
#include "Android/Utils/AGMediaUtils.h"

const ANSICHAR* AndroidNotificationManager::NotificationHelperClassName = "com/ninevastudios/androidgoodies/AGNotificationHelper";

AndroidNotificationManager::~AndroidNotificationManager()
{
}

TSharedPtr<IAndroidGoodiesNotificationMessageStyle> AndroidNotificationManager::CreateMessageStyle(FString UserDisplayName)
{
	jobject JavaObject = AGMethodCallUtils::CallStaticObjectMethod(AndroidNotificationManager::NotificationHelperClassName, "getMessagingStyle",
	                                                               "(Ljava/lang/String;)Landroidx/core/app/NotificationCompat$MessagingStyle;", *FJavaClassObject::GetJString(UserDisplayName));
	return MakeShareable(new AndroidGoodiesNotificationMessageStyle(JavaObject));
}

TSharedPtr<IAndroidGoodiesNotificationInboxStyle> AndroidNotificationManager::CreateInboxStyle()
{
	jobject JavaObject = AGMethodCallUtils::CallStaticObjectMethod(AndroidNotificationManager::NotificationHelperClassName, "getInboxStyle",
	                                                               "()Landroidx/core/app/NotificationCompat$InboxStyle;");
	return MakeShareable(new AndroidGoodiesNotificationInboxStyle(JavaObject));
}

TSharedPtr<IAndroidGoodiesNotificationBigTextStyle> AndroidNotificationManager::CreateBigTextStyle(FString BigText)
{
	jobject JavaObject = AGMethodCallUtils::CallStaticObjectMethod(AndroidNotificationManager::NotificationHelperClassName, "getBigTextStyle",
	                                                               "(Ljava/lang/String;)Landroidx/core/app/NotificationCompat$BigTextStyle;", *FJavaClassObject::GetJString(BigText));
	return MakeShareable(new AndroidGoodiesNotificationBigTextStyle(JavaObject));
}

TSharedPtr<IAndroidGoodiesNotificationBigPictureStyle> AndroidNotificationManager::CreateBigPictureStyle(UTexture2D* BigPicture)
{
	const TArray<uint8> ByteArray = AGMediaUtils::ByteArrayFromTexture(BigPicture);
	jbyteArray javaArray = AGArrayConvertor::ConvertToJByteArray(ByteArray);

	jobject JavaObject = AGMethodCallUtils::CallStaticObjectMethod(AndroidNotificationManager::NotificationHelperClassName, "getBigPictureStyle",
	                                                               "([BII)Landroidx/core/app/NotificationCompat$BigPictureStyle;", javaArray, BigPicture->GetSizeX(), BigPicture->GetSizeY());
	return MakeShareable(new AndroidGoodiesNotificationBigPictureStyle(JavaObject));
}

TSharedPtr<IAndroidGoodiesNotificationBuilder> AndroidNotificationManager::NewNotificationBuilder(FString ChannelId, TMap<FString, FString> AdditionalData)
{
	TArray<FString> keys;
	TArray<FString> result;

	if (AdditionalData.Num() > 0)
	{
		int count = AdditionalData.GetKeys(keys);

		for (int i = 0; i < count; i++)
		{
			FString key = keys[i];
			result.Add(key);
			result.Add(AdditionalData[key]);
		}
	}

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jobjectArray stringArray = AGArrayConvertor::ConvertToJStringArray(result);

	jobject javaBuilder = AGMethodCallUtils::CallStaticObjectMethod(AndroidNotificationManager::NotificationHelperClassName, "getNotificationBuilder",
	                                                                "(Landroid/app/Activity;Ljava/lang/String;[Ljava/lang/String;)Landroidx/core/app/NotificationCompat$Builder;",
	                                                                FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(ChannelId), stringArray);

	return MakeShareable(new AndroidGoodiesNotificationBuilder(javaBuilder));
}

TSharedPtr<IAndroidGoodiesNotificationChannel> AndroidNotificationManager::NewNotificationChannel(FString ID, FString Name, ChannelImportance Importance)
{
	jobject NativeChannel = AGMethodCallUtils::CallStaticObjectMethod(AndroidNotificationManager::NotificationHelperClassName,
	                                                                  "getNotificationChannel", "(Ljava/lang/String;Ljava/lang/String;I)Landroid/app/NotificationChannel;",
	                                                                  *FJavaClassObject::GetJString(ID), *FJavaClassObject::GetJString(Name), (int)Importance);
	return MakeShareable(new AndroidGoodiesNotificationChannel(NativeChannel));
}

TSharedPtr<IAndroidGoodiesNotificationChannelGroup> AndroidNotificationManager::NewNotificationChannelGroup(FString ID, FString Name)
{
	jobject NativeGroup = AGMethodCallUtils::CallStaticObjectMethod(AndroidNotificationManager::NotificationHelperClassName,
	                                                                "getNotificationChannelGroup", "(Ljava/lang/String;Ljava/lang/String;)Landroid/app/NotificationChannelGroup;",
	                                                                *FJavaClassObject::GetJString(ID), *FJavaClassObject::GetJString(Name));
	return MakeShareable(new AndroidGoodiesNotificationChannelGroup(NativeGroup));
}

void AndroidNotificationManager::Notify(TSharedPtr<IAndroidGoodiesNotification> Notification, int ID)
{
	const auto NativeNotification = StaticCastSharedPtr<AndroidGoodiesNotification>(Notification)->GetNativeNotification();
	AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName,
	                                        "notify", "(Landroid/app/Activity;Landroid/app/Notification;I)V", FJavaWrapper::GameActivityThis, NativeNotification, ID);
}

void AndroidNotificationManager::CreateNotificationChannel(TSharedPtr<IAndroidGoodiesNotificationChannel> Channel)
{
	const auto NativeNotificationChannel = StaticCastSharedPtr<AndroidGoodiesNotificationChannel>(Channel)->GetNativeNotificationChannel();
	AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName,
	                                        "createNotificationChannel", "(Landroid/app/Activity;Landroid/app/NotificationChannel;)V", FJavaWrapper::GameActivityThis,
	                                        NativeNotificationChannel);
}

void AndroidNotificationManager::CreateNotificationChannelGroup(TSharedPtr<IAndroidGoodiesNotificationChannelGroup> Group)
{
	const auto NativeNotificationChannelGroup = StaticCastSharedPtr<AndroidGoodiesNotificationChannelGroup>(Group)->GetNativeChannelGroup();
	AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName,
	                                        "createNotificationChannelGroup", "(Landroid/app/Activity;Landroid/app/NotificationChannelGroup;)V", FJavaWrapper::GameActivityThis,
	                                        NativeNotificationChannelGroup);
}

void AndroidNotificationManager::OpenExactAlarmSettingPage()
{
	AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName, "requestExactAlarmsPermission", "(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis);
}

bool AndroidNotificationManager::CanScheduleExactNotifications()
{
	return AGMethodCallUtils::CallStaticBoolMethod(NotificationHelperClassName, "canScheduleExactAlarms", "(Landroid/app/Activity;)Z", FJavaWrapper::GameActivityThis);
}

bool AndroidNotificationManager::WasApplicationOpenViaNotification()
{
	return AGMethodCallUtils::CallStaticBoolMethod(NotificationHelperClassName, "wasAppOpenViaNotification", "()Z");
}

void AndroidNotificationManager::CancelNotification(int ID)
{
	AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName, "cancelNotification", "(Landroid/app/Activity;I)V", FJavaWrapper::GameActivityThis, ID);
}

void AndroidNotificationManager::CancelAllNotifications()
{
	AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName, "cancelAllNotifications", "(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis);
}

TEnumAsByte<ChannelImportance> AndroidNotificationManager::GetCurrentImportance()
{
	return static_cast<ChannelImportance>(AGMethodCallUtils::CallStaticIntMethod(NotificationHelperClassName, "getCurrentImportance", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis));
}

TEnumAsByte<InterruptionFilter> AndroidNotificationManager::GetCurrentInterruptionFilter()
{
	return static_cast<InterruptionFilter>(AGMethodCallUtils::CallStaticIntMethod(NotificationHelperClassName, "getCurrentInterruptionFilter", "(Landroid/app/Activity;)I",
	                                                                              FJavaWrapper::GameActivityThis));
}

void AndroidNotificationManager::SetCurrentInterruptionFilter(InterruptionFilter Filter)
{
	AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName,
	                                        "setCurrentInterruptionFilter", "(Landroid/app/Activity;I)V", FJavaWrapper::GameActivityThis, (int)Filter);
}

void AndroidNotificationManager::ScheduleNotification(TSharedPtr<IAndroidGoodiesNotification> Notification, int ID, FTimespan NotifyAfter)
{
	long WhenLong = static_cast<long>(FMath::RoundHalfFromZero(NotifyAfter.GetTotalMilliseconds()));
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Schedule Notification: Delayed Time: %d"), WhenLong);

	jlong whenJavaLong = static_cast<jlong>(WhenLong);

	const auto NativeNotification = StaticCastSharedPtr<AndroidGoodiesNotification>(Notification)->GetNativeNotification();
	AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName, "scheduleNotification", "(Landroid/app/Activity;Landroid/app/Notification;IJ)V",
	                                        FJavaWrapper::GameActivityThis, NativeNotification, ID, whenJavaLong);
}

void AndroidNotificationManager::ScheduleRepeatingNotification(TSharedPtr<IAndroidGoodiesNotification> Notification, int ID, FTimespan NotifyAfter, FTimespan RepeatAfter)
{
	long whenLong = static_cast<long>(FMath::RoundHalfFromZero(NotifyAfter.GetTotalMilliseconds()));
	long repeatAfterLong = static_cast<long>(FMath::RoundHalfFromZero(RepeatAfter.GetTotalMilliseconds()));

	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Schedule Notification: Delayed Time: %d milliseconds."), whenLong);
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Schedule Notification: Repear After: %d milliseconds."), repeatAfterLong);

	jlong whenJavaLong = static_cast<jlong>(whenLong);
	jlong repeatAfterJavaLong = static_cast<jlong>(repeatAfterLong);
	const auto NativeNotification = StaticCastSharedPtr<AndroidGoodiesNotification>(Notification)->GetNativeNotification();
	AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName, "scheduleRepeatingNotification", "(Landroid/app/Activity;Landroid/app/Notification;IJJ)V",
	                                        FJavaWrapper::GameActivityThis, NativeNotification, ID, whenJavaLong, repeatAfterJavaLong);
}

void AndroidNotificationManager::CancelScheduledNotification(int ID)
{
	AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName, "cancelScheduledNotification", "(Landroid/app/Activity;I)V",
	                                        FJavaWrapper::GameActivityThis, ID);
}

FString AndroidNotificationManager::GetNotificationDataForKey(FString Key)
{
	return AGMethodCallUtils::CallStaticStringMethod(NotificationHelperClassName, "getNotificationData", "(Ljava/lang/String;)Ljava/lang/String;",
	                                                 *FJavaClassObject::GetJString(Key));
}

TSharedPtr<IAndroidGoodiesNotificationChannel> AndroidNotificationManager::GetNotificationChannel(FString ChannelId)
{
	jobject NativeChannel = AGMethodCallUtils::CallStaticObjectMethod(NotificationHelperClassName, "findNotificationChannel",
	                                                                  "(Landroid/app/Activity;Ljava/lang/String;)Landroid/app/NotificationChannel;",
	                                                                  FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(ChannelId));
	return MakeShareable(new AndroidGoodiesNotificationChannel(NativeChannel));
}

TArray<TSharedPtr<IAndroidGoodiesNotificationChannel>> AndroidNotificationManager::GetNotificationChannels()
{
	TArray<TSharedPtr<IAndroidGoodiesNotificationChannel>> Result;

	jobjectArray javaChannels = static_cast<jobjectArray>(AGMethodCallUtils::CallStaticObjectMethod(NotificationHelperClassName, "getNotificationChannels",
	                                                                                                "(Landroid/app/Activity;)[Landroid/app/NotificationChannel;", FJavaWrapper::GameActivityThis));

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	int length = Env->GetArrayLength(javaChannels);

	for (int i = 0; i < length; i++)
	{
		jobject channel = Env->GetObjectArrayElement(javaChannels, i);
		Result.Add(MakeShareable(new AndroidGoodiesNotificationChannel(channel)));
	}

	return Result;
}

void AndroidNotificationManager::DeleteNotificationChannel(FString ChannelId)
{
	AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName, "deleteNotificationChannel",
	                                        "(Landroid/app/Activity;Ljava/lang/String;)V", FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(ChannelId));
}

TSharedPtr<IAndroidGoodiesNotificationChannelGroup> AndroidNotificationManager::GetNotificationChannelGroup(FString GroupId)
{
	jobject NativeGroup = AGMethodCallUtils::CallStaticObjectMethod(NotificationHelperClassName, "findNotificationChannelGroup",
	                                                                "(Landroid/app/Activity;Ljava/lang/String;)Landroid/app/NotificationChannelGroup;",
	                                                                FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(GroupId));
	return MakeShareable(new AndroidGoodiesNotificationChannelGroup(NativeGroup));
}

TArray<TSharedPtr<IAndroidGoodiesNotificationChannelGroup>> AndroidNotificationManager::GetNotificationChannelGroups()
{
	TArray<TSharedPtr<IAndroidGoodiesNotificationChannelGroup>> Result;

	jobjectArray javaChannelGroups = static_cast<jobjectArray>(AGMethodCallUtils::CallStaticObjectMethod(NotificationHelperClassName, "getNotificationChannelGroups",
	                                                                                                     "(Landroid/app/Activity;)[Landroid/app/NotificationChannelGroup;",
	                                                                                                     FJavaWrapper::GameActivityThis));

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	int length = Env->GetArrayLength(javaChannelGroups);

	for (int i = 0; i < length; i++)
	{
		jobject group = Env->GetObjectArrayElement(javaChannelGroups, i);
		Result.Add(MakeShareable(new AndroidGoodiesNotificationChannelGroup(group)));
	}

	return Result;
}

void AndroidNotificationManager::DeleteNotificationChannelGroup(FString GroupId)
{
	AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName, "deleteNotificationChannelGroup",
	                                        "(Landroid/app/Activity;Ljava/lang/String;)V", FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(GroupId));
}

void AndroidNotificationManager::OpenNotificationChannelSettings(FString ChannelId)
{
	AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName, "openNotificationChannelSettings",
	                                        "(Landroid/app/Activity;Ljava/lang/String;)V", FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(ChannelId));
}
