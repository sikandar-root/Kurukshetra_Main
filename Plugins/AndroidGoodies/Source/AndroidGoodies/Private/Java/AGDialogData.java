// Copyright (c) 2018 Nineva Studios

package com.ninevastudios.androidgoodies;

import androidx.annotation.Keep;

@Keep
class AGDialogData {
	public String title;
	public String message;
	public int theme;

	public String positiveButtonText;
	public String negativeButtonText;
	public String neutralButtonText;

	public String[] items;

	public String[] singleChoiceItems;
	public int singleChoiceCheckedItem;

	public String[] multiChoiceItems;
	public boolean[] multiChoiceCheckedItems;
}
