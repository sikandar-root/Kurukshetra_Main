// Copyright (c) 2018 Nineva Studios

package com.ninevastudios.androidgoodies;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import androidx.annotation.Keep;

@Keep
public class AGDialog {
	@Keep
	private static DialogInterface.OnClickListener onPositiveButtonClickListener = new DialogInterface.OnClickListener() {
		@Override
		public void onClick(DialogInterface dialog, int which) {
			positiveButtonCallback();
		}
	};
	@Keep
	private static DialogInterface.OnClickListener onNegativeButtonClickListener = new DialogInterface.OnClickListener() {
		@Override
		public void onClick(DialogInterface dialog, int which) {
			negativeButtonCallback();
		}
	};
	@Keep
	private static DialogInterface.OnClickListener onNeutralButtonClickListener = new DialogInterface.OnClickListener() {
		@Override
		public void onClick(DialogInterface dialog, int which) {
			neutralButtonCallback();
		}
	};
	@Keep
	private static DialogInterface.OnClickListener onItemClickListener = new DialogInterface.OnClickListener() {
		@Override
		public void onClick(DialogInterface dialog, int which) {
			itemClickCallback(which);
		}
	};
	@Keep
	private static DialogInterface.OnClickListener onSingleChoiceItemClickListener = new DialogInterface.OnClickListener() {
		@Override
		public void onClick(DialogInterface dialog, int which) {
			singleChoiceItemClickCallback(which);
		}
	};
	@Keep
	private static DialogInterface.OnMultiChoiceClickListener onMultiChoiceClickListener = new DialogInterface.OnMultiChoiceClickListener() {
		@Override
		public void onClick(DialogInterface dialog, int which, boolean isChecked) {
			multiChoiceItemClickCallback(which, isChecked);
		}
	};
	@Keep
	private static DialogInterface.OnCancelListener onCancelListener = new DialogInterface.OnCancelListener() {
		@Override
		public void onCancel(DialogInterface dialog) {
			onCancelCallback();
		}
	};
	@Keep
	private static DialogInterface.OnDismissListener onDismissListener = new DialogInterface.OnDismissListener() {
		@Override
		public void onDismiss(DialogInterface dialog) {
			onDismissCallback();
		}
	};

	public static native void positiveButtonCallback();

	public static native void negativeButtonCallback();

	public static native void neutralButtonCallback();

	public static native void itemClickCallback(int index);

	public static native void singleChoiceItemClickCallback(int index);

	public static native void multiChoiceItemClickCallback(int index, boolean isChosen);

	public static native void onCancelCallback();

	public static native void onDismissCallback();

	@Keep
	public static void showDialog(final Activity activity, final AGDialogData dialogData) {
		activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				AlertDialog.Builder builder = new AlertDialog.Builder(activity, dialogData.theme);

				if (dialogData.title != null && !dialogData.title.isEmpty()) {
					builder.setTitle(dialogData.title);
				}

				if (dialogData.message != null && !dialogData.message.isEmpty()) {
					builder.setMessage(dialogData.message);
				}

				setButtons(dialogData, builder);
				setContent(dialogData, builder);

				final AlertDialog dialog = builder.create();
				setListeners(dialog);
				dialog.show();
			}
		});
	}

	@Keep
	public static void dismissDialog(final Activity activity, final AlertDialog dialog) {
		activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				dialog.dismiss();
			}
		});
	}

	@Keep
	private static void setButtons(AGDialogData dialogData, AlertDialog.Builder builder) {
		if (dialogData.positiveButtonText != null && !dialogData.positiveButtonText.equals("")) {
			builder.setPositiveButton(dialogData.positiveButtonText, onPositiveButtonClickListener);
		}
		if (dialogData.negativeButtonText != null && !dialogData.negativeButtonText.equals("")) {
			builder.setNegativeButton(dialogData.negativeButtonText, onNegativeButtonClickListener);
		}
		if (dialogData.neutralButtonText != null && !dialogData.neutralButtonText.equals("")) {
			builder.setNeutralButton(dialogData.neutralButtonText, onNeutralButtonClickListener);
		}
	}

	@Keep
	private static void setContent(AGDialogData dialogData, AlertDialog.Builder builder) {
		if (dialogData.items != null && dialogData.items.length > 0) {
			builder.setItems(dialogData.items, onItemClickListener);
		}
		if (dialogData.singleChoiceItems != null && dialogData.singleChoiceItems.length > 0) {
			builder.setSingleChoiceItems(dialogData.singleChoiceItems,
					dialogData.singleChoiceCheckedItem, onSingleChoiceItemClickListener);
		} else if (dialogData.multiChoiceItems != null && dialogData.multiChoiceItems.length > 0) {
			builder.setMultiChoiceItems(dialogData.multiChoiceItems, dialogData.multiChoiceCheckedItems,
					onMultiChoiceClickListener);
		}
	}

	@Keep
	private static void setListeners(AlertDialog dialog) {
		dialog.setOnCancelListener(onCancelListener);
		dialog.setOnDismissListener(onDismissListener);
	}
}
