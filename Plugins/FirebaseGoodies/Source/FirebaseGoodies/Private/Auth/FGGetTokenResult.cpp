// Copyright (c) 2023 Nineva Studios

#include "Auth/FGGetTokenResult.h"
#include "FirebaseGoodiesLog.h"

#include "Interface/IFirebaseTokenResult.h"

UFGGetTokenResult::~UFGGetTokenResult()
{
}

FString UFGGetTokenResult::GetSignInProvider()
{
	FString Result;
	
	if (!IsResultValid())
		return Result;
	
	Result = TokenResultImpl->GetSignInProvider();
	return Result;
}

FString UFGGetTokenResult::GetToken()
{
	FString Result;
	
	if (!IsResultValid())
		return Result;
	
	Result = TokenResultImpl->GetToken();
	return Result;
}

FDateTime UFGGetTokenResult::GetAuthTimestamp()
{
	FDateTime Result;
	
	if (!IsResultValid())
		return Result;
	
	Result = TokenResultImpl->GetAuthTimestamp();
	return Result;
}

FDateTime UFGGetTokenResult::GetExpirationTimestamp()
{
	FDateTime Result;
	
	if (!IsResultValid())
		return Result;
	
	Result = TokenResultImpl->GetExpirationTimestamp();
	return Result;
}

FDateTime UFGGetTokenResult::GetIssuedAtTimestamp()
{
	FDateTime Result;
	
	if (!IsResultValid())
		return Result;
	
	Result = TokenResultImpl->GetIssuedAtTimestamp();
	return Result;
}

TMap<FString, FFGValueVariant> UFGGetTokenResult::GetClaims()
{
	TMap<FString, FFGValueVariant> Result;
	
	if (!IsResultValid())
		return Result;
	
	Result = TokenResultImpl->GetClaims();
	return Result;
}

bool UFGGetTokenResult::IsResultValid()
{
	const bool IsValid = TokenResultImpl->IsTokenResultValid();
	if (!IsValid)
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Get Token Result is not valid."));
	}
	return IsValid;
}

void UFGGetTokenResult::Init(TSharedPtr<IFirebaseTokenResult> TokenResult)
{
	TokenResultImpl = TokenResult;
}

