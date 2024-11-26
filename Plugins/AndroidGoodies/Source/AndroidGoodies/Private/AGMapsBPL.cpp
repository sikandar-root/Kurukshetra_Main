// Copyright (c) 2018 Nineva Studios

#include "AGMapsBPL.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJava.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/Utils/AGMethodCallUtils.h"
#include "Android/Utils/AGArrayConvertor.h"
#endif

static const ANSICHAR* AGMapsClassName = "com/ninevastudios/androidgoodies/AGMaps";

UAGMaps::UAGMaps(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UAGMaps::UserHasMapsApp()
{
#if PLATFORM_ANDROID

	return AGMethodCallUtils::CallStaticBoolMethod(AGMapsClassName, "userHasMapsApp", "(Landroid/app/Activity;)Z",
		FJavaWrapper::GameActivityThis);

#endif
	return false;
}

bool CheckLatitudeLongitudeAndZoom(float latitude, float longitude, int zoom)
{
	if (latitude < -90.0f || latitude > 90.0f)
	{
		return false;
	}
	if (longitude < -180.0f || longitude > 180.0f)
	{
		return false;
	}
	if (zoom < 1 || zoom > 23)
	{
		return false;
	}
	return true;
}

void UAGMaps::OpenMapLocation(float latitude, float longitude, int zoom)
{
#if PLATFORM_ANDROID

	if (CheckLatitudeLongitudeAndZoom(latitude, longitude, zoom))
	{
		AGMethodCallUtils::CallStaticVoidMethod(AGMapsClassName, "openMapLocation", "(Landroid/app/Activity;FFI)V",
			FJavaWrapper::GameActivityThis, latitude, longitude, zoom);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES =>  Please, check the validity of latitude, longitude and zoom values."));
	}
#endif
}

void UAGMaps::OpenMapLocationWithLabel(float latitude, float longitude, FString label)
{
#if PLATFORM_ANDROID

	int defaultZoomValue = 1;
	if (CheckLatitudeLongitudeAndZoom(latitude, longitude, defaultZoomValue))
	{
		AGMethodCallUtils::CallStaticVoidMethod(AGMapsClassName, "openMapLocationWithLabel", "(Landroid/app/Activity;FFLjava/lang/String;)V",
			FJavaWrapper::GameActivityThis, latitude, longitude, *FJavaClassObject::GetJString(label));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Please, check the validity of latitude and longitude values."));
	}
#endif
}

void UAGMaps::OpenMapLocationWithAddress(FString address)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGMapsClassName, "openMapLocation", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(address));

#endif
}