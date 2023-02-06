#include <iostream>
#include "game.h"
#include "util.h"

using namespace std;

void turn(Player& player, std::set<std::string>* wordList)
{
    
    // print guess info
    player.printGuesses();
    cout << endl;

#ifdef DEBUG
    cout << red("DEBUG: ") << "Solution word is: " << player.solution() << endl << endl;
#endif

    player.printKeyboard();
    cout << endl;

    // get guess
    string guess;
    cout << player.name() << ", make your guess: " << endl;
    cin >> guess;
    guess = convToLower(guess);

    while (!isGuessValid(guess, wordList)) {
        cin >> guess;
        guess = convToLower(guess);
    }

    cout << endl;

    // add and check guess
    player.addGuess(guess);
    player.printLastGuess(); 
    cout << endl;

    if (player.won()) {
        cout << green("You guessed the word!") << endl;
        cout << endl;
    }
    else {
        cout << "You have " << player.remainingGuesses() << " guesses left." << endl;
    }
    
    cout << "Press enter to end your turn." << endl;
    cin.get(); cin.get();
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

void switchTurns(std::string n1, std::string n2, int gamemode)
{
    clearScreen();
    if (gamemode == 1)
    {    
        cout << n1 << ", press ENTER to start your turn. Make sure " << n2 << " is not looking at the screen." << endl;
        cin.get();
        clearScreen();
    }
}

std::string gamemode2setup(std::string n1, std::string n2, std::set<std::string>* wordList)
{
    clearScreen();
    cout << n1 << ", choose a word for " << n2 << "." << endl;
    std::string suggestions[3];

    for (int i = 0; i < 3; i++) {
        std::set<string>::iterator it = wordList->begin();
        int wordIndex = rand() % wordList->size();
        for (int j = 0; j < wordIndex; j++) {
            ++it;
        }
        suggestions[i] = *it;
    }

    cout << "Suggested words: "; for (int i=0; i < 3; i++) cout << suggestions[i] << " ";
    cout << endl;

    string word;
    cin >> word;
    word = convToLower(word);

    while (!isGuessValid(word, wordList)) {
        cin >> word;
        word = convToLower(word);
    }

    cout << endl << "You chose: " << green(word) << endl;
    cout << "Press enter and give the screen to " << n2 << "." << endl;
    cin.get(); cin.get();
    return word;
}

void showGameResult(Player& p1, Player& p2, int gamemode)
{
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
        cout << p1.name() << " won! Better luck next time " << (p2.name()) << "." << endl;
    }
    else
    {
        cout << (p2.name()) << " won! Better luck next time " << (p1.name()) << "." << endl;
    }

    if (gamemode == 1) {
        cout << "The word was " << green(p1.solution()) << endl << endl;
    }
    else {
        cout << endl << p1.name() << "'s word was " << p1.getFinalWordResult() << endl;
        cout << p2.name() << "'s word was " << p2.getFinalWordResult() << endl << endl; 
    }

    cout << p1.name() << " guessed: " << endl;
    p1.printGuesses();

    cout << endl;

    cout << p2.name() << " guessed: " << endl;
    p2.printGuesses();

    cout << endl << endl;
}