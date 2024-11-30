#include "DesktopFirebaseAuthCredentials.h"
#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT

DesktopFirebaseAuthCredentials::~DesktopFirebaseAuthCredentials()
{
}

FString DesktopFirebaseAuthCredentials::GetProvider()
{
	return DesktopCredential.provider().c_str();
}

bool DesktopFirebaseAuthCredentials::AreValid()
{
	return DesktopCredential.is_valid();
}

DesktopFirebaseAuthCredentials::DesktopFirebaseAuthCredentials(firebase::auth::Credential Credential)
{
	DesktopCredential = Credential;
}

DesktopFirebaseAuthCredentials::DesktopFirebaseAuthCredentials(firebase::auth::PhoneAuthCredential Credential)
{
	PhoneCredential = Credential;
}

firebase::auth::Credential DesktopFirebaseAuthCredentials::GetDesktopCredential() const
{
	return DesktopCredential;
}

firebase::auth::PhoneAuthCredential DesktopFirebaseAuthCredentials::GetPhoneCredential() const
{
	return PhoneCredential;
}
#endif
