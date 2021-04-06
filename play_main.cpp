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
#include "func2.h"

using namespace std;


void typewriter( string, int );
string toUpper( string str );
bool barrier2();
bool healer();

string player_name;
bool flag = false, healing, dice_guess = false, checker;    //added to detrmine whether to quit the game or not



//creating a struct to store various data of the game
//name will store the name of the player, his health, his heals_left, and his score
struct data{
    string name;
    int health, heals_left, score;
};


struct data game_status;   //making game_status a global variable to be used in the whole program


// will decide whether to deduct health for using healing or not
//returns true if health needs to be deducted
bool heal_deduction_checker( int * & heal, int size)
{
    int num = -1;
    for ( int i = 0; i < size; i++ )
    {
        if ( heal[i] == false )
        {
            heal[i] = true;
            num = i;
            break;
        }
    }

    if ( num < 2 )
    {
        return false;
    }
    else
    {
        return true;
    }
}

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

//https://mcqlearn.com/chemistry/g9/periodicity-and-properties-mcqs.php
//https://mcqlearn.com/chemistry/g9/metals-mcqs.php
//https://www.learninsta.com/mcq-questions-for-class-11-chemistry-chapter-3/
//http://www.geekmcq.com/chemistry/periodic-classification-of-elements-and-periodicity/
//converting electro-chemistry to periodicity and metals
void periodicity ( int choice, int * & heal, int size )
{
    string line;
    string answer;
    if (choice == 1 )
    {
        string correct_answer[20] = {"C", "B", "IONIZATION-ENERGY", "B", "INCREASES", "B", "NOBLE-METALS", "C", "B", "A", "C", "33", "B", "B", "A", "A", "C", "IODINE", "D", "D"} ;
        int count = 0; //To keep track of questions
        ifstream read( "periodicity_easy.txt");

        if ( read.fail() )
        {
            cout << "Error Opening the file.. OOP :(" << endl;
            exit(1);
        }

        while ( !read.eof() )
        {
            getline( read, line );
            while ( line != "**")
            {
                cout << line << endl;
		        getline( read, line );
            }

            cin >> answer;


            //converting into uppercase
            answer = toUpper( answer );

            //checking correctness of the asnwer

            if ( answer == correct_answer[count])
            {
                game_status.score++;                
            }
            else
            {
                cout << "Wrong Answer!\n";
                cout << "Correct Answer was " << correct_answer[count] << endl;
                game_status.health = game_status.health - 2;
            }
            count++;
            data_storing( game_status.health, game_status.heals_left, game_status.score );
            flag = barrier2();  // if flag becomes true quit the game
            if (flag == true || game_status.health <= 0 )
            {
                return;
            }
            //asking for heals
            if ( game_status.heals_left != 0 )
            {
                healing = healer();
                if ( healing == true )
                {
                    game_status.heals_left = game_status.heals_left - 1;   //decreasing used heals
                    //checking if guess is matched or not
                    dice_guess = random_guess();
                    // if guess is true
                    if ( dice_guess ==  true )
                    {
                        game_status.health += 10;
                    }
                    else
                    {
                        checker = heal_deduction_checker( heal, size );  //checking whether to deduct points for healing or not
                        if ( checker == true )
                        {
                            game_status.health = game_status.health - (size * 1);
                        }
                    }
                }
            }

	        if ( count == 20 )
	        {
	            break; // breaking the loop
            }
        }

	read.close();
    }
    else if (choice == 2)
    {
        string correct_answer[20] = {"INCREASES", "D", "C", "B", "C", "18", "B", "B", "D", "C", "A", "2", "D", "6", "C", "D", "ACIDIC", "C", "B", "B"} ;
        int count = 0; //To keep tract of questions
        ifstream read( "periodicity_medium.txt");

        if ( read.fail() )
        {
            cout << "Error Opening the file.. OOP :(" << endl;
            exit(1);
        }

        while ( !read.eof() )
        {
            getline( read, line );
            while ( line != "**")
            {
                cout << line << endl;
		        getline( read, line );
            }
            cin >> answer;

            //converting into uppercase
            answer = toUpper( answer );

            //checking correctness of the asnwer

            if ( answer == correct_answer[count])
            {
                game_status.score++;                
            }
            else
            {
                cout << "Wrong Answer!\n";
                cout << "Correct Answer was " << correct_answer[count] << endl;
                game_status.health = game_status.health - 2;
            }
            count++;
            data_storing( game_status.health, game_status.heals_left, game_status.score );
            flag = barrier2();  // if flag becomes true quit the game

            if (flag == true || game_status.health <= 0 )
            {
                return;
            }
            //asking for heals
            if ( game_status.heals_left != 0 )
            {
                healing = healer();
                if ( healing == true )
                {
                    game_status.heals_left = game_status.heals_left - 1;   //decreasing used heals
                    //checking if guess is matched or not
                    dice_guess = random_guess();
                    // if guess is true
                    if ( dice_guess ==  true )
                    {
                        game_status.health += 10;
                    }
                    else
                    {
                        checker = heal_deduction_checker( heal, size );  //checking whether to deduct points for healing or not
                        if ( checker == true )
                        {
                            game_status.health = game_status.health - (size * 1);
                        }
                    }
                }
            }

            if ( count == 20 )
            {
                break; // breaking the loop
            }
        }

	read.close();

    }
    else if ( choice == 3)
    {
        string correct_answer[20] = {"C", "DECREASES", "A", "C", "A", "C", "B", "B", "4", "D", "C", "ISOTOPES", "C", "B", "A", "B", "C", "ENDOTHERMIC", "A", "C"} ;
        int count = 0; //To keep tract of questions
        ifstream read( "periodicity_hard.txt");

        if ( read.fail() )
        {
            cout << "Error Opening the file.. OOP :(" << endl;
            exit(1);
        }

        while ( !read.eof() )
        {
            getline( read, line );
            while ( line != "**")
            {
                cout << line << endl;
		        getline( read, line );
            }
            cin >> answer;

            //converting into uppercase
            answer = toUpper( answer );

            //checking correctness of the asnwer

            if ( answer == correct_answer[count])
            {
                game_status.score++;                
            }
            else
            {
                cout << "Wrong Answer!\n";
                cout << "Correct Answer was " << correct_answer[count] << endl;
                game_status.health = game_status.health - 2;
            }
            count++;
            data_storing( game_status.health, game_status.heals_left, game_status.score );
            flag = barrier2();  // if flag becomes true quit the game

            if (flag == true || game_status.health <= 0 )
            {
                return;
            }
            //asking for heals
            if ( game_status.heals_left != 0 )
            {
                healing = healer();
                if ( healing == true )
                {
                    game_status.heals_left = game_status.heals_left - 1;   //decreasing used heals
                    //checking if guess is matched or not
                    dice_guess = random_guess();
                    // if guess is true
                    if ( dice_guess ==  true )
                    {
                        game_status.health += 10;
                    }
                    else
                    {
                        checker = heal_deduction_checker( heal, size );  //checking whether to deduct points for healing or not
                        if ( checker == true )
                        {
                            game_status.health = game_status.health - (size * 1);
                        }
                    }
                }
            }

            if ( count == 20 )
            {
                break; // breaking the loop
            }
        }

	read.close();


    }
}


