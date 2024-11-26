#include "AndroidFirebaseUserInfo.h"

#include "AuthLibraryAndroid.h"
#include "Android/AndroidApplication.h"
#include "Android/Utils/FGMethodCallUtils.h"

AndroidFirebaseUserInfo::AndroidFirebaseUserInfo(jobject UserInfo)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	NativeUserInfo = Env->NewGlobalRef(UserInfo);
}

AndroidFirebaseUserInfo::~AndroidFirebaseUserInfo()
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->DeleteGlobalRef(NativeUserInfo);
	NativeUserInfo = nullptr;
}

FString AndroidFirebaseUserInfo::GetUid()
{
	return FGMethodCallUtils::CallStringMethod(NativeUserInfo, "getUid", "()Ljava/lang/String;");
}

FString AndroidFirebaseUserInfo::GetProviderId()
{
	return FGMethodCallUtils::CallStringMethod(NativeUserInfo, "getProviderId", "()Ljava/lang/String;");
}

FString AndroidFirebaseUserInfo::GetDisplayName()
{
	return FGMethodCallUtils::CallStringMethod(NativeUserInfo, "getDisplayName", "()Ljava/lang/String;");
}

FString AndroidFirebaseUserInfo::GetPhotoUrl()
{
	return FGMethodCallUtils::CallStaticStringMethod(AuthLibraryAndroid::FGAuthClassName, "getUserInfoPhotoUrl", "(Lcom/google/firebase/auth/UserInfo;)Ljava/lang/String;", NativeUserInfo);
}

FString AndroidFirebaseUserInfo::GetEmail()
{
	return FGMethodCallUtils::CallStringMethod(NativeUserInfo, "getEmail", "()Ljava/lang/String;");
}

FString AndroidFirebaseUserInfo::GetPhoneNumber()
{
	return FGMethodCallUtils::CallStringMethod(NativeUserInfo, "getPhoneNumber", "()Ljava/lang/String;");
}

bool AndroidFirebaseUserInfo::IsUserInfoValid()
{
	return NativeUserInfo != nullptr;
}
