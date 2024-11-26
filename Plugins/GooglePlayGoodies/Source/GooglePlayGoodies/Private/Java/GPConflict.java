// Copyright (c) 2020 Nineva Studios

package com.ninevastudios.googleplay;

import com.google.android.gms.games.SnapshotsClient;

public class GPConflict {
	private SnapshotsClient.SnapshotConflict mSnapshotConflict = null;

	GPConflict(SnapshotsClient.SnapshotConflict snapshotConflict) {
		mSnapshotConflict = snapshotConflict;
	}

	public SnapshotsClient.SnapshotConflict getSnapshotConflict() {
		return mSnapshotConflict;
	}

	public String getSnapshotConflictId() {
		return mSnapshotConflict != null ? mSnapshotConflict.getConflictId() : "";
	}

	public GPSnapshot getLocalSnapshot() {
		return mSnapshotConflict != null ? new GPSnapshot(mSnapshotConflict.getConflictingSnapshot()) : null;
	}

	public GPSnapshot getServerSnapshot() {
		return mSnapshotConflict != null ? new GPSnapshot(mSnapshotConflict.getSnapshot()) : null;
	}
}
