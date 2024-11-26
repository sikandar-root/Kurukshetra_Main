// Copyright (c) 2018 Nineva Studios

package com.ninevastudios.androidgoodies;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import androidx.annotation.Keep;

@Keep
public class AGProgressDialog {

	@Keep
	private static DialogInterface.OnCancelListener onCancelListener = new DialogInterface.OnCancelListener() {
		@Override
		public void onCancel(DialogInterface dialog) {
			// TODO
		}
	};
	@Keep
	private static DialogInterface.OnDismissListener onDismissListener = new DialogInterface.OnDismissListener() {
		@Override
		public void onDismiss(DialogInterface dialog) {
			// TODO
		}
	};
	private ProgressDialog _progressDialog;
	private Activity _activity;

	@Keep
	public AGProgressDialog(Activity activity) {
		_activity = activity;
	}

	@Keep
	public void show(final AGProgressDialogData progressDialogData) {
		_activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				_progressDialog = new ProgressDialog(_activity, progressDialogData.theme);

				_progressDialog.setCancelable(progressDialogData.isCancellable);
				_progressDialog.setIndeterminate(progressDialogData.isIndeterminate);
				_progressDialog.setTitle(progressDialogData.title);
				_progressDialog.setMessage(progressDialogData.message);
				_progressDialog.setProgress(progressDialogData.progress);
				_progressDialog.setMax(progressDialogData.maxValue);
				_progressDialog.setProgressStyle(progressDialogData.style);

				_progressDialog.setOnCancelListener(onCancelListener);
				_progressDialog.setOnDismissListener(onDismissListener);

				_progressDialog.show();
			}
		});
	}

	@Keep
	public void dismiss() {
		_activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				_progressDialog.dismiss();
			}
		});
	}

	@Keep
	public void setProgress(final int progress) {
		_activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				_progressDialog.setProgress(progress);
			}
		});
	}

	@Keep
	public void pause() {
		_activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (_progressDialog != null) {
					_progressDialog.hide();
				}
			}
		});

	}

	@Keep
	public void resume() {
		_activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (_progressDialog != null) {
					_progressDialog.show();
				}
			}
		});
	}
}
