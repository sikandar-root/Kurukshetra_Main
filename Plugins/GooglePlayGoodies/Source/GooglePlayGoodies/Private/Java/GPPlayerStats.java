// Copyright (c) 2020 Nineva Studios

package com.ninevastudios.googleplay;

import android.app.Activity;
import android.util.Log;

import com.google.android.gms.auth.api.signin.GoogleSignIn;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.common.api.ApiException;
import com.google.android.gms.games.AnnotatedData;
import com.google.android.gms.games.Games;
import com.google.android.gms.games.PlayerStatsClient;
import com.google.android.gms.games.stats.PlayerStats;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;

public class GPPlayerStats {

	public static native void onPlayerStatsCallback(int daysSinceLastPlayed, int sessionCount, float avgSessionLen, float sessionPercentile, int purchaseCount, float purchasePercentile);

	public static void getPlayerStats(Activity activity, boolean forceRefresh) {
		GoogleSignInAccount account = GoogleSignIn.getLastSignedInAccount(activity);
		if (account != null) {
			PlayerStatsClient client = Games.getPlayerStatsClient(activity, account);
			client.loadPlayerStats(forceRefresh).addOnCompleteListener(new OnCompleteListener<AnnotatedData<PlayerStats>>() {
				@Override
				public void onComplete(Task<AnnotatedData<PlayerStats>> task) {
					if (task.isSuccessful()) {
						PlayerStats stats = task.getResult().get();
						if (stats != null) {
							onPlayerStatsCallback(
									stats.getDaysSinceLastPlayed(),
									stats.getNumberOfSessions(),
									stats.getAverageSessionLength(),
									stats.getSessionPercentile(),
									stats.getNumberOfPurchases(),
									stats.getSpendPercentile());
						}
					} else {
						if (task.getException() instanceof ApiException) {
							Log.d("GooglePlayGoodies", "Cannot retrieve player stats: " + task.getException().toString());
						}
					}
				}
			});
		}
	}

}
