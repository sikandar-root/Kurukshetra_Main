// Copyright (c) 2020 Nineva Studios

#pragma once

#include "CoreMinimal.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#endif

#include "GPEvent.generated.h"

class UTexture2D;

UCLASS(BlueprintType)
class GOOGLEPLAYGOODIES_API UGPEvent : public UObject
{
	GENERATED_BODY()

public:
	UGPEvent() = default;
	virtual ~UGPEvent();

#if PLATFORM_ANDROID
	void Init(jobject EventObject);
#endif

	DECLARE_DYNAMIC_DELEGATE_OneParam(FGPOnImageReadyDelegate, UTexture2D*, ImageTexture);

	/**
	* Get the event's id
	*
	* @return - Event's id
	*/
	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Events")
	FString EventId() const;

	/**
	* Get the event's name
	*
	* @return - Event's name
	*/
	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Events")
	FString EventName() const;

	/**
	* Get the event's description
	*
	* @return - Event's description
	*/
	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Events")
	FString EventDescription() const;

	/**
	* Get the number of increments the logged in user has made to this event
	*
	* @return - The number of increments the logged in user has made to this event.
	*/
	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Events")
	int EventValue() const;

	/**
	* Retrieves the sum of increments have been made to this event (formatted for the user's locale)
	*
	* @return - The formatted number of increments the logged in user has made to this event.
	*/
	UFUNCTION(BlueprintPure, Category = "Google Play Goodies|Events")
	FString EventFormattedValue() const;

	/**
	* Get the event's icon image
	*
	* @param OnImageReady - Called when the image is ready for use
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Events")
	void GetIconImage(const FGPOnImageReadyDelegate& OnImageReady);

	void OnIconImageReady(UTexture2D* Tex) { OnIconImageReadyDelegate.ExecuteIfBound(Tex); }

private:
	FGPOnImageReadyDelegate OnIconImageReadyDelegate;

#if PLATFORM_ANDROID
	jobject Event;
	jmethodID GetIdMethod;
	jmethodID GetNameMethod;
	jmethodID GetDescriptionMethod;
	jmethodID GetValueMethod;
	jmethodID GetFormattedValueMethod;
	jmethodID GetIconImageMethod;
#endif
};
