// Copyright (c) 2020 Nineva Studios

package com.ninevastudios.googleplay;

import android.app.Activity;
import android.net.Uri;
import android.util.Log;

import com.google.android.gms.auth.api.signin.GoogleSignIn;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.common.api.ApiException;
import com.google.android.gms.games.AnnotatedData;
import com.google.android.gms.games.EventsClient;
import com.google.android.gms.games.Games;
import com.google.android.gms.games.event.Event;
import com.google.android.gms.games.event.EventBuffer;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;

import java.util.ArrayList;

public class GPEvent {

	public static native void onLoadEventsCallback(GPEvent[] events);
	public static native void onEventIconReady(long callbackAddr, byte[] buffer, int width, int height);

	private Event mEvent = null;

	public static void incrementEvent(Activity activity, String id, int amount) {
		GoogleSignInAccount account = GoogleSignIn.getLastSignedInAccount(activity);
		if (account != null) {
			Games.getEventsClient(activity, account).increment(id, amount);
		}
	}

	public static void loadEvents(Activity activity, boolean forceRefresh, String[] ids) {
		GoogleSignInAccount account = GoogleSignIn.getLastSignedInAccount(activity);
		if (account != null) {
			EventsClient client = Games.getEventsClient(activity, account);

			OnCompleteListener<AnnotatedData<EventBuffer>> OnComplete = new OnCompleteListener<AnnotatedData<EventBuffer>>() {
				@Override
				public void onComplete(Task<AnnotatedData<EventBuffer>> task) {
					if (task.isSuccessful()) {
						ArrayList<GPEvent> result = new ArrayList<GPEvent>();
						for (Event event : task.getResult().get()) {
							result.add(new GPEvent(event));
						}
						onLoadEventsCallback(result.toArray(new GPEvent[0]));
					} else {
						if (task.getException() instanceof ApiException) {
							Log.d("GooglePlayGoodies", "Cannot retrieve event data: " + task.getException().toString());
						}
					}
				}
			};

			if (ids.length > 0) {
				client.loadByIds(forceRefresh, ids).addOnCompleteListener(OnComplete);
			} else {
				client.load(forceRefresh).addOnCompleteListener(OnComplete);
			}
		}
	}

	public GPEvent(Event event) {
		mEvent = event;
	}

	public String getEventId() {
		return mEvent.getEventId();
	}

	public String getEventName() {
		return mEvent.getName();
	}

	public String getEventDescription() {
		return mEvent.getDescription();
	}

	public long getEventValue() {
		return mEvent.getValue();
	}

	public String getEventFormattedValue() {
		return mEvent.getFormattedValue();
	}

	public void getEventIconImage(Activity activity, final long callbackAddr) {
		try {
			Uri imageUri =mEvent.getIconImageUri();
			GPUtils.loadImage(activity, imageUri, new GPUtils.OnLoadImageCallback() {
				@Override
				public void run(byte[] buffer, int width, int height, String uri) {
					onEventIconReady(callbackAddr, buffer, width, height);
				}
			});
		}
		catch (Exception e) {
			Log.d("GooglePlayGoodies", e.toString());
		}
	}

}
