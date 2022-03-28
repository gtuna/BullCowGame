// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::SetUpGame()
{
    PrintLine( TEXT("Welcome To Bull Cows!") );

    std::srand(std::time(0));
    
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("The Hidden Word is %i letters long"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Press enter to start"));
    PrintLine(TEXT("The Hidden Word is %s"), *HiddenWord);
    
}

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isograms = GetValidWords();
    
    SetUpGame();
}

TArray<FString> UBullCowCartridge::GetValidWords() const
{
    TArray<FString> Isograms;
    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            Isograms.Emplace(Word);
        }
    }
    return Isograms;
}



bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int32  Index = 0; Index < Word.Len() ; Index++)
    {
        for ( int32 Comparison = Index + 1; 
                    Comparison < Word.Len();
                        Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }       
        }        
 }
    // no duplicates encountered, return true
    return true;
}
bool UBullCowCartridge::IsValid(const FString& Guess) const
{
    if (Guess.Len() != HiddenWord.Len() )
    {
        PrintLine(TEXT("Your guess is not a valid Word! "));
        return false;
    }
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("Not an Isogram "));
        return false;
    }
    else    
    {
        return true;
    }
    
}

bool UBullCowCartridge:: ProcessGuess(const FString& Guess)
{
    if (! IsValid(Guess))
    {
        return false;
    }
    
    if ( (Guess == HiddenWord))
    {
        PrintLine(TEXT("You have Won!"));
        EndGame();
        
        return true;
    }
    else
    {
        PrintLine(TEXT("Sorry, it is not " +  Guess) );
        PrintLine(TEXT("You lost a life!" ) );
        PrintLine(TEXT("Lives: %i"), --Lives );

        if (Lives>0)
        {
            PrintLine(TEXT("Guess again.." ) );    
            auto GuessAndHiddenWord = Guess.Compare( HiddenWord);
            // auto GuessOrHiddenWord = Guess | HiddenWord; 
            FBullCowCount BCCount =  GetBullCows(Guess); 
            PrintLine(TEXT("\nBulls: %i"), BCCount.Bulls );
            PrintLine(TEXT("Cows: %i\n"), BCCount.Cows );       
        }
        else
        {
            PrintLine(TEXT("The hidden word was %s"), *HiddenWord);  
            EndGame();
        }

        return false;    
    }
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount BCCount; 
    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            BCCount.Bulls++;
            continue;
        }
        for (int32 HiddenWordIndex = 0; HiddenWordIndex < HiddenWord.Len(); HiddenWordIndex++)
        {

            if (Guess[GuessIndex] == HiddenWord[HiddenWordIndex])
            {
                BCCount.Cows++;
                break;
            }
        }
    }
    return BCCount;
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{  
    if(bGameOver)
    {
        ClearScreen();
        SetUpGame();
    }
    else
    {
        ProcessGuess(Input);   
    }      
}

void  UBullCowCartridge::EndGame()
{
  bGameOver = true;
  PrintLine(TEXT("Press enter to play again"));  
}
