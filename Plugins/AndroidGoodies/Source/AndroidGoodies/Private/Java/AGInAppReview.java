// Copyright (c) 2018 Nineva Studios

package com.ninevastudios.androidgoodies;

import android.app.Activity;
import android.util.Log;

import androidx.annotation.Keep;
import androidx.annotation.NonNull;

import com.google.android.play.core.review.ReviewInfo;
import com.google.android.play.core.review.ReviewManager;
import com.google.android.play.core.review.ReviewManagerFactory;
import com.google.android.play.core.tasks.OnCompleteListener;
import com.google.android.play.core.tasks.Task;

@Keep
public class AGInAppReview {

	@Keep
	public static native void onRequestAppReviewCompleted();

	@Keep
	public static native void onRequestAppReviewFailed();

	@Keep
	public static void requestReview(final Activity activity) {
		final ReviewManager manager = ReviewManagerFactory.create(activity);
		final Task<ReviewInfo> request = manager.requestReviewFlow();
		request.addOnCompleteListener(new OnCompleteListener<ReviewInfo>() {
			@Override
			public void onComplete(@NonNull Task<ReviewInfo> task) {
				if (request.isSuccessful()) {
					ReviewInfo reviewInfo = request.getResult();
					Task<Void> flow = manager.launchReviewFlow(activity, reviewInfo);
					flow.addOnCompleteListener(new OnCompleteListener<Void>() {
						@Override
						public void onComplete(@NonNull Task<Void> task) {
							onRequestAppReviewCompleted();
						}
					});
				} else {
					onRequestAppReviewFailed();
				}
			}
		});
	}
}
