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
