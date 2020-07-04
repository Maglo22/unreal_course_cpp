/*
    Header file for BullCowGameClass (game logic).
    No direct user interaction.
*/

#pragma once
#include <string>

// Unreal syntax
using FString = std::string;
using int32 = int;

// variables initialised to 0
struct FBullCowCount {
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus {
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame {
    public:
        FBullCowGame(); // constructor
        void Reset();
        bool IsGameWon() const;
        EGuessStatus CheckGuess(FString) const;
        int32 GetCurrentTry() const;
        int32 GetMaxTries() const;
        int32 GetHiddenWordLength() const;
        FString GetHiddenWord() const;
        
        // provide method for counting bulls & cows, an increasing try # assuming a valid guess
        FBullCowCount SubmitValidGuess(FString);

    private:
        int32 MyCurrentTry;
        bool bGameIsWon;
        FString MyHiddenWord;

        bool IsIsogram(FString) const;
        bool IsLowerCase(FString) const;
};