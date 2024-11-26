// Copyright (c) 2021 Nineva Studios

package com.ninevastudios.androidgoodies.pickers.utils;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class MimeUtils {
    static String[] IMAGE_EXTENSIONS = {
            "jpg",
            "jpeg",
            "bmp",
            "png",
            "gif",
            "tiff",
            "webp",
            "ico"
    };

    static String[] VIDEO_EXTENSIONS = {
            "avi",
            "asf",
            "mov",
            "flv",
            "swf",
            "mpg",
            "mpeg",
            "mp4",
            "wmv",
    };

    private static Set<String> SET_IMAGE_EXTENSIONS = new HashSet<String>(Arrays.asList(IMAGE_EXTENSIONS));
    private static Set<String> SET_VIDEO_EXTENSIONS = new HashSet<String>(Arrays.asList(VIDEO_EXTENSIONS));

    public static String guessMimeTypeFromExtension(String extension) {
        if (SET_IMAGE_EXTENSIONS.contains(extension.toLowerCase())) {
            return "image";
        } else if (SET_VIDEO_EXTENSIONS.contains(extension.toLowerCase())) {
            return "video";
        } else {
            return "file";
        }
    }
}
