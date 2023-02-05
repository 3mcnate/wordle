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

bool checkWord(string input, string word)
{
    // make input all lowercase 
	for (int i = 0; i < word.length(); i++)
  	{
  		word[i] = tolower(word[i]);
  	}

    if (input == word){
        // correct guess
        cout << "\x1b[32m" << "Correct! Your word was: [" << input << "] \x1b[0m" << endl;
        return true;
    }

    char correctWord [5] = {word[0], word[1], word[2], word[3], word[4]};

    // print the word with correct colors
    for (int i=0; i<5; i++){
        if (input[i] == word[i]){
            // print that index in green
            cout << "\x1b[32m[" << input[i] << "]\x1b[0m";
            correctWord[i] = '\0';

        } else if ((input[i] == correctWord[0]) || (input[i] == correctWord[1]) || (input[i] == correctWord[2]) || (input[i] == correctWord[3]) || (input[i] == correctWord[4])){
            // print that index in yellow 
            cout << "\x1b[33m[" << input[i] << "]\x1b[0m";
            for(int j = 0; j < 5; j++){
                if(input[i] == correctWord[j]){
                    correctWord[j] = '\0';
                }
            }

        } else {
            // print in red
            cout << "\x1b[31m[" << input[i] << "]\x1b[0m";

        }
    }
    cout << endl;
    return false;
}
