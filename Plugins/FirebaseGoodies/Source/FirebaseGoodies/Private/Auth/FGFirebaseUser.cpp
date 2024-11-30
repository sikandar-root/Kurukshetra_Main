// Copyright (c) 2022 Nineva Studios

#include "Auth/FGFirebaseUser.h"

#include "Auth/FGAuthLibrary.h"
#include "Auth/FGFirebaseUserInfo.h"
#include "FirebaseGoodiesLog.h"

#include "Interface/IFirebaseUser.h"

FOnUserVoidTaskCompleted UFGFirebaseUser::OnUserVoidTaskCompletedCallback;
FOnUserUpdated UFGFirebaseUser::OnUserUpdatedCallback;
FOnUserOperationError UFGFirebaseUser::OnUserOperationErrorCallback;
FOnUserStringTaskCompleted UFGFirebaseUser::OnUserStringTaskCompletedCallback;
FOnGetTokenResultCompleted UFGFirebaseUser::OnGetTokenResultCompletedCallback;

UFGFirebaseUser::~UFGFirebaseUser()
{
}

bool UFGFirebaseUser::IsAnonymous() const
{
	if (!IsUserValid())
	{
		return false;
	}

	return UserImpl->IsAnonymous();
}

bool UFGFirebaseUser::IsEmailVerified() const
{
	if (!IsUserValid())
	{
		return false;
	}

	return UserImpl->IsEmailVerified();
}

bool UFGFirebaseUser::IsUserValid() const
{
	const bool IsValid = UserImpl && UserImpl->IsUserValid();
	if (!IsValid)
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("User is not valid."));
	}
	return IsValid;
}

void UFGFirebaseUser::Delete(const FOnUserVoidTaskCompleted& OnSuccess, const FOnUserOperationError& OnError)
{
	OnUserVoidTaskCompletedCallback = OnSuccess;
	OnUserOperationErrorCallback = OnError;

	if (!IsUserValid())
	{
		return;
	}

	UserImpl->Delete(OnSuccess, OnError);
}

void UFGFirebaseUser::LinkWithCredentials(UFGAuthCredentials* Credentials, const FOnUserUpdated& OnSuccess, const FOnUserOperationError& OnError)
{
	OnUserUpdatedCallback = OnSuccess;
	OnUserOperationErrorCallback = OnError;

	if (!IsUserValid() || !Credentials->AreValid())
	{
		return;
	}

	UserImpl->LinkWithCredentials(Credentials, OnSuccess, OnError);
}

void UFGFirebaseUser::Reauthenticate(UFGAuthCredentials* Credentials, const FOnUserVoidTaskCompleted& OnSuccess, const FOnUserOperationError& OnError)
{
	OnUserVoidTaskCompletedCallback = OnSuccess;
	OnUserOperationErrorCallback = OnError;

	if (!IsUserValid() || !Credentials->AreValid())
	{
		return;
	}

	UserImpl->Reauthenticate(Credentials, OnSuccess, OnError);
}

void UFGFirebaseUser::Reload(const FOnUserVoidTaskCompleted& OnSuccess, const FOnUserOperationError& OnError)
{
	OnUserVoidTaskCompletedCallback = OnSuccess;
	OnUserOperationErrorCallback = OnError;

	if (!IsUserValid())
	{
		return;
	}

	UserImpl->Reload(OnSuccess, OnError);
}

void UFGFirebaseUser::SendEmailVerification(const FOnUserVoidTaskCompleted& OnSuccess, const FOnUserOperationError& OnError)
{
	OnUserVoidTaskCompletedCallback = OnSuccess;
	OnUserOperationErrorCallback = OnError;

	if (!IsUserValid())
	{
		return;
	}

	UserImpl->SendEmailVerification(OnSuccess, OnError);
}

