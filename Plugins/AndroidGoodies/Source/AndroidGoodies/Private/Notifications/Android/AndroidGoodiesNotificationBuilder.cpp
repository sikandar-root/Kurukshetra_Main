#include "AndroidGoodiesNotificationBuilder.h"

#include "Notifications/Android/AndroidGoodiesNotificationBigPictureStyle.h"
#include "Notifications/Android/AndroidGoodiesNotificationInboxStyle.h"
#include "Notifications/Android/AndroidGoodiesNotificationMessageStyle.h"
#include "Notifications/Android/AndroidNotificationManager.h"
#include "Notifications/AGNotificationManager.h"
#include "Notifications/Android/AndroidGoodiesNotification.h"
#include "Notifications/Android/AndroidGoodiesNotificationBigTextStyle.h"
#include "Android/Utils/AGArrayConvertor.h"
#include "Android/Utils/AGMediaUtils.h"
#include "Android/Utils/AGMethodCallUtils.h"

AndroidGoodiesNotificationBuilder::~AndroidGoodiesNotificationBuilder()
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->DeleteLocalRef(NativeBuilder);
	NativeBuilder = nullptr;
}

AndroidGoodiesNotificationBuilder::AndroidGoodiesNotificationBuilder(jobject Builder)
{
	NativeBuilder = Builder;
}

TSharedPtr<IAndroidGoodiesNotification> AndroidGoodiesNotificationBuilder::Build()
{
	jobject JavaNotification = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "build", "()Landroid/app/Notification;");
	return MakeShareable(new AndroidGoodiesNotification(JavaNotification));
}

void AndroidGoodiesNotificationBuilder::SetTitle(FString Title)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setContentTitle", "(Ljava/lang/CharSequence;)Landroidx/core/app/NotificationCompat$Builder;",
	                                                    *FJavaClassObject::GetJString(Title));
}

void AndroidGoodiesNotificationBuilder::SetText(FString Text)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setContentText", "(Ljava/lang/CharSequence;)Landroidx/core/app/NotificationCompat$Builder;",
	                                                    *FJavaClassObject::GetJString(Text));
}

void AndroidGoodiesNotificationBuilder::SetSmallIcon(FString FileName)
{
	int ResourceId = AGMethodCallUtils::CallStaticIntMethod(AndroidNotificationManager::NotificationHelperClassName, "getIconId", "(Landroid/app/Activity;Ljava/lang/String;)I",
	                                                        FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(FileName));

	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Icon ID: %d. This value should NOT be 0."), ResourceId);

	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setSmallIcon", "(I)Landroidx/core/app/NotificationCompat$Builder;", ResourceId);
}

void AndroidGoodiesNotificationBuilder::SetAutoCancel(bool bAutoCancel)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setAutoCancel", "(Z)Landroidx/core/app/NotificationCompat$Builder;", bAutoCancel);
}

void AndroidGoodiesNotificationBuilder::SetBadgeIconType(NotificationBadgeIconType BadgeIconType)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setBadgeIconType", "(I)Landroidx/core/app/NotificationCompat$Builder;", static_cast<int>(BadgeIconType));
}

static FString GetCategoryString(NotificationCategory category)
{
	FString categoryString;
	switch (category)
	{
	case CategoryAlarm:
		categoryString = "alarm";
		break;
	case CategoryCall:
		categoryString = "call";
		break;
	case CategoryEmail:
		categoryString = "email";
		break;
	case CategoryError:
		categoryString = "error";
		break;
	case CategoryEvent:
		categoryString = "event";
		break;
	case CategoryMessage:
		categoryString = "msg";
		break;
	case CategoryNavigation:
		categoryString = "navigation";
		break;
	case CategoryProgress:
		categoryString = "progress";
		break;
	case CategoryPromo:
		categoryString = "promo";
		break;
	case CategoryRecommendation:
		categoryString = "recommendation";
		break;
	case CategoryReminder:
		categoryString = "reminder";
		break;
	case CategoryService:
		categoryString = "service";
		break;
	case CategorySocial:
		categoryString = "social";
		break;
	case CategoryStatus:
		categoryString = "status";
		break;
	case CategorySystem:
		categoryString = "system";
		break;
	case CategoryTransport:
		categoryString = "transport";
		break;
	default:
		break;
	}

	return categoryString;
}

