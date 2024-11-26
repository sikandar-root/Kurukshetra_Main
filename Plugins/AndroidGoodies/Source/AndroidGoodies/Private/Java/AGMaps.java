// Copyright (c) 2018 Nineva Studios

package com.ninevastudios.androidgoodies;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import androidx.annotation.Keep;

@Keep
public class AGMaps {

	private static final String uriFormat = "geo:%f,%f?z=%d";
	private static final String uriFormatLabel = "geo:0,0?q=%f,%f(%s)";
	private static final String uriFormatAdress = "geo:0,0?q=";
	private static final int defaultZoomValue = 1;
	private static final float defaultLatLong = 0f;

	@Keep
	public static boolean userHasMapsApp(Activity activity)
	{
		Intent intent = new Intent(Intent.ACTION_VIEW);
		intent.setData(Uri.parse(String.format(uriFormat, defaultLatLong, defaultLatLong, defaultZoomValue)));
		return tryLaunchMapIntent(intent, activity);
	}

	@Keep
	public static void openMapLocation(Activity activity, float latitude, float longitude, int zoom)
	{
		Intent intent = new Intent(Intent.ACTION_VIEW);
		Uri data = Uri.parse(String.format(uriFormat, latitude, longitude, zoom));
		intent.setData(data);

		activity.startActivity(intent);
	}

	@Keep
	public static void openMapLocationWithLabel(Activity activity, float latitude, float longitude, String label)
	{
		Intent intent = new Intent(Intent.ACTION_VIEW);

		Uri data = Uri.parse(String.format(uriFormatLabel, latitude, longitude, label));
		intent.setData(data);

		activity.startActivity(intent);
	}

	@Keep
	public static void openMapLocation(Activity activity, String address)
	{
		Uri path = Uri.parse(uriFormatAdress + Uri.encode(address));

		Intent intent = new Intent(Intent.ACTION_VIEW)
				.setData(path);

		activity.startActivity(intent);
	}

	private static boolean tryLaunchMapIntent(Intent intent, Activity activity)
	{
		try {
			activity.startActivity(intent);
			return true;
		}
		catch (Exception e)
		{
			return false;
		}
	}
}
