// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Statics.generated.h"

/**
 * 
 */
UCLASS()
class MASTERTHESISUE4_API UStatics : public UGameplayStatics
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static TArray<FString> GetAnswersForQuestion(int Index, TArray<FString> Answers, TArray<int> AnswerCount);
};
