#pragma once
#include "Auth/Interface/IFirebaseTokenResult.h"

#include "Android/AndroidJNI.h"

class AndroidGetTokenResult : public IFirebaseTokenResult
{
public:
	AndroidGetTokenResult(jobject TokenResult);
	virtual ~AndroidGetTokenResult() override;
	
	virtual bool IsTokenResultValid() override;
	virtual FString GetSignInProvider() override;
	virtual FString GetToken() override;
	virtual FDateTime GetAuthTimestamp() override;
	virtual FDateTime GetExpirationTimestamp() override;
	virtual FDateTime GetIssuedAtTimestamp() override;
	virtual TMap<FString, FFGValueVariant> GetClaims() override;
	
private:
	jobject NativeTokenResult;
};
