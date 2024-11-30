// Copyright (c) 2023 Nineva Studios

#pragma once

class IFirebaseTokenResult;

#include "Common/FGValueVariant.h"

#include "FGGetTokenResult.generated.h"

UCLASS(BlueprintType)
class FIREBASEGOODIES_API UFGGetTokenResult : public UObject
{
	GENERATED_BODY()

public:
	virtual ~UFGGetTokenResult() override;

	UFUNCTION(BlueprintPure, Category = "Firebase Goodies|Auth|Get Token Result")
	FString GetSignInProvider();

	UFUNCTION(BlueprintPure, Category = "Firebase Goodies|Auth|Get Token Result")
	FString GetToken();

	UFUNCTION(BlueprintPure, Category = "Firebase Goodies|Auth|Get Token Result")
	FDateTime GetAuthTimestamp();

	UFUNCTION(BlueprintPure, Category = "Firebase Goodies|Auth|Get Token Result")
	FDateTime GetExpirationTimestamp();

	UFUNCTION(BlueprintPure, Category = "Firebase Goodies|Auth|Get Token Result")
	FDateTime GetIssuedAtTimestamp();

	UFUNCTION(BlueprintPure, Category = "Firebase Goodies|Auth|Get Token Result")
	TMap<FString, FFGValueVariant> GetClaims();

	UFUNCTION(BlueprintPure, Category = "Firebase Goodies|Auth|Get Token Result")
	bool IsResultValid();

	void Init(TSharedPtr<IFirebaseTokenResult> TokenResult);

protected:
	TSharedPtr<IFirebaseTokenResult> TokenResultImpl;
};
