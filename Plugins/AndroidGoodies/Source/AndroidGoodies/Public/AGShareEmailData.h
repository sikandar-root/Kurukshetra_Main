// Copyright (c) 2018 Nineva Studios

#pragma once

#include "Engine/Texture2D.h"
#include "AGShareEmailData.generated.h"

USTRUCT(BlueprintType)
struct ANDROIDGOODIES_API FAGShareEmailData
{
	GENERATED_USTRUCT_BODY()

	/** Subject of email. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	FString Subject;

	/** Body of email. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	FString TextBody;

	/** Image to send. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	UTexture2D* Image = nullptr;

	/** Recipient email addresses. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	TArray<FString> Recipients;

	/** CC recipients. cc stands for "carbon copy". */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	TArray<FString> CCRecepients;

	/** BCC recipients. bcc stands for "blind carbon copy". */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AndroidGoodies")
	TArray<FString> BCCRecepients;
};
