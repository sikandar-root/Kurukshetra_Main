//Copyright (c) 2020 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "Interfaces/IPluginManager.h"
#include "PluginDescriptor.h"

#include "AndroidGoodiesPluginUtils.generated.h"

UCLASS()
class UAndroidGoodiesPluginUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	* Get version name
	*
	* @param PluginName - name of the plugin to get info from
	*/
	UFUNCTION(BlueprintCallable, Category = "Admob Goodies | Plugin Utils")
		static FString GetPluginVersionName(FString PluginName);
};

