#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

std::string getRandomWord(const char* filename);

int main(int argc, char** argv)
{
    cout << endl;
    cout <<  "$$\\      $$\\                           $$\\ $$\\           "  << endl;
    cout <<  "$$ | $\\  $$ |                          $$ |$$ |          "  << endl;
    cout <<  "$$ |$$$\\ $$ | $$$$$$\\   $$$$$$\\   $$$$$$$ |$$ | $$$$$$\\  "  << endl;
    cout <<  "$$ $$ $$\\$$ |$$  __$$\\ $$  __$$\\ $$  __$$ |$$ |$$  __$$\\ "  << endl;
    cout <<  "$$$$  _$$$$ |$$ /  $$ |$$ |  \\__|$$ /  $$ |$$ |$$$$$$$$ |"  << endl;
    cout <<  "$$$  / \\$$$ |$$ |  $$ |$$ |      $$ |  $$ |$$ |$$   ____|"  << endl;
    cout <<  "$$  /   \\$$ |\\$$$$$$  |$$ |      \\$$$$$$$ |$$ |\\$$$$$$$\\ "  << endl;
    cout <<  "\\__/     \\__| \\______/ \\__|       \\_______|\\__| \\_______|"  << endl;  
    cout << endl;                        

    srand(time(0));

    string word = getRandomWord(argv[1]);


    return 0;
}

std::string getRandomWord(const char* filename)
{

}

