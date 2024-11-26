// Copyright (c) 2019 Nineva Studios

package com.ninevastudios.androidgoodies;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.media.ExifInterface;
import android.media.MediaScannerConnection;
import android.net.Uri;
import android.os.Build;
import android.os.Environment;

import androidx.annotation.Keep;
import androidx.annotation.NonNull;

import android.provider.MediaStore;
import android.util.Log;

import com.ninevastudios.androidgoodies.pickers.api.CacheLocation;
import com.ninevastudios.androidgoodies.pickers.api.CameraImagePicker;
import com.ninevastudios.androidgoodies.pickers.api.ImagePicker;
import com.ninevastudios.androidgoodies.pickers.api.Picker;
import com.ninevastudios.androidgoodies.pickers.api.callbacks.ImagePickerCallback;
import com.ninevastudios.androidgoodies.pickers.api.entity.ChosenImage;
import com.ninevastudios.androidgoodies.pickers.core.ImagePickerImpl;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.URLConnection;
import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import java.util.List;

@SuppressWarnings("unused")
@Keep
public class AGImagePicker {

	@Keep
	public static native void onImagesPicked(ChosenImage[] images);

	@Keep
	public static native void onImageReady(byte[] buffer, int width, int height);

	@Keep
	public static native void onImageError(String error);

	public static final String EXTRA_QUALITY = "Quality";
	private static final String EXTRA_MAX_SIZE = "MaximumSize";
	private static final String EXTRA_SHOULD_GENERATE_THUMBNAILS = "ShouldGenerateThumbnails";
	private static final String EXTRAS_PHOTO_OUTPUT_PATH = "EXTRAS_PHOTO_OUTPUT_PATH";
	private static final String EXTRAS_SHOULD_GET_TEXTURE = "ShouldGetTexture";
	private static final String EXTRAS_ALLOW_MULTIPLE = "AllowMultiple";
	private static final int UNUSED = -1;

	private static Activity _activity;
	private static ImagePicker imagePicker;
	private static final String FILE_KEY = "ANDROID_GOODIES_PREFS";

	@Keep
	public static void pickImage(Activity activity, int quality, int maximumSize, boolean shouldGenerateThumbnails, boolean shouldGetTexture, boolean allowMultiple) {
		_activity = activity;
		startGoodiesActivity(activity, quality, maximumSize, shouldGenerateThumbnails, shouldGetTexture, allowMultiple, Picker.PICK_IMAGE_DEVICE);
	}

	@Keep
	public static void takePhoto(Activity activity, int maximumSize, boolean shouldGenerateThumbnails, boolean shouldGetTexture) {
		_activity = activity;
		startGoodiesActivity(activity, UNUSED, maximumSize, shouldGenerateThumbnails, shouldGetTexture, false, Picker.PICK_IMAGE_CAMERA);
	}

