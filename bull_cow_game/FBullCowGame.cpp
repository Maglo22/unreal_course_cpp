/*
    Implementation of BullCowGameClass (game logic).
*/

#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map


FBullCowGame::FBullCowGame() { Reset(); } // default constructor

// Getters
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
FString FBullCowGame::GetHiddenWord() const { return MyHiddenWord; }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const {
    TMap<int32, int32> WordLengthToMaxTries { {3, 4}, {4, 6}, {5, 7}, {6, 7}, {7, 8}, {9, 9}, {10, 10} }; // map max tries to word length for difficulty tunning

    return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

// reset game and variables status
void FBullCowGame::Reset() {
    const FString HIDDEN_WORD = "planets"; // must be an isogram

    MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
    bGameIsWon = false;

    return;
}

// check if the word entered is an isogram
bool FBullCowGame::IsIsogram(FString Guess) const {
    // treat 0 and 1 letter words as isograms
    if (Guess.length() <= 1) { return true; }

    TMap<char, bool> LetterSeen; // setup map

    // loop through all letters in the word
    for (auto Letter : Guess) {  // for all letters in guess
        Letter = tolower(Letter);

        // if the letter has already been introduced in the map
        if (LetterSeen[Letter]) {
            return false; // not an isogram
        } else {
            LetterSeen[Letter] = true; // mark letter as seen
        }
    }

    return true;
}

// check if thw word entered has all letters in lowercase
bool FBullCowGame::IsLowerCase(FString Guess) const {
    // if guess is zero characters
    if (Guess.length() < 1) { return true; }

    // loop through all letters in guess
    for (auto Letter : Guess) {
        if (!islower(Letter)) { // if the letter is not lower case
            return false;
        }
    }
    return true;
}

// validation of the input word by the user
EGuessStatus FBullCowGame::CheckGuess(FString Guess) const {
    if (!IsIsogram(Guess)) { // if guess != isogram
        return EGuessStatus::Not_Isogram;
    } else if (!IsLowerCase(Guess)) { // if guess != lowercase
        return EGuessStatus::Not_Lowercase;
    } else if (Guess.length() != GetHiddenWordLength()) { // if guess length is wrong
        return EGuessStatus::Wrong_Length;    
    } else {
        return EGuessStatus::OK;
    }
}

// receives a valid guess, increments turn, returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
    MyCurrentTry++; // increment turn

    FBullCowCount BullCowCount;
    int32 WordLength = MyHiddenWord.length();

    // loop through letters of hidden word
    for (int32 HWChar = 0; HWChar < WordLength; ++HWChar) {
        // compare against the guess
        for (int32 GWChar = 0; GWChar < WordLength; ++GWChar) {
            // if they match
            if (MyHiddenWord[HWChar] == Guess[GWChar]) {
                if (HWChar == GWChar) {
                    BullCowCount.Bulls++; // increment bulls if in correct place
                } else {
                    BullCowCount.Cows++; // increment cows if in incorrect place
                }
            }
        }
    }

    if (BullCowCount.Bulls == WordLength) {
        bGameIsWon = true;
    } else {
        bGameIsWon = false;
    }

    return BullCowCount;
}

