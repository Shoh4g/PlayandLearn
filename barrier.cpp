#include <iostream>
#include <string>

#include "barrier.h"
#include "functions.h"

using namespace std;


// A function declaration allowing the use of typewriter function from different header file
void typewriter( string str, int time );




//This function acts as a barrier between different parts of the game allowing easy readibility
// It returns nothing but clears the screen after enter is pressed
void barrier()
{
    cout << endl;
    string line = "Please press Enter to continue.....\n";
    typewriter(line, 150000);  //Typewriter function to give a feel that words are beinhg said/written
    cin.get();
    system("clear");  // Linux command to clear the screen
}





//Added for providing quit function as well
// It returns a boolean value indicating whether to quit the game or not
// Enter is pressed which allows the game to continue
bool barrier2()
{
    char s;
    cout << endl;
    string line = "Please press Enter to continue..... or 'q' or any key to quit except enter\n";
    typewriter(line, 150000);

    if ( cin.get() == '\n' )   // This condition will determine whether to continue or quite
    {
        system("clear");
        return false;
    }
    else
    {
        system("clear");
        return true;
    }
}
