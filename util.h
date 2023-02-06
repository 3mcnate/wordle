#ifndef WORDLE_UTIL_H
#define WORDLE_UTIL_H

#include <set>
#include <string>

std::set<std::string> *readWords(const char *filename);

std::string getRandomWord(const char *filename);

bool isWordValid(std::set<std::string> *wordList, std::string word);

bool isGuessValid(const std::string& word, std::set<std::string>* wordList);

std::string red(std::string word);
std::string yellow(std::string word);
std::string green(std::string word);

std::string red(char c);
std::string yellow(char c);
std::string green(char c);

void clearScreen(int lines = 100);

std::string convToLower(std::string src);

#endif