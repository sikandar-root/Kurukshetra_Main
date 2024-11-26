// Copyright (c) 2021 Nineva Studios

package com.ninevastudios.androidgoodies.pickers.core.threads;

import android.content.Context;
import android.media.MediaMetadataRetriever;

import com.ninevastudios.androidgoodies.pickers.api.callbacks.AudioPickerCallback;
import com.ninevastudios.androidgoodies.pickers.api.entity.ChosenAudio;
import com.ninevastudios.androidgoodies.pickers.api.entity.ChosenFile;

import java.util.List;

public final class AudioProcessorThread extends FileProcessorThread {
    private AudioPickerCallback callback;

    public AudioProcessorThread(Context context, List<? extends ChosenFile> files, int cacheLocation) {
        super(context, files, cacheLocation);
    }

    @Override
    public void run() {
        super.run();
        postProcessAudios();
        onDone();
    }

    private void postProcessAudios() {
        for (ChosenFile file : files) {
            ChosenAudio audio = (ChosenAudio) file;
            postProcessAudio(audio);
        }
    }

    private void postProcessAudio(ChosenAudio audio) {
        MediaMetadataRetriever metadataRetriever = new MediaMetadataRetriever();
        try {
            metadataRetriever.setDataSource(audio.getOriginalPath());
            String duration = metadataRetriever.extractMetadata(MediaMetadataRetriever.METADATA_KEY_DURATION);
            if (duration != null) {
                audio.setDuration(Long.parseLong(duration));
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                metadataRetriever.release();
            }  catch (Exception e) {
            }
        }
    }

    private void onDone() {
        try {
            if (callback != null) {
                getActivityFromContext().runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        callback.onAudiosChosen((List<ChosenAudio>) files);
                    }
                });
            }
        } catch (NullPointerException e) {
            e.printStackTrace();
        }
    }

    public void setAudioPickerCallback(AudioPickerCallback callback) {
        this.callback = callback;
    }
}