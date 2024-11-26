// Copyright (c) 2018 Nineva Studios

#include "IAndroidGoodiesModule.h"
#include "Developer/Settings/Public/ISettingsModule.h"
#include "Utils/AndroidGoodiesPluginUtils.h"
#include "AndroidGoodiesLog.h"
#include "AndroidGoodiesSettings.h"
#include "CoreMinimal.h"
#include "UObject/UnrealType.h"
#include "UObject/UObjectGlobals.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "UObject/Package.h"
#include "UObject/WeakObjectPtr.h"
#include "Engine/Engine.h"
#include "Developer/Settings/Public/ISettingsModule.h"

#define LOCTEXT_NAMESPACE "AndroidGoodies"

class FAndroidGoodiesModule : public IAndroidGoodiesModule
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	UAndroidGoodiesSettings* AndroidGoodiesSettings;
};

IMPLEMENT_MODULE(FAndroidGoodiesModule, AndroidGoodies)

void FAndroidGoodiesModule::StartupModule()
{
	FString PluginName = "AndroidGoodies";

	AndroidGoodiesSettings = NewObject<UAndroidGoodiesSettings>(GetTransientPackage(), "AndroidGoodiesSettings", RF_Standalone);
	AndroidGoodiesSettings->AddToRoot();

	// Register settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "Android Goodies",
			LOCTEXT("RuntimeSettingsName", "Android Goodies"),
			LOCTEXT("RuntimeSettingsDescription", "Configure Android Goodies"),
			AndroidGoodiesSettings);
	}

	FString PluginVersionName = UAndroidGoodiesPluginUtils::GetPluginVersionName(PluginName);
	UE_LOG(LogAndroidGoodies, Verbose, TEXT("[%s] - Version: %s"), *PluginName, *PluginVersionName);
}

void FAndroidGoodiesModule::ShutdownModule()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "Android Goodies");
	}

	if (!GExitPurge)
	{
		// If we're in exit purge, this object has already been destroyed
		AndroidGoodiesSettings->RemoveFromRoot();
	}
	else
	{
		AndroidGoodiesSettings = nullptr;
	}
}

#undef LOCTEXT_NAMESPACE

DEFINE_LOG_CATEGORY(LogAndroidGoodies);
