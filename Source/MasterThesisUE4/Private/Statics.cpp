// Fill out your copyright notice in the Description page of Project Settings.


#include "Statics.h"

TArray<FString> UStatics::GetAnswersForQuestion(int Index, TArray<FString> Answers, TArray<int> AnswerCount)
{
	const int NumAnswers = AnswerCount[Index];
	int Start = 0;

	for(int i = 0; i < Index; i++)
	{
		Start += AnswerCount[i];
	}

	const int End = Start + NumAnswers - 1;

	TArray<FString> Result;

	for(int i = Start; i <= End; i++)
	{
		Result.Add(Answers[i]);
	}

	return Result;
}
