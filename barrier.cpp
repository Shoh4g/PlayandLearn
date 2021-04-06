#include <iostream>
#include <string>

#include "barrier.h"
#include "functions.h"

using namespace std;

void typewriter( string str, int time );

//This function acts as a barrier between different parts of the game allowing easy readibility
void barrier()
{
    cout << endl;
    string line = "Please press Enter to continue.....\n";
    typewriter(line, 150000);
    cin.get();
    system("clear");
}


//Added for providing quit function as well
bool barrier2()
{
    char s;
    cout << endl;
    string line = "Please press Enter to continue..... or 'q' to quit\n";
    typewriter(line, 150000);
    cin.get(s);
    system("clear");
    if (s == 'q' || s == 'Q' )
    {
        return true;
    }
    else
    {
        return false;
    }
}
