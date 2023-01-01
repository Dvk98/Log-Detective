// Fill out your copyright notice in the Description page of Project Settings.


#include "MailManager.h"

#include <cassert>

#include "Mail.h"
#include "MailAsset.h"
#include "Manual.h"
#include "ManualAsset.h"

AMailManager::AMailManager()
{
}

void AMailManager::AddId(FName Id)
{
	if(StoredMailsIDs.Find(Id) == INDEX_NONE)
	{
		StoredMailsIDs.Add(Id);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Critical Error, Added Mail although it already exists!"));
		assert(false);
	}
}

void AMailManager::AddCompletedId(FName Id)
{
	if(CompletedMailsIDs.Find(Id) == INDEX_NONE)
	{
		CompletedMailsIDs.Add(Id);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Critical Error, Added Mail although it already exists!"));
		assert(false);
	}
}

bool AMailManager::IsMailAccessible(UMail* Mail)
{
	// Check Mandatory Reqs
	if(Mail->MailAsset->RequirementsMandatory.Num() != 0)
	{
		for(auto Requirement : Mail->MailAsset->RequirementsMandatory)
		{
			if(CompletedMailsIDs.Find(Requirement) == INDEX_NONE)
			{
				return false;
			}
		}
		return true;
	}

	if(Mail->MailAsset->RequirementsOptional.Num() != 0)
	{
		// Look for Optional Reqs if there are no Mandatory ones
		for(auto Requirement : Mail->MailAsset->RequirementsOptional)
		{
			if(CompletedMailsIDs.Find(Requirement) != INDEX_NONE)
			{
				return true;
			}
		}
	}

	if(Mail->MailAsset->RequirementsOptional.Num() == 0 && Mail->MailAsset->RequirementsMandatory.Num() == 0)
	{
		return true;
	}

	return false;

}

void AMailManager::AddMail(UMail* Mail)
{
	if(StoredMails.Find(Mail) != INDEX_NONE)
	{
		return;
	}
	StoredMails.Add(Mail);
	StoredMailsChangedEvent.Broadcast(StoredMails);
}

void AMailManager::AddMails(TArray<UMail*> Mails)
{
	for(auto Mail : Mails)
	{
		if(StoredMails.Find(Mail) != INDEX_NONE) //TODO
		{
			continue;
		}
		AddMail(Mail);
	}
}

void AMailManager::RespondToMailCompletion(const TArray<TSubclassOf<UMail>>& Mails, UMail* InstigatorMail)
{
	for(auto Mail : Mails)
	{
		UMail* SpawnedMail = NewObject<UMail>(this, Mail);
		SpawnedMail->OnCompletionEvent.AddDynamic(this, &AMailManager::RespondToMailCompletion);
		SpawnedMail->Init(this);
		AddMail(SpawnedMail);
		AddId(SpawnedMail->MailAsset->Id);
	}
	AddCompletedId(InstigatorMail->MailAsset->Id);
}

TArray<UMail*> AMailManager::GetOpenMails()
{
	TArray<UMail*> MailsToReturn;

	for(auto Mail : StoredMails)
	{
		if(Mail->IsCompleted() == false && Mail->IsAccepted() == false)
		{
			if(IsMailAccessible(Mail))
			{
				MailsToReturn.Add(Mail);
			}
		}
		
	}

	return MailsToReturn;
}

TArray<UMail*> AMailManager::GetCompletedMails()
{
	TArray<UMail*> MailsToReturn;
	for(auto Mail : StoredMails)
	{
		if (Mail->IsCompleted())
		{
			MailsToReturn.Add(Mail);
		}
	}
	return MailsToReturn;
}

TArray<UMail*> AMailManager::GetAcceptedMails()
{
	TArray<UMail*> MailsToReturn;
	for(auto Mail : StoredMails)
	{
		if (!Mail->IsCompleted() && Mail->IsAccepted())
		{
			MailsToReturn.Add(Mail);
		}
	}
	return MailsToReturn;

}

TArray<UMail*> AMailManager::GetAllMails()
{
	TArray<UMail*> MailsToReturn;
	for(auto Mail : StoredMails)
	{
		if(IsMailAccessible(Mail))
		{
			MailsToReturn.Add(Mail);
		}
	}
	return MailsToReturn;
}

void AMailManager::AddManual(UManual* Manual)
{
	StoredManuals.Add(Manual);
	OnStoredManualsChangedEvent.Broadcast(GetManuals());
} 

void AMailManager::AddManuals(TArray<UManual*> Manuals)
{
	for(auto Manual : Manuals)
	{
		AddManual(Manual);
	}
}

TArray<UManual*> AMailManager::GetManuals()
{
	return StoredManuals;
}

void AMailManager::RespondToManual(UManual* Manual, UMail* InstigatorMail)
{
	for(auto i : StoredManuals)
	{
		if(i->ManualAsset->Title.IdenticalTo(Manual->ManualAsset->Title))
		{
			return;
		} 
	}
	AddManual(Manual);
}

void AMailManager::BeginPlay()
{
	if(StoredMails.Num() == 0)
	{
		for(auto Mail : StartingMails)
		{
			UMail* SpawnedMail = NewObject<UMail>(this, Mail);
			SpawnedMail->OnCompletionEvent.AddDynamic(this, &AMailManager::RespondToMailCompletion);
			SpawnedMail->Init(this);
			AddMail(SpawnedMail);
			AddId(SpawnedMail->MailAsset->Id);
		}
	}
}
