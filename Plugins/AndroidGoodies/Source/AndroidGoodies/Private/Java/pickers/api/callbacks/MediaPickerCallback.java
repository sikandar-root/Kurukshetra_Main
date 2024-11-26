// Copyright (c) 2021 Nineva Studios

package com.ninevastudios.androidgoodies.pickers.api.callbacks;

import com.ninevastudios.androidgoodies.pickers.api.entity.ChosenImage;
import com.ninevastudios.androidgoodies.pickers.api.entity.ChosenVideo;

import java.util.List;

public interface MediaPickerCallback extends PickerCallback {
    void onMediaChosen(List<ChosenImage> images, List<ChosenVideo> videos);
}
