// Copyright (c) 2020 Nineva Studios

package com.ninevastudios.googleplay;

import android.util.Log;

import com.google.android.gms.games.snapshot.SnapshotMetadata;

public class GPSnapshotMetadata {
	private SnapshotMetadata mSnapshotMetadata = null;

	public GPSnapshotMetadata(SnapshotMetadata snapshotMetadata) {
		mSnapshotMetadata = snapshotMetadata;
	}

	public SnapshotMetadata getSnapshotMetadata() {
		return mSnapshotMetadata;
	}

	public String getDescription() {
		return mSnapshotMetadata != null ? mSnapshotMetadata.getDescription() : "";
	}

	public String getDeviceName() {
		return mSnapshotMetadata != null ? mSnapshotMetadata.getDeviceName() : "";
	}

	public String getSnapshotId() {
		return mSnapshotMetadata != null ? mSnapshotMetadata.getSnapshotId() : "";
	}

	public String getUniqueName() {
		return mSnapshotMetadata != null ? mSnapshotMetadata.getUniqueName() : "";
	}

	public String getCoverImageUri() {
		return mSnapshotMetadata != null ? String.valueOf(mSnapshotMetadata.getCoverImageUri()) : "";
	}

	public float getCoverImageAspectRatioMethod() {
		return mSnapshotMetadata != null ? mSnapshotMetadata.getCoverImageAspectRatio() : 0.f;
	}

	public long getLastModifiedTimestamp() {
		return mSnapshotMetadata != null ? mSnapshotMetadata.getLastModifiedTimestamp() : 0;
	}

	public long getPlayedTime() {
		return mSnapshotMetadata != null ? mSnapshotMetadata.getPlayedTime() : 0;
	}

	public long getProgressValue() {
		return mSnapshotMetadata != null ? mSnapshotMetadata.getProgressValue() : 0;
	}
}