void AndroidGoodiesNotificationBuilder::SetCategory(NotificationCategory Category)
{
	const FString CategoryString = GetCategoryString(Category);

	if (CategoryString.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("ANDROIDGOODIES => UAGNotificationBuilder::SetCategory() - Category is wrong."));
	}
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setCategory", "(Ljava/lang/String;)Landroidx/core/app/NotificationCompat$Builder;",
	                                                    *FJavaClassObject::GetJString(CategoryString));
}

void AndroidGoodiesNotificationBuilder::SetColor(FColor Color)
{
	NativeBuilder = AGMethodCallUtils::CallStaticObjectMethod(AndroidNotificationManager::NotificationHelperClassName, "setNotificationColor",
	                                                          "(Landroidx/core/app/NotificationCompat$Builder;I)Landroidx/core/app/NotificationCompat$Builder;",
	                                                          NativeBuilder, Color.ToPackedARGB());
}

void AndroidGoodiesNotificationBuilder::SetColorized(bool bColorized)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setColorized", "(Z)Landroidx/core/app/NotificationCompat$Builder;", bColorized);
}

void AndroidGoodiesNotificationBuilder::SetContentInfo(FString Text)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setContentInfo", "(Ljava/lang/CharSequence;)Landroidx/core/app/NotificationCompat$Builder;",
	                                                    *FJavaClassObject::GetJString(Text));
}

void AndroidGoodiesNotificationBuilder::SetDefaults(FAGNotificationDefaults Defaults)
{
	int FlagsInt = 0;
	if (Defaults.Lights)
	{
		FlagsInt = FlagsInt | 4;
	}
	if (Defaults.Sound)
	{
		FlagsInt = FlagsInt | 1;
	}
	if (Defaults.Vibrate)
	{
		FlagsInt = FlagsInt | 2;
	}
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setDefaults", "(I)Landroidx/core/app/NotificationCompat$Builder;", FlagsInt);
}

void AndroidGoodiesNotificationBuilder::SetGroup(FString GroupKey)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setGroup", "(Ljava/lang/String;)Landroidx/core/app/NotificationCompat$Builder;",
	                                                    *FJavaClassObject::GetJString(GroupKey));
}

void AndroidGoodiesNotificationBuilder::SetGroupAlertBehaviour(NotificationGroupAlert Behaviour)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setGroupAlertBehavior", "(I)Landroidx/core/app/NotificationCompat$Builder;", Behaviour);
}

void AndroidGoodiesNotificationBuilder::SetGroupSummary(bool bSummary)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setGroupSummary", "(Z)Landroidx/core/app/NotificationCompat$Builder;", bSummary);
}

void AndroidGoodiesNotificationBuilder::SetLargeIcon(UTexture2D* Icon)
{
	const TArray<uint8> ByteArray = AGMediaUtils::ByteArrayFromTexture(Icon);
	jbyteArray JavaArray = AGArrayConvertor::ConvertToJByteArray(ByteArray);

	NativeBuilder = AGMethodCallUtils::CallStaticObjectMethod(AndroidNotificationManager::NotificationHelperClassName, "setNotificationLargeIcon",
	                                                          "(Landroidx/core/app/NotificationCompat$Builder;[BII)Landroidx/core/app/NotificationCompat$Builder;",
	                                                          NativeBuilder, JavaArray, Icon->GetSizeX(), Icon->GetSizeY());
}

void AndroidGoodiesNotificationBuilder::SetLights(FColor Color, int InMilliSeconds, int OutMilliSeconds)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setLights", "(III)Landroidx/core/app/NotificationCompat$Builder;", Color.ToPackedARGB(), InMilliSeconds, OutMilliSeconds);
}

