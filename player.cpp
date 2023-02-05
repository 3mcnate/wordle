#include "player.h"
#include "util.h"
#include <iostream>
#include <sstream>

#define LENGTH 5

using namespace std;

Guess::Guess(std::string guess, std::string solution)
{
    stringstream colored_word;
    correct_ = guess == solution;

    int matchingCodes[LENGTH] = { };

    for (int i = 0; i < LENGTH; i++)
    {
        if (guess[i] == solution[i]) {
            matchingCodes[i] = 2;
            solution[i] = '-';
        }
    }

    for (int i = 0; i < LENGTH; i++)
    {
        if (solution.find(guess[i]) != string::npos) {
            matchingCodes[i] = 1;
            solution[solution.find(guess[i])] = '-';
        }
    }

    for (int i = 0; i < LENGTH; i++)
    {
        stringstream letterWithBrackets;
        letterWithBrackets << '[' << guess[i] << ']';

        if (matchingCodes[i] == 0) {
            colored_word << red(letterWithBrackets.str());
        }
        else if (matchingCodes[i] == 1) {
            colored_word << yellow(letterWithBrackets.str());
        }
        else {
            colored_word << green(letterWithBrackets.str());
        }
    }

    colored_ = colored_word.str();
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

Player::Player(std::string name, int numGuesses)
    : name_(name), remainingGuesses_(numGuesses), won_(false)
{
}

void Player::addGuess(std::string guess, std::string solution)
{
    Guess g(guess, solution);
    if (g.correct())
    {
        won_ = true;
    }

    //for (int i = 0; i < guess.length(); i++) 
     //   guessedLetters_.insert(guess[i]);

    remainingGuesses_--;
    guesses_.push_back(g);
}

void Player::printGuesses()
{
    for (size_t i = 0; i < guesses_.size(); i++)
    {
        cout << guesses_[i].coloredWord() << endl;
    }
}

bool Player::won()
{
    return won_ && remainingGuesses_ != 0;
}

void Player::printLastGuess()
{
    if (guesses_.size() > 0)
        cout << guesses_[guesses_.size() - 1].coloredWord() << endl;
}

void Player::printKeyboard()
{
    
}