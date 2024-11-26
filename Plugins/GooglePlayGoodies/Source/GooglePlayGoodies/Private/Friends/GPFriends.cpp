// Copyright (c) 2020 Nineva Studios

#include "Friends/GPFriends.h"

#include "Async/Async.h"
#include "Auth/GPAccount.h"
#include "Auth/GPPlayer.h"
#include "GooglePlayGoodies.h"
#include "GooglePlayGoodiesSettings.h"
#include "GooglePlayLog.h"

#if PLATFORM_ANDROID
#include "Android/Utils/GPMethodCallUtils.h"
#include "Android/Utils/GPJavaConvertor.h"
#endif

UGPFriends::FGPOnFriendsLoad UGPFriends::OnFriendsLoadSuccessDelegate;
UGPFriends::FGPErrorDelegate UGPFriends::OnFriendsLoadFailureDelegate;


void UGPFriends::LoadFriends(int PageSize, bool ForceReload, const FGPOnFriendsLoad& OnSuccess, const FGPErrorDelegate& OnFailure)
{
	UGPFriends::OnFriendsLoadSuccessDelegate = OnSuccess;
	UGPFriends::OnFriendsLoadFailureDelegate = OnFailure;

#if PLATFORM_ANDROID
	GPMethodCallUtils::CallStaticVoidMethod("com/ninevastudios/googleplay/GPFriends", "LoadFriendsList", "(Landroid/app/Activity;IZ)V", FJavaWrapper::GameActivityThis,PageSize,ForceReload);
#endif
}

void UGPFriends::ViewAnotherPlayerProfile(const FString& OtherPlayerId, const FGPDelegate& OnSuccess)
{

#if PLATFORM_ANDROID
	GPMethodCallUtils::CallStaticVoidMethod("com/ninevastudios/googleplay/GPFriends", "viewAnotherPlayerProfile", "(Landroid/app/Activity;Ljava/lang/String;)V", FJavaWrapper::GameActivityThis, GPJavaConvertor::GetJavaString(OtherPlayerId));
#endif
}


void UGPFriends::ViewAnotherPlayerProfileWithAlternativeHints(const FString& OtherPlayerId, const FString& OtherPlayerInGameName, const FString& CurrentPlayerInGameName, const FGPCompareTwoFriends& OnSuccess)
{
#if PLATFORM_ANDROID
	GPMethodCallUtils::CallStaticVoidMethod("com/ninevastudios/googleplay/GPFriends", "viewAnotherPlayerProfileWithAlternativeHints", "(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", FJavaWrapper::GameActivityThis, GPJavaConvertor::GetJavaString(OtherPlayerId), GPJavaConvertor::GetJavaString(OtherPlayerInGameName), GPJavaConvertor::GetJavaString(CurrentPlayerInGameName));
#endif
}

#if PLATFORM_ANDROID
JNI_METHOD void Java_com_ninevastudios_googleplay_GPFriends_onListenerErrorCallback(JNIEnv* env, jclass clazz, jstring errorMessage, int errorCode)
{
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, errorMessage);
	UE_LOG(LogGooglePlayGoodies, Error, TEXT("%s | Error Code - %d"), *ErrorMessage, errorCode);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UGPFriends::OnFriendsLoadFailureDelegate.ExecuteIfBound(ErrorMessage, errorCode);
	});
}

JNI_METHOD void Java_com_ninevastudios_googleplay_GPFriends_onFriendsLoadSuccessCallback(JNIEnv* env, jclass clazz, jobjectArray friendsList)
{
	TArray<UGPPlayer*> FriendsParsedList;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	int length = Env->GetArrayLength(friendsList);
	for (int i = 0; i < length; i++)
	{
		auto javaPlayer = Env->GetObjectArrayElement(friendsList, i);

		UGPPlayer* Player = NewObject<UGPPlayer>();
		Player->Init(javaPlayer);
		FriendsParsedList.Add(Player);
	}
	
	AsyncTask(ENamedThreads::GameThread, [=]() {
		UGPFriends::OnFriendsLoadSuccessDelegate.ExecuteIfBound(FriendsParsedList);
	});
}
#endif
