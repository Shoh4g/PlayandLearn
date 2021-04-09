// Authors: Ahmed Masood and Sabyasachi Purkayastha
// Respective UIDs: 3035812127 and 3035729708
// Project 1340/2113: Text-Based Game

// This is the main program file where the actual code resides

// The librares that are used
#include <iostream>
#include <iomanip>
#include <time.h>
#include <ctime>
#include <fstream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h> //Trying to make it compaitable with linux and windows as well but need to change some functions before 
#endif              // implementig on windows


// Adding programmer created header files
#include "functions.h"  
#include "barrier.h"
#include "func2.h"

using namespace std;

//----------------------------------------------------------------------------------------------------------------


// Making function declarations
void typewriter( string, int );
string to_upper( string str );
bool barrier2();
bool healer();
void grow_array( string * & array, int & size );
bool heal_deduction_checker( int * & heal, int size );
void data_storing( int health, int heals, int score );
void show_status();
void game_play( string correct_answer[20], string file_name, int * & heal, int size, string * & report, int & arraysize, int & index );
void periodicity ( int choice, int * & heal, int size, string * & report, int & arraysize, int & index );
void electrochemistry( int choice, int * & heal, int size, string * & report, int & arraysize, int & index );
void thermochemistry( int choice, int * & heal, int size, string * & report, int & arraysize, int & index );
void chemistry_topics( int choice, int * &heal, int size, string * & report, int & arraysize, int & index );
string percentage_calculator( int count, double correct );
void topic_report( string filename,  int count, double correct );
void final_report( string * & report, int index );

//----------------------------------------------------------------------------------------------------------------

// Declaring global variables that are being used in whole program
// The name of the global variables start with g example gplayer_name
string gplayer_name;
bool gflag = false, ghealing, gdice_guess = false, gchecker;    //added to detrmine whether to quit the game or not

//----------------------------------------------------------------------------------------------------------------

//creating a struct to store various data of the game
//name will store the name of the player, his health, his heals_left, and his score
struct data{
    string name;
    int health, heals_left, score;
};


struct data game_status;   //making game_status a global variable to be used in the whole program. It does not have a g before the name

//----------------------------------------------------------------------------------------------------------------


// An array size increasing function
// This function is inspired from largenumber.cpp
// Mostly for Dynamic Memory Management
void grow_array( string * & array, int & size )
{
    if ( array == NULL )
        return;

    int newSize = size * 2;  // Doubles the size of previous array

    // doubled the size of the array;
    string * tmp = new string [ newSize ];   // Creates a new Dynamic Array
    // copy original contents
    for ( int i = 0; i < size; ++i )
        tmp[i] = array[i];

    delete [] array;  // Frees up the space

    array = tmp;
    size = newSize;
}


// this function will decide whether to deduct health for using healing or not
//returns true if health needs to be deducted
bool heal_deduction_checker( int * & heal, int size )
{
    int num = -1;  // Initialising num to -1

    // A for loop which checks whether elements of heal array are false or positive
    // false means heal is not used
    for ( int i = 0; i < size; i++ )
    {
        if ( heal[i] == false )
        {
            heal[i] = true;   // if not used, use it and convert it into
            num = i;
            break;
        }
    }

    if ( num < 2 )
    {
        return false;   // It returns false meaning health should not be deducted before 2 heals are done
    }
    else
    {
        return true;
    }

}



//This functions stores the name and status of the game in the file to be retrieved later
void data_storing( int health, int heals, int score )
{
    // Opens or creates the status.txt file
    ofstream getdata( "status.txt" );

    //checking error in the opening of the file
    if ( getdata.fail() )
    {
        cout << "Error in opening status file! OOPS :(" << endl;
        exit(1);
    }

    // assigning values to various variables of struct data structure
    game_status.name = gplayer_name;
    game_status.health = health;
    game_status.heals_left = heals;
    game_status.score = score;

    // sends data to to the file to be retrived later
    getdata << "Player Name: " << gplayer_name << endl << "Current Health: " << health << endl;
    getdata << "Heals Left: " << heals << endl << "Current Score: " << score << endl;

    getdata.close();   // closes the file
}


