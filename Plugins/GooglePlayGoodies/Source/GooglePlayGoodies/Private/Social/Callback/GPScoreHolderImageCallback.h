// Copyright (c) 2020 Nineva Studios

#pragma once

#include "CoreMinimal.h"

#include "Social/GPLeaderboardLibrary.h"

#include "GPScoreHolderImageCallback.generated.h"

UCLASS()
class UGPScoreHolderImageCallback : public UObject
{
	GENERATED_BODY()

public:
	UGPScoreHolderImageCallback();

	void BindDelegate(const FGPOnScoreHolderImageReadyDelegate& OnImageReady);
	void ExecuteDelegate(UTexture2D* Image, FString Uri);

private:
	UPROPERTY()
	FGPOnScoreHolderImageReadyDelegate OnImageReadyDelegate;
};
