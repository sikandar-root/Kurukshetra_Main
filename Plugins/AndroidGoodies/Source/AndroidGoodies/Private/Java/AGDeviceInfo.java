// Copyright (c) 2018 Nineva Studios

package com.ninevastudios.androidgoodies;

import android.app.Activity;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.Context;
import android.content.pm.InstallSourceInfo;
import android.text.TextUtils;
import android.os.Build;
import android.provider.Settings;

import androidx.annotation.Keep;

import java.util.List;

@Keep
public class AGDeviceInfo {

	@Keep
	public static String getBaseOs() {
		return Build.VERSION.BASE_OS;
	}

	@Keep
	public static String getCodeName() {
		return Build.VERSION.CODENAME;
	}

	@Keep
	public static String getRelease() {
		return Build.VERSION.RELEASE;
	}

	@Keep
	public static int getSdkInt() {
		return Build.VERSION.SDK_INT;
	}

	@Keep
	public static String getBoard() {
		return Build.BOARD;
	}

	@Keep
	public static String getBootloader() {
		return Build.BOOTLOADER;
	}

	@Keep
	public static String getBrand() {
		return Build.BRAND;
	}

	@Keep
	public static String getDevice() {
		return Build.DEVICE;
	}

	@Keep
	public static String getDisplay() {
		return Build.DISPLAY;
	}

	@Keep
	public static String getHardware() {
		return Build.HARDWARE;
	}

	@Keep
	public static String getManufacturer() {
		return Build.MANUFACTURER;
	}

	@Keep
	public static String getModel() {
		return Build.MODEL;
	}

	@Keep
	public static String getProduct() {
		return Build.PRODUCT;
	}

	@Keep
	public static String getRadio() {
		return Build.getRadioVersion();
	}

	@Keep
	public static String getSerial() {
		return Build.SERIAL;
	}

	@Keep
	public static String getTags() {
		return Build.TAGS;
	}

	@Keep
	public static String getType() {
		return Build.TYPE;
	}

	@Keep
	public static String getApplicationPackageName(Activity activity) {
		return activity.getPackageName();
	}

	@Keep
	public static boolean isPackageInstalled(Activity activity, String packageName) {
		try {
			activity.getPackageManager().getPackageInfo(packageName, PackageManager.GET_ACTIVITIES);
			return true;
		} catch (Exception e) {
			return false;
		}
	}

	@Keep
	public static PackageInfo[] getInstalledPackages(Activity activity) {
		List<PackageInfo> list = activity.getPackageManager().getInstalledPackages(0);
		return list.toArray(new PackageInfo[0]);
	}

	@Keep
	public static String getAndroidId(Activity activity) {
		return Settings.Secure.getString(activity.getContentResolver(), Settings.Secure.ANDROID_ID);
	}

	@Keep
	public static boolean hasSystemFeature(Activity activity, String featureName) {
		return activity.getPackageManager().hasSystemFeature(featureName);
	}

	@Keep
	public static String GetInstallSourceAndroid(Context context) {
		try {
			String packageName = context.getPackageName();
			PackageManager pm = context.getPackageManager();
			//android >= 10
			if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
				InstallSourceInfo info = pm.getInstallSourceInfo(packageName);
				if (info != null && info.getInstallingPackageName() != null) {
					return info.getInstallingPackageName();
				}
			} else if (pm.getInstallerPackageName(packageName) != null) {
				return pm.getInstallerPackageName(packageName);
			}
		} catch (PackageManager.NameNotFoundException e) {
		}
		return "";
	}
}
