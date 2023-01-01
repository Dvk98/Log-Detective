// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Manual.generated.h"

class UManualAsset;
class UManual;
class UMail;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnClickedEvent, UManual*, Manual, UMail*, InstigatorMail);

UCLASS(BlueprintType, Blueprintable)
class MASTERTHESISUE4_API UManual : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void OnClicked();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UManualAsset* ManualAsset;

	UPROPERTY()
	FOnClickedEvent OnClickedEvent;

	UPROPERTY(BlueprintReadWrite)
	bool bClicked = false;
	
};
