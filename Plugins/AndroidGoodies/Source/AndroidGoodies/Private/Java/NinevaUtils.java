package com.ninevastudios.androidgoodies;

import android.app.Activity;
import android.content.Intent;
import android.util.Log;

import com.ninevastudios.androidgoodies.pickers.api.Picker;

public class NinevaUtils {
  public static void logMethodCall(String methodName) {
    Log.d("AndroidGoodies", "> method: " + methodName);
  }

  public static void log(String message) {
    Log.d("AndroidGoodies", "> msg: " + message);
  }

  public static void processOnActivityResult(int requestCode, int resultCode, Intent intent, Activity activity) {

    logMethodCall("onActivityResult");
    log("result code:" + resultCode);

    switch (requestCode) {
      case Picker.PICK_IMAGE_DEVICE:
      case Picker.PICK_IMAGE_CAMERA:
        AGImagePicker.handlePhotoReceived(requestCode, resultCode, intent, activity);
        break;
      case Picker.PICK_FILE:
        AGFilePicker.handleFileReceived(requestCode, resultCode, intent, activity);
        break;
      case Picker.PICK_CONTACT:
        AGContacts.handleContactReceived(requestCode, resultCode, intent, activity);
        break;
      default:
        break;
    }
  }
}
