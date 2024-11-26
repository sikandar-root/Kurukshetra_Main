#include "AndroidGoodiesNotificationChannel.h"

#include "Notifications/Android/AndroidNotificationManager.h"
#include "Notifications/AGNotificationManager.h"
#include "Android/AndroidApplication.h"
#include "Android/Utils/AGArrayConvertor.h"
#include "Android/Utils/AGMethodCallUtils.h"

AndroidGoodiesNotificationChannel::~AndroidGoodiesNotificationChannel()
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->DeleteLocalRef(NativeNotificationChannel);
	NativeNotificationChannel = nullptr;
}

AndroidGoodiesNotificationChannel::AndroidGoodiesNotificationChannel(jobject Channel)
{
	NativeNotificationChannel = Channel;
}

jobject AndroidGoodiesNotificationChannel::GetNativeNotificationChannel()
{
	return NativeNotificationChannel;
}

FString AndroidGoodiesNotificationChannel::GetId()
{
	return AGMethodCallUtils::CallStringMethod(NativeNotificationChannel, "getId", "()Ljava/lang/String;");
}

void AndroidGoodiesNotificationChannel::SetBypassDnd(bool Bypass)
{
	AGMethodCallUtils::CallVoidMethod(NativeNotificationChannel, "setBypassDnd", "(Z)V", Bypass);
}

bool AndroidGoodiesNotificationChannel::CanBypassDnd()
{
	return AGMethodCallUtils::CallBoolMethod(NativeNotificationChannel, "canBypassDnd", "()Z");
}

void AndroidGoodiesNotificationChannel::SetShowBadge(bool Show)
{
	AGMethodCallUtils::CallVoidMethod(NativeNotificationChannel, "setShowBadge", "(Z)V", Show);
}

bool AndroidGoodiesNotificationChannel::CanShowBadge()
{
	return AGMethodCallUtils::CallBoolMethod(NativeNotificationChannel, "canShowBadge", "()Z");
}

void AndroidGoodiesNotificationChannel::SetEnableLights(bool Enable)
{
	AGMethodCallUtils::CallVoidMethod(NativeNotificationChannel, "enableLights", "(Z)V", Enable);
}

bool AndroidGoodiesNotificationChannel::ShouldShowLights()
{
	return AGMethodCallUtils::CallBoolMethod(NativeNotificationChannel, "shouldShowLights", "()Z");
}

void AndroidGoodiesNotificationChannel::SetEnableVibration(bool Enable)
{
	AGMethodCallUtils::CallVoidMethod(NativeNotificationChannel, "enableVibration", "(Z)V", Enable);
}

bool AndroidGoodiesNotificationChannel::ShouldVibrate()
{
	return AGMethodCallUtils::CallBoolMethod(NativeNotificationChannel, "shouldVibrate", "()Z");
}

FAGAudioAttributes AndroidGoodiesNotificationChannel::GetAudioAttributes()
{
	FAGAudioAttributes Attributes;
	FAGAudioAttributesFlags Flags;

	jobject javaAttributes = AGMethodCallUtils::CallObjectMethod(NativeNotificationChannel, "getAudioAttributes", "()Landroid/media/AudioAttributes;");

	Attributes.ContentType = static_cast<AudioAttributesContentType>(AGMethodCallUtils::CallIntMethod(javaAttributes, "getContentType", "()I"));
	Attributes.Usage = static_cast<AudioAttributesUsage>(AGMethodCallUtils::CallIntMethod(javaAttributes, "getUsage", "()I"));

	int FlagsInt = AGMethodCallUtils::CallIntMethod(javaAttributes, "getFlags", "()I");
	Flags.AudibilityEnforced = (FlagsInt & 1 << 0) >> 0 == 1;
	Flags.HwAvSync = (FlagsInt & 1 << 4) >> 4 == 1;
	Flags.LowLatency = (FlagsInt & 1 << 8) >> 8 == 1;
	Attributes.Flags = Flags;

	return Attributes;
}

void AndroidGoodiesNotificationChannel::SetDescription(FString Description)
{
	AGMethodCallUtils::CallVoidMethod(NativeNotificationChannel, "setDescription", "(Ljava/lang/String;)V", *FJavaClassObject::GetJString(Description));
}

FString AndroidGoodiesNotificationChannel::GetDescription()
{
	return AGMethodCallUtils::CallStringMethod(NativeNotificationChannel, "getDescription", "()Ljava/lang/String;");
}

