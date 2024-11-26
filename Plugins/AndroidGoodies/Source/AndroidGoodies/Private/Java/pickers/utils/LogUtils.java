// Copyright (c) 2021 Nineva Studios

package com.ninevastudios.androidgoodies.pickers.utils;

import android.util.Log;

import com.ninevastudios.androidgoodies.pickers.core.PickerManager;

public class LogUtils {
    public static void d(String tag, String message){
        if(PickerManager.debugglable){
            Log.d(tag, message);
        }
    }

    public static void e(String tag, String message) {
        if(PickerManager.debugglable){
            Log.e(tag, message);
        }
    }
}
