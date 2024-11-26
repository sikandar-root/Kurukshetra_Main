#pragma once

#include "Containers/UnrealString.h"
#include "Common/FGValueVariant.h"

class IFirebaseTokenResult
{
public:
	virtual ~IFirebaseTokenResult() = default;
	virtual bool IsTokenResultValid() = 0;
	virtual FString GetSignInProvider() = 0;
	virtual FString GetToken() = 0;
	virtual FDateTime GetAuthTimestamp() = 0;
	virtual FDateTime GetExpirationTimestamp() = 0;
	virtual FDateTime GetIssuedAtTimestamp() = 0;
	virtual TMap<FString, FFGValueVariant> GetClaims() = 0;
};
