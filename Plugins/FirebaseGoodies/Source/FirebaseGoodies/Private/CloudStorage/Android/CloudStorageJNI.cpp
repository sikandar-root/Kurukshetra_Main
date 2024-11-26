// Copyright (c) 2023 Nineva Studios

#include "FirebaseGoodiesLog.h"

#include "Android/Utils/FGJavaConvertor.h"
#include "Android/Utils/FGMethodCallUtils.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"
// #include "Android/AndroidJavaEnv.h"

#include "CloudStorage/Callbacks/FGCloudStorageUploadCallback.h"
#include "CloudStorage/Callbacks/FGCloudStorageDeleteFileCallback.h"
#include "CloudStorage/Callbacks/FGCloudStorageDownloadInMemoryCallback.h"
#include "CloudStorage/Callbacks/FGCloudStorageDownloadUrlCallback.h"
#include "CloudStorage/Callbacks/FGCloudStorageFileMetadataCallback.h"
#include "CloudStorage/Callbacks/FGCloudStorageProgressCallback.h"


JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudStorage_OnUploadFromDataInMemoryProgress(JNIEnv* env, jclass clazz, jlong objAddr, jint progress)
{
	int uploadProgress = FGJavaConvertor::FromJavaInt(progress);
	UFGCloudStorageUploadCallback* callback = reinterpret_cast<UFGCloudStorageUploadCallback*>(objAddr);

	if (IsValid(callback))
	{
		callback->ExecuteProgress(uploadProgress);
		callback->RemoveFromRoot();
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid progress callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudStorage_OnUploadFromDataInMemoryComplete(JNIEnv* env, jclass clazz, jlong objAddr)
{
	UFGCloudStorageUploadCallback* callback = reinterpret_cast<UFGCloudStorageUploadCallback*>(objAddr);

	if (IsValid(callback))
	{
		callback->ExecuteSuccess();
		callback->RemoveFromRoot();
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid complete callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudStorage_OnUploadFromDataInMemoryFailure(JNIEnv* env, jclass clazz, jlong objAddr, jstring error)
{
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, error);
	UE_LOG(LogFirebaseGoodies, Error, TEXT("Failed to upload: %s"), *ErrorMessage);
	
	UFGCloudStorageUploadCallback* callback = reinterpret_cast<UFGCloudStorageUploadCallback*>(objAddr);

	if (IsValid(callback))
	{
		callback->ExecuteError(ErrorMessage);
		callback->RemoveFromRoot();
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid error callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudStorage_OnUploadFromLocalFileProgress(JNIEnv* env, jclass clazz, jlong objAddr, jint progress)
{
	int uploadProgress = FGJavaConvertor::FromJavaInt(progress);

	UFGCloudStorageUploadCallback* callback = reinterpret_cast<UFGCloudStorageUploadCallback*>(objAddr);

	if (IsValid(callback))
	{
		callback->ExecuteProgress(uploadProgress);
		callback->RemoveFromRoot();
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid progress callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudStorage_OnUploadFromLocalFileComplete(JNIEnv* env, jclass clazz, jlong objAddr)
{
	UFGCloudStorageUploadCallback* callback = reinterpret_cast<UFGCloudStorageUploadCallback*>(objAddr);

	if (IsValid(callback))
	{
		callback->ExecuteSuccess();
		callback->RemoveFromRoot();
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid complete callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudStorage_OnUploadFromLocalFileFailure(JNIEnv* env, jclass clazz, jlong objAddr, jstring error)
{
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, error);
	UE_LOG(LogFirebaseGoodies, Error, TEXT("Failed to upload: %s"), *ErrorMessage);
	
	UFGCloudStorageUploadCallback* callback = reinterpret_cast<UFGCloudStorageUploadCallback*>(objAddr);

	if (IsValid(callback))
	{
		callback->ExecuteError(ErrorMessage);
		callback->RemoveFromRoot();
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid error callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudStorage_OnGetDownloadUrlComplete(JNIEnv* env, jclass clazz, jlong objAddr, jstring downloadUrl)
{
	FString downloadUrlString = FJavaHelper::FStringFromParam(env, downloadUrl);
	
	UFGCloudStorageDownloadUrlCallback* callback = reinterpret_cast<UFGCloudStorageDownloadUrlCallback*>(objAddr);

	if (IsValid(callback))
	{
		callback->ExecuteSuccess(downloadUrlString);
		callback->RemoveFromRoot();
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid complete callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudStorage_OnGetDownloadUrlError(JNIEnv* env, jclass clazz, jlong objAddr, jstring error)
{
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, error);
	UE_LOG(LogFirebaseGoodies, Error, TEXT("Failed to download: %s"), *ErrorMessage);
	
	UFGCloudStorageDownloadUrlCallback* callback = reinterpret_cast<UFGCloudStorageDownloadUrlCallback*>(objAddr);

	if (IsValid(callback))
	{
		callback->ExecuteError(ErrorMessage);
		callback->RemoveFromRoot();
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid error callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudStorage_OnDownloadToLocalFileProgress(JNIEnv* env, jclass clazz, jlong objAddr, jint progress)
{
	int uploadProgress = FGJavaConvertor::FromJavaInt(progress);
	
	UFGCloudStorageProgressCallback* callback = reinterpret_cast<UFGCloudStorageProgressCallback*>(objAddr);

	if (IsValid(callback))
	{
		callback->ExecuteProgress(uploadProgress);
		callback->RemoveFromRoot();
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid progress callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudStorage_OnDownloadToLocalFileComplete(JNIEnv* env, jclass clazz, jlong objAddr, jstring path)
{
	FString pathString = FJavaHelper::FStringFromParam(env, path);

	UFGCloudStorageProgressCallback* callback = reinterpret_cast<UFGCloudStorageProgressCallback*>(objAddr);

	if (IsValid(callback))
	{
		callback->ExecuteSuccess(pathString);
		callback->RemoveFromRoot();
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid complete callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudStorage_OnDownloadToLocalFileError(JNIEnv* env, jclass clazz, jlong objAddr, jstring error)
{
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, error);
	UE_LOG(LogFirebaseGoodies, Error, TEXT("Failed to download: %s"), *ErrorMessage);

	UFGCloudStorageProgressCallback* callback = reinterpret_cast<UFGCloudStorageProgressCallback*>(objAddr);

	if (IsValid(callback))
	{
		callback->ExecuteError(ErrorMessage);
		callback->RemoveFromRoot();
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid error callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudStorage_OnDeleteFileComplete(JNIEnv* env, jclass clazz, jlong objAddr)
{
	UFGCloudStorageDeleteFileCallback* callback = reinterpret_cast<UFGCloudStorageDeleteFileCallback*>(objAddr);

	if (IsValid(callback))
	{
		callback->ExecuteSuccess();
		callback->RemoveFromRoot();
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid complete callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudStorage_OnDeleteFileError(JNIEnv* env, jclass clazz, jlong objAddr, jstring error)
{
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, error);
	UE_LOG(LogFirebaseGoodies, Error, TEXT("Failed to delete: %s"), *ErrorMessage);

	UFGCloudStorageDeleteFileCallback* callback = reinterpret_cast<UFGCloudStorageDeleteFileCallback*>(objAddr);

	if (IsValid(callback))
	{
		callback->ExecuteError(ErrorMessage);
		callback->RemoveFromRoot();
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid error callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudStorage_OnDownloadInMemoryComplete(JNIEnv* env, jclass clazz, jlong objAddr, jbyteArray buffer)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	TArray<uint8> byteArray = FGJavaConvertor::ConvertToByteArray(buffer);
	
	UFGCloudStorageDownloadInMemoryCallback* callback = reinterpret_cast<UFGCloudStorageDownloadInMemoryCallback*>(objAddr);

	if (IsValid(callback))
	{
		callback->ExecuteSuccess(byteArray);
		callback->RemoveFromRoot();
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid complete callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudStorage_OnDownloadInMemoryError(JNIEnv* env, jclass clazz, jlong objAddr, jstring error)
{
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, error);
	UE_LOG(LogFirebaseGoodies, Error, TEXT("Failed to download: %s"), *ErrorMessage);
	
	UFGCloudStorageDownloadInMemoryCallback* callback = reinterpret_cast<UFGCloudStorageDownloadInMemoryCallback*>(objAddr);

	if (IsValid(callback))
	{
		callback->ExecuteError(ErrorMessage);
		callback->RemoveFromRoot();
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid error callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudStorage_OnGetMetadataComplete(JNIEnv* env, jclass clazz, jlong objAddr, jobject metadata)
{
	UFGStorageMetadata* result = NewObject<UFGStorageMetadata>();
	result->Init(metadata);

	UFGCloudStorageFileMetadataCallback* callback = reinterpret_cast<UFGCloudStorageFileMetadataCallback*>(objAddr);

	if (IsValid(callback))
	{
		callback->ExecuteSuccess(result);
		callback->RemoveFromRoot();
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid complete callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudStorage_OnGetMetadataError(JNIEnv* env, jclass clazz, jlong objAddr, jstring error)
{
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, error);
	UE_LOG(LogFirebaseGoodies, Error, TEXT("Failed to get metadata: %s"), *ErrorMessage);
	
	UFGCloudStorageFileMetadataCallback* callback = reinterpret_cast<UFGCloudStorageFileMetadataCallback*>(objAddr);

	if (IsValid(callback))
	{
		callback->ExecuteError(ErrorMessage);
		callback->RemoveFromRoot();
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid error callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudStorage_OnUpdateMetadataComplete(JNIEnv* env, jclass clazz, jlong objAddr, jobject metadata)
{
	UFGStorageMetadata* result = NewObject<UFGStorageMetadata>();
	result->Init(metadata);
	
	UFGCloudStorageFileMetadataCallback* callback = reinterpret_cast<UFGCloudStorageFileMetadataCallback*>(objAddr);

	if (IsValid(callback))
	{
		callback->ExecuteSuccess(result);
		callback->RemoveFromRoot();
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid complete callback"));
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGCloudStorage_OnUpdateMetadataError(JNIEnv* env, jclass clazz, jlong objAddr, jstring error)
{
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, error);
	UE_LOG(LogFirebaseGoodies, Error, TEXT("Failed to update metadata: %s"), *ErrorMessage);
	
	UFGCloudStorageFileMetadataCallback* callback = reinterpret_cast<UFGCloudStorageFileMetadataCallback*>(objAddr);

	if (IsValid(callback))
	{
		callback->ExecuteError(ErrorMessage);
		callback->RemoveFromRoot();
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Invalid error callback"));
	}
}