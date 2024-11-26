#include "AndroidGetTokenResult.h"

#include "AuthLibraryAndroid.h"
#include "Android/AndroidApplication.h"
#include "Android/Utils/FGMethodCallUtils.h"
#include "Android/AndroidJava.h"
#include "Android/AndroidJavaEnv.h"
#include "Android/AndroidPlatform.h"
#include "Android/Utils/FGJavaConvertor.h"
#include "Android/Utils/FGValueVariantUtils.h"

AndroidGetTokenResult::AndroidGetTokenResult(jobject TokenResult)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	NativeTokenResult = Env->NewGlobalRef(TokenResult);
}

AndroidGetTokenResult::~AndroidGetTokenResult()
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->DeleteGlobalRef(NativeTokenResult);
	NativeTokenResult = nullptr;
}

bool AndroidGetTokenResult::IsTokenResultValid()
{
	return NativeTokenResult != nullptr;
}

FString AndroidGetTokenResult::GetSignInProvider()
{
	return FGMethodCallUtils::CallStringMethod(NativeTokenResult, "getSignInProvider", "()Ljava/lang/String;");
}

FString AndroidGetTokenResult::GetToken()
{
	return FGMethodCallUtils::CallStringMethod(NativeTokenResult, "getToken", "()Ljava/lang/String;");
}

FDateTime AndroidGetTokenResult::GetAuthTimestamp()
{
	long Timestamp = FGMethodCallUtils::CallLongMethod(NativeTokenResult, "getAuthTimestamp", "()J");
	return FDateTime::FromUnixTimestamp(Timestamp / 1000);
}

FDateTime AndroidGetTokenResult::GetExpirationTimestamp()
{
	long Timestamp = FGMethodCallUtils::CallLongMethod(NativeTokenResult, "getExpirationTimestamp", "()J");
	return FDateTime::FromUnixTimestamp(Timestamp / 1000);
}

FDateTime AndroidGetTokenResult::GetIssuedAtTimestamp()
{
	long Timestamp = FGMethodCallUtils::CallLongMethod(NativeTokenResult, "getIssuedAtTimestamp", "()J");
	return FDateTime::FromUnixTimestamp(Timestamp / 1000);
}

TMap<FString, FFGValueVariant> AndroidGetTokenResult::GetClaims()
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	
	jobject Claims = FGMethodCallUtils::CallObjectMethod(NativeTokenResult, "getClaims", "()Ljava/util/Map;");
	return ValueVariantUtils::JavaMapToVariantMap(Env, Claims);
}
