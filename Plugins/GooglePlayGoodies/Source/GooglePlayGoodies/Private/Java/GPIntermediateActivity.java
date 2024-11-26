// Copyright (c) 2020 Nineva Studios

package com.ninevastudios.googleplay;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import androidx.annotation.NonNull;

import com.google.android.gms.auth.api.signin.GoogleSignIn;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.auth.api.signin.GoogleSignInClient;
import com.google.android.gms.auth.api.signin.GoogleSignInOptions;
import com.google.android.gms.common.api.ApiException;
import com.google.android.gms.common.api.Scope;
import com.google.android.gms.drive.Drive;
import com.google.android.gms.drive.Metadata;
import com.google.android.gms.games.Games;
import com.google.android.gms.games.Player;
import com.google.android.gms.games.PlayersClient;
import com.google.android.gms.games.SnapshotsClient;
import com.google.android.gms.games.leaderboard.LeaderboardVariant;
import com.google.android.gms.games.snapshot.SnapshotMetadata;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.android.gms.tasks.Task;

public class GPIntermediateActivity extends Activity {

	public static native void onLoginSuccessCallback(GPAccount account, GPPlayer player);
	public static native void onLoginCancelCallback();
	public static native void onLoginErrorCallback(String errorMessage);
	public static native void onLogoutSuccessCallback();


	public static native void onAddNewSnapshotCallback();
	public static native void onChooseSnapshotCallback(GPSnapshotMetadata snapshotData);
	public static native void onCloudSaveCancelCallback();
	public static native void onCloudSaveErrorCallback(String errorMessage);

	// cb user selected save
	// cb user pressed add btn

	public static final String ACTION = "action";
	public static final String REQUEST_ID = "id";
	public static final String REQUEST_ID_TOKEN = "id_token";
	public static final String REQUEST_SERVER_AUTH_CODE = "server_auth_code";
	public static final String REQUEST_PROFILE = "profile";
	public static final String REQUEST_EMAIL = "email";
	public static final String USE_CLOUD_SAVE = "cloud_save";
	public static final String CLIENT_ID = "client_id";
	public static final String LEADERBOARD_ID = "leaderboard_id";
	public static final String LEADERBOARD_TIME = "leaderboard_time";
	public static final String LEADERBOARD_COLLECTION = "leaderboard_collection";
	public static final String SAVE_CLOUD_TITLE = "save_cloud_title";
	public static final String SAVE_CLOUD_ALLOW_ADD_BUTTON = "save_cloud_allow_add_button";
	public static final String SAVE_CLOUD_ALLOW_DELETE = "save_cloud_allow_delete";
	public static final String SAVE_CLOUD_MAX_SNAPSHOTS = "save_cloud_max_snapshots";

	public static final int NO_ACTION = 0;
	public static final int LOGIN = 1;
	public static final int SILENT_LOGIN = 2;
	public static final int LOGOUT = 3;
	public static final int REVOKE_ACCESS = 4;
	public static final int ACHIEVEMENT_UI = 5;
	public static final int LEADERBOARD_UI = 6;
	public static final int CLOUD_SAVE_UI = 7;


	private GoogleSignInClient mSignInClient = null;
	private static GoogleSignInAccount mAccount = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		mAccount = GoogleSignIn.getLastSignedInAccount(this);
		GoogleSignInOptions.Builder optionsBuilder = new GoogleSignInOptions.Builder(GoogleSignInOptions.DEFAULT_GAMES_SIGN_IN);

		if (getIntent().getBooleanExtra(REQUEST_ID, false)) optionsBuilder.requestId();
		if (getIntent().getBooleanExtra(REQUEST_PROFILE, false)) optionsBuilder.requestProfile();
		if (getIntent().getBooleanExtra(REQUEST_EMAIL, false)) {
			optionsBuilder.requestEmail();
		}
		if (getIntent().getBooleanExtra(USE_CLOUD_SAVE, false)) {
			optionsBuilder.requestScopes(Drive.SCOPE_APPFOLDER);
		}

		if (getIntent().getBooleanExtra(REQUEST_SERVER_AUTH_CODE, false)) {
			String clientId = getIntent().getStringExtra(CLIENT_ID);
			if (clientId != null && !clientId.isEmpty())
				optionsBuilder.requestServerAuthCode(clientId);
		}
		if (getIntent().getBooleanExtra(REQUEST_ID_TOKEN, false)) {
			String clientId = getIntent().getStringExtra(CLIENT_ID);
			if (clientId != null && !clientId.isEmpty())
				optionsBuilder.requestIdToken(clientId);
		}

		GoogleSignInOptions signInOptions = optionsBuilder.build();
		mSignInClient = GoogleSignIn.getClient(this, signInOptions);

