#include "AuthLibraryAndroid.h"

#include "Async/Async.h"
#include "AndroidFirebaseAuthCredentials.h"
#include "AndroidFirebaseUser.h"
#include "FirebaseGoodies.h"
#include "FirebaseGoodiesSettings.h"
#include "Android/AndroidPlatform.h"
#include "Android/AndroidJNI.h"
#include "Android/Utils/FGJavaConvertor.h"
#include "Android/Utils/FGMethodCallUtils.h"
#include "FirebaseGoodiesLog.h"
#include "Android/AndroidJavaEnv.h"

AuthLibraryAndroid::~AuthLibraryAndroid()
{
}

void AuthLibraryAndroid::InitListeners(const FAuthVoidDelegate& IdTokenChangedDelegate, const FAuthVoidDelegate& AuthStateChangedDelegate)
{
	FGMethodCallUtils::CallStaticVoidMethod(FGAuthClassName, "initListeners", "()V");
}

TSharedPtr<IFirebaseUser> AuthLibraryAndroid::CurrentUser()
{
	jobject JavaUser = FGMethodCallUtils::CallStaticObjectMethod(FGAuthClassName, "currentUser", "()Lcom/google/firebase/auth/FirebaseUser;");
	return MakeShareable(new AndroidFirebaseUser(JavaUser));
}

void AuthLibraryAndroid::CreateUser(const FString& Email, const FString& Password, const FAuthUserDelegate& OnSuccess, const FAuthStringDelegate& OnError)
{
	FGMethodCallUtils::CallStaticVoidMethod(FGAuthClassName, "createUser", "(Ljava/lang/String;Ljava/lang/String;Landroid/app/Activity;)V",
	                                        *FJavaClassObject::GetJString(Email), *FJavaClassObject::GetJString(Password), FJavaWrapper::GameActivityThis);
}

void AuthLibraryAndroid::FetchProvidersForEmail(const FString& Email, const FSignInMethodsFetchedDelegate& OnSuccess, const FAuthStringDelegate& OnError)
{
	FGMethodCallUtils::CallStaticVoidMethod(FGAuthClassName, "fetchSignInMethods", "(Ljava/lang/String;)V", *FJavaClassObject::GetJString(Email));
}

void AuthLibraryAndroid::SendPasswordReset(const FString& Email, const FAuthVoidDelegate& OnSuccess, const FAuthStringDelegate& OnError)
{
	FGMethodCallUtils::CallStaticVoidMethod(FGAuthClassName, "sendPasswordReset", "(Ljava/lang/String;)V", *FJavaClassObject::GetJString(Email));
}

void AuthLibraryAndroid::SignInWithEmailAndPassword(const FString& Email, const FString& Password, const FAuthUserDelegate& OnSuccess, const FAuthStringDelegate& OnError)
{
	FGMethodCallUtils::CallStaticVoidMethod(FGAuthClassName, "signInWithEmail", "(Ljava/lang/String;Ljava/lang/String;)V",
	                                        *FJavaClassObject::GetJString(Email), *FJavaClassObject::GetJString(Password));
}

void AuthLibraryAndroid::SignInWithToken(const FString& Token, const FAuthUserDelegate& OnSuccess, const FAuthStringDelegate& OnError)
{
	FGMethodCallUtils::CallStaticVoidMethod(FGAuthClassName, "signInWithToken", "(Ljava/lang/String;)V", *FJavaClassObject::GetJString(Token));
}

void AuthLibraryAndroid::SignInAnonymously(const FAuthUserDelegate& OnSuccess, const FAuthStringDelegate& OnError)
{
	FGMethodCallUtils::CallStaticVoidMethod(FGAuthClassName, "signInAnonymously", "()V");
}

void AuthLibraryAndroid::SignInWithCredentials(TSharedPtr<IFirebaseAuthCredentials> Credentials, const FAuthUserDelegate& OnSuccess, const FAuthStringDelegate& OnError)
{
	const auto AndroidCredentials = StaticCastSharedPtr<AndroidFirebaseAuthCredentials>(Credentials);
	FGMethodCallUtils::CallStaticVoidMethod(FGAuthClassName, "signInWithCredential", "(Lcom/google/firebase/auth/AuthCredential;)V", AndroidCredentials->GetNativeCredentials());
}