	@SuppressLint("ObsoleteSdkInt")
	@Keep
	public static void saveImageToGallery(Activity activity, byte[] buffer, String fileName, int width, int height) {
		NinevaLogUtils.logMethodCall("saveImageToGallery");
		Bitmap bitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
		ByteBuffer byteBuffer = ByteBuffer.wrap(buffer);
		bitmap.copyPixelsFromBuffer(byteBuffer);

		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
			saveImageAndroidQ(activity, fileName, bitmap);
		} else {
			saveImagePreAndroidQ(activity, fileName, bitmap);
		}
	}

	private static void saveImageAndroidQ(Context context, String fileName, Bitmap bitmap) {
		NinevaLogUtils.logMethodCall("saveImageAndroidQ");

		ContentValues cv = new ContentValues();
		cv.put(MediaStore.MediaColumns.DISPLAY_NAME, fileName + ".png");
		cv.put(MediaStore.MediaColumns.MIME_TYPE, "image/png");
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
			cv.put(MediaStore.MediaColumns.RELATIVE_PATH, Environment.DIRECTORY_PICTURES);
			cv.put(MediaStore.Video.Media.IS_PENDING, 1);
		}

		ContentResolver contentResolver = context.getContentResolver();
		Uri imageUri = contentResolver.insert(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, cv);
		try {
			OutputStream fos = contentResolver.openOutputStream(imageUri);
			bitmap.compress(Bitmap.CompressFormat.PNG, 100, fos);

			if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
				cv.clear();
				cv.put(MediaStore.Video.Media.IS_PENDING, 0);
				contentResolver.update(imageUri, cv, null, null);
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}

	private static void saveImagePreAndroidQ(Activity activity, String fileName, Bitmap bitmap) {
		NinevaLogUtils.logMethodCall("saveImagePreAndroidQ");

		File root = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES);
		File file = new File(root, fileName + ".png");
		Log.d("Goodies", file.getAbsolutePath());
		try {
			FileOutputStream out = new FileOutputStream(file);
			bitmap.compress(Bitmap.CompressFormat.PNG, 100, out);
			out.flush();
			out.close();

			if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) {
				MediaScannerConnection.scanFile(activity, new String[]{file.toString()}, null,
						new MediaScannerConnection.OnScanCompletedListener() {
							public void onScanCompleted(String path, Uri uri) {
							}
						});
			} else {
				Uri uri = Uri.fromFile(file);
				Intent intent = new Intent(Intent.ACTION_MEDIA_MOUNTED, uri);
				activity.sendBroadcast(intent);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Keep
	public static void pickImageInternal(Intent intent, Activity context, int quality) {
		NinevaLogUtils.logMethodCall("pickImageInternal");

		persistImagePickerSettings(intent, context);

		imagePicker = new ImagePicker(context);
		imagePicker.setCacheLocation(CacheLocation.INTERNAL_APP_DIR);
		if (intent.getBooleanExtra(EXTRAS_SHOULD_GET_TEXTURE, false)) {
			imagePicker.setImagePickerCallback(texturePickerCallback);
		} else {
			imagePicker.setImagePickerCallback(chosenImagePickerCallback);
		}
		if (intent.getBooleanExtra(EXTRAS_ALLOW_MULTIPLE, false)) {
			imagePicker.allowMultiple();
		}
		imagePicker.setQuality(quality);
		imagePicker.pickImage();
	}

	@Keep
	public static void pickImageFromCameraInternal(Intent intent, Activity context) {
		NinevaLogUtils.logMethodCall("pickImageFromCameraInternal");

		CameraImagePicker picker = new CameraImagePicker(context);
		picker.setCacheLocation(CacheLocation.INTERNAL_APP_DIR);
		if (intent.getBooleanExtra(EXTRAS_SHOULD_GET_TEXTURE, false)) {
			picker.setImagePickerCallback(texturePickerCallback);
		} else {
			picker.setImagePickerCallback(chosenImagePickerCallback);
		}

		String outputPath = picker.pickImage();
		if (outputPath == null) {

			onImageError("Taking photo failed");
			return;
		}

		intent.putExtra(EXTRAS_PHOTO_OUTPUT_PATH, outputPath);
		persistImagePickerSettings(intent, context);
	}

	static void handlePhotoReceived(int requestCode, int resultCode, Intent data, AndroidGoodiesActivity activity) {
		NinevaLogUtils.logMethodCall("handlePhotoReceived");

		if (resultCode != Activity.RESULT_OK) {
			onImageError("Activity result is not OK.");
			return;
		}

		ImagePickerImpl picker;
		if (requestCode == Picker.PICK_IMAGE_DEVICE) {
			picker = new ImagePicker(activity);
		} else {
			picker = new CameraImagePicker(activity);
		}

		configureImagePicker(activity, picker);
		picker.setCacheLocation(CacheLocation.INTERNAL_APP_DIR);

		if (getPrefs(activity).getBoolean(EXTRAS_SHOULD_GET_TEXTURE, false)) {
			picker.setImagePickerCallback(texturePickerCallback);
		} else {
			picker.setImagePickerCallback(chosenImagePickerCallback);
		}
		picker.submit(data);
	}

	@NonNull
	private static ImagePickerCallback chosenImagePickerCallback = new ImagePickerCallback() {
		@Override
		public void onImagesChosen(List<ChosenImage> images) {
			NinevaLogUtils.logMethodCall("onImagesChosen");
			if (images.isEmpty()) {
				onImageError("Image array is empty.");
				return;
			}

			NinevaLogUtils.log("onImagesChosen:Array not empty");
			onImagesPicked(images.toArray(new ChosenImage[0]));
		}

		@Override
		public void onError(String message) {
			onImageError(message);
		}
	};

	@NonNull
	private static ImagePickerCallback texturePickerCallback = new ImagePickerCallback() {
		@Override
		public void onImagesChosen(List<ChosenImage> images) {
			NinevaLogUtils.logMethodCall("onImagesChosen");

			if (images.isEmpty()) {
				onImageError("Image array is empty.");
				return;
			}

			NinevaLogUtils.log("onImagesChosen:Array not empty");
			ChosenImage img = images.get(0);

			final int width = img.getWidth();
			final int height = img.getHeight();

			if (img.getWidth() == 0 || img.getHeight() == 0) {
				onImageError("Image width or height is 0.");
				return;
			}

			Log.d("AndroidGoodies", "Image has height and width");

			final String path = img.getOriginalPath();
			if (path.length() == 0) {
				onImageError("Image path is empty.");
				return;
			}
			Log.d("AndroidGoodies", "Image path is not empty");

			_activity.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					Bitmap bm = BitmapFactory.decodeFile(path);
					Bitmap bitmap = rotate(bm, path);

					onImageReady(getBitmapBytes(bitmap), bitmap.getWidth(), bitmap.getHeight());

					bitmap.recycle();
				}
			});
		}

		@Override
		public void onError(String message) {
			onImageError(message);
		}
	};

	static Bitmap rotate(Bitmap bitmap, String path) {
		ExifInterface ei = null;
		try {
			ei = new ExifInterface(path);
		} catch (IOException e) {
			e.printStackTrace();
		}

		int rotation = ei.getAttributeInt(ExifInterface.TAG_ORIENTATION, ExifInterface.ORIENTATION_NORMAL);
		switch (rotation) {
			case ExifInterface.ORIENTATION_ROTATE_90:
				return rotateBitmap(bitmap, 90f);
			case ExifInterface.ORIENTATION_ROTATE_180:
				return rotateBitmap(bitmap, 180f);
			case ExifInterface.ORIENTATION_ROTATE_270:
				return rotateBitmap(bitmap, 270f);
			default:
				return bitmap;
		}
	}

	private static Bitmap rotateBitmap(Bitmap bitmap, float angle) {
		Matrix matrix = new Matrix();
		matrix.preRotate(angle);
		return Bitmap.createBitmap(bitmap, 0, 0, bitmap.getWidth(), bitmap.getHeight(), matrix, false);
	}

	public static void getTextureFromPath(String imagePath) {
		if (imagePath.length() == 0) {
			onImageError("Image path is empty.");
			return;
		}
		File imgFile = new File(imagePath);
		if (!imgFile.exists()) {
			onImageError("Image path if not valid.");
			return;
		}
		String mimeType = URLConnection.guessContentTypeFromName(imgFile.getName());
		String type = mimeType.split("/")[0];

		if (!type.equals("image")) {
			onImageError("File type is not image.");
			return;
		}

		Bitmap bitmap = BitmapFactory.decodeFile(imagePath);
		int width = bitmap.getWidth();
		int height = bitmap.getHeight();

		onImageReady(getBitmapBytes(bitmap), width, height);

		bitmap.recycle();
	}

	private static void configureImagePicker(Activity activity, ImagePickerImpl picker) {
		int maxSize = getMaxImageSize(activity);
		picker.ensureMaxSize(maxSize, maxSize);
		picker.shouldGenerateThumbnails(shouldGenerateThumbnails(activity));
		picker.shouldGenerateTexture(shouldGenerateTexture(activity));
		picker.reinitialize(getPhotoOutputPath(activity));
	}

	private static int getMaxImageSize(Activity context) {
		return getPrefs(context).getInt(EXTRA_MAX_SIZE, 0);
	}

	private static boolean shouldGenerateThumbnails(Activity activity) {
		return getPrefs(activity).getBoolean(EXTRA_SHOULD_GENERATE_THUMBNAILS, true);
	}

	private static boolean shouldGenerateTexture(Activity activity) {
		return getPrefs(activity).getBoolean(EXTRAS_SHOULD_GET_TEXTURE, false);
	}

	private static SharedPreferences getPrefs(Activity context) {
		return context.getSharedPreferences(FILE_KEY, Context.MODE_PRIVATE);
	}

	private static String getPhotoOutputPath(Activity context) {
		return getPrefs(context).getString(EXTRAS_PHOTO_OUTPUT_PATH, null);
	}

	@SuppressLint("ApplySharedPref")
	private static void persistImagePickerSettings(Intent data, Activity context) {
		SharedPreferences.Editor editor = getPrefs(context).edit();
		if (data.hasExtra(EXTRA_MAX_SIZE)) {
			int maxSize = data.getIntExtra(EXTRA_MAX_SIZE, 0);
			editor.putInt(EXTRA_MAX_SIZE, maxSize);
		}
		if (data.hasExtra(EXTRA_SHOULD_GENERATE_THUMBNAILS)) {
			boolean genThumbnails = data.getBooleanExtra(EXTRA_SHOULD_GENERATE_THUMBNAILS, true);
			editor.putBoolean(EXTRA_SHOULD_GENERATE_THUMBNAILS, genThumbnails);
		}
		if (data.hasExtra(EXTRAS_SHOULD_GET_TEXTURE)) {
			boolean getTexture = data.getBooleanExtra(EXTRAS_SHOULD_GET_TEXTURE, false);
			editor.putBoolean(EXTRAS_SHOULD_GET_TEXTURE, getTexture);
		}
		if (data.hasExtra(EXTRAS_ALLOW_MULTIPLE)) {
			boolean allowMultiple = data.getBooleanExtra(EXTRAS_ALLOW_MULTIPLE, false);
			editor.putBoolean(EXTRAS_ALLOW_MULTIPLE, allowMultiple);
		}
		if (data.hasExtra(EXTRAS_PHOTO_OUTPUT_PATH)) {
			String photoOutputPath = data.getStringExtra(EXTRAS_PHOTO_OUTPUT_PATH);
			editor.putString(EXTRAS_PHOTO_OUTPUT_PATH, photoOutputPath);
		}
		editor.commit();
	}

	static byte[] getBitmapBytes(Bitmap bitmap) {
		int width = bitmap.getWidth();
		int height = bitmap.getHeight();
		int[] colors = new int[width * height];
		bitmap.getPixels(colors, 0, width, 0, 0, width, height);

		ByteBuffer byteBuffer = ByteBuffer.allocate(colors.length * 4);
		IntBuffer intBuffer = byteBuffer.asIntBuffer();
		intBuffer.put(colors);
		return byteBuffer.array();
	}

	private static void startGoodiesActivity(Activity activity, int quality, int maximumSize,
											 boolean shouldGenerateThumbnails, boolean shouldGetTexture, boolean allowMultiple, int pickerType) {
		Intent intent = new Intent(activity, AndroidGoodiesActivity.class);
		if (quality != UNUSED) {
			intent.putExtra(EXTRA_QUALITY, quality);
		}

		if (maximumSize != UNUSED) {
			intent.putExtra(EXTRA_MAX_SIZE, maximumSize);
		}

		intent.putExtra(EXTRA_SHOULD_GENERATE_THUMBNAILS, shouldGenerateThumbnails);
		intent.putExtra(EXTRAS_SHOULD_GET_TEXTURE, shouldGetTexture);
		intent.putExtra(EXTRAS_ALLOW_MULTIPLE, allowMultiple);
		intent.putExtra(AndroidGoodiesActivity.EXTRAS_PICKER_TYPE, pickerType);

		activity.startActivity(intent);
	}
}