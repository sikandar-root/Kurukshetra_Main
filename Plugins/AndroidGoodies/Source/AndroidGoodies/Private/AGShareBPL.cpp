// Copyright (c) 2018 Nineva Studios

#include "AGShareBPL.h"
#include "HighResScreenshot.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJava.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/Utils/AGArrayConvertor.h"
#include "Android/Utils/AGMediaUtils.h"
#include "Android/Utils/AGMethodCallUtils.h"
#endif

static const ANSICHAR* AGShareClassName = "com/ninevastudios/androidgoodies/AGShare";

UAGShareBPL::UAGShareBPL(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UAGShareBPL::ShareText(FString subject, FString text, bool showChooser, FString chooserTitle)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGShareClassName, "shareText", "(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;ZLjava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(subject), *FJavaClassObject::GetJString(text), showChooser, *FJavaClassObject::GetJString(chooserTitle));

#endif
}

void UAGShareBPL::ShareImage(UTexture2D* image, bool showChooser, FString chooserTitle)
{
#if PLATFORM_ANDROID

	if (!image)
	{
		UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Texture is not assigned"));
		return;
	}

	FString imageTempFilePath = AGMediaUtils::SaveTextureToTempFile(image);

	AGMethodCallUtils::CallStaticVoidMethod(AGShareClassName, "shareImage", "(Landroid/app/Activity;Ljava/lang/String;ZLjava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(imageTempFilePath), showChooser, *FJavaClassObject::GetJString(chooserTitle));
#endif
}

void UAGShareBPL::ShareTextWithImage(FString subject, FString text, UTexture2D* image, bool showChooser, FString chooserTitle)
{
#if PLATFORM_ANDROID

	if (!image)
	{
		UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Texture is not assigned"));
		return;
	}

	FString imageTempFilePath = AGMediaUtils::SaveTextureToTempFile(image);

	AGMethodCallUtils::CallStaticVoidMethod(AGShareClassName, "shareTextWithImage",	"(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;ZLjava/lang/String;)V", 
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(subject), *FJavaClassObject::GetJString(text), *FJavaClassObject::GetJString(imageTempFilePath),
		showChooser, *FJavaClassObject::GetJString(chooserTitle));

#endif
}

void UAGShareBPL::ShareVideo(FString videoPath, bool showChooser, FString chooserTitle)
{
#if PLATFORM_ANDROID

	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Video path: %s"), *videoPath);

	AGMethodCallUtils::CallStaticVoidMethod(AGShareClassName, "shareVideo", "(Landroid/app/Activity;Ljava/lang/String;ZLjava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(videoPath), showChooser, *FJavaClassObject::GetJString(chooserTitle));

#endif
}

void UAGShareBPL::ShareInstagram(UTexture2D* image)
{
#if PLATFORM_ANDROID

	if (!image)
	{
		UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Texture is not assigned"));
		return;
	}

	FString imageTempFilePath = AGMediaUtils::SaveTextureToTempFile(image);

	AGMethodCallUtils::CallStaticVoidMethod(AGShareClassName, "sendInstagramImage", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(imageTempFilePath));

#endif
}

void UAGShareBPL::SendSmsWithDefaultApp(FString phoneNumber, FString message, bool showChooser, FString chooserTitle)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGShareClassName, "sendSmsViaMessagingApp",	"(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;ZLjava/lang/String;)V", 
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(phoneNumber), *FJavaClassObject::GetJString(message), showChooser, *FJavaClassObject::GetJString(chooserTitle));

#endif
}

void UAGShareBPL::SendSmsSilently(FString phoneNumber, FString message)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGShareClassName, "sendSmsDirectly", "(Ljava/lang/String;Ljava/lang/String;)V",
		*FJavaClassObject::GetJString(phoneNumber), *FJavaClassObject::GetJString(message));

#endif
}

void UAGShareBPL::TweetText(FString text)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGShareClassName, "tweetText", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(text));

#endif
}

void UAGShareBPL::TweetTextWithImage(FString text, UTexture2D* image)
{
#if PLATFORM_ANDROID

	if (!image)
	{
		UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Texture is not assigned"));
		return;
	}

	FString imageTempFilePath = AGMediaUtils::SaveTextureToTempFile(image);

	AGMethodCallUtils::CallStaticVoidMethod(AGShareClassName, "tweetTextWithImage", "(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(text), *FJavaClassObject::GetJString(imageTempFilePath));

#endif
}

void UAGShareBPL::SendFacebookText(FString text)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGShareClassName, "sendFacebookText", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(text));

#endif
}

