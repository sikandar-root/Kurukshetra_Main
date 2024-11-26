// Copyright (c) 2020 Nineva Studios

#include "GPScoreHolderImageCallback.h"

UGPScoreHolderImageCallback::UGPScoreHolderImageCallback()
{
	if (StaticClass()->GetDefaultObject() != this)
	{
		AddToRoot();
	}
}

void UGPScoreHolderImageCallback::BindDelegate(const FGPOnScoreHolderImageReadyDelegate& OnImageReady)
{
	OnImageReadyDelegate = OnImageReady;
}

void UGPScoreHolderImageCallback::ExecuteDelegate(UTexture2D* Image, FString Uri)
{
	OnImageReadyDelegate.ExecuteIfBound(Image, Uri);
	RemoveFromRoot();
}
