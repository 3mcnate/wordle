#ifndef WORDLE_UTIL_H
#define WORDLE_UTIL_H

#include <set>
#include <string>

std::set<std::string> *readValidWords(const char *filename);

std::string getRandomWord(const char *filename);

bool isWordValid(std::set<std::string>* wordList, std::string word);

bool checkWord(string input, string word);



#endif
