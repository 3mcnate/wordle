#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include <map>

enum {
    BLACK = 1,
    RED = 2,
    YELLOW = 3,
    GREEN = 4
};

class Guess
{
    public:
        Guess(std::string guess, std::string solution, std::map<char, int>& guessedLetters);
        int* checkGuess(const std::string& guess, const std::string& solution, std::map<char, int>& guessedLetters);

        std::string coloredWord();
        bool correct();

    private:
        std::string colored_;
        bool correct_;
};

class Player
{
    public:
        Player(std::string name, std::string solution, int numGuesses = 7);

        void addGuess(std::string guess);
        void printGuesses();
        void printLastGuess();
        void printKeyboard();

        int remainingGuesses() { return remainingGuesses_; }
        std::string name() { return name_; }
        std::string solution() { return solution_; }

        std::string getFinalWordResult();

        bool won();

    private:
        void printKeyboardRow(const char* row, int size);

        std::string name_;
        std::vector<Guess> guesses_;
        int remainingGuesses_;
        bool won_;
        std::map<char, int> guessedLetters_;
        std::string solution_;
};

#endif