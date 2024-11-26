// Copyright (c) 2020 Nineva Studios

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class UGooglePlayGoodiesSettings;

class FGooglePlayGoodiesModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/**
	* Singleton-like access to this module's interface.
	*
	* @return Returns singleton instance, loading the module on demand if needed
	*/
	static inline FGooglePlayGoodiesModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FGooglePlayGoodiesModule>("GooglePlayGoodies");
	}

	/**
	* Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	*
	* @return True if the module is loaded and ready to use
	*/
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("GooglePlayGoodies");
	}

	UGooglePlayGoodiesSettings* GetSettings() const;

private:

	UGooglePlayGoodiesSettings* GooglePlayGoodiesSettings;
};
