// Copyright (c) 2023 Nineva Studios

#include "CloudStorageAndroid.h"

#include "Android/Utils/FGJavaConvertor.h"
#include "Android/Utils/FGMethodCallUtils.h"
#include "FirebaseGoodiesLog.h"

#include "CloudStorage/Callbacks/FGCloudStorageDeleteFileCallback.h"
#include "CloudStorage/Callbacks/FGCloudStorageDownloadInMemoryCallback.h"
#include "CloudStorage/Callbacks/FGCloudStorageDownloadUrlCallback.h"
#include "CloudStorage/Callbacks/FGCloudStorageFileMetadataCallback.h"
#include "CloudStorage/Callbacks/FGCloudStorageProgressCallback.h"
#include "CloudStorage/Callbacks/FGCloudStorageUploadCallback.h"

const ANSICHAR* CloudStorageAndroid::FGCloudStorageClassName = "com/ninevastudios/unrealfirebase/FGCloudStorage";

CloudStorageAndroid::~CloudStorageAndroid()
{
}

void CloudStorageAndroid::UploadFromDataInMemory(const TArray<uint8>& FileInMemory, const FString& FileStoragePath,
	const FCloudStorageIntDelegate& OnUploadFromDataInMemoryProgress, const FCloudStorageVoidDelegate& OnSuccess,
	const FCloudStorageStringDelegate& OnError)
{
	UFGCloudStorageUploadCallback* NativeCallback = NewObject<UFGCloudStorageUploadCallback>();
	NativeCallback->AddToRoot();
	NativeCallback->BindProgressDelegate(OnUploadFromDataInMemoryProgress);
	NativeCallback->BindSuccessDelegate(OnSuccess);
	NativeCallback->BindErrorDelegate(OnError);

	const int32 BufferSize = FileInMemory.Num();

	jbyteArray jArray = FGJavaConvertor::ConvertToJByteArray(FileInMemory);

	FGMethodCallUtils::CallStaticVoidMethod(FGCloudStorageClassName, "uploadFromDataInMemory", "(J[BLjava/lang/String;)V", 
		(jlong) NativeCallback, jArray, *FJavaClassObject::GetJString(FileStoragePath));
}

void CloudStorageAndroid::UploadFromLocalFile(const FString& LocalFilePath, const FString& FileStoragePath,
	const FCloudStorageIntDelegate& OnUploadProgress, const FCloudStorageVoidDelegate& OnSuccess,
	const FCloudStorageStringDelegate& OnError)
{
	UFGCloudStorageUploadCallback* NativeCallback = NewObject<UFGCloudStorageUploadCallback>();
	NativeCallback->AddToRoot();
	NativeCallback->BindProgressDelegate(OnUploadProgress);
	NativeCallback->BindSuccessDelegate(OnSuccess);
	NativeCallback->BindErrorDelegate(OnError);

	FGMethodCallUtils::CallStaticVoidMethod(FGCloudStorageClassName, "uploadFromLocalFile", "(JLjava/lang/String;Ljava/lang/String;)V", 
	(jlong) NativeCallback, *FJavaClassObject::GetJString(LocalFilePath), *FJavaClassObject::GetJString(FileStoragePath));
}

void CloudStorageAndroid::GetDownloadUrl(const FString& FileStoragePath, const FCloudStorageStringDelegate& OnSuccess,
	const FCloudStorageStringDelegate& OnError)
{
	UFGCloudStorageDownloadUrlCallback* NativeCallback = NewObject<UFGCloudStorageDownloadUrlCallback>();
	NativeCallback->AddToRoot();
	NativeCallback->BindSuccessDelegate(OnSuccess);
	NativeCallback->BindErrorDelegate(OnError);

	FGMethodCallUtils::CallStaticVoidMethod(FGCloudStorageClassName, "getDownloadUrl", "(JLjava/lang/String;)V",
		(jlong) NativeCallback, *FJavaClassObject::GetJString(FileStoragePath));
}

