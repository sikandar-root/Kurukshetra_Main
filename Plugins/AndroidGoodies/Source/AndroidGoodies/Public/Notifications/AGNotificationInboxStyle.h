// Copyright (c) 2019 Nineva Studios

#pragma once

class IAndroidGoodiesNotificationInboxStyle;

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGNotificationInboxStyle.generated.h"

/**
* Helper class for generating large-format notifications that include a list of (up to 5) strings.
* If the platform does not provide large-format notifications, this method has no effect,
* the user will always see the normal notification view.
*/
UCLASS(BlueprintType)
class ANDROIDGOODIES_API UAGNotificationInboxStyle : public UObject
{
	GENERATED_BODY()

public:
	virtual ~UAGNotificationInboxStyle() override;

	/**
	* Append a line to the digest section of the Inbox notification.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	UAGNotificationInboxStyle* AddLine(FString Line);

	/**
	* Overrides ContentTitle in the big form of the template. This defaults to the value passed to SetTitle().
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	UAGNotificationInboxStyle* SetBigContentTitle(FString Title);

	/**
	* Set the first line of text after the detail section in the big form of the template.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	UAGNotificationInboxStyle* SetSummaryText(FString Summary);

	void Init(TSharedPtr<IAndroidGoodiesNotificationInboxStyle> Style);
	TSharedPtr<IAndroidGoodiesNotificationInboxStyle> GetNativeStyle();
	bool IsValid() const;

private:
	TSharedPtr<IAndroidGoodiesNotificationInboxStyle> NativeStyle = nullptr;
};
