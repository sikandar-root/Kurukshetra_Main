// Copyright (c) 2018 Nineva Studios

#pragma once

#include "AGShareEmailData.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/Texture2D.h"
#include "AGShareBPL.generated.h"

UCLASS()
class ANDROIDGOODIES_API UAGShareBPL : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/**
	* Share the text using default Android intent.
	* @param subject - subject of message to be shared
	* @param text - text of message to be shared
	* @param showChooser - flag that indicates whether to show app chooser
	* @param chooserTitle - chooser title text
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void ShareText(FString subject, FString text, bool showChooser = true, FString chooserTitle = "Share via...");

	/**
	* Share the image using default Android intent.
	* @param image - image to be shared
	* @param showChooser - flag that indicates whether to show app chooser
	* @param chooserTitle - chooser title text
	* @note Temporary image file will be located in external storage Pictures folder, not in the app folder.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void ShareImage(UTexture2D* image, bool showChooser = true, FString chooserTitle = "Share via...");

	/**
	* Share the text with image using default Android intent.
	* @param subject - subject of message to be shared
	* @param text - text of message to be shared
	* @param image - image to be shared
	* @param showChooser - flag that indicates whether to show app chooser
	* @param chooserTitle - chooser title text
	* @note Temporary image file will be located in external storage Pictures folder, not in the app folder.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void ShareTextWithImage(FString subject, FString text, UTexture2D* image, bool showChooser = true, FString chooserTitle = "Share via...");

	/**
	* Share the video that is stored on file system. You must provide a correct video path for this method to work properly.
	* @param showChooser - flag that indicates whether to show app chooser
	* @param chooserTitle - chooser title text
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void ShareVideo(FString videoPath, bool showChooser = true, FString chooserTitle = "Share via...");

	/**
	* Send the Instagram image message.
	* @param image - image to be shared
	* @note Does nothing if Instagram is not installed.
	* @note Temporary image file will be located in external storage Pictures folder, not in the app folder.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void ShareInstagram(UTexture2D* image);

	/**
	* Send the sms using default Android intent.
	* @param phoneNumber - telephone number of sms recipient
	* @param message - sms message text
	* @param showChooser - flag that indicates whether to show app chooser
	* @param chooserTitle - chooser title text
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void SendSmsWithDefaultApp(FString phoneNumber, FString message, bool showChooser = true, FString chooserTitle = "Send SMS via...");

	/**
	* Send the sms without opening messaging app.
	* @param phoneNumber - telephone number of sms recipient
	* @param message - sms message text
	* @note User can later find the message in the Sent folder.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void SendSmsSilently(FString phoneNumber, FString message);

	/**
	* Tweet the specified text.
	* @param text - text of message to be shared
	* @note Does nothing if Twitter is not installed.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void TweetText(FString text);

	/**
	* Tweet the specified text and image.
	* @param text - text of message to be shared
	* @param image - image to be shared
	* @note Does nothing if Twitter is not installed.
	* @note Temporary image file will be located in external storage Pictures folder, not in the app folder.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void TweetTextWithImage(FString text, UTexture2D* image);

	/**
	* Send the Facebook text message.
	* @param text - text of message to be shared
	* @note Does nothing if Facebook messenger is not installed.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void SendFacebookText(FString text);

	/**
	* Send the Facebook image message.
	* @param image - image to be shared
	* @note Does nothing if Facebook messenger is not installed.
	* @note Temporary image file will be located in external storage Pictures folder, not in the app folder.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void SendFacebookImage(UTexture2D* image);

	/**
	* Send the WhatsApp message text.
	* @param text - text of message to be shared
	* @note Does nothing if WhatsApp is not installed.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void SendWhatsAppText(FString text);

	/**
	* Send the WhatsApp image message.
	* @param image - image to be shared
	* @note Does nothing if WhatsApp is not installed.
	* @note Temporary image file will be located in external storage Pictures folder, not in the app folder.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void SendWhatsAppImage(UTexture2D* image);

	/**
	* Send the Telegram text message.
	* @param text - text of message to be shared
	* @note Does nothing if Telegram is not installed.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void SendTelegramText(FString text);

	/**
	* Send the Telegram image message.
	* @param image - image to be shared
	* @note Does nothing if Telegram is not installed.
	* @note Temporary image file will be located in external storage Pictures folder, not in the app folder.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void SendTelegramImage(UTexture2D* image);

	/**
	* Send the Viber text message.
	* @param text - text of message to be shared
	* @note Does nothing if Viber is not installed.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void SendViberText(FString text);

	/**
	* Send the Viber image message.
	* @param image - image to be shared
	* @note Does nothing if Viber is not installed.
	* @note Temporary image file will be located in external storage Pictures folder, not in the app folder.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void SendViberImage(UTexture2D* image);

	/**
	* Send the email using Android intent.
	* @param emailData - structure with data to be shared via email
	* @param extraImages - array of images to be shared via email
	* @param showChooser - flag that indicates whether to show app chooser
	* @param chooserTitle - chooser title text
	* @note Temporary image file(s) will be located in external storage Pictures folder, not in the app folder.
	* @note In case of multiple images to be shared the possibility of adding text body to an email is absent.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies", meta = (AutoCreateRefTerm = "ExtraImages"))
	static void SendMultipleImagesEMail(FAGShareEmailData emailData, TArray<UTexture2D*> extraImages, bool showChooser = true, FString chooserTitle = "Send via...");

	/**
	* Send the email using Android intent.
	* @param emailData - structure with data to be shared via email
	* @param showChooser - flag that indicates whether to show app chooser
	* @param chooserTitle - chooser title text
	* @note Temporary image file will be located in external storage Pictures folder, not in the app folder.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void SendEMail(FAGShareEmailData emailData, bool showChooser = true, FString chooserTitle = "Send via...");
};