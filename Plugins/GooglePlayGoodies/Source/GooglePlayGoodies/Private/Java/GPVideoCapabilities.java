// Copyright (c) 2020 Nineva Studios

package com.ninevastudios.googleplay;

import android.media.MediaCodecInfo;

import com.google.android.gms.games.video.VideoCapabilities;

public class GPVideoCapabilities {
	private VideoCapabilities mVideoCapabilities = null;

	GPVideoCapabilities(VideoCapabilities videoCapabilities) {
		mVideoCapabilities = videoCapabilities;
	}

	public boolean[] getSupportedCaptureModes() {
		return mVideoCapabilities.getSupportedCaptureModes();
	}

	public boolean[] getSupportedQualityLevels() {
		return mVideoCapabilities.getSupportedQualityLevels();
	}

	public boolean isCameraSupported() {
		return mVideoCapabilities.isCameraSupported();
	}

	public boolean isFullySupported(int captureMode, int qualityLevel) {
		return mVideoCapabilities.isFullySupported(captureMode, qualityLevel);
	}

	public boolean isMicSupported() {
		return mVideoCapabilities.isMicSupported();
	}

	public boolean isWriteStorageSupported() {
		return mVideoCapabilities.isWriteStorageSupported();
	}

	public boolean supportsCaptureMode(int captureMode) {
		return mVideoCapabilities.supportsCaptureMode(captureMode);
	}

	public boolean supportsQualityLevel(int qualityLevel) {
		return mVideoCapabilities.supportsQualityLevel(qualityLevel);
	}
}