void AuthLibraryAndroid::SignOut()
{
	FGMethodCallUtils::CallStaticVoidMethod(FGAuthClassName, "signOut", "()V");
}

TSharedPtr<IFirebaseAuthCredentials> AuthLibraryAndroid::GetEmailCredentials(const FString& Email, const FString& Password)
{
	jobject javaCredentials = FGMethodCallUtils::CallStaticObjectMethod(FGAuthClassName, "getEmailCredential",
	                                                                    "(Ljava/lang/String;Ljava/lang/String;)Lcom/google/firebase/auth/AuthCredential;", *FJavaClassObject::GetJString(Email),
	                                                                    *FJavaClassObject::GetJString(Password));
	return MakeShareable(new AndroidFirebaseAuthCredentials(javaCredentials));
}

TSharedPtr<IFirebaseAuthCredentials> AuthLibraryAndroid::GetFacebookCredentials(const FString& Token)
{
	jobject javaCredentials = FGMethodCallUtils::CallStaticObjectMethod(FGAuthClassName, "getFacebookCredential",
	                                                                    "(Ljava/lang/String;)Lcom/google/firebase/auth/AuthCredential;", *FJavaClassObject::GetJString(Token));
	return MakeShareable(new AndroidFirebaseAuthCredentials(javaCredentials));
}

TSharedPtr<IFirebaseAuthCredentials> AuthLibraryAndroid::GetGithubCredentials(const FString& Token)
{
	jobject javaCredentials = FGMethodCallUtils::CallStaticObjectMethod(FGAuthClassName, "getGithubCredential",
	                                                                    "(Ljava/lang/String;)Lcom/google/firebase/auth/AuthCredential;", *FJavaClassObject::GetJString(Token));
	return MakeShareable(new AndroidFirebaseAuthCredentials(javaCredentials));
}

TSharedPtr<IFirebaseAuthCredentials> AuthLibraryAndroid::GetGoogleCredentials(const FString& IdToken, const FString& AccessToken)
{
	jobject javaCredentials = FGMethodCallUtils::CallStaticObjectMethod(FGAuthClassName, "getGoogleCredential",
	                                                                    "(Ljava/lang/String;Ljava/lang/String;)Lcom/google/firebase/auth/AuthCredential;",
	                                                                    *FJavaClassObject::GetJString(IdToken), *FJavaClassObject::GetJString(AccessToken));
	return MakeShareable(new AndroidFirebaseAuthCredentials(javaCredentials));
}

TSharedPtr<IFirebaseAuthCredentials> AuthLibraryAndroid::GetAppleCredentials(const FString& IdToken, const FString& RawNonce)
{
	// not available on Android
	return nullptr;
}

void AuthLibraryAndroid::GetGameCenterCredentials(const FAuthCredentialsDelegate& OnSuccess, const FAuthStringDelegate& OnError)
{
	// not available on Android
}

TSharedPtr<IFirebaseAuthCredentials> AuthLibraryAndroid::GetGenericOAuthCredentials(const FString& Provider, const FString& IdToken, const FString& AccessToken)
{
	jobject javaCredentials = FGMethodCallUtils::CallStaticObjectMethod(FGAuthClassName, "getGenericOAuthCredential",
	                                                                    "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Lcom/google/firebase/auth/AuthCredential;",
	                                                                    *FJavaClassObject::GetJString(Provider), *FJavaClassObject::GetJString(IdToken), *FJavaClassObject::GetJString(AccessToken));
	return MakeShareable(new AndroidFirebaseAuthCredentials(javaCredentials));
}

