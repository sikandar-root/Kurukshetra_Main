//Copyright (c) 2020 Nineva Studios

#include "Utils/GooglePlayGoodiesPluginUtils.h"

FString UGooglePlayGoodiesPluginUtils::GetPluginVersionName(FString PluginName)
{
	FString VersionName = "";

	IPluginManager& PluginManager = IPluginManager::Get();
	TArray<TSharedRef<IPlugin>> Plugins = PluginManager.GetEnabledPlugins();
	for (const TSharedRef<IPlugin>& Plugin : Plugins)
	{
		if (Plugin->GetName() == PluginName)
		{
			const FPluginDescriptor& Descriptor = Plugin->GetDescriptor();
			VersionName = Descriptor.VersionName;
		}
	}

	return VersionName;
}