void AndroidGoodiesNotificationBuilder::SetLocalOnly(bool bLocalOnly)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setLocalOnly", "(Z)Landroidx/core/app/NotificationCompat$Builder;", bLocalOnly);
}

void AndroidGoodiesNotificationBuilder::SetNumber(int Number)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setNumber", "(I)Landroidx/core/app/NotificationCompat$Builder;", Number);
}

void AndroidGoodiesNotificationBuilder::SetOngoing(bool bOngoing)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setOngoing", "(Z)Landroidx/core/app/NotificationCompat$Builder;", bOngoing);
}

void AndroidGoodiesNotificationBuilder::SetAlertOnce(bool bAlertOnce)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setOnlyAlertOnce", "(Z)Landroidx/core/app/NotificationCompat$Builder;", bAlertOnce);
}

void AndroidGoodiesNotificationBuilder::SetPriority(NotificationPriority Priority)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setPriority", "(I)Landroidx/core/app/NotificationCompat$Builder;", static_cast<int>(Priority));
}

void AndroidGoodiesNotificationBuilder::SetProgress(int Current, int Max, bool bIndeterminate)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setProgress", "(IIZ)Landroidx/core/app/NotificationCompat$Builder;", Max, Current, bIndeterminate);
}

void AndroidGoodiesNotificationBuilder::SetPublicVersion(TSharedPtr<IAndroidGoodiesNotification> Notification)
{
	const auto NativeNotification = StaticCastSharedPtr<AndroidGoodiesNotification>(Notification)->GetNativeNotification();
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setPublicVersion", "(Landroid/app/Notification;)Landroidx/core/app/NotificationCompat$Builder;",
	                                                    NativeNotification);
}

void AndroidGoodiesNotificationBuilder::SetShortcutId(FString ID)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setShortcutId", "(Ljava/lang/String;)Landroidx/core/app/NotificationCompat$Builder;",
	                                                    *FJavaClassObject::GetJString(ID));
}

void AndroidGoodiesNotificationBuilder::SetShowWhen(bool bShowWhen)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setShowWhen", "(Z)Landroidx/core/app/NotificationCompat$Builder;", bShowWhen);
}

void AndroidGoodiesNotificationBuilder::SetSortKey(FString Key)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setSortKey", "(Ljava/lang/String;)Landroidx/core/app/NotificationCompat$Builder;",
	                                                    *FJavaClassObject::GetJString(Key));
}

void AndroidGoodiesNotificationBuilder::SetSound(FString Path)
{
	NativeBuilder = AGMethodCallUtils::CallStaticObjectMethod(AndroidNotificationManager::NotificationHelperClassName, "setNotificationSound",
	                                                          "(Landroidx/core/app/NotificationCompat$Builder;Ljava/lang/String;)Landroidx/core/app/NotificationCompat$Builder;",
	                                                          NativeBuilder, *FJavaClassObject::GetJString(Path));
}

void AndroidGoodiesNotificationBuilder::SetSubText(FString Text)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setSubText", "(Ljava/lang/CharSequence;)Landroidx/core/app/NotificationCompat$Builder;",
	                                                    *FJavaClassObject::GetJString(Text));
}

void AndroidGoodiesNotificationBuilder::SetTicker(FString Text)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setTicker", "(Ljava/lang/CharSequence;)Landroidx/core/app/NotificationCompat$Builder;",
	                                                    *FJavaClassObject::GetJString(Text));
}

void AndroidGoodiesNotificationBuilder::SetTimeoutAfter(int MilliSeconds)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setTimeoutAfter", "(J)Landroidx/core/app/NotificationCompat$Builder;",
	                                                    static_cast<jlong>(static_cast<long>(MilliSeconds)));
}