void AndroidGoodiesNotificationChannel::SetImportance(ChannelImportance Importance)
{
	AGMethodCallUtils::CallVoidMethod(NativeNotificationChannel, "setImportance", "(I)V", static_cast<int>(Importance));
}

ChannelImportance AndroidGoodiesNotificationChannel::GetImportance()
{
	return static_cast<ChannelImportance>(AGMethodCallUtils::CallIntMethod(NativeNotificationChannel, "getImportance", "()I"));
}

void AndroidGoodiesNotificationChannel::SetLightColor(FColor Color)
{
	AGMethodCallUtils::CallVoidMethod(NativeNotificationChannel, "setLightColor", "(I)V", Color.ToPackedARGB());
}

FColor AndroidGoodiesNotificationChannel::GetLightColor()
{
	const int ColorInt = AGMethodCallUtils::CallIntMethod(NativeNotificationChannel, "getLightColor", "()I");
	return FColor(ColorInt);
}

void AndroidGoodiesNotificationChannel::SetLockScreenVisibility(NotificationVisibility Visibility)
{
	AGMethodCallUtils::CallVoidMethod(NativeNotificationChannel, "setLockscreenVisibility", "(I)V", static_cast<int>(Visibility));
}

NotificationVisibility AndroidGoodiesNotificationChannel::GetLockScreenVisibility()
{
	return static_cast<NotificationVisibility>(AGMethodCallUtils::CallIntMethod(NativeNotificationChannel, "getLockscreenVisibility", "()I"));
}

FString AndroidGoodiesNotificationChannel::GetName()
{
	return AGMethodCallUtils::CallStringMethod(NativeNotificationChannel, "getName", "()Ljava/lang/CharSequence;");
}

FString AndroidGoodiesNotificationChannel::GetSoundPath()
{
	jobject soundUri = AGMethodCallUtils::CallObjectMethod(NativeNotificationChannel, "getSound", "()Landroid/net/Uri;");
	return AGMethodCallUtils::CallStringMethod(soundUri, "getPath", "()Ljava/lang/String;");
}

void AndroidGoodiesNotificationChannel::SetVibrationPattern(TArray<float> Pattern)
{
	TArray<long> LongArray;
	for (int i = 0; i < Pattern.Num(); i++)
	{
		LongArray.Add(static_cast<long>(FMath::RoundHalfFromZero(Pattern[i] * 1000)));
	}

	jlongArray jLongArray = AGArrayConvertor::ConvertToJLongArray(LongArray);
	AGMethodCallUtils::CallVoidMethod(NativeNotificationChannel, "setVibrationPattern", "([J)V", jLongArray);
}

TArray<float> AndroidGoodiesNotificationChannel::GetVibrationPattern()
{
	TArray<float> Result;

	jlongArray JavaArray = static_cast<jlongArray>(AGMethodCallUtils::CallObjectMethod(NativeNotificationChannel, "getVibrationPattern", "()[J"));
	TArray<long> LongArray = AGArrayConvertor::ConvertToLongArray(JavaArray);

	for (int i = 0; i < LongArray.Num(); i++)
	{
		Result.Add(static_cast<float>(LongArray[i]) / 1000);
	}

	return Result;
}

void AndroidGoodiesNotificationChannel::SetSound(FString FilePath, FAGAudioAttributes Attributes)
{
	int FlagsInt = 0;
	if (Attributes.Flags.AudibilityEnforced)
	{
		FlagsInt = FlagsInt | 1;
	}
	if (Attributes.Flags.HwAvSync)
	{
		FlagsInt = FlagsInt | 16;
	}
	if (Attributes.Flags.LowLatency)
	{
		FlagsInt = FlagsInt | 256;
	}

	AGMethodCallUtils::CallStaticVoidMethod(AndroidNotificationManager::NotificationHelperClassName,
	                                        "setChannelSound", "(Landroid/app/NotificationChannel;Ljava/lang/String;III)V",
	                                        NativeNotificationChannel, *FJavaClassObject::GetJString(FilePath), static_cast<int>(Attributes.ContentType), static_cast<int>(Attributes.Usage),
	                                        FlagsInt);
}

FString AndroidGoodiesNotificationChannel::GetGroupId()
{
	return AGMethodCallUtils::CallStringMethod(NativeNotificationChannel, "getGroup", "()Ljava/lang/String;");
}

void AndroidGoodiesNotificationChannel::SetGroup(FString GroupId)
{
	AGMethodCallUtils::CallVoidMethod(NativeNotificationChannel, "setGroup", "(Ljava/lang/String;)V", *FJavaClassObject::GetJString(GroupId));
}