//https://mcqlearn.com/grade9/chemistry/electrochemistry-multiple-choice-questions-answers.php?page=4
//https://www.chem.tamu.edu/class/fyp/mcquest/ch21.html
// https://www.learncbse.in/chemistry-mcqs-for-class-12-with-answers-chapter-3/
// http://www.geekmcq.com/chemistry/electrochemistry/
void electrochemistry( int choice, int * & heal, int size)
{
    string line;
    string answer;
    if (choice == 1 )
    {
        string correct_answer[20] = {"REDUCTION", "B", "D", "B", "C", "OXIDATION", "B", "OXIDIZED", "GRAPHITE", "B", "A", "C", "B", "D", "CHEMICAL-ENERGY", "A", "ELECTROPLATING", "C", "A", "0"} ;
        int count = 0; //To keep tract of questions
        ifstream read( "electrochemistry_easy.txt");

        if ( read.fail() )
        {
            cout << "Error Opening the file.. OOP :(" << endl;
            exit(1);
        }

        while ( !read.eof() )
        {
            getline( read, line );
            while ( line != "**")
            {
                cout << line << endl;
		        getline( read, line );
            }
            cin >> answer;

            //converting into uppercase
            answer = toUpper( answer );

            //checking correctness of the asnwer

            if ( answer == correct_answer[count])
            {
                game_status.score++;                
            }
            else
            {
                cout << "Wrong Answer!\n";
                cout << "Correct Answer was " << correct_answer[count] << endl;
                game_status.health = game_status.health - 2;
            }
            count++;
            data_storing( game_status.health, game_status.heals_left, game_status.score );
            flag = barrier2();  // if flag becomes true quit the game
            if (flag == true )
            {
                return;
            }
            if ( count == 20 )
            {
                break; // breaking the loop
            }
        }

	read.close();
    }
    else if (choice == 2)
    {
        string correct_answer[20] = {"C", "ZINC", "D", "A", "OXIDIZED", "HYDROLYSIS", "A", "A", "B", "C", "OXIDATION", "B", "C", "D", "B", "D", "C", "C", "D", "C"} ;
        int count = 0; //To keep tract of questions
        ifstream read( "electrochemistry_medium.txt");

        if ( read.fail() )
        {
            cout << "Error Opening the file.. OOP :(" << endl;
            exit(1);
        }

        while ( !read.eof() )
        {
            getline( read, line );
            while ( line != "**")
            {
                cout << line << endl;
		        getline( read, line );
            }
            cin >> answer;

            //converting into uppercase
            answer = toUpper( answer );

            //checking correctness of the asnwer

            if ( answer == correct_answer[count])
            {
                game_status.score++;                
            }
            else
            {
                cout << "Wrong Answer!\n";
                cout << "Correct Answer was " << correct_answer[count] << endl;
                game_status.health = game_status.health - 2;
            }
            count++;
            data_storing( game_status.health, game_status.heals_left, game_status.score );
            flag = barrier2();  // if flag becomes true quit the game

            if (flag == true || game_status.health <= 0 )
            {
                return;
            }
            //asking for heals
            if ( game_status.heals_left != 0 )
            {
                healing = healer();
                if ( healing == true )
                {
                    game_status.heals_left = game_status.heals_left - 1;   //decreasing used heals
                    //checking if guess is matched or not
                    dice_guess = random_guess();
                    // if guess is true
                    if ( dice_guess ==  true )
                    {
                        game_status.health += 10;
                    }
                    else
                    {
                        checker = heal_deduction_checker( heal, size );  //checking whether to deduct points for healing or not
                        if ( checker == true )
                        {
                            game_status.health = game_status.health - (size * 1);
                        }
                    }
                }
            }

            if ( count == 20 )
            {
                break; // breaking the loop
            }
        }

	read.close();

    }
    else if ( choice == 3)
    {
        string correct_answer[20] = {"D", "E", "A", "E", "2.7", "A", "D", "5.4", "D", "C", "B", "C", "B", "C", "C", "D", "E", "B", "C", "C"} ;
        int count = 0; //To keep tract of questions
        ifstream read( "electrochemistry_hard.txt");

        if ( read.fail() )
        {
            cout << "Error Opening the file.. OOP :(" << endl;
            exit(1);
        }

        while ( !read.eof() )
        {
            getline( read, line );
            while ( line != "**")
            {
                cout << line << endl;
		        getline( read, line );
            }
            cin >> answer;

            //converting into uppercase
            answer = toUpper( answer );

            //checking correctness of the asnwer

            if ( answer == correct_answer[count])
            {
                game_status.score++;                
            }
            else
            {
                cout << "Wrong Answer!\n";
                cout << "Correct Answer was " << correct_answer[count] << endl;
                game_status.health = game_status.health - 2;
            }
            count++;
            data_storing( game_status.health, game_status.heals_left, game_status.score );
            flag = barrier2();  // if flag becomes true quit the game

             if (flag == true || game_status.health <= 0 )
            {
                return;
            }
            //asking for heals
            if ( game_status.heals_left != 0 )
            {
                healing = healer();
                if ( healing == true )
                {
                    game_status.heals_left = game_status.heals_left - 1;   //decreasing used heals
                    //checking if guess is matched or not
                    dice_guess = random_guess();
                    // if guess is true
                    if ( dice_guess ==  true )
                    {
                        game_status.health += 10;
                    }
                    else
                    {
                        checker = heal_deduction_checker( heal, size );  //checking whether to deduct points for healing or not
                        if ( checker == true )
                        {
                            game_status.health = game_status.health - (size * 1);
                        }
                    }
                }
            }

            if ( count == 20 )
            {
                break; // breaking the loop
            }
        }

	read.close();


    }
}


