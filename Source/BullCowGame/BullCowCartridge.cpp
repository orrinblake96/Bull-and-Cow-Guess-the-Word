// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{    
    // If game over then clear screen and setup game
    // else check player guess
    if(bGameOver)
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

    HiddenWord = TEXT("minecraft");
    Lives = HiddenWord.Len();

    PrintLine(TEXT("Guess the %i letter word.\nYou have %i lives.\nHit 'Enter' once you're ready!"), HiddenWord.Len(), HiddenWord.Len());
    PrintLine(TEXT("Hidden word: %s"), *HiddenWord); // Debug for easy testing

    bGameOver = false;
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress 'Enter' to play again!!"));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    // Length?
    // If fail then guess again
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Remember the word is %i letters long."), HiddenWord.Len());
        PrintLine(TEXT("Try again, you have %i lives left"), Lives);
        return;
    }

    // Isogram? 
    // if (!IsIsogram)
    // {
    //     PrintLine(TEXT("No repaeting letters, guess again."));
    // }

    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("Winner Winner, Chicken Dinner"));
        EndGame();
        return;
    } 

    // Remove life
    PrintLine(TEXT("Life lost, be careful!"));
    --Lives;
    
    // Check lives > 0
    // Yes, then guess again
    // Show the lives left
    if(Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You've lost all your lives, LOSERRR!!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
        return;
    }

    PrintLine(TEXT("Guess again, you've got %i lives left."), Lives);
}