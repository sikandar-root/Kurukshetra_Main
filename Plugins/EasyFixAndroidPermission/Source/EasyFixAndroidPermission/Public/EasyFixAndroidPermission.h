// Copyright 2024 Gdy Development, Inc. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FEasyFixAndroidPermissionModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
