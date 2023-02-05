#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "util.h"
#include "player.h"

using namespace std;

void turn(Player& player, const std::string& solution, std::set<std::string>* wordList);

bool isGuessValid(const std::string& word, std::set<std::string>* wordList);

void switchTurns(Player& player);

int main(int argc, char **argv)
{
    cout << endl;
    cout << "$$\\      $$\\                           $$\\ $$\\           " << endl;
    cout << "$$ | $\\  $$ |                          $$ |$$ |          " << endl;
    cout << "$$ |$$$\\ $$ | $$$$$$\\   $$$$$$\\   $$$$$$$ |$$ | $$$$$$\\  " << endl;
    cout << "$$ $$ $$\\$$ |$$  __$$\\ $$  __$$\\ $$  __$$ |$$ |$$  __$$\\ " << endl;
    cout << "$$$$  _$$$$ |$$ /  $$ |$$ |  \\__|$$ /  $$ |$$ |$$$$$$$$ |" << endl;
    cout << "$$$  / \\$$$ |$$ |  $$ |$$ |      $$ |  $$ |$$ |$$   ____|" << endl;
    cout << "$$  /   \\$$ |\\$$$$$$  |$$ |      \\$$$$$$$ |$$ |\\$$$$$$$\\ " << endl;
    cout << "\\__/     \\__| \\______/ \\__|       \\_______|\\__| \\_______|" << endl;
    cout << endl;

    if (argc < 3)
    {
        cout << "Usage: ./wordle <solutionwords> <possibleinputs>" << endl;
        return 1;
    }

    srand(time(0));
    string solution = getRandomWord(argv[1]);
    if (solution == "")
    {
        cout << "Invalid solutions filename." << endl;
        return 1;
    }

    set<string>* validWords = readValidWords(argv[2]);
    if (validWords == nullptr)
    {
        cout << "Invalid input words filename." << endl;
        return 1;
    }

    string name;

    cout << "Player 1, enter your name: " << endl;
    cin >> name;
    Player p1(name);

    cout << "Player 2, enter your name: " << endl;
    cin >> name;
    Player p2(name);

    cout << endl;

    // main program loop
    bool done = false;
    while (!done) {
        turn(p1, solution, validWords);
        if (p1.won() || p1.remainingGuesses() == 0) done = true;

        switchTurns(p2);

        turn(p2, solution, validWords);
        if (p2.won() || p2.remainingGuesses() == 0) done = true;

        if (!done) switchTurns(p1);
    }

    cout << endl << endl << endl << endl;

    if (!p1.won() && !p2.won())
    {
        cout << "Nobody Wins!" << endl;
    }
    else if (p1.won() && p2.won())
    {
        cout << "Tie!" << endl;
    }
    else if (p1.won() && !p2.won())
    {
        cout << p1.name() << " Won! Better luck next time " << p2.name() << "." << endl;
    }
    else
    {
        cout << p2.name() << " Won! Better luck next time " << p1.name() << "." << endl;
    }

    delete validWords;
    return 0;
}

void turn(Player& player, const std::string& solution, std::set<std::string>* wordList)
{
    string guess;
    cout << player.name() << ", make your guess: " << endl;
    cin >> guess;

    while (!isGuessValid(guess, wordList)) {
        cin >> guess;
    }

    player.addGuess(guess, solution);
    player.printGuesses();

    cout << "Press enter to end your turn." << endl;
    cin.get();
}

bool isGuessValid(const std::string& word, std::set<std::string>* wordList)
{
    if (word.size() != 5) {
        cout << "Please enter a 5 letter word." << endl;
        return false;
    }

    if (wordList->find(word) == wordList->end()) {
        cout << "Please enter a valid word." << endl;
        return false;
    }

    return true;
}

void switchTurns(Player& player)
{
    for (int i = 0; i < 50; i++) {
        cout << endl;
    }

    cout << player.name() << ", press ENTER to start your turn." << endl;
    cin.get();

    for (int i = 0; i < 50; i++) {
        cout << endl;
    }
}