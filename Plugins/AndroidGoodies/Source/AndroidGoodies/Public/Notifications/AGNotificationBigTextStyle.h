// Copyright (c) 2019 Nineva Studios

#pragma once

class IAndroidGoodiesNotificationBigTextStyle;

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGNotificationBigTextStyle.generated.h"

/**
* Helper class for generating large-format notifications that include a lot of text.
* If the platform does not provide large-format notifications, this method has no effect.
* The user will always see the normal notification view.
*/

UCLASS(BlueprintType)
class ANDROIDGOODIES_API UAGNotificationBigTextStyle : public UObject
{
	GENERATED_BODY()

public:
	virtual ~UAGNotificationBigTextStyle() override;


	/**
	* Override the ContentTitle in the big form of the template. This defaults to the value passed to SetContentTitle().
	*
	* @param Title - content title.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	UAGNotificationBigTextStyle* SetBigContentTitle(FString Title);

	/**
	* Set the first line of text after the detail section in the big form of the template.
	*
	* @param Summary - summary text.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	UAGNotificationBigTextStyle* SetSummaryText(FString Summary);

	void Init(TSharedPtr<IAndroidGoodiesNotificationBigTextStyle> Style);
	TSharedPtr<IAndroidGoodiesNotificationBigTextStyle> GetNativeStyle();
	bool IsValid() const;
private:
	TSharedPtr<IAndroidGoodiesNotificationBigTextStyle> NativeStyle;
};
