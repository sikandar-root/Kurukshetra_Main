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

#else
	// Print message on the screen for other platforms
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,                       // Key (-1 to display a new message each time)
			5.0f,                     // Duration to display the message
			FColor::Green,            // Color of the message
			FString::Printf(TEXT("Toast Message: %s"), *message) // Format and print the message
		);
	}
#endif

}
