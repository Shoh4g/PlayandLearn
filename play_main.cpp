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
    return 0;
}
