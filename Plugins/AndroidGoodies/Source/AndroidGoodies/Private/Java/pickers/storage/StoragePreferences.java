// Copyright (c) 2021 Nineva Studios

package com.ninevastudios.androidgoodies.pickers.storage;

import android.content.Context;
import android.content.SharedPreferences;

public class StoragePreferences {
    public SharedPreferences prefs;
    private final static String FILE = "com.ninevastudios.androidgoodies.pickers.multipicker.preferences";

    private final static String KEY_FOLDER_NAME = "folder_name";
    private final static String KEY_DEBUG = "key_debug";

    public StoragePreferences(Context context) {
        prefs = context.getSharedPreferences(FILE, Context.MODE_PRIVATE);
    }

    public void setFolderName(String folderName) {
        prefs.edit().putString(KEY_FOLDER_NAME, folderName).apply();
    }

    public String getFolderName() {
        return prefs.getString(KEY_FOLDER_NAME, null);
    }


    public void setDebuggable(boolean debug){
        prefs.edit().putBoolean(KEY_DEBUG, debug).apply();
    }

    public boolean isDebuggable() {
        return prefs.getBoolean(KEY_DEBUG, true);
    }
}
