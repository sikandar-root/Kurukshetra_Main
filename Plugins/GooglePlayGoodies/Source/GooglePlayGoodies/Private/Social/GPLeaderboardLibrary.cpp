// Copyright (c) 2020 Nineva Studios

#include "Social/GPLeaderboardLibrary.h"

#include "GooglePlayLog.h"
#include "Utils/GPUtils.h"

#include "Callback/GPScoreHolderImageCallback.h"

#include "Async/Async.h"

#if PLATFORM_ANDROID
#include "Android/Utils/GPMethodCallUtils.h"
#include "Android/Utils/GPJavaConvertor.h"
#endif

static const ANSICHAR* GPLeaderboardClassName = "com/ninevastudios/googleplay/GPLeaderboard";

FGPOnScoresLoadedDelegate UGPLeaderboardLibrary::OnScoresLoadedCallback;
FGPOnScoresLoadErrorDelegate UGPLeaderboardLibrary::OnScoresLoadErrorCallback;
FGPOnScoresLoadedDelegate UGPLeaderboardLibrary::OnTopScoresLoadedCallback;
FGPOnScoresLoadErrorDelegate UGPLeaderboardLibrary::OnTopScoresLoadErrorCallback;

void UGPLeaderboardLibrary::SubmitScore(const FString& LeaderboardID, int Score)
{
#if PLATFORM_ANDROID
	auto JIdString = FJavaClassObject::GetJString(LeaderboardID);
	GPMethodCallUtils::CallStaticVoidMethod(GPLeaderboardClassName, "submiteScore", "(Landroid/app/Activity;Ljava/lang/String;J)V", 
		FJavaWrapper::GameActivityThis, *JIdString, (jlong)Score);
#endif
}

void UGPLeaderboardLibrary::ShowLeaderboardUI(const FString& LeaderboardID, LeaderboardTimeSpan TimeSpan, LeaderboardCollection Collection)
{
#if PLATFORM_ANDROID
	auto JIdString = FJavaClassObject::GetJString(LeaderboardID);
	GPMethodCallUtils::CallStaticVoidMethod(GPLeaderboardClassName, "showUI", "(Landroid/app/Activity;Ljava/lang/String;II)V", 
		FJavaWrapper::GameActivityThis, *JIdString, static_cast<int>(TimeSpan), static_cast<int>(Collection));
#endif
}

void UGPLeaderboardLibrary::LoadPlayerCenteredScores(const FString& LeaderboardID, const FGPOnScoresLoadedDelegate& OnSuccess, const FGPOnScoresLoadErrorDelegate& OnError, int MaxResults,
                                                     LeaderboardTimeSpan TimeSpan, LeaderboardCollection Collection, bool ForceReload)
{
	OnScoresLoadedCallback = OnSuccess;
	OnScoresLoadErrorCallback = OnError;

#if PLATFORM_ANDROID
	auto JIdString = FJavaClassObject::GetJString(LeaderboardID);
	GPMethodCallUtils::CallStaticVoidMethod(GPLeaderboardClassName, "loadPlayerCenteredScores", "(Landroid/app/Activity;Ljava/lang/String;IIIZ)V",
		FJavaWrapper::GameActivityThis, *JIdString, static_cast<int>(TimeSpan), static_cast<int>(Collection), MaxResults, ForceReload);
#endif
}

void UGPLeaderboardLibrary::LoadTopScores(const FString& LeaderboardID, const FGPOnScoresLoadedDelegate& OnSuccess, const FGPOnScoresLoadErrorDelegate& OnError, int MaxResults,
                                          LeaderboardTimeSpan TimeSpan, LeaderboardCollection Collection, bool ForceReload)
{
	OnTopScoresLoadedCallback = OnSuccess;
	OnTopScoresLoadErrorCallback = OnError;

#if PLATFORM_ANDROID
	auto JIdString = FJavaClassObject::GetJString(LeaderboardID);
	GPMethodCallUtils::CallStaticVoidMethod(GPLeaderboardClassName, "loadTopScores", "(Landroid/app/Activity;Ljava/lang/String;IIIZ)V",
		FJavaWrapper::GameActivityThis, *JIdString, static_cast<int>(TimeSpan), static_cast<int>(Collection), MaxResults, ForceReload);
#endif
}

void UGPLeaderboardLibrary::GetScoreHolderImage(const FString& ScoreHolderImageUri, const FGPOnScoreHolderImageReadyDelegate& onImageReady)
{
	UGPScoreHolderImageCallback* imageCallback = NewObject<UGPScoreHolderImageCallback>();
	imageCallback->BindDelegate(onImageReady);

#if PLATFORM_ANDROID
	auto ImageUriString = FJavaClassObject::GetJString(ScoreHolderImageUri);
	GPMethodCallUtils::CallStaticVoidMethod(GPLeaderboardClassName, "getScoreHolderImage", "(Landroid/app/Activity;Ljava/lang/String;J)V",
		FJavaWrapper::GameActivityThis, *ImageUriString, (jlong)imageCallback);
#endif
}

#if PLATFORM_ANDROID
JNI_METHOD void Java_com_ninevastudios_googleplay_GPLeaderboard_OnLoadPlayerCenteredScoresSuccess(JNIEnv* env, jclass clazz, jobjectArray javaScores)
{
	TArray<FGPLeaderboardScore> Scores = GPJavaConvertor::FromJavaScores(javaScores);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UGPLeaderboardLibrary::OnScoresLoadedCallback.ExecuteIfBound(Scores);
	});
}

JNI_METHOD void Java_com_ninevastudios_googleplay_GPLeaderboard_OnLoadPlayerCenteredScoresError(JNIEnv* env, jclass clazz, jstring error)
{
	FString ErrorMessage = GPJavaConvertor::FromJavaString(error);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UGPLeaderboardLibrary::OnScoresLoadErrorCallback.ExecuteIfBound(ErrorMessage);
	});
}

JNI_METHOD void Java_com_ninevastudios_googleplay_GPLeaderboard_OnLoadTopScoresSuccess(JNIEnv* env, jclass clazz, jobjectArray javaScores)
{
	TArray<FGPLeaderboardScore> Scores = GPJavaConvertor::FromJavaScores(javaScores);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UGPLeaderboardLibrary::OnTopScoresLoadedCallback.ExecuteIfBound(Scores);
	});
}

JNI_METHOD void Java_com_ninevastudios_googleplay_GPLeaderboard_OnLoadTopScoresError(JNIEnv* env, jclass clazz, jstring error)
{
	FString ErrorMessage = GPJavaConvertor::FromJavaString(error);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UGPLeaderboardLibrary::OnTopScoresLoadErrorCallback.ExecuteIfBound(ErrorMessage);
	});
}

JNI_METHOD void Java_com_ninevastudios_googleplay_GPLeaderboard_onScoreHolderImageReady(JNIEnv* env, jclass clazz,
	jlong objAddr, jbyteArray buffer, int Width, int Height, jstring imageUri)
{
	UGPScoreHolderImageCallback* CallbackDelegate = reinterpret_cast<UGPScoreHolderImageCallback*>(objAddr);
	TArray<uint8> ByteArray = GPJavaConvertor::ToByteArray(static_cast<jbyteArray>(buffer));
	FString ImageUri = GPJavaConvertor::FromJavaString(imageUri);
	AsyncTask(ENamedThreads::GameThread, [=]() {
		CallbackDelegate->ExecuteDelegate(GPUtils::TextureFromByteArray(ByteArray, Width, Height), ImageUri);
	});
}
#endif
