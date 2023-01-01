// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mail.h"
#include "Engine/DataAsset.h"
#include "MailAsset.generated.h"

/**
 * 
 */
UCLASS()
class MASTERTHESISUE4_API UMailAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
	FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
	FText Subject;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
	FText Content;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
	TArray<FText> Questions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
	TArray<FString> Answers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
	TArray<int> AnswerCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
	TArray<TSubclassOf<UObject>> Attachments;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
	TArray<TSubclassOf<UManual>> ManualsToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
	TArray<TSubclassOf<UMail>> MailsOnCompletion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="General")
	TArray<FName> RequirementsMandatory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="General")
	TArray<FName> RequirementsOptional;

};
