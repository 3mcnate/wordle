#include "player.h"
#include "util.h"
#include <iostream>
#include <sstream>

#define LENGTH 5

using namespace std;

Guess::Guess(std::string guess, std::string solution)
{
    stringstream colored_word;
    correct_ = true;

    for (int i = 0; i < LENGTH; i++)
    {

        char letter = guess[i];
        stringstream letterWithBrackets;
        letterWithBrackets << '[' << letter << ']';

        // complete match
        if (letter == solution[i])
        {
            colored_word << green(letterWithBrackets.str());
        }

        // partial match
        else if (solution.find(letter) != string::npos)
        {
            colored_word << yellow(letterWithBrackets.str());
            correct_ = false;
        }

        // no match
        else
        {
            colored_word << red(letterWithBrackets.str());
            correct_ = false;
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
    return won_;
}