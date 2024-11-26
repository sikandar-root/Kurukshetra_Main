// Copyright (c) 2020 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "GPEventLibrary.generated.h"

class UGPEvent;

UCLASS()
class GOOGLEPLAYGOODIES_API UGPEventLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGPLoadEventsDelegate, const TArray<UGPEvent*>&, Events);
	
	/**
	* Increment an event value.
	*
	* @param EventID - ID of the event to increment
	* @param Value - Amount to be incremented by
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Events")
	static void IncrementEvent(const FString& EventID, int Value = 1);

	/**
	* Retrieve event data.
	*
	* @param OnLoadEvents - Called when events data successfully loaded
	* @param ForceRefresh - If true, this call will clear any locally cached data and attempt to fetch the latest data from the server
	* @param EventIds - IDs of the events to load, if empty all available events will be loaded
	*/
	UFUNCTION(BlueprintCallable, Category = "Google Play Goodies|Events", meta = (AutoCreateRefTerm = "EventIds"))
	static void LoadEvents(const FGPLoadEventsDelegate& OnLoadEvents, bool ForceRefresh, const TArray<FString>& EventIds);

	static FGPLoadEventsDelegate OnLoadEventsDelegate;
};
