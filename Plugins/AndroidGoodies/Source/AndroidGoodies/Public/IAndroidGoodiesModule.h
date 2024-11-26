// Copyright (c) 2018 Nineva Studios

#pragma once

#include "Modules/ModuleManager.h"

class IAndroidGoodiesModule : public IModuleInterface
{
public:

	static inline IAndroidGoodiesModule& Get()
	{
		return FModuleManager::LoadModuleChecked< IAndroidGoodiesModule >("AndroidGoodies");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("AndroidGoodies");
	}
};
