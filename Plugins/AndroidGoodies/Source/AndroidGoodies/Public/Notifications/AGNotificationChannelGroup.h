// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGNotificationChannel.h"
#include "Kismet/BlueprintFunctionLibrary.h"
class IAndroidGoodiesNotificationChannelGroup;

#include "AGNotificationChannelGroup.generated.h"

UCLASS(BlueprintType)
class ANDROIDGOODIES_API UAGNotificationChannelGroup : public UObject
{
	GENERATED_BODY()

public:
	virtual ~UAGNotificationChannelGroup() override;

	/**
	* Get the id of this group.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	FString GetId();

	/**
	* Get the user visible name of this group.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	FString GetName();

	/**
	* Get the user visible description of this group.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	FString GetDescription();

	/**
	* Set the user visible description of this group.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	UAGNotificationChannelGroup* SetDescription(FString Description);

	/**
	* Get whether or not notifications posted to channels belonging to this group are blocked.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	bool IsBlocked();

	/**
	* Get the list of channels that belong to this group
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Notifications")
	TArray<UAGNotificationChannel*> GetChannels();

	void Init(TSharedPtr<IAndroidGoodiesNotificationChannelGroup> Group);
	TSharedPtr<IAndroidGoodiesNotificationChannelGroup> GetNativeNotificationChannelGroup();
	bool IsValid() const;

private:
	TSharedPtr<IAndroidGoodiesNotificationChannelGroup> NativeNotificationChannelGroup = nullptr;
};