// This function will show your current score and health and heals left
void show_status()
{
    string line;
    ifstream showdata( "status.txt" );

    //checking error in the opening of the file
    if ( showdata.fail() )
    {
        cout << "Error in opening status file! OOPS :(" << endl;
        return;
    }

    // Printing a line pattern
    print_line_pattern( '*', 80 );

    // getting data
    while ( getline( showdata, line ) )
    {
        cout << line << endl;
    }

    showdata.close();   // closing the file

    print_line_pattern( '*', 80 );

    return;

}

//----------------------------------------------------------------------------------------------------------------


// This is a game_play function which takes correct answers array, file name to be opened for questions and heal and its size
// In this fucntion most of the game is being played and conducted
void game_play( string correct_answer[20], string file_name, int * & heal, int size, string * & report, int & arraysize, int & index )
{
    string answer;   // To store the anser of the user
    string line;    // To allowing lines from the file to be read

    int count = 0;                          //To keep track of questions and suggesting and comparing answers accordingly
    double correct = 0;                    // To keep track of correct answered questions

    ifstream read( file_name.c_str() );   //Opens the respecrive file

    // CHecking error in the file
    if ( read.fail() )
    {
        cout << "Error Opening the file.. OOP :(" << endl;
        exit(1);
    }

    // A loop that reads the complete file
    // From this respective file, Questions are selected
    while ( !read.eof() )
    {
        getline( read, line );
        while ( line != "**")   // "**" suggests one question is done in the file
        {
            cout << line << endl;
	        getline( read, line );
        }

        cin >> answer;     // taking answers from the user


        //converting answer into uppercase to counter check with actual answers
        answer = to_upper( answer );


        // To check if the answer is correct or not
        if ( answer == correct_answer[count])
        {
            cout << " Yipeee!! Answer is Correct\n";   // Correct Answer increases score and correct count
            game_status.score++; 
            correct++;              
        }
        else
        {
            cout << "Wrong Answer!\n";
            cout << "Correct Answer was " << correct_answer[count] << endl;  // Wrong Answer decreases health 
            game_status.health = game_status.health - 2;
            
        }

        count++;    // Increasing the count so that next question is asked

        // Updating the scores in status.txt
        data_storing( game_status.health, game_status.heals_left, game_status.score );
        show_status();  // showing current status
        gflag = barrier2();  // Asking if person wants to quit or to play... if flag becomes true quit the game

        // Considering when to quit the game
        // Game is quited when health is less than 0 or player has pressed q
        if ( gflag == true || game_status.health <= 0 )
        {
            // When no health is left
            if ( game_status.health <= 0 )
            {
                cout << " You have no health left :( Sorry You can't play more\n";
                data_storing( game_status.health, game_status.heals_left, game_status.score );  //updating status
                topic_report( file_name, count, correct );  // generating end of the topic report

                //checking if the array size is need to be increased or not
                if ( index >= arraysize )
                {
                    grow_array( report, arraysize );  // Increasing the array size
                }

                string percent = percentage_calculator( count, correct );  // to get percentage for final report
                report[index] = percent;  // Updating the report array with new score
                index++;
            }

            data_storing( game_status.health, game_status.heals_left, game_status.score );  //updating status
            topic_report( file_name, count, correct );  // generating end of the topic report

            //checking if the array size is need to be increased or not
            if ( index >= arraysize )
            {
                grow_array( report, arraysize );
            }

            string percent = percentage_calculator( count, correct );  // to get percentage for final report
            report[index] = percent;
            index++;
            return;   // It returns to the choosing of the topic function
        }

        //asking for heals
        if ( game_status.heals_left != 0 )   // If heals left are not zero
        {
            ghealing = healer();   // Calling the function and letting it know that whether to deduct points or not

            if ( ghealing == true )   // Meaning healing is used by the user
            {
                game_status.heals_left = game_status.heals_left - 1;   //decreasing used heals
                data_storing( game_status.health, game_status.heals_left, game_status.score );  //updating status

                //checking if guess is matched or not
                gdice_guess = random_guess();

                // if guess is true
                if ( gdice_guess ==  true )
                {
                    cout << "Your Guess is right! Yipee! You get 10 health points!!\n";  // If Guess matches  10 health points increase
                    game_status.health += 10;
                }
                else
                {
                    cout << " Your Guess is wrong :( Better Luck Next Time!\n";
                    gchecker = heal_deduction_checker( heal, size );  //checking whether to deduct points for healing or not
                                                                       // Helath is not deducted for the first two times
                    if ( gchecker == true )
                     {
                        cout << size * 1 << "health points are decreased from your health\n";  // Deducting points at the wrong guess
                        game_status.health = game_status.health - (size * 1); 
                    }
                }

                data_storing( game_status.health, game_status.heals_left, game_status.score );  //updating status
                show_status();  // showing current status
            }
        }

        // When questions are finished
        if ( count == 20 )
        {
            topic_report( file_name, count, correct );  // generating end of the topic report
            string percent = percentage_calculator( count, correct );  // to get percentage for final report

            //checking if the array size is need to be increased or not
            if ( index >= arraysize )
            {
                grow_array( report, arraysize );
            }

            report[index] = percent;
            index++;
            break; // breaking the loop
        }
    }

    read.close();   // clsoing the file in the end

}

