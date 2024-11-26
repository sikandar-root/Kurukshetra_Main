// Copyright (c) 2018 Nineva Studios

#include "AGInAppReviewBPL.h"
#include "Async/Async.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJava.h"
#include "Android/Utils/AGMethodCallUtils.h"
#endif

static const ANSICHAR* AGInAppReviewClassName = "com/ninevastudios/androidgoodies/AGInAppReview";

FOnRequestReviewCompletedDelegate UAGInAppReviewBPL::OnRequestReviewCompletedDelegate;
FOnRequestReviewFailedDelegate UAGInAppReviewBPL::OnRequestReviewFailedDelegate;

void UAGInAppReviewBPL::RequestReview(const FOnRequestReviewCompletedDelegate& onCompleteCallback, const FOnRequestReviewFailedDelegate& onFailedCallback)
{
	OnRequestReviewCompletedDelegate = onCompleteCallback;
	OnRequestReviewFailedDelegate = onFailedCallback;

#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(AGInAppReviewClassName, "requestReview", "(Landroid/app/Activity;)V",
		FJavaWrapper::GameActivityThis);
#endif
}

void UAGInAppReviewBPL::OnRequestCompleted()
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		OnRequestReviewCompletedDelegate.ExecuteIfBound();
	});
}

void UAGInAppReviewBPL::OnRequestFailed()
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		OnRequestReviewFailedDelegate.ExecuteIfBound();
	});
}

#if PLATFORM_ANDROID

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGInAppReview_onRequestAppReviewCompleted(JNIEnv* env, jclass clazz)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => onRequestAppReviewCompleted callback caught in C++!"));
	
	UAGInAppReviewBPL::OnRequestCompleted();
}

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGInAppReview_onRequestAppReviewFailed(JNIEnv* env, jclass clazz)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => onRequestAppReviewFailed callback caught in C++!"));

	UAGInAppReviewBPL::OnRequestFailed();
}

#endif
