// Copyright (c) 2018 Nineva Studios

package com.ninevastudios.androidgoodies;

import android.app.Activity;
import androidx.annotation.Keep;
import android.widget.Toast;

@Keep
public class AGToast {
	@Keep
	public static void showToast(final Activity activity, final String text, final int duration) {
		activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				Toast.makeText(activity, text, duration).show();
			}
		});
	}
}
