package com.ninevastudios.androidgoodies;

import android.util.Log;

public class NinevaLogUtils {
	public static void logMethodCall(String methodName) {
		Log.d("AndroidGoodies", "> method: " + methodName);
	}

	public static void log(String message) {
		Log.d("AndroidGoodies", "> msg: " + message);
	}
}
