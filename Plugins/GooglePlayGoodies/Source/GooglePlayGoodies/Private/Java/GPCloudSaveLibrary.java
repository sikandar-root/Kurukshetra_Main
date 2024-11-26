// Copyright (c) 2020 Nineva Studios

package com.ninevastudios.googleplay;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;

import androidx.annotation.NonNull;

import com.google.android.gms.auth.api.signin.GoogleSignIn;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.games.AnnotatedData;
import com.google.android.gms.games.Games;
import com.google.android.gms.games.SnapshotsClient;
import com.google.android.gms.games.snapshot.Snapshot;
import com.google.android.gms.games.snapshot.SnapshotMetadata;
import com.google.android.gms.games.snapshot.SnapshotMetadataBuffer;
import com.google.android.gms.games.snapshot.SnapshotMetadataChange;
import com.google.android.gms.nearby.messages.Strategy;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.android.gms.tasks.Task;

import java.io.IOException;
import java.nio.ByteBuffer;

public class GPCloudSaveLibrary {

	// Open snapshot by file name
	public static native void onOpenSnapshotByFileNameSuccessCallback(GPSnapshot snapshot);
	public static native void onOpenSnapshotByFileNameFailureCallback(String errorMessage);
	public static native void onOpenSnapshotByFileNameConflictCallback(GPConflict conflict);

	// Open snapshot with Metadata
	public static native void onOpenSnapshotWithMetadataSuccessCallback(GPSnapshot snapshot);

	public static native void onOpenSnapshotWithMetadataFailureCallback(String errorMessage);
	public static native void onOpenSnapshotWithMetadataConflictCallback(GPConflict conflict);

	// Write snapshot
	public static native void onWriteSnapshotSuccessCallback(GPSnapshotMetadata snapshotMetadata);
	public static native void onWriteSnapshotFailureCallback(String errorMessage);

	// Read snapshot
	public static native void onReadSnapshotSuccessCallback(byte[] snapshotData);
	public static native void onReadSnapshotFailureCallback(String errorMessage);

	// Get Max Cover Image Size
	public static native void onGetMaxCoverImageSizeSuccessCallback(int task);
	public static native void onGetMaxCoverImageSizeErrorCallback(String errorMessage);

	// Get Max Data Size
	public static native void onGetMaxDataSizeSuccessCallback(int dataSize);
	public static native void onGetMaxDataSizeFailureCallback(String errorMessage);

	// Delete Snapshot Metadata
	public static native void onDeleteSnapshotMetadataSuccessCallback(String task);
	public static native void onDeleteSnapshotMetadataFailureCallback(String errorMessage);

	// Load Snapshot
	public static native void onLoadSnapshotSuccessCallback(GPSnapshotMetadata[] snapshotMetadataArray);
	public static native void onLoadSnapshotFailureCallback(String errorMessage);

	// Resolve Conflict
	public static native void onResolveConflictSuccessCallback(GPSnapshot snapshot);
	public static native void onResolveConflictFailureCallback(String errorMessage);
	public static native void onResolveConflictConflictCallback(GPConflict conflict);

	public static void showSavedGamesUI(Activity activity, String title, boolean allowAddButton, boolean allowDelete, int maxSnapshots) {
		Intent intent = new Intent(activity, GPIntermediateActivity.class);
		intent.putExtra(GPIntermediateActivity.ACTION, GPIntermediateActivity.CLOUD_SAVE_UI);
		intent.putExtra(GPIntermediateActivity.SAVE_CLOUD_TITLE, title);
		intent.putExtra(GPIntermediateActivity.SAVE_CLOUD_ALLOW_ADD_BUTTON, allowAddButton);
		intent.putExtra(GPIntermediateActivity.SAVE_CLOUD_ALLOW_DELETE, allowDelete);
		intent.putExtra(GPIntermediateActivity.SAVE_CLOUD_MAX_SNAPSHOTS, maxSnapshots);
		activity.startActivity(intent);
	}

	public static void openSnapshotWithFileName(Activity activity, String fileName, boolean createIfNotFound, int conflictPolicy) {
		GoogleSignInAccount currentGoogleSignInAccount = GoogleSignIn.getLastSignedInAccount(activity);
		if (currentGoogleSignInAccount == null) {
			onOpenSnapshotByFileNameFailureCallback("OpenSnapshotWithFileName - Google Sign In Account is null!");
			return;
		}
		SnapshotsClient snapshotsClient = Games.getSnapshotsClient(activity, currentGoogleSignInAccount);
		snapshotsClient.open(fileName, createIfNotFound, conflictPolicy)
				.addOnSuccessListener(new OnSuccessListener<SnapshotsClient.DataOrConflict<Snapshot>>() {
					@Override
					public void onSuccess(SnapshotsClient.DataOrConflict<Snapshot> snapshotDataOrConflict) {
						if (snapshotDataOrConflict.isConflict()) {
							if (snapshotDataOrConflict.getConflict() != null) {
								onOpenSnapshotByFileNameConflictCallback(new GPConflict(snapshotDataOrConflict.getConflict()));
							}
						} else {
							onOpenSnapshotByFileNameSuccessCallback(new GPSnapshot(snapshotDataOrConflict.getData()));
						}
					}
				})
				.addOnFailureListener(new OnFailureListener() {
					@Override
					public void onFailure(@NonNull Exception e) {
						onOpenSnapshotByFileNameFailureCallback(e.getMessage());
					}
				});
	}

