// Copyright (c) 2021 Nineva Studios

#pragma once

#include "HAL/Platform.h"

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
#include "firebase/auth.h"

#include "Auth/FGAuthLibrary.h"
#include "FirebaseGoodiesLog.h"

#include "Async/Async.h"

class FGPhoneListener final : public firebase::auth::PhoneAuthProvider::Listener
{
public:
	virtual ~FGPhoneListener() override
	{
	}

	virtual void OnVerificationCompleted(firebase::auth::PhoneAuthCredential credential) override
	{
		UE_LOG(LogFirebaseGoodies, Verbose, TEXT("Verify phone number OnVerificationCompleted"));
		const auto Credentials = MakeShareable(new DesktopFirebaseAuthCredentials(credential));

		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			UFGAuthCredentials* Result = NewObject<UFGAuthCredentials>();
			Result->Init(Credentials);
			UFGAuthLibrary::PhoneVerificationSuccessCallback.ExecuteIfBound(Result);
		});
	}

	virtual void OnVerificationCompleted(firebase::auth::Credential credential) override
	{
		UE_LOG(LogFirebaseGoodies, Verbose, TEXT("Verify phone number OnVerificationCompleted"));
		const auto Credentials = MakeShareable(new DesktopFirebaseAuthCredentials(credential));

		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			UFGAuthCredentials* Result = NewObject<UFGAuthCredentials>();
			Result->Init(Credentials);
			UFGAuthLibrary::PhoneVerificationSuccessCallback.ExecuteIfBound(Result);
		});
	}

	virtual void OnVerificationFailed(const std::string& error) override
	{
		const FString ErrorMessage = error.c_str();
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Verify phone number error: %s"), *ErrorMessage);

		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			UFGAuthLibrary::AuthErrorCallback.ExecuteIfBound(ErrorMessage);
		});
	}

	virtual void OnCodeSent(const std::string& verification_id,
	                        const firebase::auth::PhoneAuthProvider::ForceResendingToken&
	                        force_resending_token) override
	{
		UE_LOG(LogFirebaseGoodies, Verbose, TEXT("Verify phone number OnCodeSent"));
		const FString VerificationIDString = verification_id.c_str();
		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			UFGAuthLibrary::PhoneVerificationSentCallback.ExecuteIfBound(VerificationIDString);
		});
	}

	virtual void OnCodeAutoRetrievalTimeOut(const std::string& verification_id) override
	{
		UE_LOG(LogFirebaseGoodies, Verbose, TEXT("Verify phone number OnCodeAutoRetrievalTimeOut"));
		const FString VerificationIDString = verification_id.c_str();
		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			UFGAuthLibrary::PhoneVerificationTimeoutCallback.ExecuteIfBound(VerificationIDString);
		});
	}
};
#endif
