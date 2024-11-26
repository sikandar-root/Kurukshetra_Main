// Copyright (c) 2021 Nineva Studios

package com.ninevastudios.androidgoodies.pickers.api.callbacks;

import com.ninevastudios.androidgoodies.pickers.api.entity.ChosenVideo;

import java.util.List;

public interface VideoPickerCallback extends PickerCallback {
    void onVideosChosen(List<ChosenVideo> videos);
}
