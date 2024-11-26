// Copyright (c) 2021 Nineva Studios

package com.ninevastudios.androidgoodies.pickers.api.callbacks;

import com.ninevastudios.androidgoodies.pickers.api.entity.ChosenImage;

import java.util.List;

public interface ImagePickerCallback extends PickerCallback {
    void onImagesChosen(List<ChosenImage> images);
}
