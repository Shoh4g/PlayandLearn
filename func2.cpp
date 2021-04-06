#include <iostream>
#include <string>
#include <cstdlib>  //for calling srand and rand functions
#include <ctime>    // for calling ctime

#include "barrier.h"
#include "functions.h"

using namespace std;

void typewriter( string str, int time );


//It returns true when a person wants to use healing chance
bool healer()
{
    char s;
    cout << endl;
    string line = "Do you want to heal or not (Y/N)\n";
    typewriter(line, 150000);
    cin.get(s);
    if (s == 'Y' || s == 'y' )
    {
        return true;
    }
    else
    {
        return false;
    }
}

//This function will return true or false according to the guess and will allow healing or not

bool random_guess()
{
    srand(time(NULL));
    int guess;
    int guessGenerator = (rand() % 6 )+ 1;
    cout << endl;
    string line = "Guess a number between 1 to 6\n";
    typewriter(line, 150000);
    cin >> guess;
    if ( guess == guessGenerator )
    {
        return true;
    }
    else
    {
        return false;
    }
}