// Copyright (c) 2019 Nineva Studios

package com.ninevastudios.androidgoodies;

import static android.provider.Settings.ACTION_REQUEST_SCHEDULE_EXACT_ALARM;

import android.app.Activity;
import android.app.AlarmManager;
import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationChannelGroup;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.media.AudioAttributes;
import android.net.Uri;
import android.os.Build;
import android.provider.Settings;

import androidx.annotation.Keep;
import androidx.core.app.NotificationCompat;
import androidx.core.app.NotificationManagerCompat;
import androidx.core.app.Person;

import android.util.Log;

import java.io.File;
import java.nio.ByteBuffer;

@Keep
public class AGNotificationHelper {
	private final static String OPEN_WITH_NOTIFICATION_KEY = "openedWithNotification";

	@Keep
	public static NotificationCompat.Builder getNotificationBuilder(Activity context, String channelId, String[] additionalData) {
		NotificationCompat.Builder builder = new NotificationCompat.Builder(context, channelId);

		Intent launchIntent = new Intent(context, AGNotificationLaunchActivity.class);
		launchIntent.putExtra(OPEN_WITH_NOTIFICATION_KEY, true);
		for (int i = 0; i < additionalData.length; i += 2) {
			launchIntent.putExtra(additionalData[i], additionalData[i + 1]);
		}
		launchIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
		launchIntent.setAction("actionstring" + System.currentTimeMillis());
		PendingIntent pendingIntent = PendingIntent.getActivity(context, 17, launchIntent, PendingIntent.FLAG_IMMUTABLE);
		builder.setContentIntent(pendingIntent);

		return builder;
	}

