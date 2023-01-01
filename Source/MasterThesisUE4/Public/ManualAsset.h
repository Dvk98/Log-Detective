// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ManualAsset.generated.h"

/**
 * 
 */
UCLASS()
class MASTERTHESISUE4_API UManualAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
	FString FilePath;
	
};