void UAGShareBPL::SendFacebookImage(UTexture2D* image)
{
#if PLATFORM_ANDROID

	if (!image)
	{
		UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Texture is not assigned"));
		return;
	}

	FString imageTempFilePath = AGMediaUtils::SaveTextureToTempFile(image);

	AGMethodCallUtils::CallStaticVoidMethod(AGShareClassName, "sendFacebookImage", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(imageTempFilePath));

#endif
}

void UAGShareBPL::SendWhatsAppText(FString text)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGShareClassName, "sendWhatsAppText", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(text));

#endif
}

void UAGShareBPL::SendWhatsAppImage(UTexture2D* image)
{
#if PLATFORM_ANDROID

	if (!image)
	{
		UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Texture is not assigned"));
		return;
	}

	FString imageTempFilePath = AGMediaUtils::SaveTextureToTempFile(image);

	AGMethodCallUtils::CallStaticVoidMethod(AGShareClassName, "sendWhatsAppImage", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(imageTempFilePath));

#endif
}

void UAGShareBPL::SendTelegramText(FString text)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGShareClassName, "sendTelegramText", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(text));

#endif
}

void UAGShareBPL::SendTelegramImage(UTexture2D* image)
{
#if PLATFORM_ANDROID

	if (!image)
	{
		UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Texture is not assigned"));
		return;
	}

	FString imageTempFilePath = AGMediaUtils::SaveTextureToTempFile(image);

	AGMethodCallUtils::CallStaticVoidMethod(AGShareClassName, "sendTelegramImage", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(imageTempFilePath));

#endif
}

void UAGShareBPL::SendViberText(FString text)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGShareClassName, "sendViberText", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(text));
	
#endif
}

void UAGShareBPL::SendViberImage(UTexture2D* image)
{
#if PLATFORM_ANDROID

	if (!image)
	{
		UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Texture is not assigned"));
		return;
	}

	FString imageTempFilePath = AGMediaUtils::SaveTextureToTempFile(image);

	AGMethodCallUtils::CallStaticVoidMethod(AGShareClassName, "sendViberImage", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(imageTempFilePath));

#endif
}

void UAGShareBPL::SendMultipleImagesEMail(FAGShareEmailData emailData, TArray<UTexture2D*> extraImages, bool showChooser, FString chooserTitle)
{
#if PLATFORM_ANDROID
	
	bool bIsOptional = false;
	FString imagePath;
	FString extraImagePath;
	TArray<FString> extraImagePaths;

	if (emailData.Image)
	{
		imagePath = AGMediaUtils::SaveTextureToTempFile(emailData.Image);
	}

	if (extraImages.Num() > 0)
	{
		for (int i = 0; i < extraImages.Num(); i++)
		{
			if (!extraImages[i])
			{
				UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => No image attached"));
				continue;
			}
			extraImagePath = AGMediaUtils::SaveTextureToTempFile(extraImages[i]);
			extraImagePaths.Add(extraImagePath);
		}
	}

	AGMethodCallUtils::CallStaticVoidMethod(AGShareClassName, "sendMultipleImagesEMail",
		"(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/String;ZLjava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(emailData.Subject), *FJavaClassObject::GetJString(imagePath), AGArrayConvertor::ConvertToJStringArray(extraImagePaths), 
		AGArrayConvertor::ConvertToJStringArray(emailData.Recipients), AGArrayConvertor::ConvertToJStringArray(emailData.CCRecepients), AGArrayConvertor::ConvertToJStringArray(emailData.BCCRecepients), 
		showChooser, *FJavaClassObject::GetJString(chooserTitle));

#endif
}

void UAGShareBPL::SendEMail(FAGShareEmailData emailData, bool showChooser, FString chooserTitle)
{
#if PLATFORM_ANDROID

	bool bIsOptional = false;
	FString imagePath;

	if (emailData.Image)
	{
		imagePath = AGMediaUtils::SaveTextureToTempFile(emailData.Image);
	}

	AGMethodCallUtils::CallStaticVoidMethod(AGShareClassName, "sendEMail",
		"(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/String;ZLjava/lang/String;)V",
		FJavaWrapper::GameActivityThis, *FJavaClassObject::GetJString(emailData.Subject), *FJavaClassObject::GetJString(emailData.TextBody), *FJavaClassObject::GetJString(imagePath),
		AGArrayConvertor::ConvertToJStringArray(emailData.Recipients), AGArrayConvertor::ConvertToJStringArray(emailData.CCRecepients),
		AGArrayConvertor::ConvertToJStringArray(emailData.BCCRecepients), showChooser, *FJavaClassObject::GetJString(chooserTitle));

#endif
}