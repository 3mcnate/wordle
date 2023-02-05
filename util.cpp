#include "util.h"
#include <fstream>
#include <iostream>
#include <sstream>

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
    cout << red("DEBUG: ") << "Solution word is: " << word << endl;
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

bool isWordValid(std::set<std::string> *wordList, std::string word)
{
    if (wordList->find(word) == wordList->end())
        return false;
    return true;
}

std::string red(std::string word)
{
    stringstream ss;
    ss << "\x1b[31m" << word << "\x1b[0m";
    return ss.str();
}

std::string yellow(std::string word)
{
    stringstream ss;
    ss << "\x1b[33m" << word << "\x1b[0m";
    return ss.str();
}

std::string green(std::string word)
{
    stringstream ss;
    ss << "\x1b[32m" << word << "\x1b[0m";
    return ss.str();
}

void clearScreen(int lines)
{
    for (int i = 0; i < lines; i++) 
        cout << endl;
}

std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}