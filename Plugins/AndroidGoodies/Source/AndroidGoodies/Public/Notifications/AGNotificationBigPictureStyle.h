// Copyright (c) 2019 Nineva Studios

#pragma once

class IAndroidGoodiesNotificationBigPictureStyle;

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGNotificationBigPictureStyle.generated.h"

/**
* Helper class for generating large-format notifications that include a large image attachment.
* If the platform does not provide large-format notifications, this method has no effect,
* the user will always see the normal notification view.
*/
UCLASS(BlueprintType)
class ANDROIDGOODIES_API UAGNotificationBigPictureStyle : public UObject
{
	GENERATED_BODY()

public:
	virtual ~UAGNotificationBigPictureStyle() override;

	/**
	* Override the large icon when the big notification is shown.
	*
	* @param Icon - image for the large icon.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	UAGNotificationBigPictureStyle* SetBigLargeIcon(UTexture2D* Icon);

	/**
	* Override the ContentTitle in the big form of the template. This defaults to the value passed to SetContentTitle().
	*
	* @param Title - content title.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	UAGNotificationBigPictureStyle* SetBigContentTitle(FString Title);

	/**
	* Set the first line of text after the detail section in the big form of the template.
	*
	* @param Text - summary text.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	UAGNotificationBigPictureStyle* SetSummaryText(FString Text);

	void Init(TSharedPtr<IAndroidGoodiesNotificationBigPictureStyle> Style);
	TSharedPtr<IAndroidGoodiesNotificationBigPictureStyle> GetNativeStyle();
	bool IsValid() const;

private:
	TSharedPtr<IAndroidGoodiesNotificationBigPictureStyle> NativeStyle;
};
