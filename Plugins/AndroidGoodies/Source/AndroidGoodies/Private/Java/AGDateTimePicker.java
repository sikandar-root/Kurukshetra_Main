// Copyright (c) 2018 Nineva Studios

package com.ninevastudios.androidgoodies;

import android.app.Activity;
import android.app.DatePickerDialog;
import android.app.TimePickerDialog;
import android.content.DialogInterface;
import androidx.annotation.Keep;
import android.widget.DatePicker;
import android.widget.TimePicker;

@Keep
public class AGDateTimePicker {

	private static DatePickerDialog.OnDateSetListener datePickerListener = new DatePickerDialog.OnDateSetListener() {
		@Override
		public void onDateSet(DatePicker view, int selectedYear, int selectedMonth, int selectedDay) {
			AGDateTimePicker.onDateSet(selectedYear, selectedMonth + 1, selectedDay);
		}
	};
	private static TimePickerDialog.OnTimeSetListener timePickerListener = new TimePickerDialog.OnTimeSetListener() {
		@Override
		public void onTimeSet(TimePicker view, int hourOfDay, int minute) {
			AGDateTimePicker.onTimeSet(hourOfDay, minute);
		}
	};
	private static DialogInterface.OnCancelListener cancelListener = new DialogInterface.OnCancelListener() {
		@Override
		public void onCancel(DialogInterface dialog) {
			AGDateTimePicker.onCancel();
		}
	};

	public static native void onDateSet(int year, int month, int day);

	public static native void onTimeSet(int hourOfDay, int minute);

	public static native void onCancel();

	@Keep
	public static void showDatePicker(final Activity activity, final int year, final int month, final int day, final int theme) {
		activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				DatePickerDialog dialog = new DatePickerDialog(activity, theme, datePickerListener, year, month, day);
				dialog.setOnCancelListener(cancelListener);
				dialog.show();
			}
		});
	}

	@Keep
	public static void showDatePickerWithLimits(final Activity activity, final int year, final int month, final int day,
	                                            final long fromLimit, final long toLimit, final int theme) {
		activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				DatePickerDialog dialog = new DatePickerDialog(activity, theme, datePickerListener, year, month, day);
				dialog.setOnCancelListener(cancelListener);
				DatePicker datePicker = dialog.getDatePicker();
				datePicker.setMinDate(fromLimit);
				datePicker.setMaxDate(toLimit);
				dialog.show();
			}
		});
	}

	@Keep
	public static void showTimePicker(final Activity activity, final int hour, final int minute, final int theme, final boolean is24HourView) {
		activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				TimePickerDialog dialog = new TimePickerDialog(activity, theme, timePickerListener, hour, minute, is24HourView);
				dialog.setOnCancelListener(cancelListener);
				dialog.show();
			}
		});
	}
}
