#include "AndroidFirebaseUser.h"

#include "Auth/FGGetTokenResult.h"

#include "AndroidFirebaseAuthCredentials.h"
#include "AndroidFirebaseUserInfo.h"
#include "AuthLibraryAndroid.h"
#include "AndroidGetTokenResult.h"
#include "Android/Utils/FGFirebaseAndroidScopedObject.h"

#include "Android/AndroidApplication.h"
#include "Android/Utils/FGMethodCallUtils.h"
#include "Android/AndroidJava.h"
#include "Android/AndroidJavaEnv.h"
#include "Android/AndroidPlatform.h"
#include "Android/Utils/FGJavaConvertor.h"
#include "Async/Async.h"

AndroidFirebaseUser::AndroidFirebaseUser(jobject User)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	NativeUser = Env->NewGlobalRef(User);
}

AndroidFirebaseUser::~AndroidFirebaseUser()
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->DeleteGlobalRef(NativeUser);
	NativeUser = nullptr;
}

bool AndroidFirebaseUser::IsAnonymous()
{
	return FGMethodCallUtils::CallBoolMethod(NativeUser, "isAnonymous", "()Z");
}

bool AndroidFirebaseUser::IsUserValid()
{
	return NativeUser != nullptr;
}

void AndroidFirebaseUser::Delete(const FOnUserVoidTaskCompleted& OnSuccess, const FOnUserOperationError& OnError)
{
	FGMethodCallUtils::CallStaticVoidMethod(AuthLibraryAndroid::FGAuthClassName, "deleteUser", "(Lcom/google/firebase/auth/FirebaseUser;)V", NativeUser);
}

void AndroidFirebaseUser::LinkWithCredentials(UFGAuthCredentials* Credentials, const FOnUserUpdated& OnSuccess, const FOnUserOperationError& OnError)
{
	const auto AndroidCredentials = StaticCastSharedPtr<AndroidFirebaseAuthCredentials>(Credentials->GetCredentials())->GetNativeCredentials();
	FGMethodCallUtils::CallStaticVoidMethod(AuthLibraryAndroid::FGAuthClassName, "linkUserWithCredential",
	                                        "(Lcom/google/firebase/auth/FirebaseUser;Lcom/google/firebase/auth/AuthCredential;)V",
	                                        NativeUser, AndroidCredentials);
}

void AndroidFirebaseUser::Reauthenticate(UFGAuthCredentials* Credentials, const FOnUserVoidTaskCompleted& OnSuccess, const FOnUserOperationError& OnError)
{
	const auto AndroidCredentials = StaticCastSharedPtr<AndroidFirebaseAuthCredentials>(Credentials->GetCredentials())->GetNativeCredentials();
	FGMethodCallUtils::CallStaticVoidMethod(AuthLibraryAndroid::FGAuthClassName, "reauthenticateUser",
	                                        "(Lcom/google/firebase/auth/FirebaseUser;Lcom/google/firebase/auth/AuthCredential;)V",
	                                        NativeUser, AndroidCredentials);
}

void AndroidFirebaseUser::Reload(const FOnUserVoidTaskCompleted& OnSuccess, const FOnUserOperationError& OnError)
{
	FGMethodCallUtils::CallStaticVoidMethod(AuthLibraryAndroid::FGAuthClassName, "reloadUser", "(Lcom/google/firebase/auth/FirebaseUser;)V", NativeUser);
}

void AndroidFirebaseUser::SendEmailVerification(const FOnUserVoidTaskCompleted& OnSuccess, const FOnUserOperationError& OnError)
{
	FGMethodCallUtils::CallStaticVoidMethod(AuthLibraryAndroid::FGAuthClassName, "sendEmailVerificationForUser", "(Lcom/google/firebase/auth/FirebaseUser;)V", NativeUser);
}

void AndroidFirebaseUser::UnlinkProvider(const FString& Provider, const FOnUserUpdated& OnSuccess, const FOnUserOperationError& OnError)
{
	FGMethodCallUtils::CallStaticVoidMethod(AuthLibraryAndroid::FGAuthClassName, "unlinkProviderForUser",
	                                        "(Lcom/google/firebase/auth/FirebaseUser;Ljava/lang/String;)V", NativeUser, *FJavaClassObject::GetJString(Provider));
}

