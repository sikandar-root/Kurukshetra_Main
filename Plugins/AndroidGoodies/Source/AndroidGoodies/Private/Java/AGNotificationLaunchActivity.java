// Copyright (c) 2019 Nineva Studios

package com.ninevastudios.androidgoodies;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import androidx.annotation.Keep;
import android.view.Window;

public class AGNotificationLaunchActivity extends Activity {
	@Keep
	public static Intent lastIntent;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);

		lastIntent = getIntent();

		Intent newIntent = new Intent(this, getMainActivityClass());
		this.startActivity(newIntent);
		finish();
	}

	private Class<?> getMainActivityClass() {
		String packageName = this.getPackageName();
		Intent launchIntent = this.getPackageManager().getLaunchIntentForPackage(packageName);
		try {
			return Class.forName(launchIntent.getComponent().getClassName());
		} catch (Exception e) {
			return null;
		}
	}
}
