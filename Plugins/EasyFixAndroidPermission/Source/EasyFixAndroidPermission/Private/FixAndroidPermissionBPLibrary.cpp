// Copyright 2024 Gdy Development, Inc. All Rights Reserved.



#include "FixAndroidPermissionBPLibrary.h"
#include "Kismet/GameplayStatics.h"



#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "AndroidPermissionFunctionLibrary.h"
#include "AndroidPermissionCallbackProxy.h"

#endif



int32 UFixAndroidPermissionBPLibrary::GetSDKVersion()
{
	int32 SDKVersion = -1; 

#if PLATFORM_ANDROID
	JNIEnv* JEnv = FAndroidApplication::GetJavaEnv();

	jclass VersionClass = JEnv->FindClass("android/os/Build$VERSION");
	jfieldID VersionField = JEnv->GetStaticFieldID(VersionClass, "SDK_INT", "I");
	SDKVersion = JEnv->GetStaticIntField(VersionClass, VersionField);


#endif

	return SDKVersion;
}

UAndroidPermissionCallbackProxy* UFixAndroidPermissionBPLibrary::CheckAndRequestAndroidStoragePermissions()
{
    if (GetSDKVersion() < 30)
    {

#if PLATFORM_ANDROID
        // Define the permissions you want to check/request
        FString WritePermission = "android.permission.WRITE_EXTERNAL_STORAGE";
        FString ReadPermission = "android.permission.READ_EXTERNAL_STORAGE";

        // Check if the permission is already granted
        bool bHasWritePermission = UAndroidPermissionFunctionLibrary::CheckPermission(WritePermission);
        bool bHasReadPermission = UAndroidPermissionFunctionLibrary::CheckPermission(ReadPermission);

        if (!bHasWritePermission || !bHasReadPermission)
        {
            // Request the permissions and return the callback proxy
            TArray<FString> PermissionsToRequest;
            if (!bHasWritePermission)
            {
                PermissionsToRequest.Add(WritePermission);
            }
            if (!bHasReadPermission)
            {
                PermissionsToRequest.Add(ReadPermission);
            }

            return UAndroidPermissionFunctionLibrary::AcquirePermissions(PermissionsToRequest);
        }

#endif
    }

    return nullptr;
}

void UFixAndroidPermissionBPLibrary::CheckAndroidStoragePermissionsGranted(EOnSuccess& OnSuccess, const TArray<bool>& BoolArray)
{
    if (BoolArray.Num() > 0)
    {
        if (BoolArray[0])
        {
            OnSuccess = EOnSuccess::OnSuccess;
        }
        else
        {
            OnSuccess = EOnSuccess::OnUnsuccess;
        }

    }
    else
    {
        OnSuccess = EOnSuccess::OnUnsuccess;

    }
}









