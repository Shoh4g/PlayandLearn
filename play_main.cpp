// The main file of the Program/Project
#include <iostream>
#include <iomanip>
#include <time.h>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h> //As you are writing for windows, change it into <windows.h>
#endif

#include <string>

#include "functions.h"   //creating Header files

using namespace std;


int main()
{
    introduction();
    system("clear");

    //creating dynamic memory to store the number of times healing can be done
    string Dynamic_memory = "How many times you want an opportunity to heal! ( Choose between 3 - 8 times )";
    int size; //getting size of the heal array
    cin >> size;
    int * heal = new int [size];   //creating dynamic memory
    
    //making all the array false so that it is clear that healing is not yet used! When healing
    // will be used, the false be turned to true

    for ( int i = 0; i < size; i++ )
    {
        heal[i] = false;
    }

    
    return 0;
}
