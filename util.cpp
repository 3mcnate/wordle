#include "util.h"
#include <fstream>
#include <iostream>

using namespace std;

std::string getRandomWord(const char *filename)
{
    ifstream file(filename);
    if (file.fail())
    {
        return "";
    }

    // get length of file
    file.seekg(0, file.end);
    int numWords = file.tellg() / 6;

    int randWordIndex = (rand() % numWords) * 6;
    file.seekg(randWordIndex, file.beg);

    string word;
    getline(file, word);

#ifdef DEBUG
    cout << "Solution word is: " << word << endl;
#endif

    return word;
}

std::set<std::string> *readValidWords(const char *filename)
{
    ifstream file(filename);
    if (file.fail())
    {
        cout << "Incorrect valid words list filename." << endl;
        return nullptr;
    }

    set<string> *allWords = new set<string>;

    string word;
    while (file >> word)
    {
        allWords->insert(word);
    }

    return allWords;
}

bool isWordValid(std::set<std::string>* wordList, std::string word)
{
    if (wordList->find(word) == wordList->end()) return false;
    return true;
}  