void CloudStorageAndroid::DownloadToLocalFile(const FString& FileStoragePath, const FString& LocalFileName,
	EAndroidStorageLocation Destination, const FCloudStorageStringDelegate& OnSuccess,
	const FCloudStorageStringDelegate& OnError, const FCloudStorageIntDelegate& OnProgress)
{
	FString EnumAsString = UEnum::GetDisplayValueAsText(Destination).ToString();

	UFGCloudStorageProgressCallback* NativeCallback = NewObject<UFGCloudStorageProgressCallback>();
	NativeCallback->AddToRoot();
	NativeCallback->BindProgressDelegate(OnProgress);
	NativeCallback->BindSuccessDelegate(OnSuccess);
	NativeCallback->BindErrorDelegate(OnError);
	
	FGMethodCallUtils::CallStaticVoidMethod(FGCloudStorageClassName, "downloadToLocalFile", "(Landroid/app/Activity;JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis,
		(jlong) NativeCallback,
		*FJavaClassObject::GetJString(FileStoragePath),
		*FJavaClassObject::GetJString(LocalFileName),
		*FJavaClassObject::GetJString(EnumAsString));
}

void CloudStorageAndroid::DeleteFile(const FString& FileStoragePath, const FCloudStorageVoidDelegate& OnSuccess,
	const FCloudStorageStringDelegate& OnError)
{
	UFGCloudStorageDeleteFileCallback* NativeCallback = NewObject<UFGCloudStorageDeleteFileCallback>();
	NativeCallback->AddToRoot();
	NativeCallback->BindSuccessDelegate(OnSuccess);
	NativeCallback->BindErrorDelegate(OnError);

	FGMethodCallUtils::CallStaticVoidMethod(FGCloudStorageClassName, "deleteFile", "(JLjava/lang/String;)V",
		(jlong) NativeCallback, *FJavaClassObject::GetJString(FileStoragePath));
}

void CloudStorageAndroid::DownloadInMemory(const FString& FileStoragePath, int64 FileSizeLimit,
	const FCloudStorageByteArrayDelegate& OnSuccess, const FCloudStorageStringDelegate& OnError)
{
	UFGCloudStorageDownloadInMemoryCallback* NativeCallback = NewObject<UFGCloudStorageDownloadInMemoryCallback>();
	NativeCallback->AddToRoot();
	NativeCallback->BindSuccessDelegate(OnSuccess);
	NativeCallback->BindErrorDelegate(OnError);
	
	FGMethodCallUtils::CallStaticVoidMethod(FGCloudStorageClassName, "downloadInMemory", "(JLjava/lang/String;J)V", 
	(jlong) NativeCallback, *FJavaClassObject::GetJString(FileStoragePath), (jlong)FileSizeLimit);
}

void CloudStorageAndroid::GetFileMetadata(const FString& FileStoragePath,
	const FCloudStorageMetadataDelegate& OnSuccess, const FCloudStorageStringDelegate& OnError)
{
	UFGCloudStorageFileMetadataCallback* NativeCallback = NewObject<UFGCloudStorageFileMetadataCallback>();
	NativeCallback->AddToRoot();
	NativeCallback->BindSuccessDelegate(OnSuccess);
	NativeCallback->BindErrorDelegate(OnError);

	FGMethodCallUtils::CallStaticVoidMethod(FGCloudStorageClassName, "getFileMetadata", "(JLjava/lang/String;)V",
		(jlong) NativeCallback, *FJavaClassObject::GetJString(FileStoragePath));
}

void CloudStorageAndroid::UpdateFileMetadata(const FString& FileStoragePath,
	UFGStorageMetadataValues* NewMetadataValues, const FCloudStorageMetadataDelegate& OnSuccess,
	const FCloudStorageStringDelegate& OnError)
{
	UFGCloudStorageFileMetadataCallback* NativeCallback = NewObject<UFGCloudStorageFileMetadataCallback>();
	NativeCallback->AddToRoot();
	NativeCallback->BindSuccessDelegate(OnSuccess);
	NativeCallback->BindErrorDelegate(OnError);
	
	FGMethodCallUtils::CallStaticVoidMethod(FGCloudStorageClassName, "updateMetadata",
	"(JLjava/lang/String;Lcom/google/firebase/storage/StorageMetadata$Builder;)V",
	(jlong) NativeCallback,
	*FJavaClassObject::GetJString(FileStoragePath),
	NewMetadataValues->JavaMetadataBuilderObject);
}
