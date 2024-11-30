#pragma once
#include "Auth/Interface/IFirebaseAuthCredentials.h"

#import <FirebaseAuthInterop/FIRAuthInterop.h>
#import <FirebaseAuth/FirebaseAuth-Swift.h>

class IOSFirebaseAuthCredentials : public IFirebaseAuthCredentials
{
public:
	IOSFirebaseAuthCredentials(FIRAuthCredential* Credential);
	virtual ~IOSFirebaseAuthCredentials() override;
	virtual FString GetProvider() override;
	virtual bool AreValid() override;
	
	FIRAuthCredential* GetNativeCredentials() const;

private:
	FIRAuthCredential* NativeCredential;
};
