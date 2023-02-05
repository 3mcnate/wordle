#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "util.h"
#include <fstream>
#include <cstring>
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv)
{
    cout << endl;
    cout << "\x1b[36m $$\\      $$\\                           $$\\ $$\\           \x1b[0m" << endl;
    cout << "\x1b[36m $$ | $\\  $$ |                          $$ |$$ |          \x1b[0m" << endl;
    cout << "\x1b[36m $$ |$$$\\ $$ | $$$$$$\\   $$$$$$\\   $$$$$$$ |$$ | $$$$$$\\  \x1b[0m" << endl;
    cout << "\x1b[35m $$ $$ $$\\$$ |$$  __$$\\ $$  __$$\\ $$  __$$ |$$ |$$  __$$\\ \x1b[0m" << endl;
    cout << "\x1b[35m $$$$  _$$$$ |$$ /  $$ |$$ |  \\__|$$ /  $$ |$$ |$$$$$$$$ |\x1b[0m" << endl;
    cout << "\x1b[35m $$$  / \\$$$ |$$ |  $$ |$$ |      $$ |  $$ |$$ |$$   ____|\x1b[0m" << endl;
    cout << "\x1b[34m $$  /   \\$$ |\\$$$$$$  |$$ |      \\$$$$$$$ |$$ |\\$$$$$$$\\ \x1b[0m" << endl;
    cout << "\x1b[34m \\__/     \\__| \\______/ \\__|       \\_______|\\__| \\_______|\x1b[0m" << endl;
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

    string temp;
    bool p2Won = false;
    bool p1Won = false;
    string p1, p2, g1, g2, guessCheck;
    int p1GuessRemain = 7;
    int p2GuessRemain = 7;

    cout << "Player 1, enter your name: " << endl;
    cin >> p1;
    cout << "Player 2, enter your name: " << endl;
    cin >> p2;

    cout << endl;

    while(p1GuessRemain > 0 && p2GuessRemain > 0 && p1Won == false && p2Won == false){
        if(p1GuessRemain < 7){
            cout << p1 << ", press Enter to start your turn." << endl;
            cin.ignore();
            cin.get();
            cout << "Here is your previous guess: " << endl;
            checkWord(g1, word);
            cout << endl;
        }
        cout << p1 << ", make your guess: " << endl;
        cin >> g1;
        if(g1.size() != 5 || !isWordValid(validWords, g1)){ 
            cout << "Please enter a word that is 5 letters long: " << endl;
            cin >> g1;
            while(g1.size() != 5 || !isWordValid(validWords, g1)){ 
                cout << "Please enter a word that is 5 letters long: " << endl;
                cin >> g1;
            }
        }
        p1Won = checkWord(g1, word);

        cout << "Press Enter to Continue" << endl;
        cin.ignore();
        cin.get();

        for(int k = 0; k < 100; k++){ //clear the terminal at end of turn
            cout << endl;
        }

        cout << endl;
        cout << "________________________________________________________________" << endl;
        cout << endl;

        //player 2's turn
        if(p2GuessRemain < 7){
            cout << p2 << ", press Enter to start your turn." << endl;
            cin.ignore();
            cin.get();
            cout << "Here is your previous guess: " << endl;
            checkWord(g2, word);
            cout << endl;
        }

        cout << p2 << ", make your guess: " << endl;
        cin >> g2;
        if(g2.size() != 5 || !isWordValid(validWords, g2)){ // || !isWord(g2)
            cout << "Please enter a word that is 5 letters long: " << endl;
            cin >> g2;
            while(g2.size() != 5 || !isWordValid(validWords, g2)){ // || !isWord(g2)
                cout << "Please enter a word that is 5 letters long: " << endl;
                cin >> g2;
            }
        }
        p2Won = checkWord(g2, word);

        cout << "Press Enter to Continue" << endl;
        cin.ignore();
        cin.get();

        for(int k = 0; k < 100; k++){ //clear the terminal at end of turn
            cout << endl;
        }

        cout << endl;
        cout << "________________________________________________________________" << endl;
        cout << endl;

        p1GuessRemain -= 1;
        p2GuessRemain -= 1;
    }

    if(p1Won == false && p2Won == false){
        cout << "Nobody Wins!" << endl;
        cout << "The correct word was " << word << endl;
    }else if(p1Won == true && p2Won == true){
        cout << "Tie game." << endl;
    }else if(p1Won == true && p2Won == false){
        cout << p1 << " Won! Better luck next time " << p2 << "." << endl;
    }else{
        cout << p2 << " Won! Better luck next time " << p1 << "." << endl;
    }

    delete validWords;
    return 0;
}


