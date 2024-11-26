// Copyright (c) 2020 Nineva Studios

package com.ninevastudios.googleplay;

import com.google.android.gms.games.snapshot.Snapshot;
import com.google.android.gms.games.snapshot.SnapshotContents;

public class GPSnapshot {
	static GPSnapshotMetadata lastMetadata;

	Snapshot mSnapshot = null;

	GPSnapshot(Snapshot snapshot) {
		mSnapshot = snapshot;
	}

	public Snapshot getSnapshot() {
		return mSnapshot;
	}

	public GPSnapshotMetadata getSnapshotMetadata() {
		if (mSnapshot != null) {
			lastMetadata = new GPSnapshotMetadata(mSnapshot.getMetadata());
			return lastMetadata;
		} else {
			return null;
		}
	}
	public SnapshotContents getSnapshotContents() {
		return mSnapshot.getSnapshotContents();
	}
}
