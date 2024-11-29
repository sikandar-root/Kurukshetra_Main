package com.ninevastudios.androidgoodies;

import android.app.Activity;

import com.ninevastudios.androidgoodies.pickers.api.CacheLocation;
import com.ninevastudios.androidgoodies.pickers.api.CameraImagePicker;
import com.ninevastudios.androidgoodies.pickers.api.ImagePicker;
import com.ninevastudios.androidgoodies.pickers.api.callbacks.ImagePickerCallback;

public class AGImagePickerUtils {
	public static CameraImagePicker createCameraImagePicker(Activity context, ImagePickerCallback callback,
															int maxSize, boolean generateThumbnails, boolean generateTexture, int quality) {
        NinevaUtils.log("max size: " + maxSize);
		CameraImagePicker picker = new CameraImagePicker(context);
		picker.setImagePickerCallback(callback);
		picker.setCacheLocation(CacheLocation.INTERNAL_APP_DIR);

		picker.ensureMaxSize(maxSize, maxSize);
		picker.shouldGenerateThumbnails(generateThumbnails);
		picker.shouldGenerateTexture(generateTexture);
		picker.setQuality(quality);

		return picker;
	}

	public static ImagePicker createImagePicker(Activity context, ImagePickerCallback callback,
												int maxSize, boolean generateThumbnails, boolean generateTexture, int quality) {
		NinevaUtils.log("max size: " + maxSize);
		ImagePicker picker = new ImagePicker(context);
		picker.setCacheLocation(CacheLocation.INTERNAL_APP_DIR);
		picker.setImagePickerCallback(callback);

		picker.ensureMaxSize(maxSize, maxSize);
		picker.shouldGenerateThumbnails(generateThumbnails);
		picker.shouldGenerateTexture(generateTexture);
		picker.setQuality(quality);

		return picker;
	}
}
