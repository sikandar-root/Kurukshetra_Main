// Copyright (c) 2019 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

class IAndroidGoodiesNotification;

#include "AGNotification.generated.h"

UCLASS()
class ANDROIDGOODIES_API UAGNotification : public UObject
{
	GENERATED_BODY()

public:
	virtual ~UAGNotification() override;
	void Init(TSharedPtr<IAndroidGoodiesNotification> Notification);
	TSharedPtr<IAndroidGoodiesNotification> GetNativeNotification();
private:
	TSharedPtr<IAndroidGoodiesNotification> NativeNotification;
};
