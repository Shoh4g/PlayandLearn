// The main file of the Program/Project
#include <iostream>
#include <iomanip>
#include <time.h>
#include <ctime>
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h> //As you are writing for windows, change it into <windows.h>
#endif

#include <string>

#include "functions.h"   //creating Header files
#include "barrier.h"

using namespace std;


void typewriter( string, int );

string player_name;



//creating a struct to store various data of the game
//name will store the name of the player, his health, his heals_left, and his score
struct data{
    string name;
    int health, heals_left, score;
};


data game_status;   //making game_status a global variable to be used in the whole program



//This functions stors the name and status of the game in the file to be retrieved later
void data_storing( int health, int heals, int score)
{
    ofstream getdata("status.txt");

    if (getdata.fail())
    {
        cout << "Error in opening status file! OOPS :(" << endl;
        exit(1);
    }

    game_status.name = player_name;
    game_status.health = health;
    game_status.heals_left = heals;
    game_status.score = score;

    getdata << "Name: " << player_name << endl << "Current Health: " << health << endl;
    getdata << "Heals Left: " << heals << endl << "Current Score: " << score << endl;

    getdata.close();
}


void electrochemistry ( int choice )
{
    if (choice == 1 )
    {

    }
    else if (choice == 2)
    {

    }
    else if ( choice == 3)
    {

    }
}



void environmentalchemistry( int choice)
{
    if (choice == 1 )
    {

    }
    else if (choice == 2)
    {

    }
    else if ( choice == 3)
    {

    }
}


void thermochemistry( int choice)
{
    string line;
    if (choice == 1 )
    {
        ifstream read( "thermochemistry_easy.txt");
        if ( read.fail() )
        {
            cout << "Error Opening the file.. OOP :(" << endl;
            exit(1);
        }

        while (!read.eof() )
        {
            getline(read, line);
            while ( line != "**")
            {
                cout << line << endl;
            }
        }
    }

    else if (choice == 2)
    {

    }
    else if ( choice == 3)
    {

    }
}

// Questions taken from following websites
//https://www.mcqspk.com/thermochemistry-mcqs/3/
//https://www.chem.tamu.edu/class/fyp/mcquest/ch15.html
//https://www.neetprep.com/questions/54-Chemistry/650-Thermodynamics

void chemistry_topics( int choice)
 {
    int  difficulty_level;
    string level_selection = "What difficulty level you want?\n->Press 1 for Easy\n->Press 2 for Medium\n-> Press 3 for Hard\n";
    typewriter(level_selection);
    cin >> difficulty_level;

    if (choice == 1 )
    {
        electrochemistry(difficulty_level);
    }
    else if (choice == 2)
    {
        environmentalchemistry(difficulty_level);
    }
    else if ( choice == 3)
    {
        thermochemistry(difficulty_level);
    }
}

int main()
{
    player_name = introduction();

    //creating dynamic memory to store the number of times healing can be done
    string Dynamic_memory = "How many times you want an opportunity to heal! ( Choose between 3 - 8 times )\n";
    int size; //getting size of the heal array
    typewriter(Dynamic_memory);
    cin >> size;
    int * heal = new int [size];   //creating dynamic memory
    
    //making all the array false so that it is clear that healing is not yet used! When healing
    // will be used, the false be turned to true

    for ( int i = 0; i < size; i++ )
    {
        heal[i] = false;
    }


    data_storing(50,size,0);  //storing initial data of the player


    //Selecting topic related to chemistry
    int topic;
    string topic_selection = "What topics you want to practice and test!\n->Press 1 for Electro-Chemistry\n->Press 2 for Environmental Chemistry\n";
    string topic_selection2 = "-> Press 3 for Thermo-Chemistry\n";
    typewriter(topic_selection);
    typewriter(topic_selection2);
    cin >> topic;

    chemistry_topics( topic );


    
    return 0;
}
