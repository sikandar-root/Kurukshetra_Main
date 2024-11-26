// Copyright (c) 2018 Nineva Studios

#include "AGToastBPL.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJava.h"
#include "Android/Utils/AGMethodCallUtils.h"
#endif

static const ANSICHAR* AGToastClassName = "com/ninevastudios/androidgoodies/AGToast";

UAGToastBPL::UAGToastBPL(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UAGToastBPL::ShowToast(FString message, ToastLength length)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGToastClassName, "showToast", "(Landroid/app/Activity;Ljava/lang/String;I)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(message), length);

#endif
}
