#include <iostream>
#include <ctime>

// print welcome message
void PrintIntro() {
    std::cout   << "        .,,uod8B8bou,,.\n"
                << ".,uod8BBBBBBBBBBBBBBBBRPFT?l!i:.\n"
                << ",=m8BBBBBBBBBBBBBBBRPFT?!||||||||||||||\n"
                << "!...:!TVBBBRPFT||||||||||!!^^\"\"'   ||||\n"
                << "!.......:!?|||||!!^^\"\"'            ||||\n"
                << "!.........||||                     ||||\n"
                << "!.........||||  ##                 ||||\n"
                << "!.........||||                     ||||\n"
                << "!.........||||                     ||||\n"
                << "!.........||||                     ||||\n"
                << "!.........||||                     ||||\n"
                << "`.........||||                    ,||||\n"
                << ".;.......||||               _.-!!|||||\n"
                << ".,uodWBBBBb.....||||       _.-!!|||||||||!:'\n"
                << "!YBBBBBBBBBBBBBBb..!|||:..-!!|||||||!iof68BBBBBb....\n"
                << "!..YBBBBBBBBBBBBBBb!!||||||||!iof68BBBBBBRPFT?!::   `.\n"
                << "!....YBBBBBBBBBBBBBBbaaitf68BBBBBBRPFT?!:::::::::     `.\n"
                << "!......YBBBBBBBBBBBBBBBBBBBRPFT?!::::::;:!^\"`;:::       `.\n"
                << "!........YBBBBBBBBBBRPFT?!::::::::::^''...::::::;         iBBbo.\n"
                << "`..........YBRPFT?!::::::::::::::::::::::::;iof68bo.      WBBBBbo.\n"
                << "`..........:::::::::::::::::::::::;iof688888888888b.     `YBBBP^'\n"
                << "`........::::::::::::::::;iof688888888888888888888b.     `\n"
                << "`......:::::::::;iof688888888888888888888888888888b.\n"
                << "`....:::;iof688888888888888888888888888888888899fT!\n"
                << "`..::!8888888888888888888888888888888899fT|!^\"'\n"
                << "`' !!988888888888888888888888899fT|!^\"'\n"
                << "`!!8888888888888888899fT|!^\"'\n"
                << "  `!988888888899fT|!^\"'\n"
                << "   `!9899fT|!^\"'\n"
                << "     `!^\"'\n\n";

    std::cout << "> You are breaking into a secure server room" << std::endl
              << "> Enter the correct codes to advance" << std::endl << std::endl;
}

void PrintLevel(int levelDifficulty, int Tries) {
    std::cout << "> Firewall level " << levelDifficulty << std::endl
              << "> Enter the correct codes (three numbers) to advance. [ " << Tries << " tries left ]" << std::endl;
}

bool PlayGame(int Difficulty, int Tries) {
    PrintLevel(Difficulty, Tries);
    const int CodeA = rand() % Difficulty + 1, CodeB = rand() % Difficulty + Difficulty, CodeC = rand() % Difficulty + 1;

    const int CodeSum = CodeA + CodeB + CodeC;
    const int CodeProduct = CodeA * CodeB * CodeC;

    std::cout << "> The codes add-up to: " << CodeSum << std::endl;
    std::cout << "> The codes multiply to give: " << CodeProduct << std::endl;

    int GuessA, GuessB, GuessC;

    std::cout << "> ";

    // store player guess
    std::cin >> GuessA >> GuessB >> GuessC;

    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;

    // check if guess is correct
    if(GuessSum == CodeSum && GuessProduct == CodeProduct) {
        std::cout << std::endl << "> --- Hack successful. Level complete. ---" << std::endl << std::endl;
        return true;
    }
    else {
        std::cout << std::endl << "> --- Hack unsuccessful. Incorrect codes ---" << std::endl << std::endl;
        return false;
    }
}

int main() {
    srand(time(NULL)); // seed for rand based on computers time of day

    int LevelDifficulty = 1;
    int TriesLeft = 3;
    const int MaxDifficulty = 5;

    PrintIntro();

    while(LevelDifficulty <= MaxDifficulty && TriesLeft != 0) { // loop until all levels completed or tries remain
        bool bLevelComplete = PlayGame(LevelDifficulty, TriesLeft);

        std::cin.clear(); // clears any erros
        std::cin.ignore(); // discards buffer

        if (bLevelComplete) {
            ++LevelDifficulty;
        }
        else {
            --TriesLeft;
        }
        
    }

    if (TriesLeft == 0) {
        std::cout << std::endl << "> --- Breach detected. Server locked up. ---" << std::endl
                  << "> [ You lose ]" << std::endl;
    }
    else {
        std::cout << std::endl << "> --- Hack complete. Server access granted. ---" << std::endl
                  << "> [ You win ]" << std::endl;
    }

    return 0;
}