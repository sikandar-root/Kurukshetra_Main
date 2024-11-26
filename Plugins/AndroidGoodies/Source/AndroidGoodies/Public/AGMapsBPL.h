// Copyright (c) 2018 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGMapsBPL.generated.h"

/*Class to open maps with locations, searches and addresses*/
UCLASS()
class ANDROIDGOODIES_API UAGMaps : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/**
	* Checks if user has any maps apps installed.
	* 
	* @return - true if there are maps apps installed, otherwise - false
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool UserHasMapsApp();

	/**
	* Show the map at the given longitude and latitude at a certain zoom level.
	* @param latitude - latitude of the location (may range from -90.0 to 90.0)
	* @param longitude - longitude of the location (may range from -180.0 to 180.0)
	* @param zoom - level of 1 shows the whole Earth, centered at the given latitude and longitude (the highest (closest) zoom level is 23)
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void OpenMapLocation(float latitude, float longitude, int zoom);

	/**
	* Show the map at the given longitude and latitude with a certain label.
	* @param latitude - latitude of the location (may range from -90.0 to 90.0)
	* @param longitude - longitude of the location (may range from -180.0 to 180.0)
	* @param label - name of existing map object situated at the provided location
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void OpenMapLocationWithLabel(float latitude, float longitude, FString label);

	/**
	* Opens the map location with the provided address.
	* @param address - address of certain object
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void OpenMapLocationWithAddress(FString address);
};