void thermochemistry( int choice, int * & heal, int size)
{
    string line;
    string answer;
    if (choice == 1 )
    {
        string correct_answer[20] = {"D", "A", "D", "B", "D", "THERMOCHEMISTRY", "C", "J", "C", "A", "B", "EXOTHERMIC", "A", "B", "D", "D", "D", "GLASS-CALORIMETER", "B", "D"} ;
        int count = 0; //To keep tract of questions
        ifstream read( "thermochemistry_easy.txt");

        if ( read.fail() )
        {
            cout << "Error Opening the file.. OOP :(" << endl;
            exit(1);
        }

        while ( !read.eof() )
        {
            getline( read, line );
            while ( line != "**")
            {
                cout << line << endl;
		        getline( read, line );
            }
            cin >> answer;

            //converting into uppercase
            answer = toUpper( answer );

            //checking correctness of the asnwer

            if ( answer == correct_answer[count])
            {
                game_status.score++;                
            }
            else
            {
                cout << "Wrong Answer!\n";
                cout << "Correct Answer was " << correct_answer[count] << endl;
                game_status.health = game_status.health - 2;
            }
            count++;
            data_storing( game_status.health, game_status.heals_left, game_status.score );
            flag = barrier2();  // if flag becomes true quit the game

            if (flag == true || game_status.health <= 0 )
            {
                return;
            }
            //asking for heals
            if ( game_status.heals_left != 0 )
            {
                healing = healer();
                if ( healing == true )
                {
                    game_status.heals_left = game_status.heals_left - 1;   //decreasing used heals
                    //checking if guess is matched or not
                    dice_guess = random_guess();
                    // if guess is true
                    if ( dice_guess ==  true )
                    {
                        game_status.health += 10;
                    }
                    else
                    {
                        checker = heal_deduction_checker( heal, size );  //checking whether to deduct points for healing or not
                        if ( checker == true )
                        {
                            game_status.health = game_status.health - (size * 1);
                        }
                    }
                }
            }

            if ( count == 20 )
            {
                break; // breaking the loop
            }
        }

	read.close();
    }
    else if (choice == 2)
    {
        string correct_answer[20] = {"STATE-FUNCTIONS", "A", "A", "A", "C", "B", "C", "B", "A", "D", "D", "D", "C", "B", "A", "C", "GIBBS-ENERGY", "A", "D", "A"} ;
        int count = 0; //To keep tract of questions
        ifstream read( "thermochemistry_medium.txt");

        if ( read.fail() )
        {
            cout << "Error Opening the file.. OOP :(" << endl;
            exit(1);
        }

        while ( !read.eof() )
        {
            getline( read, line );
            while ( line != "**")
            {
                cout << line << endl;
		        getline( read, line );
            }
            cin >> answer;

            //converting into uppercase
            answer = toUpper( answer );

            //checking correctness of the asnwer

            if ( answer == correct_answer[count])
            {
                game_status.score++;                
            }
            else
            {
                cout << "Wrong Answer!\n";
                cout << "Correct Answer was " << correct_answer[count] << endl;
                game_status.health = game_status.health - 2;
            }
            count++;
            data_storing( game_status.health, game_status.heals_left, game_status.score );
            flag = barrier2();  // if flag becomes true quit the game

            if (flag == true || game_status.health <= 0 )
            {
                return;
            }
            //asking for heals
            if ( game_status.heals_left != 0 )
            {
                healing = healer();
                if ( healing == true )
                {
                    game_status.heals_left = game_status.heals_left - 1;   //decreasing used heals
                    //checking if guess is matched or not
                    dice_guess = random_guess();
                    // if guess is true
                    if ( dice_guess ==  true )
                    {
                        game_status.health += 10;
                    }
                    else
                    {
                        checker = heal_deduction_checker( heal, size );  //checking whether to deduct points for healing or not
                        if ( checker == true )
                        {
                            game_status.health = game_status.health - (size * 1);
                        }
                    }
                }
            }

            if ( count == 20 )
            {
                break; // breaking the loop
            }
        }

	read.close();

    }
    else if ( choice == 3)
    {
        string correct_answer[20] = {"E", "A", "+30.0", "C", "E", "D", "B", "D", "A", "-581.0", "C", "A", "A", "A", "E", "-140.0", "C", "A", "D", "D"} ;
        int count = 0; //To keep tract of questions
        ifstream read( "thermochemistry_hard.txt");

        if ( read.fail() )
        {
            cout << "Error Opening the file.. OOP :(" << endl;
            exit(1);
        }

        while ( !read.eof() )
        {
            getline( read, line );
            while ( line != "**")
            {
                cout << line << endl;
		        getline( read, line );
            }
            cin >> answer;

            //converting into uppercase
            answer = toUpper( answer );

            //checking correctness of the asnwer

            if ( answer == correct_answer[count])
            {
                game_status.score++;                
            }
            else
            {
                cout << "Wrong Answer!\n";
                cout << "Correct Answer was " << correct_answer[count] << endl;
                game_status.health = game_status.health - 2;
            }
            count++;
            data_storing( game_status.health, game_status.heals_left, game_status.score );
            flag = barrier2();  // if flag becomes true quit the game

            if (flag == true || game_status.health <= 0 )
            {
                return;
            }
            //asking for heals
            if ( game_status.heals_left != 0 )
            {
                healing = healer();
                if ( healing == true )
                {
                    game_status.heals_left = game_status.heals_left - 1;   //decreasing used heals
                    //checking if guess is matched or not
                    dice_guess = random_guess();
                    // if guess is true
                    if ( dice_guess ==  true )
                    {
                        game_status.health += 10;
                    }
                    else
                    {
                        checker = heal_deduction_checker( heal, size );  //checking whether to deduct points for healing or not
                        if ( checker == true )
                        {
                            game_status.health = game_status.health - (size * 1);
                        }
                    }
                }
            }

            if ( count == 20 )
            {
                break; // breaking the loop
            }
        }

	read.close();


    }
}

