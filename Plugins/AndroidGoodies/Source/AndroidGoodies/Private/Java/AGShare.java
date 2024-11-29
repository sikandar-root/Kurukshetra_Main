// Copyright (c) 2018 Nineva Studios

package com.ninevastudios.androidgoodies;

import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.net.Uri;
import android.os.Build;

import androidx.annotation.Keep;
import androidx.annotation.NonNull;
import androidx.core.content.FileProvider;

import android.telephony.SmsManager;
import android.widget.Toast;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

@Keep
@SuppressWarnings("unused")
public class AGShare {
	private static final int maxSmsLength = 140;
	private static final String mimeTypeTextPlain = "text/plain";
	private static final String mimeTypeImageAll = "image/*";
	private static final String mimeTypeVideoAll = "video/*";
	private static final String mimeTypeAllFiles = "*/*";
	private static final String extraSmsBody = "sms_body";
	private static final String extraAddress = "address";
	private static final String twitterPackageName = "com.twitter.android";
	private static final String twitterUrl = "https://twitter.com/intent/tweet?text=";
	private static final String facebookPackageName = "com.facebook.katana";
	private static final String whatsAppPackageName = "com.whatsapp";
	private static final String instagramPackageName = "com.instagram.android";
	private static final String telegramPackageName = "org.telegram.messenger";
	private static final String viberPackageName = "com.viber.voip";

	@Keep
	public static void shareText(Activity activity, String subject, String textBody,
								 boolean withChooser, String chooserTitle) {
		launchShareIntent(activity, withChooser, chooserTitle,
				createShareTextIntent(subject, textBody));
	}

	@Keep
	public static void shareImage(Activity activity, String imagePath, boolean withChooser,
								  String chooserTitle) {
		launchShareIntent(activity, withChooser, chooserTitle,
				createShareImageIntent(activity, imagePath));
	}

	@Keep
	public static void shareTextWithImage(Activity activity, String subject, String textBody,
										  String imagePath, boolean withChooser, String chooserTitle) {
		launchShareIntent(activity, withChooser, chooserTitle,
				createShareTextWithImageIntent(activity, subject, textBody, imagePath));
	}

