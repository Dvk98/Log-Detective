// Fill out your copyright notice in the Description page of Project Settings.


#include "MTBPFunctionLibrary.h"

#include <string>

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/DateTime.h"

bool UMTBPFunctionLibrary::FileSaveString(FString SaveTextB, FString FileNameB)
{
	return FFileHelper::SaveStringToFile(SaveTextB, *(FPaths::ProjectContentDir() + FileNameB));
}

bool UMTBPFunctionLibrary::FileLoadString(FString FileNameA, FString& SaveTextA)
{
	return FFileHelper::LoadFileToString(SaveTextA, *(FPaths::ProjectContentDir() + FileNameA));
}

FString UMTBPFunctionLibrary::LogSetDate(FString Log, FDateTime DateTime)
{
	TArray<FString> Lines = LogSeparateLines(Log);
	FDateTime StartDateTime = DateTime;
	FString ReturnString;
	for(auto Line : Lines)
	{
		DateTime = StartDateTime;
		int i = Line.Find("[", ESearchCase::IgnoreCase, ESearchDir::FromStart);
		int j = Line.Find("]", ESearchCase::IgnoreCase, ESearchDir::FromStart);
		if(i == j || i + 1 == j)
		{
			UE_LOG(LogTemp, Warning, TEXT("Error in LogSetData Processing, no date found"));
		}
		FString Time = Line.Mid(i+1, j-(i+1));
		Line.RemoveAt(i+1, j-(i+1));
		DateTime += FTimespan(0, 0, FCString::Atoi(*Time));

		Line.InsertAt(i+1, DateTime.ToIso8601());
		ReturnString += Line;
	}

	return ReturnString;
}

TArray<FString> UMTBPFunctionLibrary::LogSeparateLines(FString Log)
{
	TArray<FString> Lines;
	FString Endline = "\n";

	while(true)
	{
		FString Line;

		if(!Log.Split(Endline, &Line, &Log, ESearchCase::IgnoreCase, ESearchDir::FromStart))
		{
			Lines.Add(Line);
			break;
		}
		Lines.Add(Line);
	}

	return Lines;
}

TArray<FString> UMTBPFunctionLibrary::FilterForToken(FString Content, FString Token)
{
	TArray<FString> Lines;
	FString Endline = "\r";

	while(true)
	{
		FString Line;

		if(!Content.Split(Endline, &Line, &Content, ESearchCase::IgnoreCase, ESearchDir::FromStart))
		{
			Lines.Add(Line);
			break;
		}
		Lines.Add(Line);
	}

	int counter = 1;
	TArray<FString> ReturnString;
	for (auto Line : Lines) 
	{
		if(Line.Find(Token, ESearchCase::IgnoreCase, ESearchDir::FromStart) != INDEX_NONE)
		{
			FString ReturnLine;
			ReturnLine.Append(FString::FromInt(counter) + ": ");
			ReturnLine.Append(Line);
			ReturnString.Add(ReturnLine);
		}
		counter++;
	}

	return ReturnString;
}
