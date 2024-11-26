// Copyright (c) 2020 Nineva Studios

#include "AGChosenImage.h"

#if PLATFORM_ANDROID
#include "Android/Utils/AGMethodCallUtils.h"
#endif

int UAGChosenImage::GetOrientation()
{
	int Orientation = -1;

#if PLATFORM_ANDROID
	Orientation = AGMethodCallUtils::CallIntMethod(JavaChosenFileObject, "getOrientation", "()I");
#endif

	return Orientation;
}

FString UAGChosenImage::GetThumbnailPath()
{
	FString ThumbnailPath;

#if PLATFORM_ANDROID
	ThumbnailPath = AGMethodCallUtils::CallStringMethod(JavaChosenFileObject, "getThumbnailPath", "()Ljava/lang/String;");
#endif

	return ThumbnailPath;
}

FString UAGChosenImage::GetThumbnailSmallPath()
{
	FString ThumbnailSmallPath;

#if PLATFORM_ANDROID
	ThumbnailSmallPath = AGMethodCallUtils::CallStringMethod(JavaChosenFileObject, "getThumbnailSmallPath", "()Ljava/lang/String;");
#endif

	return ThumbnailSmallPath;
}

int UAGChosenImage::GetWidth()
{
	int Width = -1;

#if PLATFORM_ANDROID
	Width = AGMethodCallUtils::CallIntMethod(JavaChosenFileObject, "getWidth", "()I");
#endif

	return Width;
}

int UAGChosenImage::GetHeight()
{
	int Height = -1;

#if PLATFORM_ANDROID
	Height = AGMethodCallUtils::CallIntMethod(JavaChosenFileObject, "getHeight", "()I");
#endif

	return Height;
}

FString UAGChosenImage::GetOrientationName()
{
	FString OrientationName;

#if PLATFORM_ANDROID
	OrientationName = AGMethodCallUtils::CallStringMethod(JavaChosenFileObject, "getOrientationName", "()Ljava/lang/String;");
#endif

	return OrientationName;
}