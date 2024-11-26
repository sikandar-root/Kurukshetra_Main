// Copyright (c) 2020 Nineva Studios

package com.ninevastudios.googleplay;

import com.google.android.gms.games.video.CaptureState;

public class GPCaptureState {
	private CaptureState mCaptureState = null;

	GPCaptureState (CaptureState captureState) {
		mCaptureState = captureState;
	}

	public int getCaptureMode() {
		return mCaptureState != null ? mCaptureState.getCaptureMode() : -1;
	}

	public int getCaptureQuality() {
		return mCaptureState != null ? mCaptureState.getCaptureQuality() : -1;
	}

	public boolean isCapturing() {
		return mCaptureState.isCapturing();
	}

	public boolean isOverlayVisible() {
		return mCaptureState.isOverlayVisible();
	}

	public  boolean isPaused() {
		return mCaptureState.isPaused();
	}
}
