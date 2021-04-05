#include <iostream>

#include "barrier.h"
#include "functions.h"

using namespace std;

void typewriter( string, int );

//This function acts as a barrier between different parts of the game allowing easy readibility
void barrier()
{
    cout << endl;
    string line = "Please press Enter to continue.....\n";
    typewriter(line);
    cin.get();
    system("clear");
}