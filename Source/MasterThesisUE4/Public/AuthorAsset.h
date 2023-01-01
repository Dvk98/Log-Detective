// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AuthorAsset.generated.h"

/**
 * 
 */
UCLASS()
class MASTERTHESISUE4_API UAuthorAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
	FText Address;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
	TSoftObjectPtr<UTexture2D> Image;

};
