#include "IOSGetTokenResult.h"

#include "IOS/Utils/FGValueVariantUtils.h"

#import <FirebaseAuth/FirebaseAuth.h>

IOSGetTokenResult::IOSGetTokenResult(FIRAuthTokenResult* TokenResult)
{
	[TokenResult retain];
	NativeTokenResult = TokenResult;
}

IOSGetTokenResult::~IOSGetTokenResult()
{
	if (NativeTokenResult) {
		[NativeTokenResult release];
	}

	NativeTokenResult = nil;
}

bool IOSGetTokenResult::IsTokenResultValid()
{
	return NativeTokenResult != nil;
}

FString IOSGetTokenResult::GetSignInProvider()
{
	return FString(NativeTokenResult.signInProvider);
}

FString IOSGetTokenResult::GetToken()
{
	return FString(NativeTokenResult.token);
}

FDateTime DateTimeFromNSDate(NSDate* Date)
{
	long Timestamp = (long) [Date timeIntervalSince1970];
	return FDateTime::FromUnixTimestamp(Timestamp);
}

FDateTime IOSGetTokenResult::GetAuthTimestamp()
{
	return DateTimeFromNSDate(NativeTokenResult.authDate);
}

FDateTime IOSGetTokenResult::GetExpirationTimestamp()
{
	return DateTimeFromNSDate(NativeTokenResult.expirationDate);
}

FDateTime IOSGetTokenResult::GetIssuedAtTimestamp()
{
	return DateTimeFromNSDate(NativeTokenResult.issuedAtDate);
}

TMap<FString, FFGValueVariant> IOSGetTokenResult::GetClaims()
{
	return ValueVariantUtils::NSDictionaryToVariantMap(NativeTokenResult.claims);
}
