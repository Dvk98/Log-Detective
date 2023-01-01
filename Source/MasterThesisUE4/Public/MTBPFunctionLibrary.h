// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MTBPFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MASTERTHESISUE4_API UMTBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "save")
	static bool FileSaveString(FString SaveTextB, FString FileNameB);

	UFUNCTION(BlueprintPure, Category = "save")
	static bool FileLoadString(FString FileNameA, FString& SaveTextA);

	UFUNCTION(BlueprintPure, Category = "log")
	static FString LogSetDate(FString Log, FDateTime DateTime);

	UFUNCTION(BlueprintPure, Category = "log")
	static TArray<FString> LogSeparateLines(FString Log);

	UFUNCTION(BlueprintCallable, Category = "log")
	static TArray<FString> FilterForToken(FString Content, FString Token);
	
};