void AndroidFirebaseUser::UpdateEmail(const FString& Email, const FOnUserVoidTaskCompleted& OnSuccess, const FOnUserOperationError& OnError)
{
	FGMethodCallUtils::CallStaticVoidMethod(AuthLibraryAndroid::FGAuthClassName, "updateEmailForUser",
	                                        "(Lcom/google/firebase/auth/FirebaseUser;Ljava/lang/String;)V", NativeUser, *FJavaClassObject::GetJString(Email));
}

void AndroidFirebaseUser::UpdatePassword(const FString& Password, const FOnUserVoidTaskCompleted& OnSuccess, const FOnUserOperationError& OnError)
{
	FGMethodCallUtils::CallStaticVoidMethod(AuthLibraryAndroid::FGAuthClassName, "updatePasswordForUser",
	                                        "(Lcom/google/firebase/auth/FirebaseUser;Ljava/lang/String;)V", NativeUser, *FJavaClassObject::GetJString(Password));
}

void AndroidFirebaseUser::UpdatePhoneNumber(UFGAuthCredentials* Credentials, const FOnUserVoidTaskCompleted& OnSuccess, const FOnUserOperationError& OnError)
{
	const auto AndroidCredentials = StaticCastSharedPtr<AndroidFirebaseAuthCredentials>(Credentials->GetCredentials())->GetNativeCredentials();
	FGMethodCallUtils::CallStaticVoidMethod(AuthLibraryAndroid::FGAuthClassName, "updatePhoneNumberForUser",
	                                        "(Lcom/google/firebase/auth/FirebaseUser;Lcom/google/firebase/auth/AuthCredential;)V",
	                                        NativeUser, AndroidCredentials);
}

void AndroidFirebaseUser::UpdateProfile(const FString& displayName, const FString& avatarUrl, const FOnUserVoidTaskCompleted& OnSuccess, const FOnUserOperationError& OnError)
{
	FGMethodCallUtils::CallStaticVoidMethod(AuthLibraryAndroid::FGAuthClassName, "updateProfileForUser",
	                                        "(Lcom/google/firebase/auth/FirebaseUser;Ljava/lang/String;Ljava/lang/String;)V",
	                                        NativeUser, *FJavaClassObject::GetJString(displayName), *FJavaClassObject::GetJString(avatarUrl));
}

void AndroidFirebaseUser::GetToken(bool ForceRefresh, const FOnUserStringTaskCompleted& OnSuccess, const FOnUserOperationError& OnError)
{
	FGMethodCallUtils::CallStaticVoidMethod(AuthLibraryAndroid::FGAuthClassName, "getUserToken",
	                                        "(Lcom/google/firebase/auth/FirebaseUser;Z)V", NativeUser, ForceRefresh);
}

TArray<TSharedPtr<IFirebaseUserInfo>> AndroidFirebaseUser::GetProviderData()
{
	TArray<TSharedPtr<IFirebaseUserInfo>> Result;

	jobject javaArrayList = FGMethodCallUtils::CallStaticObjectMethod(AuthLibraryAndroid::FGAuthClassName, "getUserProviderData",
	                                                                  "(Lcom/google/firebase/auth/FirebaseUser;)Ljava/util/ArrayList;",
	                                                                  NativeUser);

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass ArrayListClass = FJavaWrapper::FindClass(Env, "java/util/ArrayList", false);
	jmethodID SizeMethod = FJavaWrapper::FindMethod(Env, ArrayListClass, "size", "()I", false);
	jmethodID GetMethod = FJavaWrapper::FindMethod(Env, ArrayListClass, "get", "(I)Ljava/lang/Object;", false);

	const int Size = Env->CallIntMethod(javaArrayList, SizeMethod);

	for (int i = 0; i < Size; i++)
	{
		jobject Item = Env->CallObjectMethod(javaArrayList, GetMethod, i);
		Result.Add(MakeShareable(new AndroidFirebaseUserInfo(Item)));
	}

	return Result;
}

