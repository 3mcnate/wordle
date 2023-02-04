#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <set>

using namespace std;

std::set<std::string> *readValidWords(const char *filename);
std::string getRandomWord(const char *filename);

int main(int argc, char **argv)
{
    cout << endl;
    cout << "$$\\      $$\\                           $$\\ $$\\           " << endl;
    cout << "$$ | $\\  $$ |                          $$ |$$ |          " << endl;
    cout << "$$ |$$$\\ $$ | $$$$$$\\   $$$$$$\\   $$$$$$$ |$$ | $$$$$$\\  " << endl;
    cout << "$$ $$ $$\\$$ |$$  __$$\\ $$  __$$\\ $$  __$$ |$$ |$$  __$$\\ " << endl;
    cout << "$$$$  _$$$$ |$$ /  $$ |$$ |  \\__|$$ /  $$ |$$ |$$$$$$$$ |" << endl;
    cout << "$$$  / \\$$$ |$$ |  $$ |$$ |      $$ |  $$ |$$ |$$   ____|" << endl;
    cout << "$$  /   \\$$ |\\$$$$$$  |$$ |      \\$$$$$$$ |$$ |\\$$$$$$$\\ " << endl;
    cout << "\\__/     \\__| \\______/ \\__|       \\_______|\\__| \\_______|" << endl;
    cout << endl;

    if (argc < 3)
    {
        cout << "Usage: ./wordle <solutionwords> <possibleinputs>" << endl;
        return 1;
    }

    srand(time(0));
    string word = getRandomWord(argv[1]);
    if (word == "")
    {
        cout << "Invalid solutions filename." << endl;
        return 1;
    }

    set<string> *validWords = readValidWords(argv[2]);
    if (validWords == nullptr)
    {
        cout << "Invalid input words filename." << endl;
        return 1;
    }

    delete validWords;
    return 0;
}

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

std::set<std::string>* readValidWords(const char *filename)
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