TSharedPtr<IFirebaseAuthCredentials> AuthLibraryAndroid::GetPlayGamesCredentials(const FString& ServerAuthCode)
{
	jobject javaCredentials = FGMethodCallUtils::CallStaticObjectMethod(FGAuthClassName, "getPlayGamesCredential",
	                                                                    "(Ljava/lang/String;)Lcom/google/firebase/auth/AuthCredential;", *FJavaClassObject::GetJString(ServerAuthCode));
	return MakeShareable(new AndroidFirebaseAuthCredentials(javaCredentials));
}

TSharedPtr<IFirebaseAuthCredentials> AuthLibraryAndroid::GetTwitterCredentials(const FString& Token, const FString& Secret)
{
	jobject javaCredentials = FGMethodCallUtils::CallStaticObjectMethod(FGAuthClassName, "getTwitterCredential",
	                                                                    "(Ljava/lang/String;Ljava/lang/String;)Lcom/google/firebase/auth/AuthCredential;",
	                                                                    *FJavaClassObject::GetJString(Token), *FJavaClassObject::GetJString(Secret));
	return MakeShareable(new AndroidFirebaseAuthCredentials(javaCredentials));
}

TSharedPtr<IFirebaseAuthCredentials> AuthLibraryAndroid::GetPhoneCredentials(const FString& VerificationId, const FString& VerificationCode)
{
	jobject javaCredentials = FGMethodCallUtils::CallStaticObjectMethod(FGAuthClassName, "getPhoneCredential",
	                                                                    "(Ljava/lang/String;Ljava/lang/String;)Lcom/google/firebase/auth/AuthCredential;",
	                                                                    *FJavaClassObject::GetJString(VerificationId), *FJavaClassObject::GetJString(VerificationCode));
	return MakeShareable(new AndroidFirebaseAuthCredentials(javaCredentials));
}

void AuthLibraryAndroid::VerifyPhoneNumber(const FString& Number, int TimeoutMillis, const FAuthCredentialsDelegate& OnSuccess, const FAuthStringDelegate& OnError,
                                           const FAuthStringDelegate& OnTimeout, const FAuthStringDelegate& OnSmsSent)
{
	FGMethodCallUtils::CallStaticVoidMethod(FGAuthClassName, "verifyPhoneNumber", "(Ljava/lang/String;ILandroid/app/Activity;)V",
	                                        *FJavaClassObject::GetJString(Number), TimeoutMillis, FJavaWrapper::GameActivityThis);
}

void AuthLibraryAndroid::PromptGoogleSignIn(const FAuthCredentialsDelegate& OnSuccess, const FAuthStringDelegate& OnError)
{
	const UFirebaseGoodiesSettings* Settings = FFirebaseGoodiesModule::Get().GetSettings();
	FGMethodCallUtils::CallStaticVoidMethod(FGAuthClassName, "signInWithGoogle", "(Landroid/app/Activity;Ljava/lang/String;)V",
	                                        FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(Settings->AndroidOauthClientID));
}

void AuthLibraryAndroid::SendSignInLinkToEmail(const FString& Email, FActionCodeSettings Settings, const FAuthVoidDelegate& OnSuccess, const FAuthStringDelegate& OnError)
{
	FGMethodCallUtils::CallStaticVoidMethod(FGAuthClassName, "sendSignInLinkToEmail", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;ZLjava/lang/String;Z)V",
	                                        *FJavaClassObject::GetJString(Email),
	                                        *FJavaClassObject::GetJString(Settings.Url), *FJavaClassObject::GetJString(Settings.IosBundle), *FJavaClassObject::GetJString(Settings.DynamicLinkDomain),
	                                        *FJavaClassObject::GetJString(Settings.AndroidPackageName), Settings.bInstallIfNotAvailable, *FJavaClassObject::GetJString(Settings.MinimumAppVersion),
	                                        Settings.bCanHandleCodeInApp
	);
}

