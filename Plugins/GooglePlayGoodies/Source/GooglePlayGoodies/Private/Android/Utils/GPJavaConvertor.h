// Copyright (c) 2018 Nineva Studios

#pragma once

#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"
#include "Engine/Texture2D.h"
#include "Social/GPLeaderboardScore.h"

namespace GPJavaConvertor
{
TArray<uint8> ToByteArray(jbyteArray JavaArray);
jbyteArray ToJavaByteArray(const TArray<uint8>& Data);
TArray<bool> ToBoolArray(jbooleanArray JavaArray);
jbooleanArray ToJavaBoolArray(const TArray<bool>& Data);
jobjectArray ToJavaStringArray(const TArray<FString>& StringArray);
jbyteArray ConvertToJByteArray(const TArray<uint8>& byteArray);
jstring GetJavaString(FString string);
FString FromJavaString(jstring javaString);
TArray<FGPLeaderboardScore> FromJavaScores(jobjectArray javaScores);
FGPLeaderboardScore FromJavaScore(jobject javaScore);
TArray<uint8> ByteArrayFromTexture(UTexture2D* image);
};
