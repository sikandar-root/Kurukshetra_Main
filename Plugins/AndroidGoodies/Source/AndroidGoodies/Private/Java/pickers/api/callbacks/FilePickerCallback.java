// Copyright (c) 2021 Nineva Studios

package com.ninevastudios.androidgoodies.pickers.api.callbacks;

import com.ninevastudios.androidgoodies.pickers.api.entity.ChosenFile;

import java.util.List;

public interface FilePickerCallback extends PickerCallback {
    void onFilesChosen(List<ChosenFile> files);
}