	@Keep
	public static NotificationChannelGroup getNotificationChannelGroup(String id, String name) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
			return new NotificationChannelGroup(id, name);
		}

		return null;
	}

	@Keep
	public static NotificationChannel getNotificationChannel(String id, String name, int importance) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
			return new NotificationChannel(id, name, importance);
		}

		return null;
	}

	@Keep
	public static void notify(Activity activity, Notification notification, int id) {
		NotificationManagerCompat manager = NotificationManagerCompat.from(activity);
		manager.notify(id, notification);
	}

	@Keep
	public static int getIconId(Activity context, String fileName) {
		String defaultPackage = context.getPackageName();
		if (defaultPackage != null) {
			Log.d("AndroidGoodies", "Successfully got the package name");
			try {
				return context.getResources().getIdentifier(fileName, "drawable", context.getPackageName());
			} catch (Exception e) {
				return 0;
			}
		}

		Log.d("AndroidGoodies", "Could not get the package name. Returning 0.");
		return 0;
	}

	@Keep
	public static void createNotificationChannel(Activity activity, NotificationChannel channel) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
			NotificationManager manager = (NotificationManager) activity.getSystemService(Context.NOTIFICATION_SERVICE);
			if (manager != null) {
				manager.createNotificationChannel(channel);
				Log.d("AndroidGoodies", "Notification channel was created successfully.");
			} else {
				Log.d("AndroidGoodies", "Unable to get Notification Manager");
			}
		} else {
			Log.d("AndroidGoodies", "Notification channels are not supported on this device.");
		}
	}

	@Keep
	public static void createNotificationChannelGroup(Activity activity, NotificationChannelGroup group) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
			NotificationManager manager = (NotificationManager) activity.getSystemService(Context.NOTIFICATION_SERVICE);
			if (manager != null) {
				manager.createNotificationChannelGroup(group);
				Log.d("AndroidGoodies", "Notification channel group was created successfully.");
			} else {
				Log.d("AndroidGoodies", "Unable to get Notification Manager");
			}
		} else {
			Log.d("AndroidGoodies", "Notification channels are not supported on this device.");
		}
	}

	@Keep
	public static boolean wasAppOpenViaNotification() {
		if (AGNotificationLaunchActivity.lastIntent == null) {
			return false;
		}

		return AGNotificationLaunchActivity.lastIntent.getBooleanExtra(OPEN_WITH_NOTIFICATION_KEY, false);
	}

	@Keep
	public static NotificationCompat.Builder setNotificationColor(NotificationCompat.Builder builder, int color) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
			builder.setColor(color);
		}
		return builder;
	}

	@Keep
	public static NotificationCompat.Builder setNotificationLargeIcon(NotificationCompat.Builder builder,
																	  byte[] buffer, int width, int height) {

		builder.setLargeIcon(bitmapFromByteArray(buffer, width, height));

		return builder;
	}

	@Keep
	public static NotificationCompat.Builder setNotificationSound(NotificationCompat.Builder builder,
																  String path) {
		File file = new File(path);
		if (file.exists()) {
			builder.setSound(Uri.fromFile(file));
		}

		return builder;
	}

	@Keep
	public static void cancelNotification(Activity activity, int id) {
		NotificationManagerCompat manager = NotificationManagerCompat.from(activity);
		manager.cancel(id);
	}

	@Keep
	public static int getCurrentImportance(Activity activity) {
		NotificationManagerCompat manager = NotificationManagerCompat.from(activity);
		return manager.getImportance();
	}

	@Keep
	public static int getCurrentInterruptionFilter(Activity activity) {
		NotificationManager manager = (NotificationManager) activity.getSystemService(Context.NOTIFICATION_SERVICE);
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
			return manager.getCurrentInterruptionFilter();
		}

		return 0;
	}

	@Keep
	public static void setCurrentInterruptionFilter(Activity activity, int filter) {
		NotificationManager manager = (NotificationManager) activity.getSystemService(Context.NOTIFICATION_SERVICE);
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
			manager.setInterruptionFilter(filter);
		}
	}

	@Keep
	public static void cancelAllNotifications(Activity activity) {
		NotificationManagerCompat manager = NotificationManagerCompat.from(activity);
		manager.cancelAll();
	}

	@Keep
	public static void scheduleNotification(Activity activity, Notification notification, int id, long when) {
		Log.d("AndroidGoodies", "Scheduling notification, delay: " + when);
		AlarmManager alarmManager = (AlarmManager) activity.getSystemService(Context.ALARM_SERVICE);
		Intent intent = getIntentForNotification(activity, notification, id);
		int flags = PendingIntent.FLAG_UPDATE_CURRENT | PendingIntent.FLAG_IMMUTABLE;
		if (canScheduleExactAlarms(activity)) {
			alarmManager.setExact(AlarmManager.RTC_WAKEUP, System.currentTimeMillis() + when,
					PendingIntent.getBroadcast(activity, id, intent, flags));
		} else {
			alarmManager.set(AlarmManager.RTC_WAKEUP, System.currentTimeMillis() + when,
					PendingIntent.getBroadcast(activity, id, intent, flags));
		}
	}

	@Keep
	public static boolean canScheduleExactAlarms(Activity activity) {
		AlarmManager alarmManager = (AlarmManager) activity.getSystemService(Context.ALARM_SERVICE);
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S) {
			return alarmManager.canScheduleExactAlarms();
		} else {
			return true;
		}
	}

	@Keep
	public static void requestExactAlarmsPermission(Activity activity) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S) {
			activity.startActivity(new Intent(ACTION_REQUEST_SCHEDULE_EXACT_ALARM));
		} else {
			Log.d("AndroidGoodies", "No need to request permission on android " + Build.VERSION.SDK_INT);
		}
	}

	@Keep
	public static void scheduleRepeatingNotification(Activity activity, Notification notification, int id, long when, long repeatAfter) {
		Log.d("AndroidGoodies", "Delay: " + when);
		Log.d("AndroidGoodies", "Repeat after: " + repeatAfter);
		AlarmManager alarmManager = (AlarmManager) activity.getSystemService(Context.ALARM_SERVICE);
		Intent intent = getIntentForNotification(activity, notification, id);
		alarmManager.setRepeating(AlarmManager.RTC_WAKEUP, System.currentTimeMillis() + when, repeatAfter,
				PendingIntent.getBroadcast(activity, id, intent, PendingIntent.FLAG_UPDATE_CURRENT | PendingIntent.FLAG_IMMUTABLE));
	}

	@Keep
	public static void cancelScheduledNotification(Activity activity, int id) {
		AlarmManager alarmManager = (AlarmManager) activity.getSystemService(Context.ALARM_SERVICE);
		Intent intent = getIntentForNotification(activity, new Notification(), id);
		alarmManager.cancel(PendingIntent.getBroadcast(activity, id, intent, PendingIntent.FLAG_UPDATE_CURRENT | PendingIntent.FLAG_IMMUTABLE));
	}

	@Keep
	public static String getNotificationData(String key) {
		if (AGNotificationLaunchActivity.lastIntent == null) {
			return "";
		}

		if (AGNotificationLaunchActivity.lastIntent.hasExtra(key)) {
			return AGNotificationLaunchActivity.lastIntent.getStringExtra(key);
		}

		return "";
	}

	@Keep
	public static NotificationCompat.BigTextStyle getBigTextStyle(String bigText) {
		NotificationCompat.BigTextStyle style = new NotificationCompat.BigTextStyle();
		style.bigText(bigText);
		return style;
	}

	@Keep
	public static NotificationCompat.MessagingStyle getMessagingStyle(String userName) {
		Person person = new Person.Builder().setName(userName).build();
		return new NotificationCompat.MessagingStyle(person);
	}

	@Keep
	public static NotificationCompat.BigPictureStyle getBigPictureStyle(byte[] buffer, int width, int height) {
		NotificationCompat.BigPictureStyle style = new NotificationCompat.BigPictureStyle();
		style.bigPicture(bitmapFromByteArray(buffer, width, height));
		return style;
	}

	@Keep
	public static NotificationCompat.InboxStyle getInboxStyle() {
		return new NotificationCompat.InboxStyle();
	}

	@Keep
	public static NotificationCompat.BigPictureStyle setBigLargeIcon(NotificationCompat.BigPictureStyle style, byte[] buffer, int width, int height) {
		style.bigLargeIcon(bitmapFromByteArray(buffer, width, height));
		return style;
	}

	@Keep
	public static void setChannelSound(NotificationChannel channel, String soundPath, int contentType, int usage, int flags) {
		if (android.os.Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
			AudioAttributes attributes = new AudioAttributes.Builder()
					.setUsage(usage)
					.setFlags(flags)
					.setContentType(contentType)
					.build();

			File sound = new File(soundPath);
			if (sound.exists()) {
				Log.d("AndroidGoodies", "Sound file exists. Setting it to Notification channel.");
				channel.setSound(Uri.fromFile(sound), attributes);
			} else {
				Log.d("AndroidGoodies", "Sound file does not exist. Will not SetSound for the notification channel.");
			}
		}
	}

	@Keep
	public static NotificationChannel findNotificationChannel(Activity activity, String id) {
		NotificationManager manager = (NotificationManager) activity.getSystemService(Context.NOTIFICATION_SERVICE);
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
			return manager.getNotificationChannel(id);
		}

		return null;
	}

	@Keep
	public static NotificationChannel[] getNotificationChannels(Activity activity) {
		NotificationManager manager = (NotificationManager) activity.getSystemService(Context.NOTIFICATION_SERVICE);
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
			return manager.getNotificationChannels().toArray(new NotificationChannel[0]);
		}

		return null;
	}

	@Keep
	public static NotificationChannelGroup[] getNotificationChannelGroups(Activity activity) {
		NotificationManager manager = (NotificationManager) activity.getSystemService(Context.NOTIFICATION_SERVICE);
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
			return manager.getNotificationChannelGroups().toArray(new NotificationChannelGroup[0]);
		}

		return null;
	}


	@Keep
	public static NotificationChannelGroup findNotificationChannelGroup(Activity activity, String id) {
		NotificationManager manager = (NotificationManager) activity.getSystemService(Context.NOTIFICATION_SERVICE);
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
			return manager.getNotificationChannelGroup(id);
		}

		return null;
	}

	@Keep
	public static void deleteNotificationChannel(Activity activity, String id) {
		NotificationManager manager = (NotificationManager) activity.getSystemService(Context.NOTIFICATION_SERVICE);
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
			manager.deleteNotificationChannel(id);
		}
	}

	@Keep
	public static void deleteNotificationChannelGroup(Activity activity, String id) {
		NotificationManager manager = (NotificationManager) activity.getSystemService(Context.NOTIFICATION_SERVICE);
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
			manager.deleteNotificationChannelGroup(id);
		}
	}

	@Keep
	public static NotificationCompat.Builder addOpenUrlAction(Activity context,
															  NotificationCompat.Builder builder,
															  String iconName,
															  String title,
															  String url) {
		Uri uri = Uri.parse(url);
		Intent intent = new Intent(Intent.ACTION_VIEW);
		intent.setData(uri);

		int iconId = getIconId(context, iconName);

		PendingIntent pendingIntent = PendingIntent.getActivity(context, 17, intent, PendingIntent.FLAG_UPDATE_CURRENT | PendingIntent.FLAG_IMMUTABLE);

		NotificationCompat.Action action = new NotificationCompat.Action.Builder(iconId, title, pendingIntent)
				.build();

		builder.addAction(action);

		return builder;
	}

	@Keep
	public static void openNotificationChannelSettings(Activity activity, String id) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O && findNotificationChannel(activity, id) != null) {
			Intent intent = new Intent(Settings.ACTION_CHANNEL_NOTIFICATION_SETTINGS);
			intent.putExtra(Settings.EXTRA_APP_PACKAGE, activity.getApplicationContext().getPackageName());
			intent.putExtra(Settings.EXTRA_CHANNEL_ID, id);
			activity.startActivity(intent);
		}
	}

	private static Intent getIntentForNotification(Activity activity, Notification notification, int id) {
		Intent intent = new Intent(activity, NotificationBroadcastReceiver.class);
		intent.putExtra("notification", notification);
		intent.putExtra("id", id);
		intent.putExtra("tag", "tag");
		return intent;
	}

	private static Bitmap bitmapFromByteArray(byte[] buffer, int width, int height) {
		Bitmap bitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
		ByteBuffer byteBuffer = ByteBuffer.wrap(buffer);
		bitmap.copyPixelsFromBuffer(byteBuffer);
		return bitmap;
	}
}