void AndroidGoodiesNotificationBuilder::SetUsesChronometer(bool bUsesChronometer)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setUsesChronometer", "(Z)Landroidx/core/app/NotificationCompat$Builder;", bUsesChronometer);
}

void AndroidGoodiesNotificationBuilder::SetVibrate(TArray<float> Pattern)
{
	TArray<long> LongArray;
	for (int i = 0; i < Pattern.Num(); i++)
	{
		LongArray.Add(static_cast<long>(FMath::RoundHalfFromZero(Pattern[i] * 1000)));
	}
	jlongArray jLongArray = AGArrayConvertor::ConvertToJLongArray(LongArray);
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setVibrate", "([J)Landroidx/core/app/NotificationCompat$Builder;", jLongArray);
}

void AndroidGoodiesNotificationBuilder::SetVisibility(NotificationVisibility Visibility)
{
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setVisibility", "(I)Landroidx/core/app/NotificationCompat$Builder;", static_cast<int>(Visibility));
}

void AndroidGoodiesNotificationBuilder::SetWhen(FDateTime DateTime)
{
	auto DateLong = DateTime.ToUnixTimestamp() * 1000;
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setWhen", "(J)Landroidx/core/app/NotificationCompat$Builder;",
	                                                    static_cast<jlong>(DateLong));
}

void AndroidGoodiesNotificationBuilder::SetBigTextStyle(TSharedPtr<IAndroidGoodiesNotificationBigTextStyle> Style)
{
	const auto NativeStyle = StaticCastSharedPtr<AndroidGoodiesNotificationBigTextStyle>(Style)->GetNativeStyle();
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setStyle", "(Landroidx/core/app/NotificationCompat$Style;)Landroidx/core/app/NotificationCompat$Builder;",
	                                                    NativeStyle);
}

void AndroidGoodiesNotificationBuilder::SetMessagingStyle(TSharedPtr<IAndroidGoodiesNotificationMessageStyle> Style)
{
	const auto NativeStyle = StaticCastSharedPtr<AndroidGoodiesNotificationMessageStyle>(Style)->GetNativeStyle();
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setStyle", "(Landroidx/core/app/NotificationCompat$Style;)Landroidx/core/app/NotificationCompat$Builder;",
	                                                    NativeStyle);
}

void AndroidGoodiesNotificationBuilder::SetBigPictureStyle(TSharedPtr<IAndroidGoodiesNotificationBigPictureStyle> Style)
{
	const auto NativeStyle = StaticCastSharedPtr<AndroidGoodiesNotificationBigPictureStyle>(Style)->GetNativeStyle();
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setStyle", "(Landroidx/core/app/NotificationCompat$Style;)Landroidx/core/app/NotificationCompat$Builder;",
	                                                    NativeStyle);
}

void AndroidGoodiesNotificationBuilder::SetInboxStyle(TSharedPtr<IAndroidGoodiesNotificationInboxStyle> Style)
{
	const auto NativeStyle = StaticCastSharedPtr<AndroidGoodiesNotificationInboxStyle>(Style)->GetNativeStyle();
	NativeBuilder = AGMethodCallUtils::CallObjectMethod(NativeBuilder, "setStyle", "(Landroidx/core/app/NotificationCompat$Style;)Landroidx/core/app/NotificationCompat$Builder;",
	                                                    NativeStyle);
}

void AndroidGoodiesNotificationBuilder::AddOpenUrlAction(FString IconName, FString Title, FString URL)
{
	NativeBuilder = AGMethodCallUtils::CallStaticObjectMethod(AndroidNotificationManager::NotificationHelperClassName, "addOpenUrlAction",
	                                                          "(Landroid/app/Activity;Landroidx/core/app/NotificationCompat$Builder;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Landroidx/core/app/NotificationCompat$Builder;",
	                                                          FJavaWrapper::GameActivityThis, NativeBuilder, *FJavaClassObject::GetJString(IconName), *FJavaClassObject::GetJString(Title),
	                                                          *FJavaClassObject::GetJString(URL));
}