//----------------------------------------------------------------------------------------------------------------


// The websites from where the questions are taken
//https://mcqlearn.com/chemistry/g9/periodicity-and-properties-mcqs.php
//https://mcqlearn.com/chemistry/g9/metals-mcqs.php
//https://www.learninsta.com/mcq-questions-for-class-11-chemistry-chapter-3/
//http://www.geekmcq.com/chemistry/periodic-classification-of-elements-and-periodicity/
//This function gives questions to the player from the respective files according to his choice 
// of difficulty level of the topic 'Periodicity'
// It takes choice as an argument to know what difficulty level a person wants, heal array to know about healing and size of the dynamic array
void periodicity ( int choice, int * & heal, int size, string * & report, int & arraysize, int & index )
{

    // Choice for easy level
    if ( choice == 1 )
    {
        //checking if the array size is need to be increased or not
        if ( index >= arraysize )
        {
            grow_array( report, arraysize );
        }

        report[index] = "Easy";
        index++;
        // An array containing correct answers
        string correct_answer[20] = { "C", "B", "IONIZATION-ENERGY", "B", "INCREASES", "B", "NOBLE-METALS", "C", "B", "A", "C", "33", "B", "B", "A", "A", "C", "IODINE", "D", "D" } ;
        string file_name = "periodicity_easy.txt";  // File name
        game_play( correct_answer, file_name, heal, size, report, arraysize, index );   // Playing the game

    }
    // Choice for medium level
    else if ( choice == 2 )
    {
        //checking if the array size is need to be increased or not
        if ( index >= arraysize )
        {
            grow_array( report, arraysize );
        }

        report[index] = "Medium";
        index++;
        // An array containing correct answers
        string correct_answer[20] = {"INCREASES", "D", "C", "B", "C", "18", "B", "B", "D", "C", "A", "2", "D", "6", "C", "D", "ACIDIC", "C", "B", "B"} ;
        string file_name = "periodicity_medium.txt";  //File that contains questions
        game_play( correct_answer, file_name, heal, size, report, arraysize, index );   // Playing the game

    }
    // choice for hard level
    else if ( choice == 3 )
    {
        //checking if the array size is need to be increased or not
        if ( index >= arraysize )
        {
            grow_array( report, arraysize );
        }

        report[index] = "Hard";
        index++;
        // An array containing the correct answers
        string correct_answer[20] = {"C", "DECREASES", "A", "C", "A", "C", "B", "B", "4", "D", "C", "ISOTOPES", "C", "B", "A", "B", "C", "ENDOTHERMIC", "A", "C"} ;
        string file_name = "periodicity_hard.txt";  //File name that contains questions
        game_play( correct_answer, file_name, heal, size, report, arraysize, index );   // Playing the game
 
     }
}


