// Copyright (c) 2020 Nineva Studios

package com.ninevastudios.googleplay;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.util.Log;

import com.google.android.gms.common.images.ImageManager;

import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class GPUtils {

	interface OnLoadImageCallback {
		void run(byte[] buffer, int width, int height, String imageUri);
	}

	public static void loadImage(final Activity activity, final Uri image, final OnLoadImageCallback callback) {
		activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				ImageManager manager = ImageManager.create(activity);
				manager.loadImage(new ImageManager.OnImageLoadedListener() {
					@Override
					public void onImageLoaded(Uri uri, Drawable drawable, boolean isRequestedDrawable) {
						if (isRequestedDrawable) {
							Bitmap bitmap = null;

							if (drawable instanceof BitmapDrawable) {
								BitmapDrawable bitmapDrawable = (BitmapDrawable) drawable;
								if (bitmapDrawable.getBitmap() != null) {
									bitmap = bitmapDrawable.getBitmap();
								}
							} else {
								if (drawable.getIntrinsicWidth() <= 0 || drawable.getIntrinsicHeight() <= 0) {
									bitmap = Bitmap.createBitmap(1, 1, Bitmap.Config.ARGB_8888); // Single color bitmap will be created of 1x1 pixel
								} else {
									bitmap = Bitmap.createBitmap(drawable.getIntrinsicWidth(), drawable.getIntrinsicHeight(), Bitmap.Config.ARGB_8888);
								}

								Canvas canvas = new Canvas(bitmap);
								drawable.setBounds(0, 0, canvas.getWidth(), canvas.getHeight());
								drawable.draw(canvas);
							}

							if (bitmap != null) {
								int width = bitmap.getWidth();
								int height = bitmap.getHeight();
								int[] colors = new int[width * height];
								bitmap.getPixels(colors, 0, width, 0, 0, width, height);

								ByteBuffer byteBuffer = ByteBuffer.allocate(colors.length * 4);
								IntBuffer intBuffer = byteBuffer.asIntBuffer();
								intBuffer.put(colors);

								callback.run(byteBuffer.array(), width, height, uri.toString());
							} else {
								Log.d("GooglePlayGoodies", "Cannot retrieve image");
							}
						}
					}
				}, image);
			}
		});
	}

}
