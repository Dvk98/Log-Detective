// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MailManager.generated.h"

class UManual;
class UMail;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStoredMailsChangedEvent, const TArray<UMail*>&, Mails);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStoredManualsChangedEvent, const TArray<UManual*>&, Manuals);

UCLASS(Blueprintable, BlueprintType)
class MASTERTHESISUE4_API AMailManager : public AActor
{
	GENERATED_BODY()

public:

	AMailManager();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UMail*> StoredMails;

	TArray<FName> CompletedMailsIDs;
	TArray<FName> StoredMailsIDs;

	void AddId(FName Id);
	void AddCompletedId(FName Id);

	bool IsMailAccessible(UMail* Mail);

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UMail>> StartingMails;

	UFUNCTION(BlueprintCallable)
	void AddMail(UMail* Mail);

	UFUNCTION(BlueprintCallable)
	void AddMails(TArray<UMail*> Mails);

	UPROPERTY(BlueprintAssignable)
	FOnStoredMailsChangedEvent StoredMailsChangedEvent;

	UFUNCTION()
	void RespondToMailCompletion(const TArray<TSubclassOf<UMail>>& Mails, UMail* InstigatorMail);

	UFUNCTION(BlueprintCallable)
	TArray<UMail*> GetOpenMails();

	UFUNCTION(BlueprintCallable)
	TArray<UMail*> GetCompletedMails();

	UFUNCTION(BlueprintCallable)
	TArray<UMail*> GetAcceptedMails();

	UFUNCTION(BlueprintCallable)
	TArray<UMail*> GetAllMails();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UManual*> StoredManuals;

	UFUNCTION(BlueprintCallable)
	void AddManual(UManual* Manual);

	UFUNCTION(BlueprintCallable)
	void AddManuals(TArray<UManual*> Manuals);

	UFUNCTION(BlueprintCallable)
	TArray<UManual*> GetManuals();

	UPROPERTY(BlueprintAssignable)
	FOnStoredManualsChangedEvent OnStoredManualsChangedEvent;

	UFUNCTION()
	void RespondToManual(UManual* Manual, UMail* InstigatorMail);

protected:

	virtual void BeginPlay() override;
};
