/*
    Console executable.
    Acts as the view in a MVC pattern, responsible for all user interaction.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// Unreal syntax
using FText = std::string;
using int32 = int;

// functions
void PrintIntro();
void PlayGame();
bool AskToPlayAgain();
FText GetValidGuess();
void PrintGameSummary();

// game instance
FBullCowGame BCGame;

// app entry point
int main() {

    do {
        PrintIntro();
        PlayGame();
        std::cout << std::endl;
    } while (AskToPlayAgain());

    return 0;
}

// prints intro to the game
void PrintIntro() {
    std::cout << std::endl << "Welcome to Bulls and Cows." << std::endl;
    std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " isogram I'm thinking of?" << std::endl;

    return;
}

void PlayGame() {
    BCGame.Reset();

    FText Guess = "";
    int32 MaxTries = BCGame.GetMaxTries();

    // loop until game is won or out of tries
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
        Guess = GetValidGuess(); // get user input

        // submit valid guess to the game
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        // print number of bulls and cows
        std::cout << "Bulls: " << BullCowCount.Bulls << "." << "   Cows: " << BullCowCount.Cows << "." << std::endl;    
    }

    // TODO summarize game
    PrintGameSummary();

    return;
}

bool AskToPlayAgain() {
    FText Response = "";

    std::cout << "Would you like to play again (y/n)? ";
    std::getline(std::cin, Response);

    return (Response[0] == 'y' || Response[0] == 'Y');
}

// loops until user inputs a valid guess
FText GetValidGuess() {
    FText Guess = "";
    EGuessStatus Status = EGuessStatus::Invalid_Status;

    do {
        // get user input
        std::cout << std::endl << "Try #" << BCGame.GetCurrentTry() << " [of " << BCGame.GetMaxTries() << "]. Your guess: ";
        std::getline(std::cin, Guess);

        Status = BCGame.CheckGuess(Guess);

        switch (Status) {
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter an Isogram (word without repeating letters)." << std::endl;
                break;
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word." << std::endl;
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter all lowercase letters." << std::endl;
                break;
        
            default:
                break;
        }
    } while (Status != EGuessStatus::OK); // loop until we get no errors

    return Guess;
}

void PrintGameSummary() {
    if (BCGame.IsGameWon()) {
        std::cout << "Congratulations! You guessed the word correctly." << std::endl;
    } else {
        std::cout << "Better luck next time." << std::endl << "The word was: " << BCGame.GetHiddenWord() << ". " << std::endl;
    }
    std::cout << "Game ended." << std::endl;

    return;
}