	@Keep
	public static void shareVideo(final Activity activity, final String videoPath, final boolean withChooser,
								  final String chooserTitle) {
		activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				launchShareIntent(activity, withChooser, chooserTitle, createShareVideoIntent(activity, videoPath));
			}
		});
	}

	@Keep
	public static void sendSmsViaMessagingApp(Activity activity, String phoneNumber, String message,
											  boolean withChooser, String chooserTitle) {
		launchShareIntent(activity, withChooser, chooserTitle,
				createSmsIntent(phoneNumber, message));
	}

	@Keep
	public static void sendSmsDirectly(String phoneNumber, String message) {
		SmsManager smsManager = SmsManager.getDefault();
		if (message.length() <= maxSmsLength) {
			smsManager.sendTextMessage(phoneNumber, null, message, null, null);
		} else {
			ArrayList<String> messages = smsManager.divideMessage(message);
			smsManager.sendMultipartTextMessage(phoneNumber, null, messages, null, null);
		}
	}

	@Keep
	public static void sendEMail(Activity activity, String subject, String textBody, String imagePath,
								 String[] recipients, String[] cc, String[] bcc,
								 boolean withChooser, String chooserTitle) {
		Intent intent = createMultiImageEMailIntent(subject, textBody, recipients, cc, bcc);
		launchEmailActivity(activity, imagePath, new String[0], withChooser, chooserTitle, intent);
	}

	@Keep
	public static void sendMultipleImagesEMail(Activity activity, String subject, String imagePath, String[] extraImagePaths,
											   String[] recipients, String[] cc, String[] bcc, boolean withChooser, String chooserTitle) {

		Intent intent = createMultiImageEMailIntent(subject, null, recipients, cc, bcc);
		launchEmailActivity(activity, imagePath, extraImagePaths, withChooser, chooserTitle, intent);
	}

	private static void launchEmailActivity(Activity activity, String imagePath, String[] extraImagePaths, boolean withChooser, String chooserTitle, Intent intent) {
		if (!imagePath.isEmpty() || extraImagePaths.length > 0) {
			ArrayList<Uri> paths = new ArrayList<>();

			if (!imagePath.isEmpty()) {
				Uri singlePath = FileProvider.getUriForFile(activity, getAuthority(activity), new File(imagePath));
				paths.add(singlePath);
			}
			for (String extraImagePath : extraImagePaths) {
				Uri arrayPath = FileProvider.getUriForFile(activity, getAuthority(activity), new File(extraImagePath));
				paths.add(arrayPath);
			}

			intent.putParcelableArrayListExtra(Intent.EXTRA_STREAM, paths);
		}

		try {
			launchShareIntent(activity, withChooser, chooserTitle, intent);
		} catch (Exception e) {
			NinevaUtils.log(e.getMessage());
		}
	}

	@Keep
	public static void tweetText(Activity activity, String message) {
		if (AGDeviceInfo.isPackageInstalled(activity, twitterPackageName)) {
			tweet(activity, createTweetIntent(message));
		} else {
			openTwitterUrl(activity, message);
		}
	}

	@Keep
	public static void tweetTextWithImage(Activity activity, String message, String imagePath) {
		if (AGDeviceInfo.isPackageInstalled(activity, twitterPackageName)) {
			Uri path = FileProvider.getUriForFile(activity, getAuthority(activity), new File(imagePath));

			Intent intent = createTweetIntent(message)
					.setType(mimeTypeAllFiles)
					.putExtra(Intent.EXTRA_STREAM, path);
			tweet(activity, intent);
		} else {
			openTwitterUrl(activity, message);
		}
	}

	@Keep
	public static void sendFacebookText(Activity activity, String message) {
		sendTextMessage(activity, message, facebookPackageName);
	}

	@Keep
	public static void sendFacebookImage(Activity activity, String imagePath) {
		sendImage(activity, imagePath, facebookPackageName);
	}

	@Keep
	public static void sendWhatsAppText(Activity activity, String message) {
		sendTextMessage(activity, message, whatsAppPackageName);
	}

	@Keep
	public static void sendWhatsAppImage(Activity activity, String imagePath) {
		sendImage(activity, imagePath, whatsAppPackageName);
	}

	@Keep
	public static void sendInstagramText(Activity activity, String message) {
		sendTextMessage(activity, message, instagramPackageName);
	}

	@Keep
	public static void sendInstagramImage(Activity activity, String imagePath) {
		sendImage(activity, imagePath, instagramPackageName);
	}

	@Keep
	public static void sendTelegramText(Activity activity, String message) {
		sendTextMessage(activity, message, telegramPackageName);
	}

	@Keep
	public static void sendTelegramImage(Activity activity, String imagePath) {
		sendImage(activity, imagePath, telegramPackageName);
	}

	@Keep
	public static void sendViberText(Activity activity, String message) {
		sendTextMessage(activity, message, viberPackageName);
	}

	@Keep
	public static void sendViberImage(Activity activity, String imagePath) {
		sendImage(activity, imagePath, viberPackageName);
	}

	@Keep
	public static String getCacheDirectory(Activity activity) {
		return activity.getCacheDir().getAbsolutePath();
	}

	private static Intent createShareTextIntent(String subject, String textBody) {
		return new Intent(Intent.ACTION_SEND)
				.setType(mimeTypeTextPlain)
				.putExtra(Intent.EXTRA_SUBJECT, subject)
				.putExtra(Intent.EXTRA_TEXT, textBody);
	}

	private static Intent createShareImageIntent(Activity activity, String imagePath) {
		Uri path = FileProvider.getUriForFile(activity, getAuthority(activity), new File(imagePath));

		return new Intent(Intent.ACTION_SEND)
				.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION)
				.setType(mimeTypeImageAll)
				.putExtra(Intent.EXTRA_STREAM, path);
	}

	private static Intent createShareTextWithImageIntent(Activity activity, String subject, String textBody, String imagePath) {
		Uri path = FileProvider.getUriForFile(activity, getAuthority(activity), new File(imagePath));

		return new Intent(Intent.ACTION_SEND)
				.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION)
				.setType(mimeTypeAllFiles)
				.putExtra(Intent.EXTRA_STREAM, path)
				.putExtra(Intent.EXTRA_SUBJECT, subject)
				.putExtra(Intent.EXTRA_TEXT, textBody);
	}

	private static Intent createShareVideoIntent(Activity activity, String videoPath) {
		Uri path = FileProvider.getUriForFile(activity, getAuthority(activity), new File(videoPath));

		return new Intent(Intent.ACTION_SEND)
				.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION)
				.setType(mimeTypeVideoAll)
				.putExtra(Intent.EXTRA_STREAM, path);
	}

	@NonNull
	public static String getAuthority(Activity activity) {
		return activity.getPackageName() + "." + AGFileProvider.class.getSimpleName();
	}

	private static Intent createSmsIntent(String phoneNumber, String message) {
		Intent intent = new Intent(Intent.ACTION_VIEW);
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) {
			intent.setData(Uri.parse("sms:" + phoneNumber));
		} else {
			intent.setType("vnd.android-dir/mms-sms");
			intent.putExtra(extraAddress, phoneNumber);
		}
		intent.putExtra(extraSmsBody, message);
		return intent;
	}

	private static Intent createEMailIntent(String subject, String textBody, String[] recipients,
											String[] cc, String[] bcc) {
		return new Intent(Intent.ACTION_SENDTO, Uri.parse("mailto:"))
				.putExtra(Intent.EXTRA_SUBJECT, subject)
				.putExtra(Intent.EXTRA_TEXT, textBody)
				.putExtra(Intent.EXTRA_EMAIL, recipients)
				.putExtra(Intent.EXTRA_CC, cc)
				.putExtra(Intent.EXTRA_BCC, bcc);
	}

	private static Intent createMultiImageEMailIntent(String subject, String textBody, String[] recipients,
													  String[] cc, String[] bcc) {

		return new Intent(Intent.ACTION_SEND_MULTIPLE)
				.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION)
				.setData(Uri.parse("mailto:"))
				.setType("plain/text")
				.putExtra(Intent.EXTRA_SUBJECT, subject)
				.putExtra(Intent.EXTRA_TEXT, textBody)
				.putExtra(Intent.EXTRA_EMAIL, recipients)
				.putExtra(Intent.EXTRA_CC, cc)
				.putExtra(Intent.EXTRA_BCC, bcc);
	}

	private static void openTwitterUrl(Activity activity, String message) {
		Uri uri = Uri.parse(twitterUrl + Uri.encode(message));
		activity.startActivity(new Intent(Intent.ACTION_VIEW, uri));
	}

	private static Intent createTweetIntent(String textBody) {
		return new Intent(Intent.ACTION_SEND)
				.setType(mimeTypeTextPlain)
				.putExtra(Intent.EXTRA_TEXT, textBody);
	}

	private static void sendTextMessage(Activity activity, String message, String packageName) {
		if (AGDeviceInfo.isPackageInstalled(activity, packageName)) {
			Intent intent = new Intent(Intent.ACTION_SEND)
					.setType(mimeTypeTextPlain)
					.putExtra(Intent.EXTRA_TEXT, message)
					.setPackage(packageName);
			activity.startActivity(intent);
		} else {
			showPackageNotFoundToast(activity, packageName);
		}
	}

	private static void sendImage(Activity activity, String imagePath, String packageName) {
		if (AGDeviceInfo.isPackageInstalled(activity, packageName)) {
			Intent intent = createShareImageIntent(activity, imagePath)
					.setPackage(packageName);
			activity.startActivity(intent);
		} else {
			showPackageNotFoundToast(activity, packageName);
		}
	}

	private static void showPackageNotFoundToast(Activity activity, String packageName) {
		String log = "Can't send item because " + packageName + " is not installed";
		AGToast.showToast(activity, log, Toast.LENGTH_SHORT);
	}

	private static void launchShareIntent(Activity activity, boolean withChooser, String chooserTitle, Intent intent) {
		if (withChooser) {
			Intent chooserIntent = Intent.createChooser(intent, chooserTitle);
			activity.startActivity(chooserIntent);
		} else {
			activity.startActivity(intent);
		}
	}

	private static void tweet(Activity activity, Intent tweetIntent) {
		final PackageManager packageManager = activity.getPackageManager();
		final List<ResolveInfo> resolveInfoList = packageManager.queryIntentActivities(tweetIntent, PackageManager.MATCH_DEFAULT_ONLY);

		for (ResolveInfo resolveInfo : resolveInfoList) {
			if (resolveInfo.activityInfo.packageName.startsWith(twitterPackageName) && resolveInfo.activityInfo.name.toLowerCase().contains("composer")) {
				tweetIntent.setClassName(resolveInfo.activityInfo.packageName, resolveInfo.activityInfo.name);
				activity.startActivity(tweetIntent);
			}
		}
	}
}
