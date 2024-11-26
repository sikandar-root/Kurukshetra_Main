#pragma once
#include "Auth/Interface/IFirebaseAuthCredentials.h"
#include "Containers/UnrealString.h"
#include "Android/AndroidJNI.h"

class AndroidFirebaseAuthCredentials : public IFirebaseAuthCredentials
{
public:
	AndroidFirebaseAuthCredentials(jobject Credentials);
	virtual ~AndroidFirebaseAuthCredentials() override;
	virtual FString GetProvider() override;
	virtual bool AreValid() override;

	jobject GetNativeCredentials();
private:
	jobject NativeCredentials;
};
