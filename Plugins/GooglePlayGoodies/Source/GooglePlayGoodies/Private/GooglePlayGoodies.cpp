// Copyright (c) 2020 Nineva Studios

#include "GooglePlayGoodies.h"
#include "GooglePlayGoodiesSettings.h"
#include "GooglePlayLog.h"
#include "Utils/GooglePlayGoodiesPluginUtils.h"

#include "Engine/Engine.h"
#include "Developer/Settings/Public/ISettingsModule.h"

#define LOCTEXT_NAMESPACE "FGooglePlayGoodiesModule"

void FGooglePlayGoodiesModule::StartupModule()
{
	const FString PluginName = "GooglePlayGoodies";

	GooglePlayGoodiesSettings = NewObject<UGooglePlayGoodiesSettings>((UObject*)GetTransientPackage(), "GooglePlayGoodiesSettings", RF_Standalone);
	GooglePlayGoodiesSettings->AddToRoot();

	// Register settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "GooglePlayGoodies",
			LOCTEXT("RuntimeSettingsName", "Google Play Goodies"),
			LOCTEXT("RuntimeSettingsDescription", "Configure Google Play Goodies"),
			GooglePlayGoodiesSettings);
	}

	const FString PluginVersionName = UGooglePlayGoodiesPluginUtils::GetPluginVersionName(PluginName);
	UE_LOG(LogGooglePlayGoodies, Verbose, TEXT("[%s] - Version: %s"), *PluginName, *PluginVersionName);
}

void FGooglePlayGoodiesModule::ShutdownModule()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "GooglePlayGoodies");
	}

	if (!GExitPurge)
	{
		// If we're in exit purge, this object has already been destroyed
		GooglePlayGoodiesSettings->RemoveFromRoot();
	}
	else
	{
		GooglePlayGoodiesSettings = nullptr;
	}
}

UGooglePlayGoodiesSettings* FGooglePlayGoodiesModule::GetSettings() const
{
	return GooglePlayGoodiesSettings;
}

#undef LOCTEXT_NAMESPACE

DEFINE_LOG_CATEGORY(LogGooglePlayGoodies);

IMPLEMENT_MODULE(FGooglePlayGoodiesModule, GooglePlayGoodies)
