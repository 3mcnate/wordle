#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "util.h"

using namespace std;

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

    string temp;
    bool p2Won = false;
    bool p1Won = false;
    string p1, p2, g1, g2, guessCheck;
    int p1GuessRemain = 5;
    int p2GuessRemain = 5;

    cout << "Player 1, enter your name: " << endl;
    cin >> p1;
    cout << "Player 2, enter your name: " << endl;
    cin >> p2;

    cout << endl;

    while (p1GuessRemain > 0 && p2GuessRemain > 0 && p1Won == false && p2Won == false)
    {
        if (p1GuessRemain < 7)
        {
            cout << "Dont scroll up." << endl;
        }
        cout << p1 << ", make your guess: " << endl;
        cin >> g1;
        if (g1.size() != 5 || !isWordValid(validWords, g1))
        { 
            cout << "Please enter a word that is 5 letters long: " << endl;
            cin >> g1;
            while (g1.size() != 5 || !isWordValid(validWords, g1))
            {
                cout << "Please enter a word that is 5 letters long: " << endl;
                cin >> g1;
            }
        }
        // guessCheck = makeGuess(g1);
        for (int i = 0; i < 5; i++)
        {
            if (guessCheck[i] == '0')
            {
                // make letter grey
                cout << "[ " << g1[i] << " ]" << endl;
            }
            else if (guessCheck[i] == '1')
            {
                // make letter yellow
                cout << "[ " << g1[i] << " ]" << endl;
            }
            else if (guessCheck[i] == '2')
            {
                // make letter green
                cout << "[ " << g1[i] << " ]" << endl;
            }
        }

        if (guessCheck[0] == '2' && guessCheck[1] == '2' && guessCheck[2] == '2' && guessCheck[3] == '2' && guessCheck[4] == '2')
        {
            cout << p1 << " Guessed the correct Word! Last chance " << p2 << "!" << endl;
            p1Won = true;
        }

        cout << "Press Enter to Continue" << endl;
        cin.ignore();
        cin.get();
        
        for (int k = 0; k < 100; k++)
        { // clear the terminal at end of turn
            cout << endl;
        }

        cout << endl;
        cout << "________________________________________________________________" << endl;
        cout << endl;

        // player 2's turn
        cout << "Dont scroll up." << endl;

        cout << p2 << ", make your guess: " << endl;
        cin >> g2;
        if (g2.size() != 5 || !isWordValid(validWords, g2))
        { 
            cout << "Please enter a word that is 5 letters long: " << endl;
            cin >> g2;
            while (g2.size() != 5 || !isWordValid(validWords, g2))
            { 
                cout << "Please enter a word that is 5 letters long: " << endl;
                cin >> g2;
            }
        }
        // guessCheck = makeGuess(g1);
        for (int i = 0; i < 5; i++)
        {
            if (guessCheck[i] == '0')
            {
                // make letter grey
                cout << "[ " << g2[i] << " ]" << endl;
            }
            else if (guessCheck[i] == '1')
            {
                // make letter yellow
                cout << "[ " << g2[i] << " ]" << endl;
            }
            else if (guessCheck[i] == '2')
            {
                // make letter green
                cout << "[ " << g2[i] << " ]" << endl;
            }
        }

        if (guessCheck[0] == '2' && guessCheck[1] == '2' && guessCheck[2] == '2' && guessCheck[3] == '2' && guessCheck[4] == '2')
        {
            cout << p2 << " Guessed the correct word!" << endl;
            p2Won = true;
            break;
        }

        cout << "Press Enter to Continue" << endl;
        cin.ignore();
        cin.get();

        for (int k = 0; k < 100; k++)
        { // clear the terminal at end of turn
            cout << endl;
        }

        cout << endl;
        cout << "________________________________________________________________" << endl;
        cout << endl;

        p1GuessRemain -= 1;
        p2GuessRemain -= 1;
    }

    if (p1Won == false && p2Won == false)
    {
        cout << "Nobody Wins!" << endl;
    }
    else if (p1Won == true && p2Won == true)
    {
        cout << "Tie game." << endl;
    }
    else if (p1Won == true && p2Won == false)
    {
        cout << p1 << " Won! Better luck next time " << p2 << "." << endl;
    }
    else
    {
        cout << p2 << " Won! Better luck next time " << p1 << "." << endl;
    }

    delete validWords;
    return 0;
}


