// Copyright (c) 2020 Nineva Studios

package com.ninevastudios.googleplay;

import static com.google.android.gms.auth.api.signin.GoogleSignIn.getLastSignedInAccount;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.Intent;
import android.content.IntentSender;
import android.util.Log;

import androidx.annotation.NonNull;

import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.common.api.ApiException;
import com.google.android.gms.games.AnnotatedData;
import com.google.android.gms.games.FriendsResolutionRequiredException;
import com.google.android.gms.games.Games;
import com.google.android.gms.games.PlayerBuffer;
import com.google.android.gms.games.PlayersClient;
import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.android.gms.tasks.Task;

public class GPFriends {
	public static native void onListenerErrorCallback(String errorMessage, int errorCode);

	public static native void onFriendsLoadSuccessCallback(GPPlayer[] friendsList);

	private static int cachedPageSize = 10;
	private static boolean cachedForceReload = true;

	public static int SHOW_SHARING_FRIENDS_CONSENT = 789;
	public static int UNKNOWN_ERROR = -1;

	public static void LoadFriendsList(final Activity activity, int pageSize, boolean forceReload) {
		cachedPageSize = pageSize;
		cachedForceReload = forceReload;

		GoogleSignInAccount lastSignedInAccount = getLastSignedInAccount(activity);
		if (lastSignedInAccount == null) {
			onListenerErrorCallback("User not logged in", UNKNOWN_ERROR);
			return;
		}
		PlayersClient playersClient = Games.getPlayersClient(activity, lastSignedInAccount);

		final Task<AnnotatedData<PlayerBuffer>> friendsListTask = playersClient.loadFriends(pageSize, forceReload);
		friendsListTask
				.addOnSuccessListener(new OnSuccessListener<AnnotatedData<PlayerBuffer>>() {
					@Override
					public void onSuccess(AnnotatedData<PlayerBuffer> playerBufferAnnotatedData) {
						PlayerBuffer playerBuffer = playerBufferAnnotatedData.get();
						GPPlayer[] parsedFriendsList = new GPPlayer[playerBuffer.getCount()];

						for (int i = 0; i < playerBuffer.getCount(); i++) {
							parsedFriendsList[i] = new GPPlayer(playerBuffer.get(i));
						}
						onFriendsLoadSuccessCallback(parsedFriendsList);
					}
				})
				.addOnFailureListener(new OnFailureListener() {
					@Override
					public void onFailure(@NonNull Exception e) {
						if (e instanceof FriendsResolutionRequiredException) {
							PendingIntent pendingIntent = ((FriendsResolutionRequiredException) friendsListTask.getException())
									.getResolution();
							try {
								activity.startIntentSenderForResult(pendingIntent.getIntentSender(), SHOW_SHARING_FRIENDS_CONSENT, null, 0, 0, 0, null);
							} catch (IntentSender.SendIntentException sendIntentException) {
								sendIntentException.printStackTrace();
								onListenerErrorCallback(e.toString(), UNKNOWN_ERROR);
							}
						} else if (e instanceof ApiException) {
							// https://developers.google.com/android/reference/com/google/android/gms/common/api/CommonStatusCodes
							onListenerErrorCallback(e.toString(), ((ApiException)e).getStatusCode());
						} else {
							onListenerErrorCallback(e.toString(), UNKNOWN_ERROR);
						}
					}
				});
	}
	
	public static void LoadFriendsList(Activity activity) {
		LoadFriendsList(activity, cachedPageSize, cachedForceReload);
	}

	public static void viewAnotherPlayerProfile(final Activity activity, String anotherPlayerId) {
		GoogleSignInAccount account = getLastSignedInAccount(activity);
		if (account == null) {
			Log.d("Error", "getLastSignedInAccount - null");
			return;
		}
		Games.getPlayersClient(activity, account)
				.getCompareProfileIntent(anotherPlayerId)
				.addOnSuccessListener(new OnSuccessListener<Intent>() {
					@Override 
					public void onSuccess(Intent intent) { 
						activity.startActivityForResult(intent, 0);
					}});
	}

	public static void viewAnotherPlayerProfileWithAlternativeHints(final Activity activity, final String otherPlayerId, final String otherPlayerInGameName, final String currentPlayerInGameName)
	{
		GoogleSignInAccount account = getLastSignedInAccount(activity);
		if (account == null) {
			Log.d("Error", "getLastSignedInAccount - null");
			return;
		}
		Games.getPlayersClient(activity, account)
				.getCompareProfileIntentWithAlternativeNameHints(otherPlayerId, otherPlayerInGameName, currentPlayerInGameName)
				.addOnSuccessListener(new OnSuccessListener<Intent>() {
					@Override
					public void onSuccess(Intent  intent) {
						activity.startActivityForResult(intent, 0);
					}});
	}
}
