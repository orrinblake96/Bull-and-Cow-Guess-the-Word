// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();
    PrintLine(TEXT("Hidden word: %s"), *HiddenWord); // Debug for easy testing

    // Welcome Player
    PrintLine(TEXT("*-- Welcome to Bull and Cows --*\nIt's a game of intellects..."));
    PrintLine(TEXT("Guess the %i letter word.\nHit 'Enter' once you're ready!"), HiddenWord.Len());

    //Set Lives

    // Prompt player for guess
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    if (Input == HiddenWord)
    {
        PrintLine(TEXT("Winner Winner, Chicken Dinner"));
    } 
    else
    {
        if (Input.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("Hidden Word is %i characters long\nGuess again!!"), HiddenWord.Len());
        }
        
        PrintLine(TEXT("Loserrr!"));
    }
    // Isogram? Length?
    // If fail then guess again
    // Remove life

    // Check lives > 0
    // Yes, then guess again
    // Show the lives left
    // No, then lose/show word and ask if playagain
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("minecraft");
    Lives = HiddenWord.Len();
}