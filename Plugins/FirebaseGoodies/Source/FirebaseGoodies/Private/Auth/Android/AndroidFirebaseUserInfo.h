#pragma once
#include "Auth/Interface/IFirebaseUserInfo.h"

#include "Android/AndroidJNI.h"

class AndroidFirebaseUserInfo : public IFirebaseUserInfo
{
public:
	AndroidFirebaseUserInfo(jobject UserInfo);
	virtual ~AndroidFirebaseUserInfo() override;
	virtual FString GetUid() override;
	virtual FString GetProviderId() override;
	virtual FString GetDisplayName() override;
	virtual FString GetPhotoUrl() override;
	virtual FString GetEmail() override;
	virtual FString GetPhoneNumber() override;
	virtual bool IsUserInfoValid() override;

private:
	jobject NativeUserInfo;
};
