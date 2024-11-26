#pragma once
#include "Auth/Interface/IFirebaseTokenResult.h"

@class FIRAuthTokenResult;

class IOSGetTokenResult : public IFirebaseTokenResult
{
public:
	IOSGetTokenResult(FIRAuthTokenResult* TokenResult);
	virtual ~IOSGetTokenResult() override;
	
	virtual bool IsTokenResultValid() override;
	virtual FString GetSignInProvider() override;
	virtual FString GetToken() override;
	virtual FDateTime GetAuthTimestamp() override;
	virtual FDateTime GetExpirationTimestamp() override;
	virtual FDateTime GetIssuedAtTimestamp() override;
	virtual TMap<FString, FFGValueVariant> GetClaims() override;
	
private:
	FIRAuthTokenResult* NativeTokenResult;
};