// Questions are taken from the followinhg websites
//https://mcqlearn.com/grade9/chemistry/electrochemistry-multiple-choice-questions-answers.php?page=4
//https://www.chem.tamu.edu/class/fyp/mcquest/ch21.html
// https://www.learncbse.in/chemistry-mcqs-for-class-12-with-answers-chapter-3/
// http://www.geekmcq.com/chemistry/electrochemistry/
//This function gives questions to the player from the respective files according to his choice 
// of difficulty level of the topic 'Electrochemistry'
// It takes choice as an argument to know what difficulty level a person wants, heal array to know about healing and size of the dynamic array
void electrochemistry( int choice, int * & heal, int size, string * & report, int & arraysize, int & index )
{
    // choice for easy level
    if ( choice == 1 )
    {
        //checking if the array size is need to be increased or not
        if ( index >= arraysize )
        {
            grow_array( report, arraysize );
        }

        report[index] = "Easy";
        index++;
        //An array cobtaining correct answers
        string correct_answer[20] = {"REDUCTION", "B", "D", "B", "C", "OXIDATION", "B", "OXIDIZED", "GRAPHITE", "B", "A", "C", "B", "D", "CHEMICAL-ENERGY", "A", "ELECTROPLATING", "C", "A", "0"} ;
        string file_name = "electrochemistry_easy.txt"; //File name having the quetsions
        game_play( correct_answer, file_name, heal, size, report, arraysize, index );   // Playing the game

    }
    // choice for medium level
    else if (choice == 2 )
    {
        //checking if the array size is need to be increased or not
        if ( index >= arraysize )
        {
            grow_array( report, arraysize );
        }

        report[index] = "Medium";
        index++;
        // An array containing the correct answers
        string correct_answer[20] = {"C", "ZINC", "D", "A", "OXIDIZED", "HYDROLYSIS", "A", "A", "B", "C", "OXIDATION", "B", "C", "D", "B", "D", "C", "C", "D", "C"} ;
        string file_name = "electrochemistry_medium.txt";  //file name containing the questions
        game_play( correct_answer, file_name, heal, size, report, arraysize, index );   // Playing the game

    }
    //choice for hard level
    else if ( choice == 3 )
    {
        //checking if the array size is need to be increased or not
        if ( index >= arraysize )
        {
            grow_array( report, arraysize );
        }

        report[index] = "Hard";
        index++;
        //An array having the correct answers
        string correct_answer[20] = {"D", "E", "A", "E", "2.7", "A", "D", "5.4", "D", "C", "B", "C", "B", "C", "C", "D", "E", "B", "C", "C"} ;
        string file_name = "electrochemistry_hard.txt";  //file name containing the questions
        game_play( correct_answer, file_name, heal, size, report, arraysize, index );   // Playing the game

    }
}


// Questions taken from following websites
//https://www.mcqspk.com/thermochemistry-mcqs/3/
//https://www.chem.tamu.edu/class/fyp/mcquest/ch15.html
//https://www.neetprep.com/questions/54-Chemistry/650-Thermodynamics
//This function gives questions to the player from the respective files according to his choice 
// of difficulty level of the topic 'Therochemistry'
// It takes choice as an argument to know what difficulty level a person wants, heal array to know about healing and size of the dynamic array
void thermochemistry( int choice, int * & heal, int size, string * & report, int & arraysize, int & index )
{
    // choice for easy level
    if ( choice == 1 )
    {
        //checking if the array size is need to be increased or not
        if ( index >= arraysize )
        {
            grow_array( report, arraysize );
        }

        report[index] = "Easy";
        index++;
        //An array containing the correct answers
        string correct_answer[20] = {"D", "A", "D", "B", "D", "THERMOCHEMISTRY", "C", "J", "C", "A", "B", "EXOTHERMIC", "A", "B", "D", "D", "D", "GLASS-CALORIMETER", "B", "D"} ;
        string file_name = "thermochemistry_easy.txt";  // file having the questions
        game_play( correct_answer, file_name, heal, size, report, arraysize, index );  // Playing the game

    //choice for medium level 
    }
    else if (choice == 2 )
    {
        //checking if the array size is need to be increased or not
        if ( index >= arraysize )
        {
            grow_array( report, arraysize );
        }

        report[index] = "Medium";
        index++;
        //An array containing the correct answers
        string correct_answer[20] = {"STATE-FUNCTIONS", "A", "A", "A", "C", "B", "C", "B", "A", "D", "D", "D", "C", "B", "A", "C", "GIBBS-ENERGY", "A", "D", "A"} ;
        string file_name = "thermochemistry_medium.txt"; //file having the questions
        game_play( correct_answer, file_name, heal, size, report, arraysize, index );  //playing the game

    }
    // choice for hard level
    else if ( choice == 3 )
    {
        //checking if the array size is need to be increased or not
        if ( index >= arraysize )
        {
            grow_array( report, arraysize );
        }
        
        report[index] = "Hard";
        index++;
        // An array containing the correct answers
        string correct_answer[20] = {"E", "A", "+30.0", "C", "E", "D", "B", "D", "A", "-581.0", "C", "A", "A", "A", "E", "-140.0", "C", "A", "D", "D"} ;
        string file_name = "thermochemistry_hard.txt"; //file containing the questions
        game_play( correct_answer, file_name, heal, size, report, arraysize, index );   // Playing the game
    }

}

