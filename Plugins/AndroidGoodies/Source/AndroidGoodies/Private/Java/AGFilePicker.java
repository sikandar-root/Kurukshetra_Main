// Copyright (c) 2020 Nineva Studios


package com.ninevastudios.androidgoodies;

import android.app.Activity;
import android.content.Intent;

import androidx.annotation.Keep;
import androidx.annotation.NonNull;

import com.ninevastudios.androidgoodies.pickers.api.CacheLocation;
import com.ninevastudios.androidgoodies.pickers.api.FilePicker;
import com.ninevastudios.androidgoodies.pickers.api.callbacks.FilePickerCallback;
import com.ninevastudios.androidgoodies.pickers.api.entity.ChosenFile;

import java.util.List;

@Keep
public class AGFilePicker {

	@Keep
	public static native void onFilesPicked(ChosenFile[] files);

	@Keep
	public static native void onFilesPickError(String error);

	@Keep
	public static void pickFile(Activity activity, boolean allowMultiple) {
		FilePicker filePicker = createFilePicker(activity);
		if (allowMultiple) {
			filePicker.allowMultiple();
		}
		filePicker.pickFile();
	}

	static void handleFileReceived(int requestCode, int resultCode, Intent data, Activity activity) {
		if (resultCode != Activity.RESULT_OK) {
			onFilesPickError("FilePicker activity result is not OK.");
			return;
		}

		FilePicker picker = createFilePicker(activity);
		picker.submit(data);
	}

	@NonNull
	private static FilePicker createFilePicker(Activity activity) {
		FilePicker picker = new FilePicker(activity);
		picker.setCacheLocation(CacheLocation.INTERNAL_APP_DIR);
		picker.setFilePickerCallback(filePickerCallback);
		return picker;
	}

	@NonNull
	private static final FilePickerCallback filePickerCallback = new FilePickerCallback() {
		@Override
		public void onFilesChosen(List<ChosenFile> files) {
			NinevaUtils.log("onFilesChosen callback");
			if (files.isEmpty()) {
				onFilesPickError("File array is empty");
				return;
			}

			NinevaUtils.log("File array not empty");

			onFilesPicked(files.toArray(new ChosenFile[0]));
		}

		@Override
		public void onError(String message) {
			onFilesPickError(message);
		}
	};
}