void UFGFirebaseUser::UnlinkProvider(const FString& Provider, const FOnUserUpdated& OnSuccess, const FOnUserOperationError& OnError)
{
	OnUserUpdatedCallback = OnSuccess;
	OnUserOperationErrorCallback = OnError;

	if (Provider.IsEmpty())
	{
		OnError.ExecuteIfBound("-1", "Provider empty");
		return;
	}
	
	if (!IsUserValid())
	{
		return;
	}

	UserImpl->UnlinkProvider(Provider, OnSuccess, OnError);
}

void UFGFirebaseUser::UpdateEmail(const FString& Email, const FOnUserVoidTaskCompleted& OnSuccess, const FOnUserOperationError& OnError)
{
	OnUserVoidTaskCompletedCallback = OnSuccess;
	OnUserOperationErrorCallback = OnError;

	if (Email.IsEmpty())
	{
		OnError.ExecuteIfBound("-1", "Email empty");
		return;
	}

	if (!IsUserValid())
	{
		return;
	}

	UserImpl->UpdateEmail(Email, OnSuccess, OnError);
}

void UFGFirebaseUser::UpdatePassword(const FString& Password, const FOnUserVoidTaskCompleted& OnSuccess, const FOnUserOperationError& OnError)
{
	OnUserVoidTaskCompletedCallback = OnSuccess;
	OnUserOperationErrorCallback = OnError;

	if (Password.IsEmpty())
	{
		OnError.ExecuteIfBound("-1", "Password empty");
		return;
	}

	if (!IsUserValid())
	{
		return;
	}

	UserImpl->UpdatePassword(Password, OnSuccess, OnError);
}

void UFGFirebaseUser::UpdatePhoneNumber(UFGAuthCredentials* Credentials, const FOnUserVoidTaskCompleted& OnSuccess,
                                        const FOnUserOperationError& OnError)
{
	OnUserVoidTaskCompletedCallback = OnSuccess;
	OnUserOperationErrorCallback = OnError;

	if (!IsUserValid() || !Credentials->AreValid())
	{
		return;
	}

	UserImpl->UpdatePhoneNumber(Credentials, OnSuccess, OnError);
}

void UFGFirebaseUser::UpdateProfile(const FString& DisplayName, const FString& AvatarUrl, const FOnUserVoidTaskCompleted& OnSuccess,
                                    const FOnUserOperationError& OnError)
{
	OnUserVoidTaskCompletedCallback = OnSuccess;
	OnUserOperationErrorCallback = OnError;

	if (!IsUserValid())
	{
		return;
	}

	UserImpl->UpdateProfile(DisplayName, AvatarUrl, OnSuccess, OnError);
}

void UFGFirebaseUser::GetToken(bool ForceRefresh, const FOnUserStringTaskCompleted& OnSuccess, const FOnUserOperationError& OnError)
{
	OnUserStringTaskCompletedCallback = OnSuccess;
	OnUserOperationErrorCallback = OnError;

	if (!IsUserValid())
	{
		return;
	}

	UserImpl->GetToken(ForceRefresh, OnSuccess, OnError);
}

TArray<UFGFirebaseUserInfo*> UFGFirebaseUser::GetProviderData() const
{
	TArray<UFGFirebaseUserInfo*> Result;

	for (const auto& Provider : UserImpl->GetProviderData())
	{
		UFGFirebaseUserInfo* Info = NewObject<UFGFirebaseUserInfo>();
		Info->Init(Provider);
		Result.Add(Info);
	}

	return Result;
}

void UFGFirebaseUser::GetIdToken(bool ForceRefresh, const FOnGetTokenResultCompleted& OnSuccess, const FOnUserOperationError& OnError)
{
	OnGetTokenResultCompletedCallback = OnSuccess;
	OnUserOperationErrorCallback = OnError;

	if (!IsUserValid())
	{
		return;
	}

	UserImpl->GetIdToken(ForceRefresh, OnSuccess, OnError);
}

void UFGFirebaseUser::Init(const TSharedPtr<IFirebaseUser>& User)
{
	UserImpl = User;
	UserInfoImpl = User;
}