// Questions taken from following websites
//https://www.mcqspk.com/thermochemistry-mcqs/3/
//https://www.chem.tamu.edu/class/fyp/mcquest/ch15.html
//https://www.neetprep.com/questions/54-Chemistry/650-Thermodynamics

void chemistry_topics( int choice, int * &heal, int size)
 {
    int  difficulty_level;
    string level_selection = "What difficulty level you want?\n->Press 1 for Easy\n->Press 2 for Medium\n-> Press 3 for Hard\n";
    typewriter(level_selection, 150000);
    cin >> difficulty_level;

    if (choice == 1 )
    {
        electrochemistry(difficulty_level, heal, size);
        if ( flag == true )  //true flag informs to quit the game
        {
            return;
        }
    }
    else if (choice == 2)
    {
        periodicity(difficulty_level, heal, size);
        if ( flag == true )  //true flag informs to quit the game
        {
            return;
        }
    }
    else if ( choice == 3)
    {
        thermochemistry(difficulty_level, heal, size);
        if ( flag == true )  //true flag informs to quit the game
        {
            return;
        }
    }
}

int main()
{
    player_name = introduction();

    //creating dynamic memory to store the number of times healing can be done
    string Dynamic_memory = "How many times you want an opportunity to heal! ( Choose between 3 - 8 times )\n";
    int size; //getting size of the heal array
    typewriter(Dynamic_memory, 150000);
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
    string topic_selection = "What topics you want to practice and test!\n->Press 1 for Electro-Chemistry\n->Press 2 for Periodicity\n";
    string topic_selection2 = "-> Press 3 for Thermo-Chemistry\n";
    string continue_game = "Do want to play again? (Y/N)\n";
    string continue_answer;

    // adding a do while loop for asking game and continuing it
    do
    {
        typewriter(topic_selection, 150000);
        typewriter(topic_selection2, 150000);
        cin >> topic;
        chemistry_topics( topic, heal, size );   // sending heal array as well to keep track of healings
        typewriter( continue_game, 150000 );
        cin >> continue_answer;
    }while ( continue_answer == "Y" || continue_answer == "y");



    if ( flag == true || game_status.health <= 0 || continue_answer == "N" || continue_answer == "n")  //true flag informs to quit the game
    {
        string end = "Bye Bye! I hope you enjoyed the game!";
        //report card generator


        typewriter(end, 150000);
        delete[] heal;  // to avoide memory leak
        return 0;
    }
    
    return 0;
    delete[] heal;  // to avoide memory leak
}
