#include "AndroidFirebaseAuthCredentials.h"
#include "Android/AndroidApplication.h"
#include "Android/Utils/FGMethodCallUtils.h"

AndroidFirebaseAuthCredentials::~AndroidFirebaseAuthCredentials()
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->DeleteGlobalRef(NativeCredentials);
	NativeCredentials = nullptr;
}

AndroidFirebaseAuthCredentials::AndroidFirebaseAuthCredentials(jobject Credentials)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	NativeCredentials = Env->NewGlobalRef(Credentials);
}

FString AndroidFirebaseAuthCredentials::GetProvider()
{
	return FGMethodCallUtils::CallStringMethod(NativeCredentials, "getProvider", "()Ljava/lang/String;");
}

bool AndroidFirebaseAuthCredentials::AreValid()
{
	return NativeCredentials != nullptr;
}

jobject AndroidFirebaseAuthCredentials::GetNativeCredentials()
{
	return NativeCredentials;
}
