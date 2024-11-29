// Copyright (c) 2020 Nineva Studios

#include "AGChosenFile.h"

#if PLATFORM_ANDROID
#include "Android/Utils/AGMethodCallUtils.h"
#endif

UAGChosenFile::~UAGChosenFile()
{
#if !WITH_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => UAGChosenFile::~UAGChosenFile()"));
#endif	
#if PLATFORM_ANDROID
	if (JavaChosenFileObject)
	{
		JNIEnv* Env = FAndroidApplication::GetJavaEnv();
		Env->DeleteGlobalRef(JavaChosenFileObject);
		JavaChosenFileObject = nullptr;
	}
#endif
}

bool UAGChosenFile::IsSuccess()
{
	bool IsSuccess = false;

#if PLATFORM_ANDROID
	IsSuccess = AGMethodCallUtils::CallBoolMethod(JavaChosenFileObject, "getDisplayName", "()Z");
#endif

	return IsSuccess;
}

FString UAGChosenFile::GetDisplayName()
{
	FString DisplayName;
	   
#if PLATFORM_ANDROID
	DisplayName = AGMethodCallUtils::CallStringMethod(JavaChosenFileObject, "getDisplayName", "()Ljava/lang/String;");
#endif

	return DisplayName;
}

 FString UAGChosenFile::GetOriginalPath()
 {
	 FString OriginalPath;

#if PLATFORM_ANDROID
	 OriginalPath = AGMethodCallUtils::CallStringMethod(JavaChosenFileObject, "getOriginalPath", "()Ljava/lang/String;");
#endif

	 return OriginalPath;
 }

 FString UAGChosenFile::GetMimeType()
 {
	 FString MimeType;

#if PLATFORM_ANDROID
	MimeType = AGMethodCallUtils::CallStringMethod(JavaChosenFileObject, "getMimeType", "()Ljava/lang/String;");
#endif

	return MimeType;
 }

 int64 UAGChosenFile::GetSize()
 {
	 int64 Size = -1;

#if PLATFORM_ANDROID
	 Size = (int64)AGMethodCallUtils::CallLongMethod(JavaChosenFileObject, "getSize", "()J");
#endif

	 return Size;
 }

 FDateTime UAGChosenFile::GetCreatedAt()
 {
	 FDateTime CreatedAt;

#if PLATFORM_ANDROID
	jobject CreatedAtDate = AGMethodCallUtils::CallObjectMethod(JavaChosenFileObject, "getCreatedAt", "()Ljava/util/Date;");
	int64 SecondsSinceEpoch = AGMethodCallUtils::CallLongMethod(CreatedAtDate, "getTime", "()J") / 1000;
	CreatedAt = FDateTime::FromUnixTimestamp(SecondsSinceEpoch);
#endif

	 return CreatedAt;
 }

 FString UAGChosenFile::GetFileExtensionFromMimeType()
 {
	 FString FileExtensionFromMimeType;

#if PLATFORM_ANDROID
	 FileExtensionFromMimeType = AGMethodCallUtils::CallStringMethod(JavaChosenFileObject, "getFileExtensionFromMimeType", "()Ljava/lang/String;");
#endif

	 return FileExtensionFromMimeType;
 }

 FString UAGChosenFile::GetFileExtensionFromMimeTypeWithoutDot()
 {
	 FString FileExtensionFromMimeTypeWithoutDot;

#if PLATFORM_ANDROID
	 FileExtensionFromMimeTypeWithoutDot = AGMethodCallUtils::CallStringMethod(JavaChosenFileObject, "getFileExtensionFromMimeTypeWithoutDot", "()Ljava/lang/String;");
#endif

	 return FileExtensionFromMimeTypeWithoutDot;
 }

 FString UAGChosenFile::GetHumanReadableSize(bool bytesRounded)
 {
	 FString HumanReadableSize;

#if PLATFORM_ANDROID
	 HumanReadableSize = AGMethodCallUtils::CallStringMethod(JavaChosenFileObject, "getHumanReadableSize", "(Z)Ljava/lang/String;", bytesRounded);
#endif

	 return HumanReadableSize;
 }

#if PLATFORM_ANDROID
 void UAGChosenFile::Init(jobject javaChosenFile)
 {
	 JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	 JavaChosenFileObject = Env->NewGlobalRef(javaChosenFile);
 }
#endif