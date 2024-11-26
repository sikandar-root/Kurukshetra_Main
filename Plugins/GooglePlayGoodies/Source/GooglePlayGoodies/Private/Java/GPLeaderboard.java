// Copyright (c) 2020 Nineva Studios

package com.ninevastudios.googleplay;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.util.Log;

import androidx.annotation.NonNull;

import com.google.android.gms.auth.api.signin.GoogleSignIn;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.games.AnnotatedData;
import com.google.android.gms.games.Games;
import com.google.android.gms.games.LeaderboardsClient;
import com.google.android.gms.games.leaderboard.LeaderboardScore;
import com.google.android.gms.games.leaderboard.LeaderboardScoreBuffer;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;

public class GPLeaderboard {

	public static native void OnLoadPlayerCenteredScoresSuccess(LeaderboardScore[] scores);

	public static native void OnLoadPlayerCenteredScoresError(String error);

	public static native void OnLoadTopScoresSuccess(LeaderboardScore[] scores);

	public static native void OnLoadTopScoresError(String error);

	public static native void onScoreHolderImageReady(long callbackAddr, byte[] buffer, int width, int height, String uri);

	public static void submiteScore(Activity activity, String id, long score) {
		GoogleSignInAccount account = GoogleSignIn.getLastSignedInAccount(activity);
		if (account != null) {
			LeaderboardsClient client = Games.getLeaderboardsClient(activity, account);
			client.submitScore(id, score);
		}
	}

	public static void showUI(Activity activity, String id, int time, int collection) {
		if (GPAuth.isLoggedIn(activity)) {
			Intent intent = new Intent(activity, GPIntermediateActivity.class);
			intent.putExtra(GPIntermediateActivity.ACTION, GPIntermediateActivity.LEADERBOARD_UI);
			intent.putExtra(GPIntermediateActivity.LEADERBOARD_ID, id);
			intent.putExtra(GPIntermediateActivity.LEADERBOARD_TIME, time);
			intent.putExtra(GPIntermediateActivity.LEADERBOARD_COLLECTION, collection);
			activity.startActivity(intent);
		}
	}

	public static void loadPlayerCenteredScores(Activity activity, String leaderboardId, int span, int leaderboardCollection, int maxResults, boolean forceReload) {
		if (!GPAuth.isLoggedIn(activity)) {
			OnLoadPlayerCenteredScoresError("Could not Load Player Centered Scores. Please, sign in first.");
			return;
		}

		GoogleSignInAccount account = GoogleSignIn.getLastSignedInAccount(activity);
		if (account == null) {
			OnLoadPlayerCenteredScoresError("Could not Load Player Centered Scores. Please, sign in first.");
			return;
		}

		final LeaderboardsClient client = Games.getLeaderboardsClient(activity, account);
		client.loadPlayerCenteredScores(leaderboardId, span, leaderboardCollection, maxResults, forceReload).addOnCompleteListener(new OnCompleteListener<AnnotatedData<LeaderboardsClient.LeaderboardScores>>() {
			@Override
			public void onComplete(@NonNull Task<AnnotatedData<LeaderboardsClient.LeaderboardScores>> task) {
				if (task.isSuccessful()) {
					LeaderboardScoreBuffer scoreBuffer = task.getResult().get().getScores();

					LeaderboardScore[] scores = new LeaderboardScore[scoreBuffer.getCount()];
					for (int i = 0; i < scoreBuffer.getCount(); i++) {
						scores[i] = scoreBuffer.get(i);
					}

					OnLoadPlayerCenteredScoresSuccess(scores);
				} else {
					OnLoadPlayerCenteredScoresError(task.getException().getMessage());
				}
			}
		});
	}

	public static void loadTopScores(Activity activity, String leaderboardId, int span, int leaderboardCollection, int maxResults, boolean forceReload) {
		if (!GPAuth.isLoggedIn(activity)) {
			OnLoadTopScoresError("Could not Load Top Scores. Please, sign in first.");
			return;
		}

		GoogleSignInAccount account = GoogleSignIn.getLastSignedInAccount(activity);
		if (account == null) {
			OnLoadTopScoresError("Could not Load Top Scores. Please, sign in first.");
			return;
		}

		final LeaderboardsClient client = Games.getLeaderboardsClient(activity, account);
		client.loadTopScores(leaderboardId, span, leaderboardCollection, maxResults, forceReload).addOnCompleteListener(new OnCompleteListener<AnnotatedData<LeaderboardsClient.LeaderboardScores>>() {
			@Override
			public void onComplete(@NonNull Task<AnnotatedData<LeaderboardsClient.LeaderboardScores>> task) {
				if (task.isSuccessful()) {
					LeaderboardScoreBuffer scoreBuffer = task.getResult().get().getScores();

					LeaderboardScore[] scores = new LeaderboardScore[scoreBuffer.getCount()];
					for (int i = 0; i < scoreBuffer.getCount(); i++) {
						scores[i] = scoreBuffer.get(i);
					}

					OnLoadTopScoresSuccess(scores);
				} else {
					OnLoadTopScoresError(task.getException().getMessage());
				}
			}
		});
	}

	public static void getScoreHolderImage(Activity activity, String scoreHolderIconUri, final long callbackAddr) {
		try {
			Uri imageUri = Uri.parse(scoreHolderIconUri);
			GPUtils.loadImage(activity, imageUri, new GPUtils.OnLoadImageCallback() {
				@Override
				public void run(byte[] buffer, int width, int height, String uri) {
					onScoreHolderImageReady(callbackAddr, buffer, width, height, uri);
				}
			});
		}
		catch (Exception e) {
			Log.d("GooglePlayGoodies", e.toString());
		}
	}
}
