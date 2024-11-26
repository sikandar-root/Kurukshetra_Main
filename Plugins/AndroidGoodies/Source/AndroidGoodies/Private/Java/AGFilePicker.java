// Copyright (c) 2020 Nineva Studios


package com.ninevastudios.androidgoodies;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;

import androidx.annotation.Keep;
import androidx.annotation.NonNull;

import android.util.Log;

import com.ninevastudios.androidgoodies.pickers.api.CacheLocation;
import com.ninevastudios.androidgoodies.pickers.api.FilePicker;
import com.ninevastudios.androidgoodies.pickers.api.Picker;
import com.ninevastudios.androidgoodies.pickers.api.callbacks.FilePickerCallback;
import com.ninevastudios.androidgoodies.pickers.api.entity.ChosenFile;

import java.util.List;

@Keep
public class AGFilePicker {

	@Keep
	public static native void onFilesPicked(ChosenFile[] files);

	@Keep
	public static native void onFilesPickError(String error);

	private static FilePicker filePicker;
	private static final String FILE_KEY = "ANDROID_GOODIES_PREFS";
	private static boolean allowMultipleFiles;

	@Keep
	public static void pickFile(Activity activity, boolean allowMultiple) {
		allowMultipleFiles = allowMultiple;

		Intent intent = new Intent(activity, AndroidGoodiesActivity.class);
		intent.putExtra(AndroidGoodiesActivity.EXTRAS_PICKER_TYPE, Picker.PICK_FILE);

		activity.startActivity(intent);
	}

	@Keep
	public static void pickFileInternal(Intent intent, Activity context) {
		persistFilePickerSettings(intent, context);

		filePicker = new FilePicker(context);
		filePicker.setCacheLocation(CacheLocation.INTERNAL_APP_DIR);
		if (allowMultipleFiles) {
			filePicker.allowMultiple();
		}
		filePicker.setFilePickerCallback(filePickerCallback);
		filePicker.pickFile();
	}

	static void handleFileReceived(int requestCode, int resultCode, Intent data, AndroidGoodiesActivity activity) {
		if (resultCode != Activity.RESULT_OK) {
			onFilesPickError("FilePicker activity result is not OK.");
			return;
		}

		FilePicker picker = new FilePicker(activity);
		picker.setCacheLocation(CacheLocation.INTERNAL_APP_DIR);
		picker.setFilePickerCallback(filePickerCallback);
		picker.submit(data);
	}

	@NonNull
	private static FilePickerCallback filePickerCallback = new FilePickerCallback() {
		@Override
		public void onFilesChosen(List<ChosenFile> files) {
			Log.d("Android Goodies", "FilePicker inside callback");
			if (files.isEmpty()) {
				onFilesPickError("File array is empty");
				return;
			}

			Log.d("Android Goodies", "File array not empty");

			onFilesPicked(files.toArray(new ChosenFile[0]));
		}

		@Override
		public void onError(String message) {
			onFilesPickError(message);
		}
	};

	private static SharedPreferences getPrefs(Activity context) {
		return context.getSharedPreferences(FILE_KEY, Context.MODE_PRIVATE);
	}

	@SuppressLint("ApplySharedPref")
	private static void persistFilePickerSettings(Intent data, Activity context) {
		SharedPreferences.Editor editor = getPrefs(context).edit();
		editor.commit();
	}
}