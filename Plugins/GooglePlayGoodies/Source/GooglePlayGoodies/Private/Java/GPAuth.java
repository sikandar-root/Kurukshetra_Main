// Copyright (c) 2020 Nineva Studios

package com.ninevastudios.googleplay;

import android.app.Activity;
import android.content.Intent;
import android.util.Log;

import com.google.android.gms.auth.api.signin.GoogleSignIn;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.drive.Drive;
import com.google.android.gms.games.Games;
import com.google.android.gms.games.GamesClient;

public class GPAuth {

	private static Activity ueActivity = null;

	public static void login(Activity activity, boolean silent, boolean requeestId, boolean requestProfile, boolean requestEmail, boolean requestIdToken, boolean requestCloudSave, boolean requestServerAuthCode, String clientId) {
		ueActivity = activity;

		Intent intent = new Intent(activity, GPIntermediateActivity.class);
		intent.putExtra(GPIntermediateActivity.ACTION, silent ? GPIntermediateActivity.SILENT_LOGIN : GPIntermediateActivity.LOGIN);
		intent.putExtra(GPIntermediateActivity.REQUEST_ID, requeestId);
		intent.putExtra(GPIntermediateActivity.REQUEST_PROFILE, requestProfile);
		intent.putExtra(GPIntermediateActivity.REQUEST_EMAIL, requestEmail);
		intent.putExtra(GPIntermediateActivity.REQUEST_ID_TOKEN, requestIdToken);
		intent.putExtra(GPIntermediateActivity.REQUEST_SERVER_AUTH_CODE, requestServerAuthCode);
		intent.putExtra(GPIntermediateActivity.CLIENT_ID, clientId);
		intent.putExtra(GPIntermediateActivity.USE_CLOUD_SAVE, requestCloudSave);
		activity.startActivity(intent);
	}

	public static void logout(Activity activity) {
		if (isLoggedIn(activity)) {
			Intent intent = new Intent(activity, GPIntermediateActivity.class);
			intent.putExtra(GPIntermediateActivity.ACTION, GPIntermediateActivity.LOGOUT);
			activity.startActivity(intent);
		}
	}

	public static void revoke(Activity activity) {
		if (isLoggedIn(activity)) {
			Intent intent = new Intent(activity, GPIntermediateActivity.class);
			intent.putExtra(GPIntermediateActivity.ACTION, GPIntermediateActivity.REVOKE_ACCESS);
			activity.startActivity(intent);
		}
	}

	public static boolean isLoggedIn(Activity activity) {
		return GoogleSignIn.getLastSignedInAccount(activity) != null;
	}

	public static void setPopupView() {
		GoogleSignInAccount account =  GoogleSignIn.getLastSignedInAccount(ueActivity);
		if (ueActivity != null && account != null) {
			GamesClient gamesClient = Games.getGamesClient(ueActivity, account);
			gamesClient.setViewForPopups(ueActivity.findViewById(android.R.id.content));
		}
	}
}