const ANSICHAR* AuthLibraryAndroid::FGAuthClassName = "com/ninevastudios/unrealfirebase/FGAuth";

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGAuth_OnIdTokenChanged(JNIEnv* env, jclass clazz)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UFGAuthLibrary::IdTokenChangedCallback.ExecuteIfBound();
	});
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGAuth_OnAuthStateChanged(JNIEnv* env, jclass clazz)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UFGAuthLibrary::AuthStateChangedCallback.ExecuteIfBound();
	});
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGAuth_OnUserCreated(JNIEnv* env, jclass clazz, jobject user)
{
	const auto AndroidUser = MakeShareable(new AndroidFirebaseUser(user));

	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UFGFirebaseUser* User = NewObject<UFGFirebaseUser>();
		User->Init(AndroidUser);
		UFGAuthLibrary::UserCreateSuccessCallback.ExecuteIfBound(User);
	});
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGAuth_OnAuthError(JNIEnv* env, jclass clazz, jstring error)
{
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, error);
	UE_LOG(LogFirebaseGoodies, Error, TEXT("Auth error: %s"), *ErrorMessage);

	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UFGAuthLibrary::AuthErrorCallback.ExecuteIfBound(ErrorMessage);
	});
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGAuth_OnSignInMethodsFetched(JNIEnv* env, jclass clazz, jobjectArray methods)
{
	const TArray<FString> Providers = FGJavaConvertor::ConvertToStringArray(methods);

	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UFGAuthLibrary::SignInMethodsFetchedCallback.ExecuteIfBound(Providers);
	});
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGAuth_OnPasswordResetSent(JNIEnv* env, jclass clazz)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UFGAuthLibrary::PasswordResetSuccessCallback.ExecuteIfBound();
	});
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGAuth_OnSignInSuccess(JNIEnv* env, jclass clazz, jobject user)
{
	const auto AndroidUser = MakeShareable(new AndroidFirebaseUser(user));

	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UFGFirebaseUser* User = NewObject<UFGFirebaseUser>();
		User->Init(AndroidUser);
		UFGAuthLibrary::SignInSuccessCallback.ExecuteIfBound(User);
	});
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGAuth_OnPhoneVerified(JNIEnv* env, jclass clazz, jobject credential)
{
	const auto AndroidCredentials = MakeShareable(new AndroidFirebaseAuthCredentials(credential));

	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UFGAuthCredentials* Result = NewObject<UFGAuthCredentials>();
		Result->Init(AndroidCredentials);
		UFGAuthLibrary::PhoneVerificationSuccessCallback.ExecuteIfBound(Result);
	});
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGAuth_OnPhoneVerificationCodeSent(JNIEnv* env, jclass clazz, jstring s)
{
	const FString VerificationId = FJavaHelper::FStringFromParam(env, s);

	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UFGAuthLibrary::PhoneVerificationSentCallback.ExecuteIfBound(VerificationId);
	});
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGAuth_OnPhoneVerificationTimeout(JNIEnv* env, jclass clazz, jstring s)
{
	const FString VerificationId = FJavaHelper::FStringFromParam(env, s);

	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UFGAuthLibrary::PhoneVerificationTimeoutCallback.ExecuteIfBound(VerificationId);
	});
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGAuth_OnGoogleSignInSuccess(JNIEnv* env, jclass clazz, jobject credential)
{
	const auto AndroidCredentials = MakeShareable(new AndroidFirebaseAuthCredentials(credential));

	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UFGAuthCredentials* Result = NewObject<UFGAuthCredentials>();
		Result->Init(AndroidCredentials);
		UFGAuthLibrary::SignInWithGoogleSuccessCallback.ExecuteIfBound(Result);
	});
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGAuth_OnSendSignInLinkToEmailSuccess(JNIEnv* env, jclass clazz)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UFGAuthLibrary::SendSignInLinkSuccessCallback.ExecuteIfBound();
	});
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGAuth_OnSendSignInLinkToEmailError(JNIEnv* env, jclass clazz, jstring error)
{
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, error);
	UE_LOG(LogFirebaseGoodies, Error, TEXT("Send sign in link to email error: %s"), *ErrorMessage);

	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UFGAuthLibrary::SendSignInLinkErrorCallback.ExecuteIfBound(ErrorMessage);
	});
}
