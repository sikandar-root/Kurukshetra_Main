package com.ninevastudios.androidgoodies;

import android.app.Notification;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import androidx.core.app.NotificationManagerCompat;
import android.util.Log;

public class NotificationBroadcastReceiver extends BroadcastReceiver {
	@Override
	public void onReceive(Context context, Intent intent) {
		Log.d("AndroidGoodies", "OnBroadcastReceived");
		Notification notification = intent.getParcelableExtra("notification");
		int id = intent.getIntExtra("id", 0);
		String tag = intent.getStringExtra("tag");

		NotificationManagerCompat.from(context).notify(tag, id, notification);
	}
}