	public static void openSnapshotWithMetadata(Activity activity, GPSnapshotMetadata metadata, int conflictPolicy) {
		GoogleSignInAccount currentGoogleSignInAccount = GoogleSignIn.getLastSignedInAccount(activity);
		if (currentGoogleSignInAccount == null) {
			onOpenSnapshotWithMetadataFailureCallback("OpenSnapshotWithMetadata - Google Sign In Account is null!");
			return;
		}
		SnapshotsClient snapshotsClient = Games.getSnapshotsClient(activity, currentGoogleSignInAccount);
		snapshotsClient.open(metadata.getSnapshotMetadata(), conflictPolicy).addOnSuccessListener(new OnSuccessListener<SnapshotsClient.DataOrConflict<Snapshot>>() {
			@Override
			public void onSuccess(SnapshotsClient.DataOrConflict<Snapshot> snapshotDataOrConflict) {
				if (snapshotDataOrConflict.isConflict()) {
					SnapshotsClient.SnapshotConflict conflict = snapshotDataOrConflict.getConflict();
					if (conflict != null) {
						onOpenSnapshotWithMetadataConflictCallback(new GPConflict(snapshotDataOrConflict.getConflict()));
					}
				} else {
					onOpenSnapshotWithMetadataSuccessCallback(new GPSnapshot(snapshotDataOrConflict.getData()));
				}
			}
		}).addOnFailureListener(new OnFailureListener() {
			@Override
			public void onFailure(@NonNull Exception e) {
				onOpenSnapshotWithMetadataFailureCallback(e.getMessage());
			}
		});
	}


	public static void writeSnapshot(Activity activity, GPSnapshot snapshot, byte[] data, String description, long playedTimeMillis, long progressValue, byte[] bufferBitmap, int width, int height) {
		GoogleSignInAccount singInAccount = GoogleSignIn.getLastSignedInAccount(activity);
		if (singInAccount == null) {
			onWriteSnapshotFailureCallback("WriteSnapshot - Google Sign In Account is null!");
			return;
		}

		snapshot.getSnapshot().getSnapshotContents().writeBytes(data);

		SnapshotMetadataChange.Builder metadataChangeBuilder = new SnapshotMetadataChange.Builder();
		if (bufferBitmap != null) {
			metadataChangeBuilder.setCoverImage(getBitmap(bufferBitmap, width, height));
		}
		metadataChangeBuilder.setPlayedTimeMillis(playedTimeMillis)
				.setProgressValue(progressValue)
				.setDescription(description);

		SnapshotsClient snapshotsClient = Games.getSnapshotsClient(activity, singInAccount);
		snapshotsClient.commitAndClose(snapshot.getSnapshot(), metadataChangeBuilder.build())
				.addOnSuccessListener(new OnSuccessListener<SnapshotMetadata>() {
					@Override
					public void onSuccess(SnapshotMetadata snapshotMetadata) {
						onWriteSnapshotSuccessCallback(new GPSnapshotMetadata(snapshotMetadata));
					}
				})
				.addOnFailureListener(new OnFailureListener() {
					@Override
					public void onFailure(@NonNull Exception e) {
						onWriteSnapshotFailureCallback(e.getMessage());
					}
				});
	}

	public static void readSnapshot(GPSnapshot snapshot) {
		try {
			onReadSnapshotSuccessCallback(snapshot.getSnapshotContents().readFully());
		} catch (IOException e) {
			onReadSnapshotFailureCallback(e.getMessage());
		}
	}

	public static void getMaxCoverImageSize(Activity activity) {
		GoogleSignInAccount currentGoogleSignInAccount = GoogleSignIn.getLastSignedInAccount(activity);
		if (currentGoogleSignInAccount == null) {
			onOpenSnapshotByFileNameFailureCallback("getMaxCoverImageSize - Google Sign In Account is null!");
			return;
		}
		SnapshotsClient snapshotsClient = Games.getSnapshotsClient(activity, currentGoogleSignInAccount);
		snapshotsClient.getMaxCoverImageSize()
				.addOnSuccessListener(new OnSuccessListener<Integer>() {
					@Override
					public void onSuccess(Integer integer) {
						onGetMaxCoverImageSizeSuccessCallback(integer);
					}
				})
				.addOnFailureListener(new OnFailureListener() {
					@Override
					public void onFailure(@NonNull Exception e) {
						onGetMaxCoverImageSizeErrorCallback(e.getMessage());
					}
				});
	}

