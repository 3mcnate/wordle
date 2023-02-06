#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <cstring>
#include "util.h"
#include "player.h"
#include "game.h"

using namespace std;

int main(int argc, char **argv)
{
    #ifndef SEED
        srand(time(0));
    #else
        srand(SEED);
    #endif

    clearScreen();

    cout << endl;
    cout << "\x1b[36m $$\\      $$\\                           $$\\ $$\\           \x1b[0m" << endl;
    cout << "\x1b[36m $$ | $\\  $$ |                          $$ |$$ |          \x1b[0m" << endl;
    cout << "\x1b[36m $$ |$$$\\ $$ | $$$$$$\\   $$$$$$\\   $$$$$$$ |$$ | $$$$$$\\  \x1b[0m" << endl;
    cout << "\x1b[35m $$ $$ $$\\$$ |$$  __$$\\ $$  __$$\\ $$  __$$ |$$ |$$  __$$\\ \x1b[0m" << endl;
    cout << "\x1b[35m $$$$  _$$$$ |$$ /  $$ |$$ |  \\__|$$ /  $$ |$$ |$$$$$$$$ |\x1b[0m" << endl;
    cout << "\x1b[35m $$$  / \\$$$ |$$ |  $$ |$$ |      $$ |  $$ |$$ |$$   ____|\x1b[0m" << endl;
    cout << "\x1b[34m $$  /   \\$$ |\\$$$$$$  |$$ |      \\$$$$$$$ |$$ |\\$$$$$$$\\ \x1b[0m" << endl;
    cout << "\x1b[34m \\__/     \\__| \\______/ \\__|       \\_______|\\__| \\_______|\x1b[0m" << endl;
    cout << endl << endl;
    cout << "By Nate, Tanya, Nick, and Alaba." << endl << endl;

    if (argc < 3)
    {
        cout << "Usage: ./wordle <solutionwords> <possibleinputs>" << endl;
        return 1;
    }

    string solution = getRandomWord(argv[1]);
    if (solution == "")
    {
        cout << "Invalid solutions filename." << endl;
        return 1;
    }

    set<string>* validWords = readValidWords(argv[2]);
    if (validWords == nullptr)
    {
        cout << "Invalid possible inputs filename." << endl;
        return 1;
    }

    cout << "Available gamemodes: " << endl;
    cout << "\t1: Each player gets the same random word." << endl
         << "\t2: Each player picks a word for the other player." << endl;
    cout << endl << "Choose 1 or 2: ";

    int gamemode;
    while (!(cin >> gamemode) && !(gamemode == 1 || gamemode == 2)) {
        cout << "Please enter either 1 or 2: ";
        cin.ignore();
        cin.clear();
    } 
    cout << endl;
    
    
    #ifdef DEBUG
        string override;
        cout << red("DEBUG: ") << "Override solution and force gamemode 1 (press enter to do nothing): ";
        getline(cin, override);
        if (override != "") {
            gamemode = 1;
            solution = override;
            cout << red("DEBUG: ") << "New solution word is: " << solution << endl;
        }
    #endif 

    string name1, name2;
    string solution1, solution2;
    
    cout << "Player 1, enter your name: " << endl;
    cin >> name1;
    cout << endl;

    cout << "Player 2, enter your name: " << endl;
    cin >> name2;
    
    if (gamemode == 2) {
        solution2 = gamemode2setup(name1, name2, validWords);
        solution1 = gamemode2setup(name2, name1, validWords);
    }
    else {
        solution1 = solution2 = solution;
    }
    
    Player p1(name1, solution1, TURNS);
    Player p2(name2, solution2, TURNS);

    clearScreen();

    // main program loop
    bool done = false;
    while (!done) {
        turn(p1, validWords);
        if (p1.won() || p1.remainingGuesses() == 0) done = true;

        switchTurns(p2.name(), p1.name(), gamemode);

        turn(p2, validWords);
        if (p2.won() || p2.remainingGuesses() == 0) done = true;

        if (!done) switchTurns(p1.name(), p2.name(), gamemode);
    }

    clearScreen();

    showGameResult(p1, p2, gamemode);

    delete validWords;
    return 0;
}

