//This c++ program generate introduction for the game and has some important functions which are used in the game
#include <iostream>
#include <iomanip>
#include <time.h>
#include <ctime>
#ifdef _WIN32
#include <Windows.h>  //However, program need sto be changed. Change system("clear") to system("cls") and use numbers in Sleep(1000) for 1 sec in windows
#else                 // and sleep(1) for 1 sec in linux
#include <unistd.h> //for windows, change it into <windows.h>
#endif

#include <string>

#include "functions.h"   //creating Header files
#include "barrier.h"


using namespace std;

//A function to convert everything to uppercase
string toUpper( string str )
{
    for ( int i = 0; i < str.length(); i++ )
    {
        char y = str[i];
        if (y >= 'a' && y <= 'z')
        {
            str[i] = ( ( y - 'a') + 65 );
        }
    }

    return str;
} 


// This function gives a typewriter effect to the output of the game
//It uses sleep function to give out the cout output with delay!
void typewriter( string str, int time )
{
    for ( int i = 0; str[i] != '\0'; i++ )
    {
        cout << str[i];
	cout.flush();
	usleep( time );
    }
}

// Creating a function which will print a a specific set of characters on the screen for certain times
// For example if character entered is '*' and number of times to be printed is 80 the output will look like
// ********************************************************************************
void print_line_pattern( char character_to_print, int times )
{
    for ( int i = 0; i < times; i++ )
    {
        cout << character_to_print;
    }

    cout << endl;
}



//This Function creates an introductory diamond logo of the screen
void diamond( char diamondCharacter, int m, int r)
{
    for ( int i = 0; i < r;  i++ )
    {
        if ( i != r - 1 )
        {
            if ( i == 0 )
            {
                cout << setw( m - (3 * i ) + 1) << diamondCharacter;
                cout << endl;
                sleep(1);
            }
            else
            {
                cout << setw( m - (3 * i )) << diamondCharacter << setw( ( 6 * i ) + 2 ) << diamondCharacter;
                cout << endl;
                sleep(1);
            }
        }
        else 
        {
            cout << setw( m - (3 * i )) << diamondCharacter << setw( ( 6 * i ) + 1 ) << " P.L.A.Y_A.N.D_L.E.A.R.N " << diamondCharacter;;
            cout << endl;
            sleep(1);            
        }
    }
    
    for ( int i = r - 2 ; i >= 0;  i-- )
    {
            if ( i == 0 )
            {
                cout << setw( m - (3 * i  ) + 1) << diamondCharacter;
                cout << endl;
                sleep(1);
            }
            else
            {
                cout << setw( m - (3 * i )) << diamondCharacter << setw( ( 6 * i ) + 2 ) << diamondCharacter;
                cout << endl;
                sleep(1);
            }
    }
}

// This function contains the main introduction of the game!
//It returnss name of the player
string introduction()
{
    string player_name;   
    string greetings  = "Greetings ";
    string line_1 = "This is how game works!\n";
    string description_1 = "This game focuses on various concepts of Chemistry and is a supplement to text-books and revision guides!\n";
    string description_2 = "The game will consist of 3 rounds!\nEach round is related to specific topics in the Chemistry!\n";
    string description_3 = "Each round is then further divided into 3 difficulty levels :\n--> Easy\n--> Medium\n--> Hard\n";
    string description_4 = "You will answer chemistry related mcqs at each level.\nAt the start of the game, you will be provided with 50 health points.\n";
    string description_5 = "If you answer the mcqs correctly, your score will increase by 1.\nHowever, if you answer the mcqs wrong, your health points will decrease by 2!\n";
    string description_6 = "The game ends when your health points reach to 0.\nThe interesting thing about this game is that you can heal (regain 10 health points) ";
    string description_7 = "yourself for certain times.\nThe amount of times you can heal is determined in the start where you mention the maximum number of times you want to heal (from 3-8 times).\n"; 
    string description_8 = "However, the catch is that the healing procedure depends on your guess between 1-6.\nIf your guess matches with the ";
    string description_9 = "number resulted from rolling of the dice, you will regain 10 health points .i.e. healed!\nMoreover, the game gets more interesting! The first two times ";
    string description_10 = "if your guess is wrong, no health points will be deducted.\nHowever, after then every next time, your guess is wrong, health points";
    string description_11 = " will be deducted from your current health points!\nThe amount of health points deducted depends on your choice of number of rolls.\n";
    string description_12 = "The deduction in health is equal to (choice of rolls*1).\nSo use healing CAREFULLY!\nAt the end of each topic/level, you can quit the game by pressing 'q' or move on another ";
    string description_13 = "topic/level by pressing 'ENTER'.At the end of each topic, your score will be shown.At the end of the game or when you quit, you final report card will be displayed.\n";
    string description_14 = "Lastly, you will be asked to answer the questions in two ways!\n1- By typing in the mcq letter.\n2- By typing in the answer which won't have any options.\n";
    string description_15 = "If you enter unexpected values, the game might behave in unexpected ways :(\nIf game crashes, you can restart the program.\n";

    system("clear"); // clear screen command for linux
    print_line_pattern( '=', 80 );
    sleep(1);
    diamond( '*', 40, 5 );
    sleep(1);
    print_line_pattern( '=', 80 );
    sleep(2);
    system("clear");  //for windows use system("cls")

 
    string asking_player_name = "What should we call you?\n";
    typewriter( asking_player_name, 150000 );
    getline( cin, player_name);

    typewriter( greetings, 150000 );
    typewriter ( player_name, 150000 );
    sleep(1);
    cout <<"!\n";
    sleep(1);
    print_line_pattern( '_', 80 );
    sleep( 1 );
    typewriter( line_1, 150000 );
    print_line_pattern( '_', 80 );
    sleep( 1 );
    typewriter( description_1, 150000 );
    typewriter( description_2, 150000 );
    typewriter( description_3, 150000 );
    typewriter( description_4, 150000 );
    typewriter( description_5, 150000 );
    typewriter( description_6, 150000 );
    typewriter( description_7, 150000 );
    typewriter( description_8, 150000 );
    typewriter( description_9, 150000 );
    typewriter( description_10, 150000 );
    typewriter( description_11, 150000 );
    typewriter( description_12, 150000 );
    typewriter( description_13, 150000 );
    typewriter( description_14, 150000 );
    typewriter( description_15, 150000 );
    print_line_pattern( '_', 80 );
    sleep( 1 );
    barrier();

    return player_name;
    
}