//----------------------------------------------------------------------------------------------------------------

// this function allows you to select the topics you want to practice and test
void chemistry_topics( int choice, int * &heal, int size, string * & report, int & arraysize, int & index )
 {
    int  difficulty_level;   // To aid in choosing easy, medium, hard
    string level_selection = "What difficulty level you want?\n->Press 1 for Easy\n->Press 2 for Medium\n->Press 3 for Hard\n";
    typewriter( level_selection, 150000 );
    cin >> difficulty_level;

    // Checking if the key enetered is right or not
    while ( difficulty_level != 1 && difficulty_level != 2 && difficulty_level != 3 )
    {
        cout << "You entered the wrong key!\n";
        typewriter( level_selection, 150000 );
        cin.ignore();  //clearing the input stream
        cin >> difficulty_level;   //asking for choice again
    }


    // choice for choosing electrochemistry
    if ( choice == 1 )
    {
        //checking if the array size is need to be increased or not
        if ( index >= arraysize )
        {
            grow_array( report, arraysize );
        }

        report[index] = "Electro-Chemistry";
        index++;
        electrochemistry( difficulty_level, heal, size, report, arraysize, index );

        if ( gflag == true )  //true flag informs to quit the game and tellls to get out of this function
        {
            return;
        }
    }
    // choice for choosing periodicity
    else if ( choice == 2 )
    {
        //checking if the array size is need to be increased or not
        if ( index >= arraysize )
        {
            grow_array( report, arraysize );
        }

        report[index] = "Periodicity";
        index++;        
        periodicity( difficulty_level, heal, size, report, arraysize, index );

        if ( gflag == true )  //true flag informs to quit the game
        {
            return;
        }
    }
    // choice for choosing thermochemistry
    else if ( choice == 3 )
    {
        //checking if the array size is need to be increased or not
        if ( index >= arraysize )
        {
            grow_array( report, arraysize );
        }

        report[index] = "Thermo-Chemistry";
        index++;
        thermochemistry( difficulty_level, heal, size, report, arraysize, index );

        if ( gflag == true )  //true flag informs to quit the game
        {
            return;
        }
    }
}


//----------------------------------------------------------------------------------------------------------------

// A function that returns percentage score in the form of string
string percentage_calculator( int count, double correct )
{
    cout << showpoint << fixed << setprecision(2);   //Fixing the percision of show
    double percentage = ( correct / count ) * 100.00 ;  //calculating the percentage 
    string percent = to_string( percentage );   //converting percentage into string
    return percent;
}


//This will print the end of the topic score report
void topic_report( string filename,  int count, double correct )
{
    system( "clear" );
    cout << showpoint << fixed << setprecision(2);  //Setting up the precision
    show_status();   // This will show the player name, health, heals, and score
    double percentage = ( correct / count ) * 100.00 ;  //calculating the percentage
    cout << "Your Score in " << filename << " is " << percentage << "%" << endl;

    // adding comments with respect to score
    if ( percentage < 50.0 )
    {
        cout << "Practice and revise more next time!\n\n";
    }
    else if ( percentage < 70.0 && percentage > 50.0 )
    {
        cout << "Score could be improved! \n\n";
    }
    else if ( percentage < 80.0 && percentage > 70.0 )
    {
        cout << "Score could be improved! \n\n";
    }
    else if ( percentage > 80.0 )
    {
        cout << "Wow Champ!\n\n";
    }    

}