		int action = getIntent().getIntExtra(ACTION, NO_ACTION);
		switch (action) {
			case LOGIN: {
				login(false);
				break;
			}
			case SILENT_LOGIN: {
				login(true);
				break;
			}
			case LOGOUT: {
				logout();
				break;
			}
			case REVOKE_ACCESS: {
				revoke();
				break;
			}
			case ACHIEVEMENT_UI: {
				showAchievementUI();
				break;
			}
			case LEADERBOARD_UI: {
				showLeaderboardUI(
						getIntent().getStringExtra(LEADERBOARD_ID),
						getIntent().getIntExtra(LEADERBOARD_TIME, LeaderboardVariant.TIME_SPAN_ALL_TIME),
						getIntent().getIntExtra(LEADERBOARD_COLLECTION, LeaderboardVariant.COLLECTION_PUBLIC)
				);
				break;
			}
			case CLOUD_SAVE_UI:
				showSavedGamesUI(
						getIntent().getStringExtra(SAVE_CLOUD_TITLE),
						getIntent().getBooleanExtra(SAVE_CLOUD_ALLOW_ADD_BUTTON, false),
						getIntent().getBooleanExtra(SAVE_CLOUD_ALLOW_DELETE, false),
						getIntent().getIntExtra(SAVE_CLOUD_MAX_SNAPSHOTS, 0));
				break;
			default:
				finish();
		}
	}


	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);

		if (requestCode == LOGIN) {
			if (resultCode == Activity.RESULT_CANCELED) {
				onLoginCancelCallback();
			} else {
				Task<GoogleSignInAccount> task = GoogleSignIn.getSignedInAccountFromIntent(data);
				try {
					mAccount = task.getResult(ApiException.class);
					handleLoginSuccess();
				} catch (ApiException apiException) {
					onLoginErrorCallback("Google API Error " + apiException.getStatusCode());
				}
			}
		}

		if (requestCode == CLOUD_SAVE_UI) {
			if (resultCode == Activity.RESULT_CANCELED) {
				onCloudSaveCancelCallback();
			} else {
				if (data.hasExtra(SnapshotsClient.EXTRA_SNAPSHOT_METADATA)) {
					SnapshotMetadata snapshotMetadata = data.getParcelableExtra(SnapshotsClient.EXTRA_SNAPSHOT_METADATA);
					onChooseSnapshotCallback(new GPSnapshotMetadata(snapshotMetadata));
				} else if (data.hasExtra(SnapshotsClient.EXTRA_SNAPSHOT_NEW)) {
					onAddNewSnapshotCallback();
				}
			}
		}

		finish();
	}

	private void login(boolean silent) {
		if (silent) {
			mSignInClient.silentSignIn().addOnCompleteListener(
					new OnCompleteListener<GoogleSignInAccount>() {
						@Override
						public void onComplete(Task<GoogleSignInAccount> task) {
							if (task.isSuccessful()) {
								mAccount = task.getResult();
								handleLoginSuccess();
								finish();
							}
							else {
								login(false);
							}
						}
					}
			);
		} else {
			Intent intent = mSignInClient.getSignInIntent();
			startActivityForResult(intent, LOGIN);
		}
	}

	private void logout() {
		if (mAccount == null || mSignInClient == null) {
			finish();
			return;
		}

		mSignInClient.signOut().addOnCompleteListener(this,
				new OnCompleteListener<Void>() {
					@Override
					public void onComplete(Task<Void> task) {
						onLogoutSuccessCallback();
						mAccount = null;
						finish();
					}
				});
	}

	private void revoke() {
		if (mAccount == null || mSignInClient == null) {
			finish();
			return;
		}

		mSignInClient.revokeAccess().addOnCompleteListener(this,
				new OnCompleteListener<Void>() {
					@Override
					public void onComplete(Task<Void> task) {
						mAccount = null;
						finish();
					}
				});
	}

	private void handleLoginSuccess() {
		// need to explicitly set a view for the popups so they are show in UE activity
		GPAuth.setPopupView();

		PlayersClient playersClient = Games.getPlayersClient(this, mAccount);
		playersClient.getCurrentPlayer().addOnCompleteListener(new OnCompleteListener<Player>() {
			@Override
			public void onComplete(Task<Player> task) {
				Player player = null;
				if (task.isSuccessful()) {
					player = task.getResult();
				}

				GPAccount accountWrapper = new GPAccount(mAccount);
				GPPlayer playerWrapper = new GPPlayer(player);
				onLoginSuccessCallback(accountWrapper, playerWrapper);
			}
		});
	}

	private void showAchievementUI() {
		Games.getAchievementsClient(this, mAccount)
				.getAchievementsIntent()
				.addOnSuccessListener(new OnSuccessListener<Intent>() {
					@Override
					public void onSuccess(Intent intent) {
						startActivityForResult(intent, ACHIEVEMENT_UI);
					}
				});
	}

	private void showLeaderboardUI(String id, int time, int collection) {
		Games.getLeaderboardsClient(this, mAccount)
				.getLeaderboardIntent(id, time, collection)
				.addOnSuccessListener(new OnSuccessListener<Intent>() {
					@Override
					public void onSuccess(Intent intent) {
						startActivityForResult(intent, LEADERBOARD_UI);
					}
				});

	}

	private void showSavedGamesUI(String title, boolean allowAddButton, boolean allowDelete, int maxSnapshots) {
		final Activity ueActivity = this;
		GoogleSignInAccount currentGoogleSignInAccount = GoogleSignIn.getLastSignedInAccount(this);
		if (currentGoogleSignInAccount == null) {
			onCloudSaveErrorCallback("User is not logged in");
			finish();
			return;
		}
		SnapshotsClient snapshotsClient = Games.getSnapshotsClient(this, currentGoogleSignInAccount);
		Task<Intent> intentTask = snapshotsClient.getSelectSnapshotIntent(title, allowAddButton, allowDelete, maxSnapshots);

		intentTask.addOnCompleteListener(this, new OnCompleteListener<Intent>() {
			@Override
			public void onComplete(@NonNull Task<Intent> task) {
				if (task.isSuccessful()) {
					ueActivity.startActivityForResult(task.getResult(), CLOUD_SAVE_UI);
				} else {
					onCloudSaveErrorCallback(task.getException().getMessage());
					finish();
				}
			}
		});
	}
}
