// Copyright (c) 2018 Nineva Studios

package com.ninevastudios.androidgoodies;

import android.app.Activity;
import android.content.Intent;
import android.provider.AlarmClock;
import androidx.annotation.Keep;

import java.util.ArrayList;

@Keep
public class AGAlarmClock {
	@Keep
	public static void setAlarm(Activity activity, int hour, int minute, String message, int[] days, boolean vibrate, boolean skipUi) {
		Intent alarmIntent = new Intent(AlarmClock.ACTION_SET_ALARM)
				.putExtra(AlarmClock.EXTRA_HOUR, hour)
				.putExtra(AlarmClock.EXTRA_MINUTES, minute)
				.putExtra(AlarmClock.EXTRA_MESSAGE, message)
				.putExtra(AlarmClock.EXTRA_VIBRATE, vibrate)
				.putExtra(AlarmClock.EXTRA_SKIP_UI, skipUi)
				.putExtra(AlarmClock.EXTRA_DAYS, createDaysList(days));

		activity.startActivity(alarmIntent);
	}

	@Keep
	public static void showAllAlarms(Activity activity) {
		Intent showAlarmsIntent = new Intent(AlarmClock.ACTION_SHOW_ALARMS);

		activity.startActivity(showAlarmsIntent);
	}

	@Keep
	public static void snoozeAlarm(Activity activity, int snoozeDurationMinutes) {
		Intent snoozeIntent = new Intent(AlarmClock.ACTION_SNOOZE_ALARM)
				.putExtra(AlarmClock.EXTRA_ALARM_SNOOZE_DURATION, snoozeDurationMinutes);

		activity.startActivity(snoozeIntent);
	}

	@Keep
	public static boolean canSetAlarm(Activity activity) {
		Intent showAlarmsIntent = new Intent(AlarmClock.ACTION_SHOW_ALARMS);

		try {
			showAlarmsIntent.resolveActivity(activity.getPackageManager());
			return true;
		} catch (Exception e) {
			return false;
		}
	}

	@Keep
	public static void setTimer(Activity activity, int lengthSeconds, String message, boolean skipUi) {
		Intent timerIntent = new Intent(AlarmClock.ACTION_SET_TIMER)
				.putExtra(AlarmClock.EXTRA_LENGTH, lengthSeconds)
				.putExtra(AlarmClock.EXTRA_MESSAGE, message)
				.putExtra(AlarmClock.EXTRA_SKIP_UI, skipUi);

		activity.startActivity(timerIntent);
	}

	@Keep
	public static void showAllTimers(Activity activity) {
		Intent showTimersIntent = new Intent(AlarmClock.ACTION_SHOW_TIMERS);

		activity.startActivity(showTimersIntent);
	}

	@Keep
	public static boolean canSetTimer(Activity activity) {
		Intent showTimersIntent = new Intent(AlarmClock.ACTION_SHOW_TIMERS);

		try {
			showTimersIntent.resolveActivity(activity.getPackageManager());
			return true;
		} catch (Exception e) {
			return false;
		}
	}

	private static ArrayList<Integer> createDaysList(int[] days) {
		ArrayList<Integer> daysList = new ArrayList<>();
		for (int day : days) {
			daysList.add(day);
		}

		return daysList;
	}
}
