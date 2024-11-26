﻿// Copyright (c) 2023 Nineva Studios

#pragma once

#include "CloudFunctions/Interface/ICloudFunctions.h"


class CloudFunctionsAndroid : public ICloudFunctions
{
public:
	virtual ~CloudFunctionsAndroid() override;

	virtual void CallStringFunction(const FString& MethodName, FString Region,
		const TMap<FString, FFGValueVariant>& Parameters,
		const FCloudFunctionsStringDelegate& OnSuccess,
		const FCloudFunctionsStringDelegate& OnError) override;

	virtual void CallIntFunction(const FString& MethodName, FString Region,
		const TMap<FString, FFGValueVariant>& Parameters,
		const FCloudFunctionsIntDelegate& OnSuccess,
		const FCloudFunctionsStringDelegate& OnError) override;
	
	virtual void CallFloatFunction(const FString& MethodName, FString Region,
		const TMap<FString, FFGValueVariant>& Parameters,
		const FCloudFunctionsFloatDelegate& OnSuccess,
		const FCloudFunctionsStringDelegate& OnError) override;
	
	virtual void CallBoolFunction(const FString& MethodName, FString Region,
		const TMap<FString, FFGValueVariant>& Parameters,
		const FCloudFunctionsBoolDelegate& OnSuccess,
		const FCloudFunctionsStringDelegate& OnError) override;
	
	virtual void CallVoidFunction(const FString& MethodName, FString Region,
		const TMap<FString, FFGValueVariant>& Parameters,
		const FCloudFunctionsVoidDelegate& OnSuccess,
		const FCloudFunctionsStringDelegate& OnError) override;
	
	virtual void CallMapFunction(const FString& MethodName, FString Region,
		const TMap<FString, FFGValueVariant>& Parameters,
		const FCloudFunctionsMapDelegate& OnSuccess,
		const FCloudFunctionsStringDelegate& OnError) override;
	
	virtual void CallArrayFunction(const FString& MethodName, FString Region,
		const TMap<FString, FFGValueVariant>& Parameters,
		const FCloudFunctionsArrayDelegate& OnSuccess,
		const FCloudFunctionsStringDelegate& OnError) override;
};