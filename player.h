#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

class Guess
{
public:
    Guess(std::string guess, std::string solution);
    std::string coloredWord();
    bool correct();

private:
    std::string colored_;
    bool correct_;
};

class Player
{
public:
    Player(std::string name, int numGuesses = 7);

    void addGuess(std::string guess, std::string solution);
    void printGuesses();

    bool won();

private:
    std::string name_;
    std::vector<Guess> guesses_;
    int remainingGuesses_;
    bool won_;
};

#endif