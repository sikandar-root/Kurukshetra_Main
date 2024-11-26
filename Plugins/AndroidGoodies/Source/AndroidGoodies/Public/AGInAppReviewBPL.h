// Copyright (c) 2018 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGInAppReviewBPL.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnRequestReviewCompletedDelegate);
DECLARE_DYNAMIC_DELEGATE(FOnRequestReviewFailedDelegate);

/*Class to request in-app reviews*/
UCLASS()
class ANDROIDGOODIES_API UAGInAppReviewBPL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Show in-app review if possible. This ONLY works in apps published on Google Play. You can't test it without publishing your app to Google Play. However, you can test your integration without publishing your app to production using either internal test tracks or internal app sharing See https://developer.android.com/guide/playcore/in-app-review/test
	* @param onCompleteCallback - invoked when the review flow has finished, t1his does not mean that review has been successful
	* @param onFailedCallback - invoked when requesting a review failed
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void RequestReview(const FOnRequestReviewCompletedDelegate& onCompleteCallback, const FOnRequestReviewFailedDelegate& onFailedCallback);

	// Callbacks interface methods to be called from Android
	static void OnRequestCompleted();
	static void OnRequestFailed();

private:
	static FOnRequestReviewCompletedDelegate OnRequestReviewCompletedDelegate;
	static FOnRequestReviewFailedDelegate OnRequestReviewFailedDelegate;
};
