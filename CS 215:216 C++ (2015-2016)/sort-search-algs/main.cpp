//---------------------------------------------------------------
//
// Name: Steven Anker Penava Jr
// Secttion: 004
// Professor: Yi Pike
// Date: February 14th, 2016
//
//---------------------------------------------------------------
// Assignment: Programming Project 1
// Purpose: To ask the user for a sequence of integers, and
// to then take those integers and sort them in different ways
//---------------------------------------------------------------
// File: main.cpp
//---------------------------------------------------------------

//----INCLUDE STATEMENTS-----------------------------------------
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
using namespace std;
#include "IntSequence.h"
//---------------------------------------------------------------

//---------------------------------------------------------------
// NOTE TO TA: You may notice there is no code within my member
// functions to handle an empty list. This is because, with the
// way I have my program written, the user is never able to
// enter options 2, 3, 4, or 5 on the main menu unless the size
// of the array/sequence is greater than 0.
//---------------------------------------------------------------

// Main function
int main()
{
    // Variables used in main function
    IntSequence seq1; // sequence
    int userInput; // user choice for main menu
    bool endProgram = false; // flag for ending the program
    int userNum; // user input for number to be added to sequence
    bool goodNum=true; // data validation for number input
    bool sortQuit = false; // flag for exiting sort menu
    int sortChoice; // sort choice
    int searchChoice; // search choice
    int target; // target 1
    int target2; // target 2
    int lindex=0; // left index/min
    int keyIndex; // key index for sequential search
    int bSearchValue; // key index for binary search
    
    // Welcome message
    cout << "Welcome to the Sorting Algorithm Program." << endl;
    cout << "This program was written by Steven Penava. Thanks for using it!" << endl;
    cout << endl;
    cout << "Please choose one of the following options by entering the corresponding number on your keyboard." << endl;
    cout << endl;
    seq1.printOptions();
    
    // User input for main menu
    cin >> userInput;
    
    // Input validation
    while (cin.fail() || userInput > 6 || userInput < 1)
    {
        cout << endl;
        cout << "That was either a non-integer or an integer not between 1 and 6. Try again." << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cout << "=================================================================" << endl;
        seq1.printOptions();
        cin >> userInput;
    }
    
    // While loop for whole program (so main menu repeats)
    while (!cin.fail() && userInput >= 1 && userInput <= 6)
    {
        // While loop to keep program running
        while (endProgram == false)
        {
            goodNum=true; // setting flag to true so each loop it resets
            if (userInput == 1) //--------------------------------------INSERT FUNCTION-----------------------
            {
                // While loop for input validation
                while (goodNum == true)
                {
                    cout << "Enter an INTEGER ('q' or 'Q' to quit): ";
                    cin.clear();
                    cin >> userNum;
                    if (cin.fail())
                    {
                        // Checking input with string (q or Q check)
                        string check_input;
                        cin.clear();
                        cin >> check_input;
                        if (check_input == "Q" || check_input == "q")
                        {
                            goodNum = false; // ending the loop
                            cin.clear();
                        }
                        else
                        {
                            cout << "That wasn't a number! Try again." << endl;
                            cin.clear();
                            cin.ignore(256, '\n');
                        }
                    }
                    else
                    {
                        seq1.insert(userNum); // inserting the number into the sequence
                    }
                }
                cout << "=================================================================" << endl;
                seq1.printOptions();
                cin.clear();
                cin.ignore(256, '\n');
                cin >> userInput;
                // Data validation / repeating menu again
                while (cin.fail() || userInput > 6 || userInput < 1)
                {
                    cout << "That was either a non-integer or an integer not between 1 and 6. Try again." << endl;
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "=================================================================" << endl;
                    seq1.printOptions();
                    cin >> userInput;
                }
            }
            
            if (userInput == 2) //---------------------------------------PRINT FUNCTION-----------------------
            {
                seq1.print();
                cout << "=================================================================" << endl;
                seq1.printOptions();
                
                cin.clear();
                cin.ignore(256, '\n');
                
                cin >> userInput;
                // Data validation / making menu again
                while (cin.fail() || userInput > 6 || userInput < 1)
                {
                    cout << "That was either a non-integer or an integer not between 1 and 6. Try again." << endl;
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "=================================================================" << endl;
                    seq1.printOptions();
                    cin >> userInput;
                }
            }
            
            if (userInput == 3) //----------------------------------------SORT FUNCTION-----------------------
            {
                // Checking if the sequence exists or not
                if (seq1.doesExist() == false)
                {
                    cout << endl;
                    cout << "You can't perform operations on a sequence that doesn't exist! Choose option 1 first." << endl;
                    cout << "=================================================================" << endl;
                    seq1.printOptions();
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> userInput;
                    // Data validation / making main menu again
                    while (cin.fail() || userInput < 1 || userInput > 6)
                    {
                        cout << "That was either a non-integer or an integer not between 1 and 6. Try again." << endl;
                        cin.clear();
                        cin.ignore(256, '\n');
                        cout << "=================================================================" << endl;
                        seq1.printOptions();
                        cin >> userInput;
                    }
                }
                // Check if the sequence exists or not (if it does...)
                else if (seq1.doesExist() == true)
                {
                    cout << "=================================================================" << endl;
                    seq1.printSortOp();
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> sortChoice;
                    // Data validation for sort menu
                    while (cin.fail() || sortChoice < 1 || sortChoice > 4)
                    {
                        cout << endl;
                        cout << "That was either a non-integer or an integer not between 1 and 4. Try again." << endl;
                        cin.clear();
                        cin.ignore(256, '\n');
                        cout << "=================================================================" << endl;
                        seq1.printSortOp();
                        cin >> sortChoice;
                    }
                    // Selection sort choice
                    if (sortChoice == 1)
                    {
                        cout << "===Selection Sort================================================" << endl;
                        seq1.selection_sort();
                        seq1.print();
                        
                    }
                    // Insertion sort choice
                    if (sortChoice == 2)
                    {
                        cout << "===Insertion Sort================================================" << endl;
                        seq1.insertion_sort();
                        seq1.print();
                        
                    }
                    // Bubble sort choice
                    if (sortChoice == 3)
                    {
                        cout << "===Bubble Sort===================================================" << endl;
                        seq1.bubble_sort();
                        seq1.print();
                    }
                    // Return to menu choice
                    if (sortChoice == 4)
                    {
                        cout << "=================================================================" << endl;
                        seq1.printOptions();
                        cin >> userInput;
                        // Data validation / making menu again
                        while (cin.fail() || userInput > 6 || userInput < 1)
                        {
                            cout << "That was either a non-integer or an integer not between 1 and 6. Try again." << endl;
                            cin.clear();
                            cin.ignore(256, '\n');
                            cout << "=================================================================" << endl;
                            seq1.printOptions();
                            cin >> userInput;
                        }
                    }
                }
            }
            
            if (userInput == 4) //-------------------------------------SHUFFLE FUNCTION-----------------------
            {
                // Check if the sequence exists or not
                if (seq1.doesExist() == false)
                {
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << endl;
                    cout << "You can't perform operations on a sequence that doesn't exist! Choose option 1 first." << endl;
                    cout << "=================================================================" << endl;
                    seq1.printOptions();
                    cin >> userInput;
                    // Data validation / making main menu again
                    while (cin.fail() || userInput > 6 || userInput < 1)
                    {
                        cout << endl;
                        cout << "That was either a non-integer or an integer not between 1 and 6. Try again." << endl;
                        cin.clear();
                        cin.ignore(256, '\n');
                        cout << endl;
                        cout << "=================================================================" << endl;
                        seq1.printOptions();
                        cin.clear();
                        cin >> userInput;
                    }
                }
                // Check if the sequence exists or not (if it does...)
                if (seq1.doesExist() == true)
                {
                    seq1.shuffle(); // calling shuffle
                    seq1.print();
                    cout << "=================================================================" << endl;
                    seq1.printOptions();
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> userInput;
                    // Data validation / making menu again
                    while (cin.fail() || userInput > 6 || userInput < 1)
                    {
                        cout << endl;
                        cout << "That was either a non-integer or an integer not between 1 and 6. Try again." << endl;
                        cin.clear();
                        cin.ignore(256, '\n');
                        cout << "=================================================================" << endl;
                        seq1.printOptions();
                        cin.clear();
                        cin >> userInput;
                        cout << endl;
                    }
                }
  
            }
            
            if (userInput == 5) //--------------------------------------SEARCH FUNCTION-----------------------
            {
                // Check if the sequence exists or not
                if (seq1.doesExist() == false)
                {
                    cout << endl;
                    cout << "You can't perform operations on a sequence that doesn't exist! Choose option 1 first." << endl;
                    cout << "=================================================================" << endl;
                    seq1.printOptions();
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> userInput;
                    // Data validation / making menu again
                    while (cin.fail() || userInput > 6 || userInput < 1)
                    {
                        cout << endl;
                        cout << "That was either a non-integer or an integer not between 1 and 6. Try again." << endl;
                        cin.clear();
                        cin.ignore(256, '\n');
                        cout << "=================================================================" << endl;
                        seq1.printOptions();
                        cin.clear();
                        cin >> userInput;
                    }
                }
                // Check if the sequence exists or not (if it does...)
                if (seq1.doesExist() == true)
                {
                    cout << "=================================================================" << endl;
                    seq1.printSearchOp();
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> searchChoice; // getting user's choice for search type
                    // Data validation / making menu again
                    while (cin.fail() || searchChoice > 3 || searchChoice < 1)
                    {
                        cout << endl;
                        cout << "That was either a non-integer or an integer not between 1 and 3. Try again." << endl;
                        cin.clear();
                        cin.ignore(256, '\n');
                        cout << "=================================================================" << endl;
                        seq1.printSearchOp();
                        cin >> searchChoice;
                        
                    }
                    // If the user entered one of the proper numbers...
                    if (searchChoice >=1 && searchChoice <=3)
                    {
                        // Sequential
                        if (searchChoice == 1)
                        {
                            cout << "===Sequential Search=============================================" << endl;
                            goodNum = true; // setting flag to true again
                            cout << "Enter the key to find: ";
                            cin >> target; // input key to find...
                            // Data validation
                            while (cin.fail())
                            {
                                cout << "That wasn't an integer. Enter again: ";
                                cin.clear();
                                cin.ignore(256, '\n');
                                cin >> target;
                            }
                            seq1.print();
                            keyIndex = seq1.sequential_search(target); // key index assigning
                            // If not found...
                            if (keyIndex==-1)
                            {
                                cout << "Not found." << endl;
                            }
                            // If found...
                            else
                            {
                                cout << "Key found at index "<<keyIndex<<endl;
                                cout << "Search made with "<<keyIndex+1<<" comparison(s)." << endl; // +1 for comparison #
                            }
                            cin.clear();
                        }
                        // Binary
                        if (searchChoice == 2)
                        {
                            cout << "===Binary Search=================================================" << endl;
                            goodNum = true; // setting flag to true again
                            cout << "Enter the key to find: ";
                            cin >> target2; // input target...
                            // Data validation
                            while (cin.fail())
                            {
                                cout << "That wasn't an integer. Enter again: ";
                                cin.clear();
                                cin.ignore(256, '\n');
                                cin >> target2;
                            }
                            
                            // Printing sequences (sorted/unsorted)
                            cout << setw(2) << "Unsorted ";
                            seq1.print();
                            cout << setw(2) << "Sorted   ";
                            // Calling a sort function that doesn't print the steps
                            seq1.bubble_sort_noPrint();
                            int rindex=seq1.getSize()-1;
                            bSearchValue = seq1.binary_search(target2, lindex, rindex); // key index
                            seq1.print();
                            // Doesn't exist
                            if (bSearchValue == -1)
                            {
                                cout << "Not found." << endl;
                            }
                            //Exists
                            else
                            {
                                cout << "Key found at index " << bSearchValue << endl;
                                cout << "Search found with " << seq1.getSearchCount() << " comparison(s)" << endl;
                                seq1.resetSearchCount();
                            }
                        }
                        // Quit
                        if (searchChoice == 3)
                        {
                            sortQuit = true; // flag to true - quit
                            // Making menu again
                            cout << "=================================================================" << endl;
                            seq1.printOptions();
                            cin.clear();
                            cin.ignore(256, '\n');
                            cin >> userInput;
                            // Input validation
                            while (cin.fail() || userInput > 6 || userInput < 1)
                            {
                                cout << endl;
                                cout << "That was either a non-integer or an integer not between 1 and 6. Try again." << endl;
                                cin.clear();
                                cin.ignore(256, '\n');
                                cout << "=================================================================" << endl;
                                seq1.printOptions();
                                cin.clear();
                                cin >> userInput;
                            }

                        }
                    }
                }
            }

            if (userInput == 6) //----------------------------------------QUIT FUNCTION-----------------------
            {
                endProgram = true;
            }
        }
        
        // End program
        cout << "Thanks for using my program!" << endl;
        break; // break statement to exit
    }
    return 0; // returning 0
}


