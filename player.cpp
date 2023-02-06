#include "player.h"
#include "util.h"
#include <iostream>
#include <sstream>

#define LENGTH 5

using namespace std;

Guess::Guess(std::string guess, std::string solution, std::map<char, int>& guessedLetters)
{
    stringstream colored_word;
    correct_ = guess == solution;
    
    int* indexColors = checkGuess(guess, solution, guessedLetters);

    for (int i = 0; i < LENGTH; i++)
    {
        stringstream letterWithBrackets;
        letterWithBrackets << '[' << guess[i] << ']';

        if (indexColors[i] == RED) {
            colored_word << red(letterWithBrackets.str());
        }
        else if (indexColors[i] == YELLOW) {
            colored_word << yellow(letterWithBrackets.str());
        }
        else {
            colored_word << green(letterWithBrackets.str());
        }
    }

    colored_ = colored_word.str();
    delete [] indexColors;
}

int* Guess::checkGuess(const std::string& guess, const std::string& solution, std::map<char, int>& guessedLetters)
{

    int* indexColors = new int[LENGTH];
    for (int i = 0; i < LENGTH; i++) indexColors[i] = RED;
    
    char removedCharacter = '-'; // guess guaranteed to not contain removed character

    string solutionCopy = solution;

    // first pass: check for full matches
    for (int i = 0; i < LENGTH; i++) {
        if (guess[i] == solutionCopy[i]) {
            indexColors[i] = GREEN;
            guessedLetters[guess[i]] = GREEN;

            // make sure to remove character to prevent duplicates from being colored yellow.
            solutionCopy[i] = removedCharacter;
        }
    }

    // second pass: check for partial/non matches
    for (int i = 0; i < LENGTH; i++) {
        size_t pos = solutionCopy.find(guess[i]);

        // check if current letter exists in solution
        if (pos != string::npos && indexColors[i] != GREEN && indexColors[pos] != GREEN) {
            indexColors[i] = YELLOW;

            if (guessedLetters[guess[i]] < YELLOW)
                guessedLetters[guess[i]] = YELLOW;
            
            // make sure to remove from solution to color the correct number of letters yellow.
            solutionCopy[pos] = removedCharacter;
        }

        else if (guessedLetters[guess[i]] < RED) {
            guessedLetters[guess[i]] = RED;
        } 
    }

    return indexColors;
}


std::string Guess::coloredWord()
{
    return colored_;
}

bool Guess::correct()
{
    return correct_;
}

/**
 *
 *  PLAYER
 *
 */

Player::Player(std::string name, std::string solution, int numGuesses)
    : name_(name), solution_(solution), remainingGuesses_(numGuesses), won_(false)
{
    for (int i = 'a'; i < 'z' + 1; i++) {
        guessedLetters_[(char)i] = BLACK;
    }
}

void Player::addGuess(std::string guess)
{
    Guess g(guess, solution_, guessedLetters_);
    
    if (g.correct())
    {
        won_ = true;
    }

    remainingGuesses_--;
    guesses_.push_back(g);
}

void Player::printGuesses()
{
    for (size_t i = 0; i < guesses_.size(); i++)
    {
        cout << "  " << guesses_[i].coloredWord() << endl;
    }
}

bool Player::won()
{
    return won_ && remainingGuesses_ != 0;
}

void Player::printLastGuess()
{
    if (guesses_.size() > 0)
        cout << "  " << guesses_[guesses_.size() - 1].coloredWord() << endl;
}

void Player::printKeyboard()
{
    const char* firstRow = "qwertyuiop"; // size = 11
    const char* secondRow = "asdfghjkl"; // size = 10
    const char* thirdRow = "zxcvbnm"; // size = 8

    printKeyboardRow(firstRow, 11);
    printKeyboardRow(secondRow, 10);
    cout << ' '; printKeyboardRow(thirdRow, 8);
}

void Player::printKeyboardRow(const char* row, int size)
{
    cout << "  ";
    for (int i = 0; i < size; i++) {

        string letter(1, row[i]);
        int letterCode = guessedLetters_[row[i]];

#ifdef DEBUGKEYBOARD
    cout << "Letter: " << letter << "\t\tLetter code: " << letterCode << endl;
#endif

        if (letterCode == BLACK) cout << letter;
        else if (letterCode == RED) cout << red(letter);
        else if (letterCode == YELLOW) cout << yellow(letter);
        else if (letterCode == GREEN) cout << green(letter);
        cout << ' ';
    }

    cout << endl;
}

std::string Player::getFinalWordResult()
{
    stringstream final;

    for (int i = 0; i < LENGTH; i++) {
        char letter = solution_[i];
        if (guessedLetters_[letter] == BLACK) final << letter;
        if (guessedLetters_[letter] == YELLOW) final << yellow(letter);
        if (guessedLetters_[letter] == GREEN) final << green(letter);
    }

    return final.str();
}