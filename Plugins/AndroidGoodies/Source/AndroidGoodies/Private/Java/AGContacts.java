// Copyright (c) 2019 Nineva Studios

package com.ninevastudios.androidgoodies;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.ContentProviderOperation;
import android.content.ContentResolver;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.provider.ContactsContract;
import android.provider.ContactsContract.CommonDataKinds.Phone;
import androidx.annotation.Keep;
import android.telephony.TelephonyManager;
import android.util.Log;

import java.util.ArrayList;

@Keep
public class AGContacts {
	private static final String DISPLAY_NAME_COLUMN_NAME = "DISPLAY_NAME";

	@Keep
	@SuppressLint({"HardwareIds", "MissingPermission"})
	public static String getSimPhoneNumber(Activity activity) {
		TelephonyManager tMgr = (TelephonyManager) activity.getSystemService(Context.TELEPHONY_SERVICE);
		try {
			String result = tMgr.getLine1Number();
			return result == null ? "" : result;
		} catch (Exception e) {
			Log.d("AndroidGoodies", "Could not get SIM number: " + e.getMessage());
			return "";
		}
	}

	@Keep
	public static AGContact[] fetchContactsWithName(Activity activity, String name) {
		ContentResolver resolver = activity.getContentResolver();
		Cursor contact = resolver.query(ContactsContract.Contacts.CONTENT_URI, null,
				DISPLAY_NAME_COLUMN_NAME + " = '" + name + "'", null, null);

		if (contact == null) {
			return new AGContact[0];
		}

		ArrayList<AGContact> contactsArray = new ArrayList<>();

		while (contact.moveToNext()) {
			String contactId = contact.getString(contact.getColumnIndex(ContactsContract.Contacts._ID));
			AGContact agContact = new AGContact();
			agContact.DisplayName = contact.getString(contact.getColumnIndex(DISPLAY_NAME_COLUMN_NAME));
			ArrayList<String> phonesList = new ArrayList<>();

			Cursor phones = resolver.query(Phone.CONTENT_URI, null,
					Phone.CONTACT_ID + " = " + contactId, null, null);
			if (phones != null) {
				while (phones.moveToNext()) {
					phonesList.add(phones.getString(phones.getColumnIndex(Phone.NUMBER)));
				}

				phones.close();
			}

			agContact.PhoneNumbers = phonesList.toArray(new String[0]);
			contactsArray.add(agContact);
		}
		contact.close();

		return contactsArray.toArray(new AGContact[0]);
	}

	@Keep
	public static AGContact[] fetchContactsWithNumber(Activity activity, String number) {
		ContentResolver resolver = activity.getContentResolver();
		Uri uri = Uri.withAppendedPath(ContactsContract.PhoneLookup.CONTENT_FILTER_URI, Uri.encode(number));
		Cursor contact = resolver.query(uri, null, null, null, null);

		if (contact == null) {
			return new AGContact[0];
		}

		ArrayList<AGContact> contactsArray = new ArrayList<>();

		while (contact.moveToNext()) {
			String contactId = contact.getString(contact.getColumnIndex(ContactsContract.Contacts._ID));
			AGContact agContact = new AGContact();
			agContact.DisplayName = contact.getString(contact.getColumnIndex(DISPLAY_NAME_COLUMN_NAME));
			ArrayList<String> phonesList = new ArrayList<>();

			Cursor phones = resolver.query(Phone.CONTENT_URI, null,
					Phone.CONTACT_ID + " = " + contactId, null, null);
			if (phones != null) {
				while (phones.moveToNext()) {
					phonesList.add(phones.getString(phones.getColumnIndex(Phone.NUMBER)));

					agContact.PhoneNumbers = phonesList.toArray(new String[0]);
					contactsArray.add(agContact);
				}

				phones.close();
			}
		}

		contact.close();

		return contactsArray.toArray(new AGContact[0]);
	}

	@Keep
	public static AGContact[] fetchAllContacts(Activity activity) {
		ContentResolver resolver = activity.getContentResolver();
		Cursor contacts = resolver.query(ContactsContract.Contacts.CONTENT_URI,
				null, null, null, null);

		if (contacts == null) {
			return new AGContact[0];
		}

		ArrayList<AGContact> contactsArray = new ArrayList<>();

		while (contacts.moveToNext()) {
			String contactId = contacts.getString(contacts.getColumnIndex(ContactsContract.Contacts._ID));
			AGContact agContact = new AGContact();
			agContact.DisplayName = contacts.getString(contacts.getColumnIndex(DISPLAY_NAME_COLUMN_NAME));
			ArrayList<String> phonesList = new ArrayList<>();

			Cursor phones = resolver.query(Phone.CONTENT_URI, null,
					Phone.CONTACT_ID + " = " + contactId, null, null);
			if (phones != null) {
				while (phones.moveToNext()) {
					phonesList.add(phones.getString(phones.getColumnIndex(Phone.NUMBER)));

					agContact.PhoneNumbers = phonesList.toArray(new String[0]);
					contactsArray.add(agContact);
				}

				phones.close();
			}
		}

		contacts.close();

		return contactsArray.toArray(new AGContact[0]);
	}

	@Keep
	public static boolean addContact(Activity activity, AGContact contact) {
		try {
			ContentResolver resolver = activity.getContentResolver();

			ArrayList<ContentProviderOperation> operations =
					new ArrayList<>();

			operations.add(ContentProviderOperation.newInsert(ContactsContract.RawContacts.CONTENT_URI)
					.withValue(ContactsContract.RawContacts.ACCOUNT_TYPE, null)
					.withValue(ContactsContract.RawContacts.ACCOUNT_NAME, null)
					.build());

			setContactName(operations, contact.DisplayName);

			for (int i = 1; i < contact.PhoneNumbers.length; i++) {
				addContactNumber(operations, contact.PhoneNumbers[i]);
			}

			resolver.applyBatch(ContactsContract.AUTHORITY, operations);

			return true;
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
	}

	private static void setContactName(ArrayList<ContentProviderOperation> operations, String userName) {
		operations.add(ContentProviderOperation.newInsert(ContactsContract.Data.CONTENT_URI)
				.withValueBackReference(ContactsContract.Data.RAW_CONTACT_ID, 0)
				.withValue(ContactsContract.Data.MIMETYPE, ContactsContract.CommonDataKinds.StructuredName.CONTENT_ITEM_TYPE)
				.withValue(ContactsContract.CommonDataKinds.StructuredName.DISPLAY_NAME, userName)
				.build());
	}

	private static void addContactNumber(ArrayList<ContentProviderOperation> operations, String number) {
		operations.add(ContentProviderOperation.newInsert(ContactsContract.Data.CONTENT_URI)
				.withValueBackReference(ContactsContract.Data.RAW_CONTACT_ID, 0)
				.withValue(ContactsContract.Data.MIMETYPE, Phone.CONTENT_ITEM_TYPE)
				.withValue(Phone.NUMBER, number)
				.withValue(ContactsContract.CommonDataKinds.Phone.TYPE, Phone.TYPE_MOBILE)
				.build());
	}
}
