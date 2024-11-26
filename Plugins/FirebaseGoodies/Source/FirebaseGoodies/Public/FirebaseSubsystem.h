// Copyright (c) 2022 Nineva Studios

#pragma once

#include "FirebaseGoodiesSettings.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "FirebaseSubsystem.generated.h"

UCLASS()
class FIREBASEGOODIES_API UFirebaseSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/**
	* @return true if Firebase app initialized successfully.
	*/
	UFUNCTION(BlueprintPure, Category = "Firebase Goodies")
	bool IsAppValid() const;

private:
	static void LogInit();
	void InitDesktop(const UFirebaseGoodiesSettings* Settings) const;
	void InitIos(const UFirebaseGoodiesSettings* Settings);
	static void InitDbOptions(const UFirebaseGoodiesSettings* Settings);
};
