// Copyright (c) 2020 Nineva Studios

package com.ninevastudios.googleplay;

import android.app.Activity;
import android.net.Uri;
import android.util.Log;

import com.google.android.gms.games.CurrentPlayerInfo;
import com.google.android.gms.games.Player;

public class GPPlayer {

	public static native void onIconReady(long callbackAddr, byte[] buffer, int width, int height);
	public static native void onBannerReady(long callbackAddr, byte[] buffer, int width, int height);

	private Player mPlayer = null;
	private long mCallbackAddr;

	public GPPlayer(Player player) {
		mPlayer = player;
	}

	public void initCallbacks(long callbackAddr) {
		mCallbackAddr = callbackAddr;
	}

	public String getDisplayName() {
		return mPlayer != null ? mPlayer.getDisplayName() : "";
	}

	public String getPlayerId() {
		return mPlayer != null ? mPlayer.getPlayerId() != null ? mPlayer.getPlayerId() : "" : "";
	}

	public String getTitle() {
		return mPlayer != null ? mPlayer.getTitle() : "";
	}

	public long getTimestampSeconds() {
		return mPlayer != null ? (mPlayer.getRetrievedTimestamp()/1000) : 0;
	}

	public int getFriendsListVisibilityStatus() {
		if (mPlayer != null && mPlayer.getCurrentPlayerInfo() != null) {
			return mPlayer.getCurrentPlayerInfo().getFriendsListVisibilityStatus();
		}
		return Player.FriendsListVisibilityStatus.UNKNOWN;
	}

	public int getPlayerFriendStatus() {
		if (mPlayer != null && mPlayer.getRelationshipInfo() != null) {
			return mPlayer.getRelationshipInfo().getFriendStatus();
		}
		return Player.PlayerFriendStatus.UNKNOWN;
	}

	public void getBannerImage(Activity activity, boolean isPortraitOrientation) {
		try {
			Uri imageUri = isPortraitOrientation ? mPlayer.getBannerImagePortraitUri() : mPlayer.getBannerImageLandscapeUri();
			GPUtils.loadImage(activity, imageUri, new GPUtils.OnLoadImageCallback() {
				@Override
				public void run(byte[] buffer, int width, int height, String uri) {
					onBannerReady(mCallbackAddr, buffer, width, height);
				}
			});
		}
		catch (Exception e) {
			Log.d("GooglePlayGoodies", e.toString());
		}
	}

	public void getIconImage(Activity activity, boolean isHiRes) {
		try {
			Uri imageUri = isHiRes ? mPlayer.getHiResImageUri() : mPlayer.getIconImageUri();
			GPUtils.loadImage(activity, imageUri, new GPUtils.OnLoadImageCallback() {
				@Override
				public void run(byte[] buffer, int width, int height, String uri) {
					onIconReady(mCallbackAddr, buffer, width, height);
				}
			});
		}
		catch (Exception e) {
			Log.d("GooglePlayGoodies", e.toString());
		}
	}
}
