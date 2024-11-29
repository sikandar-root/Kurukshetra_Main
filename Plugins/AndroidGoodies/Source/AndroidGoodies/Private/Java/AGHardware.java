// Copyright (c) 2019 Nineva Studios

package com.ninevastudios.androidgoodies;

import android.annotation.SuppressLint;
import android.annotation.TargetApi;
import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.hardware.Camera;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraManager;
import android.media.AudioAttributes;
import android.net.ConnectivityManager;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.NetworkRequest;
import android.net.NetworkSpecifier;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiManager;
import android.net.wifi.WifiNetworkSpecifier;
import android.net.wifi.WifiNetworkSuggestion;
import android.os.BatteryManager;
import android.os.Build;
import android.os.PatternMatcher;
import android.os.VibrationEffect;
import android.os.Vibrator;

import androidx.annotation.Keep;
import androidx.annotation.NonNull;

import android.provider.Settings;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;

@SuppressWarnings("deprecation")
@Keep
public class AGHardware {
	private static Camera _camera;

	public static native void onReceiverSuccessCallback(AScanResult[] results);

	public static native void onReceiverFailureCallback(String message);

	@Keep
	public static void enableFlashlight(Activity activity, final boolean enable) {

		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
			enableFlashlightNew(activity, enable);
		} else {
			enableFlashlightOld(activity, enable);
		}
	}

	@Keep
	public static boolean hasVibrator(Activity activity) {
		Vibrator vibrator = (Vibrator) activity.getSystemService(Context.VIBRATOR_SERVICE);
		return vibrator != null && vibrator.hasVibrator();
	}

	@Keep
	public static boolean hasAmplitudeControl(Activity activity) {
		Vibrator vibrator = (Vibrator) activity.getSystemService(Context.VIBRATOR_SERVICE);
		return vibrator != null && Build.VERSION.SDK_INT >= Build.VERSION_CODES.O && vibrator.hasAmplitudeControl();
	}

	@Keep
	public static void vibrate(Activity activity, final long duration) {
		Vibrator vibrator = (Vibrator) activity.getSystemService(Context.VIBRATOR_SERVICE);
		if (vibrator != null) {
			vibrator.vibrate(duration);
		}
	}

	@Keep
	public static void vibrate(Activity activity, final long[] intervals, final int repeat) {
		Vibrator vibrator = (Vibrator) activity.getSystemService(Context.VIBRATOR_SERVICE);
		if (vibrator != null) {
			vibrator.vibrate(intervals, repeat);
		}
	}

	@TargetApi(Build.VERSION_CODES.O)
	@Keep
	public static void vibrate(Activity activity, VibrationEffect effect) {
		Vibrator vibrator = (Vibrator) activity.getSystemService(Context.VIBRATOR_SERVICE);
		if (vibrator != null && effect != null) {
			vibrator.vibrate(effect);
		}
	}

	@TargetApi(Build.VERSION_CODES.O)
	@Keep
	public static void vibrate(Activity activity, VibrationEffect effect, final int flags, final int usage, final int contentType) {
		Vibrator vibrator = (Vibrator) activity.getSystemService(Context.VIBRATOR_SERVICE);
		if (vibrator != null && effect != null) {
			vibrator.vibrate(effect,
					new AudioAttributes.Builder()
							.setUsage(usage)
							.setFlags(flags)
							.setContentType(contentType)
							.build());
		}
	}

	@Keep
	public static void stopVibration(Activity activity) {
		Vibrator vibrator = (Vibrator) activity.getSystemService(Context.VIBRATOR_SERVICE);
		if (vibrator != null) {
			vibrator.cancel();
		}
	}

	@Keep
	@TargetApi(Build.VERSION_CODES.O)
	public static VibrationEffect createVibrationEffect(final long duration, final int amplitude) {
		Log.d("AndroidGoodies", String.valueOf(amplitude));
		return VibrationEffect.createOneShot(duration, amplitude);
	}

	@Keep
	@TargetApi(Build.VERSION_CODES.O)
	public static VibrationEffect createVibrationEffect(final long[] durations, final int amplitude) {
		return VibrationEffect.createWaveform(durations, amplitude);
	}

	@Keep
	@TargetApi(Build.VERSION_CODES.O)
	public static VibrationEffect createVibrationEffect(final long[] durations, int[] amplitudes, final int repeat) {
		return VibrationEffect.createWaveform(durations, amplitudes, repeat);
	}

	@Keep
	public static long computeRemainingChargeTime(Activity activity) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
			BatteryManager manager = (BatteryManager) activity.getSystemService(Context.BATTERY_SERVICE);

			long result = manager != null ? manager.computeChargeTimeRemaining() : -1;
			Log.d("AndroidGoodies", String.valueOf(result));
			return result;
		}

		return -1;
	}

	@Keep
	@SuppressLint("ObsoleteSdkInt")
	public static int getBatteryCapacity(Activity activity) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
			BatteryManager manager = (BatteryManager) activity.getSystemService(Context.BATTERY_SERVICE);
			return manager != null ? manager.getIntProperty(BatteryManager.BATTERY_PROPERTY_CAPACITY) : -1;
		}

		return -1;
	}

	@Keep
	@SuppressLint("ObsoleteSdkInt")
	public static int getBatteryChargeCounter(Activity activity) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
			BatteryManager manager = (BatteryManager) activity.getSystemService(Context.BATTERY_SERVICE);
			return manager != null ? manager.getIntProperty(BatteryManager.BATTERY_PROPERTY_CHARGE_COUNTER) : -1;
		}

		return -1;
	}

	@Keep
	@SuppressLint("ObsoleteSdkInt")
	public static int getAverageBatteryCurrent(Activity activity) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
			BatteryManager manager = (BatteryManager) activity.getSystemService(Context.BATTERY_SERVICE);
			return manager != null ? manager.getIntProperty(BatteryManager.BATTERY_PROPERTY_CURRENT_AVERAGE) : -1;
		}

		return -1;
	}

	@Keep
	@SuppressLint("ObsoleteSdkInt")
	public static int getImmediateBatteryCurrent(Activity activity) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
			BatteryManager manager = (BatteryManager) activity.getSystemService(Context.BATTERY_SERVICE);
			return manager != null ? manager.getIntProperty(BatteryManager.BATTERY_PROPERTY_CURRENT_NOW) : -1;
		}

		return -1;
	}

	@Keep
	@SuppressLint("ObsoleteSdkInt")
	public static int getBatteryCurrent(Activity activity) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
			BatteryManager manager = (BatteryManager) activity.getSystemService(Context.BATTERY_SERVICE);
			return manager != null ? manager.getIntProperty(BatteryManager.BATTERY_PROPERTY_CURRENT_NOW) : -1;
		}

		return -1;
	}

	@Keep
	@SuppressLint("ObsoleteSdkInt")
	public static long getBatteryEnergyCounter(Activity activity) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
			BatteryManager manager = (BatteryManager) activity.getSystemService(Context.BATTERY_SERVICE);
			long result = manager != null ? manager.getLongProperty(BatteryManager.BATTERY_PROPERTY_ENERGY_COUNTER) : -1;
			result = result == Long.MIN_VALUE ? -1 : result;
			Log.d("AndroidGoodies", String.valueOf(result));
			return result;
		}

		return -1;
	}

	@Keep
	public static int getBatteryStatus(Activity activity) {
		IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		Intent batteryIntent = activity.registerReceiver(null, filter);
		if (batteryIntent == null) {
			return BatteryManager.BATTERY_STATUS_UNKNOWN;
		}

		return batteryIntent.getIntExtra(BatteryManager.EXTRA_STATUS, BatteryManager.BATTERY_STATUS_UNKNOWN);
	}

	@TargetApi(Build.VERSION_CODES.P)
	@Keep
	public static boolean isBatteryLow(Activity activity) {
		IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		Intent batteryIntent = activity.registerReceiver(null, filter);
		if (batteryIntent == null) {
			return false;
		}

		return batteryIntent.getBooleanExtra(BatteryManager.EXTRA_BATTERY_LOW, false);
	}

	@Keep
	public static int getBatteryHealth(Activity activity) {
		IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		Intent batteryIntent = activity.registerReceiver(null, filter);
		if (batteryIntent == null) {
			return BatteryManager.BATTERY_HEALTH_UNKNOWN;
		}

		return batteryIntent.getIntExtra(BatteryManager.EXTRA_HEALTH, BatteryManager.BATTERY_HEALTH_UNKNOWN);
	}

	@Keep
	public static int getBatteryLevel(Activity activity) {
		IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		Intent batteryIntent = activity.registerReceiver(null, filter);
		if (batteryIntent == null) {
			return -1;
		}

		return batteryIntent.getIntExtra(BatteryManager.EXTRA_LEVEL, -1);
	}

	@Keep
	public static int getBatteryPluggedState(Activity activity) {
		IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		Intent batteryIntent = activity.registerReceiver(null, filter);
		if (batteryIntent == null) {
			return 0;
		}

		return batteryIntent.getIntExtra(BatteryManager.EXTRA_PLUGGED, 0);
	}

	@Keep
	public static boolean isBatteryPresent(Activity activity) {
		IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		Intent batteryIntent = activity.registerReceiver(null, filter);
		if (batteryIntent == null) {
			return false;
		}

		return batteryIntent.getBooleanExtra(BatteryManager.EXTRA_PRESENT, false);
	}

	@Keep
	public static int getBatteryScale(Activity activity) {
		IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		Intent batteryIntent = activity.registerReceiver(null, filter);
		if (batteryIntent == null) {
			return -1;
		}

		return batteryIntent.getIntExtra(BatteryManager.EXTRA_SCALE, -1);
	}

	@Keep
	public static String getBatteryTechnology(Activity activity) {
		String unknownString = "Unknown";

		IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		Intent batteryIntent = activity.registerReceiver(null, filter);
		if (batteryIntent == null) {
			return unknownString;
		}

		String result = batteryIntent.getStringExtra(BatteryManager.EXTRA_TECHNOLOGY);
		return result == null ? unknownString : result;
	}

	@Keep
	public static int getBatteryTemperature(Activity activity) {
		IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		Intent batteryIntent = activity.registerReceiver(null, filter);
		if (batteryIntent == null) {
			return Integer.MIN_VALUE;
		}

		return batteryIntent.getIntExtra(BatteryManager.EXTRA_TEMPERATURE, Integer.MIN_VALUE);
	}

	@Keep
	public static int getBatteryVoltage(Activity activity) {
		IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		Intent batteryIntent = activity.registerReceiver(null, filter);
		if (batteryIntent == null) {
			return 0;
		}

		return batteryIntent.getIntExtra(BatteryManager.EXTRA_VOLTAGE, 0);
	}

	@Keep
	public static void startWifiScan(Activity activity) {
		final WifiManager wifiManager = (WifiManager) activity.getApplicationContext().getSystemService(Context.WIFI_SERVICE);
		BroadcastReceiver wifiScanReceiver = new BroadcastReceiver() {
			@Override
			public void onReceive(Context context, Intent intent) {
				if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.M) {
					boolean success = intent.getBooleanExtra(WifiManager.EXTRA_RESULTS_UPDATED, false);
					if (success) {
						onReceiverSuccessCallback(getScanResults(wifiManager));
					} else {
						onReceiverFailureCallback("onReceive error");
					}
				} else {
					onReceiverSuccessCallback(getScanResults(wifiManager));
				}
			}
		};
		IntentFilter intentFilter = new IntentFilter();
		intentFilter.addAction(WifiManager.SCAN_RESULTS_AVAILABLE_ACTION);
		activity.registerReceiver(wifiScanReceiver, intentFilter);
		boolean success = wifiManager.startScan();
		if (!success) {
			activity.unregisterReceiver(wifiScanReceiver);
			onReceiverFailureCallback("Scan was not started.");
		}
	}

	@Keep
	public static void connectToWifiNetwork(final Activity context, String ssid, String password, boolean isWpa2) {
		if (Build.VERSION.SDK_INT < Build.VERSION_CODES.Q) {
			ssid = "\"" + ssid + "\"";

			Log.d("AndroidGoodies", "SSID: " + ssid);
			Log.d("AndroidGoodies", "Password: " + password);

			WifiConfiguration conf = new WifiConfiguration();
			conf.SSID = ssid;

			if (password.isEmpty()) {
				conf.allowedKeyManagement.set(WifiConfiguration.KeyMgmt.NONE);
			} else {
				conf.allowedKeyManagement.set(WifiConfiguration.KeyMgmt.WPA_PSK);
				conf.preSharedKey = "\"" + password + "\"";
			}

			WifiManager wifiManager = (WifiManager) context.getApplicationContext().getSystemService(Context.WIFI_SERVICE);
			int networkId = wifiManager.addNetwork(conf);
			Log.d("AndroidGoodies", "Network ID: " + networkId);

			wifiManager.disconnect();
			wifiManager.enableNetwork(networkId, true);
			wifiManager.reconnect();
		} else {
			WifiNetworkSuggestion.Builder suggestionBuilder = new WifiNetworkSuggestion.Builder()
					.setSsid(ssid)
					.setPriority(100);

			if (isWpa2 && !password.isEmpty())
				suggestionBuilder.setWpa2Passphrase(password);
			else if (!isWpa2 && !password.isEmpty())
				suggestionBuilder.setWpa3Passphrase(password);

			final List<WifiNetworkSuggestion> suggestionsList = new ArrayList<>();
			suggestionsList.add(suggestionBuilder.build());

			WifiManager wifiManager =
					(WifiManager) context.getApplicationContext().getSystemService(Context.WIFI_SERVICE);
			int status = wifiManager.addNetworkSuggestions(suggestionsList);
			if (status == 0) {
				Log.d("AndroidGoodies", "Wifi network suggestion added.");
			} else {
				Log.e("AndroidGoodies", "Wifi network suggestion not added: " + status);
			}
		}
	}

	@Keep
	public static boolean isWifiEnabled(Activity context) {
		WifiManager wifiManager = (WifiManager) context.getApplicationContext().getSystemService(Context.WIFI_SERVICE);
		return wifiManager.isWifiEnabled();
	}

	@Keep
	public static void enableWifi(Activity context, boolean enable) {
		if (Build.VERSION.SDK_INT < Build.VERSION_CODES.Q) {
			WifiManager wifiManager = (WifiManager) context.getApplicationContext().getSystemService(Context.WIFI_SERVICE);
			wifiManager.setWifiEnabled(enable);
		} else {
			Intent panelIntent = new Intent(Settings.Panel.ACTION_WIFI);
			context.startActivityForResult(panelIntent, 1);
		}
	}

	@NonNull
	private static AScanResult[] getScanResults(WifiManager wifiManager) {
		List<ScanResult> scannedWifiArray = wifiManager.getScanResults();
		AScanResult[] aScanResults = new AScanResult[scannedWifiArray.size()];
		for (int i = 0; i < scannedWifiArray.size(); i++) {
			aScanResults[i] = new AScanResult(scannedWifiArray.get(i));
		}
		return aScanResults;
	}

	private static void enableFlashlightOld(Activity activity, final boolean enable) {
		try {
			activity.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					if (enable) {
						_camera = Camera.open();
						Camera.Parameters cameraParameters = _camera.getParameters();
						cameraParameters.setFlashMode(Camera.Parameters.FLASH_MODE_ON);
						_camera.setParameters(cameraParameters);
						_camera.startPreview();
					} else {
						if (_camera != null) {
							_camera.stopPreview();
							_camera.release();
							_camera = null;
						}
					}
				}
			});
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@TargetApi(Build.VERSION_CODES.M)
	private static void enableFlashlightNew(Activity activity, final boolean enable) {
		try {
			CameraManager cameraManager = (CameraManager) activity.getSystemService(Context.CAMERA_SERVICE);
			if (cameraManager != null) {
				String cameraId = cameraManager.getCameraIdList()[0];
				cameraManager.setTorchMode(cameraId, enable);
			} else {
				Log.d("AndroidGoodies", "enableFlashlight: could not get camera manager");
			}
		} catch (CameraAccessException e) {
			e.printStackTrace();
		}
	}
}
