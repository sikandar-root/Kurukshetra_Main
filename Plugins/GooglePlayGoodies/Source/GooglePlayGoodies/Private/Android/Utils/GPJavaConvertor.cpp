// Copyright (c) 2018 Nineva Studios

#include "GPJavaConvertor.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "GPMethodCallUtils.h"
#include "TextureResource.h"

#include "Runtime/Launch/Resources/Version.h"

namespace GPJavaConvertor
{
TArray<uint8> ToByteArray(jbyteArray JavaArray)
{
	TArray<uint8> ByteArray;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jbyte* JavaByte = Env->GetByteArrayElements(JavaArray, 0);

	const int Length = Env->GetArrayLength(JavaArray);
	for (int i = 0; i < Length; i++)
	{
		ByteArray.Add(JavaByte[i]);
	}

	return ByteArray;
}

jbyteArray ToJavaByteArray(const TArray<uint8>& Data)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	const int DataLength = Data.Num();
	jbyteArray LocalArray = Env->NewByteArray(DataLength);

	jbyte Buffer[DataLength];
	for (int i = 0; i < DataLength; i++)
	{
		Buffer[i] = Data[i];
	}

	Env->SetByteArrayRegion(LocalArray, 0, DataLength, Buffer);
	jbyteArray ResultArray = (jbyteArray)Env->NewGlobalRef(LocalArray);
	Env->DeleteLocalRef(LocalArray);

	return ResultArray;
}

TArray<bool> ToBoolArray(jbooleanArray JavaArray)
{
	TArray<bool> BoolArray;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jboolean* JavaBool = Env->GetBooleanArrayElements(JavaArray, 0);

	const int Length = Env->GetArrayLength(JavaArray);
	for (int i = 0; i < Length; i++)
	{
		BoolArray.Add(JavaBool[i]);
	}

	return BoolArray;
}

jbooleanArray ToJavaBoolArray(const TArray<bool>& Data)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	const int DataLength = Data.Num();
	jbooleanArray LocalArray = Env->NewBooleanArray(DataLength);

	jboolean Buffer[DataLength];
	for (int i = 0; i < DataLength; i++)
	{
		Buffer[i] = Data[i];
	}

	Env->SetBooleanArrayRegion(LocalArray, 0, DataLength, Buffer);
	jbooleanArray ResultArray = (jbooleanArray)Env->NewGlobalRef(LocalArray);
	Env->DeleteLocalRef(LocalArray);

	return ResultArray;
}

jobjectArray ToJavaStringArray(const TArray<FString>& StringArray)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jobjectArray JStringArray = (jobjectArray)Env->NewObjectArray(StringArray.Num(), FJavaWrapper::JavaStringClass, nullptr);

	for (int i = 0; i < StringArray.Num(); i++)
	{
		auto JString = FJavaClassObject::GetJString(StringArray[i]);
		Env->SetObjectArrayElement(JStringArray, i, *JString);
	}

	return JStringArray;
}

jbyteArray ConvertToJByteArray(const TArray<uint8>& byteArray)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jbyteArray javaByteArray = (jbyteArray)Env->NewByteArray(byteArray.Num());

	jbyte* javaByteArrayPtr = (jbyte*)malloc(byteArray.Num() * sizeof(jbyte));

	for (int i = 0; i < byteArray.Num(); i++)
	{
		javaByteArrayPtr[i] = byteArray[i];
	}

	Env->SetByteArrayRegion(javaByteArray, 0, byteArray.Num(), javaByteArrayPtr);

	free(javaByteArrayPtr);

	return javaByteArray;
}

jstring GetJavaString(FString string)
{
	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();
	jstring local = JEnv->NewStringUTF(TCHAR_TO_UTF8(*string));
	jstring result = (jstring)JEnv->NewGlobalRef(local);
	JEnv->DeleteLocalRef(local);
	return result;
}

FString FromJavaString(jstring javaString)
{
	JNIEnv* Env = AndroidJavaEnv::GetJavaEnv();
	const char* UTFString = Env->GetStringUTFChars(javaString, nullptr);
	FString Result(UTF8_TO_TCHAR(UTFString));
	Env->ReleaseStringUTFChars(javaString, UTFString);
	Env->DeleteLocalRef(javaString);

	return Result;
}

TArray<FGPLeaderboardScore> FromJavaScores(jobjectArray javaScores)
{
	TArray<FGPLeaderboardScore> Scores;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	int length = Env->GetArrayLength(javaScores);

	for (int i = 0; i < length; i++)
	{
		Scores.Add(FromJavaScore(Env->GetObjectArrayElement(javaScores, i)));
	}

	return Scores;
}

FGPLeaderboardScore FromJavaScore(jobject javaScore)
{
	FGPLeaderboardScore Score;

	Score.DisplayRank = GPMethodCallUtils::CallStringMethod(javaScore, "getDisplayRank", "()Ljava/lang/String;");
	Score.DisplayScore = GPMethodCallUtils::CallStringMethod(javaScore, "getDisplayScore", "()Ljava/lang/String;");
	Score.Rank = GPMethodCallUtils::CallLongMethod(javaScore, "getRank", "()J");
	Score.Timestamp = FDateTime::FromUnixTimestamp(GPMethodCallUtils::CallLongMethod(javaScore, "getTimestampMillis", "()J") / 1000);
	Score.ScoreHolderDisplayName = GPMethodCallUtils::CallStringMethod(javaScore, "getScoreHolderDisplayName", "()Ljava/lang/String;");
	Score.ScoreTag = GPMethodCallUtils::CallStringMethod(javaScore, "getScoreTag", "()Ljava/lang/String;");

	jobject hiResImageUri = GPMethodCallUtils::CallObjectMethod(javaScore, "getScoreHolderHiResImageUri", "()Landroid/net/Uri;");
	Score.ScoreHolderHiResImageUri = GPMethodCallUtils::CallStringMethod(hiResImageUri, "toString", "()Ljava/lang/String;");

	jobject iconImageUri = GPMethodCallUtils::CallObjectMethod(javaScore, "getScoreHolderIconImageUri", "()Landroid/net/Uri;");
	Score.ScoreHolderIconImageUri = GPMethodCallUtils::CallStringMethod(iconImageUri, "toString", "()Ljava/lang/String;");

	return Score;
}

TArray<uint8> ByteArrayFromTexture(UTexture2D* image)
{
	FTexturePlatformData* texturePlatformData;

#if ENGINE_MAJOR_VERSION == 4
	texturePlatformData = image->PlatformData;
#elif ENGINE_MAJOR_VERSION == 5
	texturePlatformData = image->GetPlatformData();
#endif

	bool isBGRA = texturePlatformData->PixelFormat == PF_B8G8R8A8;

	FColor* MipData = (FColor*)texturePlatformData->Mips[0].BulkData.Lock(LOCK_READ_ONLY);
	TArray<uint8> bytes;
	int w = image->GetSizeX();
	int h = image->GetSizeY();
	for (int i = 0; i < w * h; i++)
	{
		bytes.Add(isBGRA ? MipData[i].R : MipData[i].B);
		bytes.Add(MipData[i].G);
		bytes.Add(isBGRA ? MipData[i].B : MipData[i].R);
		bytes.Add(MipData[i].A);
	}
	texturePlatformData->Mips[0].BulkData.Unlock();

	image->UpdateResource();

	return bytes;
}

}
