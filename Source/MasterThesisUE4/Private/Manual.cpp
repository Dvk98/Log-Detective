// Fill out your copyright notice in the Description page of Project Settings.


#include "Manual.h"

void UManual::OnClicked()
{
	OnClickedEvent.Broadcast(this, nullptr);
}
