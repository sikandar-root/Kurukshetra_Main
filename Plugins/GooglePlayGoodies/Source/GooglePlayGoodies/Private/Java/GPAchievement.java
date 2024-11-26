// Copyright (c) 2020 Nineva Studios

package com.ninevastudios.googleplay;

import android.app.Activity;
import android.content.Intent;

import com.google.android.gms.auth.api.signin.GoogleSignIn;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.games.AchievementsClient;
import com.google.android.gms.games.Games;

public class GPAchievement {

	public static void unlock(Activity activity, String id) {
		GoogleSignInAccount account = GoogleSignIn.getLastSignedInAccount(activity);
		if (account != null) {
			AchievementsClient client = Games.getAchievementsClient(activity, account);
			client.unlock(id);
		}
	}

	public static void increment(Activity activity, String id, int value) {
		GoogleSignInAccount account = GoogleSignIn.getLastSignedInAccount(activity);
		if (account != null) {
			AchievementsClient client = Games.getAchievementsClient(activity, account);
			client.increment(id, value);
		}
	}

	public static void showUI(Activity activity) {
		if (GPAuth.isLoggedIn(activity)) {
			Intent intent = new Intent(activity, GPIntermediateActivity.class);
			intent.putExtra(GPIntermediateActivity.ACTION, GPIntermediateActivity.ACHIEVEMENT_UI);
			activity.startActivity(intent);
		}
	}

}