void AndroidFirebaseUser::GetIdToken(bool ForceRefresh, const FOnGetTokenResultCompleted& OnSuccess, const FOnUserOperationError& OnError)
{
	FGMethodCallUtils::CallStaticVoidMethod(AuthLibraryAndroid::FGAuthClassName, "getUserIdToken",
											"(Lcom/google/firebase/auth/FirebaseUser;Z)V", NativeUser, ForceRefresh);
}

FString AndroidFirebaseUser::GetUid()
{
	return FGMethodCallUtils::CallStringMethod(NativeUser, "getUid", "()Ljava/lang/String;");
}

FString AndroidFirebaseUser::GetProviderId()
{
	return FGMethodCallUtils::CallStringMethod(NativeUser, "getProviderId", "()Ljava/lang/String;");
}

FString AndroidFirebaseUser::GetDisplayName()
{
	return FGMethodCallUtils::CallStringMethod(NativeUser, "getDisplayName", "()Ljava/lang/String;");
}

FString AndroidFirebaseUser::GetPhotoUrl()
{
	return FGMethodCallUtils::CallStaticStringMethod(AuthLibraryAndroid::FGAuthClassName, "getUserInfoPhotoUrl", "(Lcom/google/firebase/auth/UserInfo;)Ljava/lang/String;", NativeUser);
}

FString AndroidFirebaseUser::GetEmail()
{
	return FGMethodCallUtils::CallStringMethod(NativeUser, "getEmail", "()Ljava/lang/String;");
}

FString AndroidFirebaseUser::GetPhoneNumber()
{
	return FGMethodCallUtils::CallStringMethod(NativeUser, "getPhoneNumber", "()Ljava/lang/String;");
}

bool AndroidFirebaseUser::IsEmailVerified()
{
	return FGMethodCallUtils::CallBoolMethod(NativeUser, "isEmailVerified", "()Z");
}

bool AndroidFirebaseUser::IsUserInfoValid()
{
	return NativeUser != nullptr;
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGAuth_OnUserVoidTaskCompleted(JNIEnv* env, jclass clazz, jstring uid)
{
	const FString Result = FJavaHelper::FStringFromParam(env, uid);

	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UFGFirebaseUser::OnUserVoidTaskCompletedCallback.ExecuteIfBound(Result);
	});
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGAuth_OnUserStringTaskCompleted(JNIEnv* env, jclass clazz, jstring uid, jstring result)
{
	const FString UserId = FJavaHelper::FStringFromParam(env, uid);
	const FString Result = FJavaHelper::FStringFromParam(env, result);

	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UFGFirebaseUser::OnUserStringTaskCompletedCallback.ExecuteIfBound(UserId, Result);
	});
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGAuth_OnUserUpdated(JNIEnv* env, jclass clazz, jobject user)
{
	const auto User = MakeShareable(new AndroidFirebaseUser(user));

	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UFGFirebaseUser* UserObject = NewObject<UFGFirebaseUser>();
		UserObject->Init(User);
		UFGFirebaseUser::OnUserUpdatedCallback.ExecuteIfBound(UserObject);
	});
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGAuth_OnUserOperationError(JNIEnv* env, jclass clazz, jstring uid, jstring error)
{
	const FString UIDString = FJavaHelper::FStringFromParam(env, uid);
	const FString ErrorString = FJavaHelper::FStringFromParam(env, error);

	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UFGFirebaseUser::OnUserOperationErrorCallback.ExecuteIfBound(UIDString, ErrorString);
	});
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGAuth_OnUserTokenResultCompleted(JNIEnv* env, jclass clazz, jstring uid, jobject getTokenResult)
{
	const FString UIDString = FJavaHelper::FStringFromParam(env, uid);
	auto GetTokenResultAndroid = MakeShareable(new AndroidGetTokenResult(*NewGlobalJavaObject(getTokenResult)));
	
	AsyncTask(ENamedThreads::GameThread, [UIDString, GetTokenResultAndroid]()
	{
		UFGGetTokenResult* GetTokenResult = NewObject<UFGGetTokenResult>();
		GetTokenResult->Init(GetTokenResultAndroid);
		UFGFirebaseUser::OnGetTokenResultCompletedCallback.ExecuteIfBound(UIDString, GetTokenResult);
	});
}
