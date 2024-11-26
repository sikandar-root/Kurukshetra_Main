// Copyright (c) 2020 Nineva Studios

package com.ninevastudios.googleplay;

import android.app.Activity;
import android.content.Intent;
import android.view.View;

import androidx.annotation.NonNull;

import com.google.android.gms.auth.api.signin.GoogleSignIn;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.games.Games;
import com.google.android.gms.games.VideosClient;
import com.google.android.gms.games.video.CaptureState;
import com.google.android.gms.games.video.VideoCapabilities;
import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.android.gms.tasks.Task;

public class GPVideoRecordingLibrary {

	private static final int RC_VIDEO_OVERLAY = 9011;

	// Video Recording
	public static native void onVideoRecordingFailureCallback(String errorMessage);

	// Get Capture Capabilities
	public static native void onGetCaptureCapabilitiesSuccessCallback(GPVideoCapabilities captureCapabilities);
	public static native void onGetCaptureCapabilitiesFailureCallback(String errorMessage);

	// Get Capture State
	public static native void onGetCaptureStateSuccessCallback(GPCaptureState captureState);
	public static native void onGetCaptureStateFailureCallback(String errorMessage);

	// Is Capture Supported
	public static native void onIsCaptureSupportedSuccessCallback(boolean captureSupported);
	public static native void onIsCaptureSupportedFailureCallback(String errorMessage);

	// Register On Capture Overlay State Changed Listener
	public static native void onRegisterCaptureOverlayStateChangedListenerCallback(int overlayState);
	public static native void onRegisterCaptureOverlayStateFailureListenerCallback(String errorMessage);

/*	// Unregister On Capture Overlay State Changed Listener
	public static native void onUnregisterCaptureOverlayStateChangedListenerCallback(int overlayState);
	public static native void onUnregisterCaptureOverlayStateFailureListenerCallback(String errorMessage);*/

	public static void showVideoRecordingOverlay(Activity activity) {
		final Activity mActivity = activity;
		GoogleSignInAccount signedInAccount = GoogleSignIn.getLastSignedInAccount(mActivity);
		if (signedInAccount == null) {
			onVideoRecordingFailureCallback("You are not signed in google account");
			return;
		}
		Games.getVideosClient(mActivity, signedInAccount)
				.getCaptureOverlayIntent()
				.addOnSuccessListener(new OnSuccessListener<Intent>() {
					@Override
					public void onSuccess(Intent intent) {
						mActivity.startActivityForResult(intent, RC_VIDEO_OVERLAY);
					}
				})
				.addOnFailureListener(new OnFailureListener() {
					@Override
					public void onFailure(@NonNull Exception e) {
						onVideoRecordingFailureCallback(e.getMessage());
					}
				});
	}

	public static void getCaptureCapabilities(Activity activity) {
		final Activity mActivity = activity;
		GoogleSignInAccount signedInAccount = GoogleSignIn.getLastSignedInAccount(mActivity);
		if (signedInAccount == null) {
			onGetCaptureCapabilitiesFailureCallback("You are not signed in google account");
			return;
		}
		Games.getVideosClient(mActivity, signedInAccount)
				.getCaptureCapabilities()
				.addOnSuccessListener(new OnSuccessListener<VideoCapabilities>() {
					@Override
					public void onSuccess(VideoCapabilities videoCapabilities) {
						onGetCaptureCapabilitiesSuccessCallback(new GPVideoCapabilities(videoCapabilities));
					}
				})
				.addOnFailureListener(new OnFailureListener() {
					@Override
					public void onFailure(@NonNull Exception e) {
						onGetCaptureCapabilitiesFailureCallback(e.getMessage());
					}
				});
	}

	public static void getCaptureState(Activity activity) {
		final Activity mActivity = activity;
		GoogleSignInAccount signedInAccount = GoogleSignIn.getLastSignedInAccount(mActivity);
		if (signedInAccount == null) {
			onGetCaptureStateFailureCallback("You are not signed in google account");
			return;
		}
		Games.getVideosClient(mActivity, signedInAccount)
				.getCaptureState()
				.addOnSuccessListener(new OnSuccessListener<CaptureState>() {
					@Override
					public void onSuccess(CaptureState captureState) {
						onGetCaptureStateSuccessCallback(new GPCaptureState(captureState));
					}
				})
				.addOnFailureListener(new OnFailureListener() {
					@Override
					public void onFailure(@NonNull Exception e) {
						onGetCaptureStateFailureCallback(e.getMessage());
					}
				});
	}

	public static void isCaptureSupported(Activity activity) {
		final Activity mActivity = activity;
		GoogleSignInAccount signedInAccount = GoogleSignIn.getLastSignedInAccount(mActivity);
		if (signedInAccount == null) {
			onIsCaptureSupportedFailureCallback("You are not signed in google account");
			return;
		}
		Games.getVideosClient(mActivity, signedInAccount)
				.isCaptureSupported()
				.addOnSuccessListener(new OnSuccessListener<Boolean>() {
					@Override
					public void onSuccess(Boolean aBoolean) {
						onIsCaptureSupportedSuccessCallback(aBoolean);
					}
				})
				.addOnFailureListener(new OnFailureListener() {
					@Override
					public void onFailure(@NonNull Exception e) {
						onIsCaptureSupportedFailureCallback(e.getMessage());
					}
				});
	}

	private static final VideosClient.OnCaptureOverlayStateListener captureOverlayStateListener = new VideosClient.OnCaptureOverlayStateListener() {
		@Override
		public void onCaptureOverlayStateChanged(int overlayState) {
			onRegisterCaptureOverlayStateChangedListenerCallback(overlayState);
		}
	};

	public static void registerOnCaptureOverlayStateChangedListener(Activity activity) {
		GoogleSignInAccount signedInAccount = GoogleSignIn.getLastSignedInAccount(activity);
		if (signedInAccount == null) {
			onRegisterCaptureOverlayStateFailureListenerCallback("You are not signed in google account");
			return;
		}
		Games.getVideosClient(activity, signedInAccount).registerOnCaptureOverlayStateChangedListener(captureOverlayStateListener);
	}

	public static void unregisterOnCaptureOverlayStateChangedListener(Activity activity) {
		GoogleSignInAccount signedInAccount = GoogleSignIn.getLastSignedInAccount(activity);
		if (signedInAccount == null) {
			onRegisterCaptureOverlayStateFailureListenerCallback("You are not signed in google account");
			return;
		}
		Games.getVideosClient(activity, signedInAccount).unregisterOnCaptureOverlayStateChangedListener(captureOverlayStateListener);
	}
}