// This wil print the final report of the player
void final_report( string * & report, int index )
{
    cout << setfill('*');  // filling the mepty white spaces with *
    cout << setw(30) << gplayer_name << setw(30) << "*" << endl; 
    cout << setw(30) << "Final Report" << setw(30) << "*" << endl;
    cout << endl; 
    cout << setfill(' ');

    //printing scores
    for ( int i = 0; i < index; i += 3)
    {
        cout << setw(20) << report[i] << setw(10) << "|" << setw(10) << report[i + 1] << setw(10) << "|" << setw(5) << report[i + 2] << endl;
    }

    cout << endl << endl;
}

//----------------------------------------------------------------------------------------------------------------


// This is the main function
int main()
{
    gplayer_name = introduction();   // Stores the player name

    //creating dynamic memory to store the number of times healing can be done
    string Dynamic_memory = "How many times you want an opportunity to heal! ( Choose between 3 - 8 times )\n";
    int size; //getting size of the heal array

    typewriter( Dynamic_memory, 150000 );
    cin >> size;
    int * heal = new int [size];   //creating dynamic memory
    

    //making all the array false so that it is clear that healing is not yet used! When healing
    // will be used, the false be turned to true
    for ( int i = 0; i < size; i++ )
    {
        heal[i] = false;
    }


    data_storing(50,size,0);  //storing initial data of the player

//--------------------------------------------------------------------------------------------
    //Creating Dynamic array for report production
    int report_index_counter = 0;  // to keep track of where to add what things
    string * report = NULL;
    int arraysize = 3;  //initial arraysize
    report = new string [arraysize];
//------------------------------------------------------------------


    //Selecting topic related to chemistry
    int topic;
    string topic_selection = "What topics you want to practice and test!\n->Press 1 for Electro-Chemistry\n->Press 2 for Periodicity\n";
    string topic_selection2 = "->Press 3 for Thermo-Chemistry\n";
    string continue_game = "Do want to play again? (Y/N)\n";
    string continue_answer;

    // adding a do while loop for asking game and continuing it
    do
    {
        typewriter( topic_selection, 150000 );
        typewriter( topic_selection2, 150000 );
        cin >> topic;

        // Checking if the key enetered is right or not
        while ( topic != 1 && topic != 2 && topic != 3 )
        {
            cout << "You entered the wrong key!\n";
            typewriter( topic_selection, 150000 );
            typewriter( topic_selection2, 150000 );
            cin.ignore();  //clearing the input stream
            cin >> topic;
        }

        chemistry_topics( topic, heal, size, report, arraysize, report_index_counter );   // sending heal array as well to keep track of healings
        // checking flag for quit signal
        if ( gflag == true )
        {
            break;  // break the loop
        }

        typewriter( continue_game, 150000 );
        cin.ignore();  //clearing the input stream
        cin >> continue_answer;

        // Checking if the key enetered is right or not
        while ( continue_answer != "y" && continue_answer != "y" && continue_answer != "n" && continue_answer != "N" )
        {
            cout << "You entered the wrong key!\n";
            typewriter( continue_game, 150000 );
            cin.ignore();  //clearing the input stream
            cin >> continue_answer;
        }

    }while ( continue_answer == "Y" || continue_answer == "y");



    if ( gflag == true || game_status.health <= 0 || continue_answer == "N" || continue_answer == "n" )  //true flag informs to quit the game
    {
        
        string end = "Bye Bye! I hope you enjoyed the game!\n\n";
        //report card generator
        final_report( report, report_index_counter );


        typewriter( end, 150000 );
        delete[] heal;  // to avoide memory leak
        delete[] report;
        return 0;
    }
    
   
    delete[] heal;  // to avoide memory leak
    delete[] report;
    return 0;
}
