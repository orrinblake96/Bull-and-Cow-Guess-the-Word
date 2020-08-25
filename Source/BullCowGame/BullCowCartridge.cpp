// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Math/UnrealMathUtility.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWords.txt");
    FFileHelper::LoadFileToStringArrayWithPredicate(Isograms, *WordListPath, [](const FString& Word) 
    {
        return Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word);
    });

    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    // If game over then clear screen and setup game
    // else check player guess
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
        return;
    }

    ProcessGuess(Input);
}

void UBullCowCartridge::SetupGame()
{
    // Welcome Player
    PrintLine(TEXT("*-- Welcome to Bull and Cows --*\nIt's a game of intellects..."));

    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len();

    PrintLine(TEXT("Guess the %i letter word.\nYou have %i lives.\nHit 'Enter' once you're ready!"), HiddenWord.Len(), HiddenWord.Len());
    // PrintLine(TEXT("Hidden word: %s"), *HiddenWord); // Debug for easy testing
    
    bGameOver = false;
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress 'Enter' to play again!!"));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("Winner Winner, Chicken Dinner"));
        EndGame();
        return;
    }

    // Length?
    // If fail then guess again
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Remember the word is %i letters long."), HiddenWord.Len());
        PrintLine(TEXT("Try again, you have %i lives left"), Lives);
        return;
    }

    // Isogram?
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again."));
        return;
    }

    // Remove life
    PrintLine(TEXT("Life lost, be careful!"));
    --Lives;

    // Check lives > 0
    // Yes, then guess again
    // Show the lives left
    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You've lost all your lives, LOSERRR!!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
        return;
    }

    FBullCowCount Count = GetBullCows(Guess);

    PrintLine(TEXT("You have %i Bulls and %i Cows."), Count.Bulls, Count.Cows);

    PrintLine(TEXT("Guess again, you've got %i lives left."), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word)
{
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }

    return true;

    //loop length of word
    //loop length - self
    //if current char equals any other char then false
    //else true
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if(Word.Len() >= 4 && Word.Len() <= 8)
        {
            if(IsIsogram(Word))
            {
                ValidWords.Emplace(Word);
            }
        }
    }
    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if(Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }
        
        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if(Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
               Count.Cows++;
               break;
            }
        } 
    }
    return Count; 
}