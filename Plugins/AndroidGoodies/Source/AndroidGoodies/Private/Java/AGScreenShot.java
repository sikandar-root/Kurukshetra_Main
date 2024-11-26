// Copyright (c) 2019 Nineva Studios

package com.ninevastudios.androidgoodies;

import android.annotation.TargetApi;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.hardware.display.DisplayManager;
import android.media.projection.MediaProjectionManager;
import android.os.Build;
import androidx.annotation.Keep;

public class AGScreenShot {

	static final int CODE_TAKE_SCREENSHOT = 100500;
	static final String EXTRA_SCREENSHOT = "EXTRA_SCREENSHOT";
	private static final int VIRTUAL_DISPLAY_FLAGS = DisplayManager.VIRTUAL_DISPLAY_FLAG_OWN_CONTENT_ONLY | DisplayManager.VIRTUAL_DISPLAY_FLAG_PUBLIC;
	static MediaProjectionManager projectionManager;

	@TargetApi(Build.VERSION_CODES.LOLLIPOP)
	@Keep
	public static void takeScreenShot(Activity context) {
		projectionManager = (MediaProjectionManager) context.getSystemService(Context.MEDIA_PROJECTION_SERVICE);

		Intent intent = new Intent(context, AndroidGoodiesActivity.class);
		intent.putExtra(EXTRA_SCREENSHOT, true);
		context.startActivity(intent);
	}

	@TargetApi(Build.VERSION_CODES.LOLLIPOP)
	static void takeShotInternal(Context context, Intent data) {
//		final MediaProjection mediaProjection = projectionManager.getMediaProjection(Activity.RESULT_OK, data);
//		if (mediaProjection == null) {
//			AGImagePicker.onImageReceiveError("Could not get Media Projection");
//			return;
//		}
//
//		WindowManager wm = (WindowManager) context.getSystemService(Context.WINDOW_SERVICE);
//		if(wm == null) {
//			AGImagePicker.onImageReceiveError("Could not get Window Manager");
//			return;
//		}
//
//		Display display = wm.getDefaultDisplay();
//		final DisplayMetrics metrics = new DisplayMetrics();
//		display.getMetrics(metrics);
//		Point size = new Point();
//		display.getRealSize(size);
//		final int mWidth = size.x;
//		final int mHeight = size.y;
//		int mDensity = metrics.densityDpi;
//		final boolean isPortrait = mHeight > mWidth;
//
//		final ImageReader mImageReader = ImageReader.newInstance(mWidth, mHeight, PixelFormat.RGBA_8888, 2);
//
//		final Handler handler = new Handler();
//
//		mediaProjection.createVirtualDisplay("screen-mirror", mWidth, mHeight, mDensity, VIRTUAL_DISPLAY_FLAGS, mImageReader.getSurface(), null, handler);
//
//		mImageReader.setOnImageAvailableListener(new ImageReader.OnImageAvailableListener() {
//			@Override
//			public void onImageAvailable(ImageReader reader) {
//				reader.setOnImageAvailableListener(null, handler);
//				Image image;
//				Bitmap tempBmp;
//				try {
//					image = reader.acquireLatestImage();
//					int deviceWidth = metrics.widthPixels;
//					int deviceHeight = metrics.heightPixels;
//					if (deviceHeight > deviceWidth != isPortrait) {
//						//noinspection SuspiciousNameCombination
//						deviceWidth = metrics.heightPixels;
//						//noinspection SuspiciousNameCombination
//						deviceHeight = metrics.widthPixels;
//					}
//
//					final Image.Plane[] planes = image.getPlanes();
//					final ByteBuffer buffer = planes[0].getBuffer();
//					int pixelStride = planes[0].getPixelStride();
//					int rowStride = planes[0].getRowStride();
//					int rowPadding = rowStride - pixelStride * deviceWidth;
//
//					tempBmp = Bitmap.createBitmap(
//							deviceWidth + (int) ((float) rowPadding / (float) pixelStride),
//							deviceHeight, Bitmap.Config.ARGB_8888);
//					tempBmp.copyPixelsFromBuffer(buffer);
//
//					image.close();
//					reader.close();
//
//					Bitmap result = trim(tempBmp);
//
//					AGImagePicker.onImageReceived(AGImagePicker.getBitmapBytes(result), result.getWidth(), result.getHeight());
//				} catch (Throwable e) {
//					AGImagePicker.onImageReceiveError(e.getMessage());
//				} finally {
//					mImageReader.close();
//					mediaProjection.stop();
//				}
//			}
//		}, handler);
	}

	static Bitmap trim(Bitmap source) {
		int firstX = 0, firstY = 0;
		int lastX = source.getWidth();
		int lastY = source.getHeight();
		int[] pixels = new int[source.getWidth() * source.getHeight()];
		source.getPixels(pixels, 0, source.getWidth(), 0, 0, source.getWidth(), source.getHeight());
		loop:
		for (int x = 0; x < source.getWidth(); x++) {
			for (int y = 0; y < source.getHeight(); y++) {
				if (pixels[x + (y * source.getWidth())] != Color.TRANSPARENT) {
					firstX = x;
					break loop;
				}
			}
		}
		loop:
		for (int y = 0; y < source.getHeight(); y++) {
			for (int x = firstX; x < source.getWidth(); x++) {
				if (pixels[x + (y * source.getWidth())] != Color.TRANSPARENT) {
					firstY = y;
					break loop;
				}
			}
		}
		loop:
		for (int x = source.getWidth() - 1; x >= firstX; x--) {
			for (int y = source.getHeight() - 1; y >= firstY; y--) {
				if (pixels[x + (y * source.getWidth())] != Color.TRANSPARENT) {
					lastX = x;
					break loop;
				}
			}
		}
		loop:
		for (int y = source.getHeight() - 1; y >= firstY; y--) {
			for (int x = source.getWidth() - 1; x >= firstX; x--) {
				if (pixels[x + (y * source.getWidth())] != Color.TRANSPARENT) {
					lastY = y;
					break loop;
				}
			}
		}
		return Bitmap.createBitmap(source, firstX, firstY, lastX - firstX, lastY - firstY);
	}
}
