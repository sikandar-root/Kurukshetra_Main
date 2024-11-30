#pragma once

#include "HAL/Platform.h"

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT

#include "Auth/Interface/IFirebaseAuthCredentials.h"
#include "firebase/auth.h"

class DesktopFirebaseAuthCredentials : public IFirebaseAuthCredentials
{
public:
	DesktopFirebaseAuthCredentials(firebase::auth::Credential Credential);
	DesktopFirebaseAuthCredentials(firebase::auth::PhoneAuthCredential Credential);
	
	virtual ~DesktopFirebaseAuthCredentials() override;
	virtual FString GetProvider() override;
	virtual bool AreValid() override;

	firebase::auth::Credential GetDesktopCredential() const;
	firebase::auth::PhoneAuthCredential GetPhoneCredential() const;

private:
	firebase::auth::Credential DesktopCredential;
	firebase::auth::PhoneAuthCredential PhoneCredential;
};

#endif
