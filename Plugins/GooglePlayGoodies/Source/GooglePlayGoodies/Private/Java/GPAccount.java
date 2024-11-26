// Copyright (c) 2020 Nineva Studios

package com.ninevastudios.googleplay;

import com.google.android.gms.auth.api.signin.GoogleSignInAccount;

public class GPAccount {

	private GoogleSignInAccount mAccount = null;

	public GPAccount(GoogleSignInAccount account) {
		mAccount = account;
	}

	public String getDisplayName() {
		if (mAccount == null)
			return "";

		String result = mAccount.getDisplayName();
		return result == null ? "" : result;
	}

	public String getAccountId() {
		if (mAccount == null)
			return "";

		String result = mAccount.getId();
		return result == null ? "" : result;
	}

	public String getEmail() {
		if (mAccount == null)
			return "";

		String result = mAccount.getEmail();
		return result == null ? "" : result;
	}

	public String getIdToken() {
		if (mAccount == null)
			return "";

		String result = mAccount.getIdToken();
		return result == null ? "" : result;
	}

	public String getServerAuthCode() {
		if (mAccount == null)
			return "";

		String result = mAccount.getServerAuthCode();
		return result == null ? "" : result;
	}
}
