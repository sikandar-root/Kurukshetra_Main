package com.ninevastudios.androidgoodies;

import android.net.wifi.ScanResult;
import android.os.Build;

public class AScanResult {

	public ScanResult mScanResult = null;

	public AScanResult(ScanResult scanResult) {
		mScanResult = scanResult;
	}

	public String getBSSID() {
		return mScanResult != null ? mScanResult.BSSID : "";
	}

	public String getSSID() {
		return mScanResult != null ? mScanResult.SSID : "";
	}

	public String getCapabilities() { return mScanResult != null ? mScanResult.capabilities : ""; }

	public String getOperatorFriendlyName() {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
			return mScanResult.operatorFriendlyName != null ? mScanResult.operatorFriendlyName.toString() : null;
		} else {
			return "";
		}
	}

	public String getVenueName() {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
			return mScanResult.venueName != null ? mScanResult.venueName.toString() : null;
		} else {
			return "";
		}
	}

	public int getCenterFreq0() {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
			return mScanResult.centerFreq0;
		} else {
			return 0;
		}
	}

	public int getCenterFreq1() {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
			return mScanResult.centerFreq0;
		} else {
			return 0;
		}
	}

	public int getChannelWidth() {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
			return mScanResult.channelWidth;
		} else {
			return 0;
		}
	}

	public int getFrequency() {
		return mScanResult.frequency;
	}

	public int getLevel() {
		return mScanResult.level;
	}

	public long getTimestamp() {
		return mScanResult.timestamp;
	}
}