	public static void getMaxDataSize(Activity activity) {
		GoogleSignInAccount currentGoogleSignInAccount = GoogleSignIn.getLastSignedInAccount(activity);
		if (currentGoogleSignInAccount == null) {
			onOpenSnapshotByFileNameFailureCallback("getMaxDataSize - Google Sign In Account is null!");
			return;
		}
		SnapshotsClient snapshotsClient = Games.getSnapshotsClient(activity, currentGoogleSignInAccount);
		snapshotsClient.getMaxDataSize()
				.addOnSuccessListener(new OnSuccessListener<Integer>() {
					@Override
					public void onSuccess(Integer integer) {
						onGetMaxDataSizeSuccessCallback(integer);
					}
				})
				.addOnFailureListener(new OnFailureListener() {
					@Override
					public void onFailure(@NonNull Exception e) {
						onGetMaxDataSizeFailureCallback(e.getMessage());
					}
				});
	}

	@NonNull
	private static Bitmap getBitmap(byte[] bufferBitmap, int width, int height) {
		Bitmap bitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
		ByteBuffer byteBuffer = ByteBuffer.wrap(bufferBitmap);
		bitmap.copyPixelsFromBuffer(byteBuffer);
		return bitmap;
	}

	public static void deleteSnapshot(Activity activity, GPSnapshotMetadata snapshotMetadata) {
		GoogleSignInAccount currentGoogleSignInAccount = GoogleSignIn.getLastSignedInAccount(activity);
		if (currentGoogleSignInAccount == null) {
			onOpenSnapshotByFileNameFailureCallback("deleteSnapshot - Google Sign In Account is null!");
			return;
		}
		SnapshotsClient snapshotsClient = Games.getSnapshotsClient(activity, currentGoogleSignInAccount);
		snapshotsClient.delete(snapshotMetadata.getSnapshotMetadata())
				.addOnSuccessListener(new OnSuccessListener<String>() {
					@Override
					public void onSuccess(String s) {
						onDeleteSnapshotMetadataSuccessCallback(s);
					}
				})
				.addOnFailureListener(new OnFailureListener() {
					@Override
					public void onFailure(@NonNull Exception e) {
						onDeleteSnapshotMetadataFailureCallback(e.getMessage());
					}
				});
	}

	public static void loadSnapshot(Activity activity, boolean forceReload) {
		GoogleSignInAccount currentGoogleSignInAccount = GoogleSignIn.getLastSignedInAccount(activity);
		if (currentGoogleSignInAccount == null) {
			onOpenSnapshotByFileNameFailureCallback("loadSnapshot - Google Sign In Account is null!");
			return;
		}
		SnapshotsClient snapshotsClient = Games.getSnapshotsClient(activity, currentGoogleSignInAccount);
		snapshotsClient.load(forceReload)
				.addOnSuccessListener(new OnSuccessListener<AnnotatedData<SnapshotMetadataBuffer>>() {
					@Override
					public void onSuccess(AnnotatedData<SnapshotMetadataBuffer> snapshotMetadataBufferAnnotatedData) {
						SnapshotMetadataBuffer snapshotMetadataBuffer = snapshotMetadataBufferAnnotatedData.get();
						if (snapshotMetadataBuffer != null) {
							GPSnapshotMetadata[] parsedSnapshotMetadataList = new GPSnapshotMetadata[snapshotMetadataBuffer.getCount()];
							for (int i = 0; i < snapshotMetadataBuffer.getCount(); i++) {
								parsedSnapshotMetadataList[i] = new GPSnapshotMetadata(snapshotMetadataBuffer.get(i));
							}
							onLoadSnapshotSuccessCallback(parsedSnapshotMetadataList);
						}
					}
				})
				.addOnFailureListener(new OnFailureListener() {
					@Override
					public void onFailure(@NonNull Exception e) {
						onLoadSnapshotFailureCallback(e.getMessage());
					}
				});
	}

	public static void resolveConflict(Activity activity, String conflictId, GPSnapshot snapshot) {
		GoogleSignInAccount currentGoogleSignInAccount = GoogleSignIn.getLastSignedInAccount(activity);
		if (currentGoogleSignInAccount == null) {
			onOpenSnapshotByFileNameFailureCallback("loadSnapshot - Google Sign In Account is null!");
			return;
		}
		SnapshotsClient snapshotsClient = Games.getSnapshotsClient(activity, currentGoogleSignInAccount);
		snapshotsClient.resolveConflict(conflictId, snapshot.getSnapshot())
				.addOnSuccessListener(new OnSuccessListener<SnapshotsClient.DataOrConflict<Snapshot>>() {
					@Override
					public void onSuccess(SnapshotsClient.DataOrConflict<Snapshot> snapshotDataOrConflict) {
						if (snapshotDataOrConflict.isConflict()) {
							onResolveConflictConflictCallback(new GPConflict(snapshotDataOrConflict.getConflict()));
						} else {
							onResolveConflictSuccessCallback(new GPSnapshot(snapshotDataOrConflict.getData()));
						}
					}
				})
				.addOnFailureListener(new OnFailureListener() {
					@Override
					public void onFailure(@NonNull Exception e) {
						onResolveConflictFailureCallback(e.getMessage());
					}
				});
	}
}
