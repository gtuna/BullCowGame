// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount{
	int32 Bulls = 0;
	int32 Cows = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetUpGame();
	void  EndGame();
	int GetMaxTries() const;
	TArray<FString> GetValidWords() const;
	FString GetRandomValidWord() const;
	FBullCowCount GetBullCows(const FString& Guess) const;

	// Your declarations go below!
	private:
	bool IsValid(const FString& ) const;
	bool IsIsogram(const FString& ) const;
	bool ProcessGuess(const FString&);	
	FString HiddenWord;
	int32 Lives;
	bool bGameOver;
	TArray<FString> Isograms; 

};
