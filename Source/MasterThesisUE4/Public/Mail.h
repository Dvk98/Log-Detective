// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuthorAsset.h"
#include "GameFramework/Actor.h"
#include "Mail.generated.h"

class AMailManager;
class UManual;
class UMailAsset;
class UMail;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCompletionEvent, const TArray<TSubclassOf<UMail>>&, Mails, UMail*, InstigatorMail);

UCLASS(BlueprintType, Blueprintable)
class MASTERTHESISUE4_API UMail : public UObject
{
	GENERATED_BODY()

public:

	void OnCompletion();
	void SetDefaults();
	void Init(AMailManager* MailManager);

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetAuthorImage();

	UFUNCTION(BlueprintCallable)
	bool CheckAnswer(FString ProvidedAnswer, TArray<FString> CorrectAnswers);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UAuthorAsset* AuthorAsset;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UMailAsset* MailAsset;

	UPROPERTY()
	FOnCompletionEvent OnCompletionEvent;

	UPROPERTY(BlueprintReadWrite)
	TArray<UObject*> Attachments;

	UPROPERTY(BlueprintReadOnly)
	TArray<UManual*> SpawnedManuals;

	UFUNCTION(BlueprintCallable)
	void Accept();

	UFUNCTION(BlueprintCallable)
	bool IsAccepted();

	UFUNCTION(BlueprintCallable)
	void Complete();

	UFUNCTION(BlueprintCallable)
	bool IsCompleted();

	UPROPERTY(BlueprintReadOnly)
	FDateTime Datetime;

private:

	bool Accepted;

	bool Completed;

};
