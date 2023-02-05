#ifndef WORDLE_UTIL_H
#define WORDLE_UTIL_H

#include <set>
#include <string>

std::set<std::string> *readValidWords(const char *filename);

std::string getRandomWord(const char *filename);

bool isWordValid(std::set<std::string> *wordList, std::string word);

std::string red(std::string word);
std::string yellow(std::string word);
std::string green(std::string word);

#endif