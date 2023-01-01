// Fill out your copyright notice in the Description page of Project Settings.


#include "Mail.h"

#include <cassert>

#include "MailAsset.h"
#include "MailManager.h"
#include "Manual.h"


void UMail::OnCompletion()
{
	if(MailAsset->MailsOnCompletion.Num() == 0)
	{
		return;
	}

	OnCompletionEvent.Broadcast(MailAsset->MailsOnCompletion, this);
}

void UMail::SetDefaults()
{
	Accepted = false;
	Completed = false;

	Datetime = FDateTime::Now();
}

void UMail::Init(AMailManager* MailManager)
{
	SetDefaults();
	if(SpawnedManuals.Num() == 0)
	{
		for(auto ManualToSpawn : MailAsset->ManualsToSpawn)
		{
			UManual* SpawnedManual = NewObject<UManual>(this, ManualToSpawn);
			SpawnedManual->OnClickedEvent.AddDynamic(MailManager, &AMailManager::RespondToManual);
			SpawnedManuals.Add(SpawnedManual);

		}
	}

}

UTexture2D* UMail::GetAuthorImage()
{
	if(AuthorAsset->Image.IsPending())
	{
        AuthorAsset->Image = Cast< UTexture2D>(AuthorAsset->Image.LoadSynchronous());
	}
	return AuthorAsset->Image.Get();

}

bool UMail::CheckAnswer(FString ProvidedAnswer, TArray<FString> CorrectAnswers)
{
	bool result = false;
	for(auto CorrectAnswer : CorrectAnswers)
	{
		result = CorrectAnswer == ProvidedAnswer ? true : false;
		if(result == true)
		{
			break;
		}
	}
	return result;
}

void UMail::Accept()
{
	Accepted = true;
}

bool UMail::IsAccepted()
{
	return Accepted;
}

void UMail::Complete()
{
	Completed = true;
	OnCompletion();
}

bool UMail::IsCompleted()
{
	return Completed;
}

