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
// File: IntSequence.cpp (source file for IntSequence header)
//---------------------------------------------------------------

//----INCLUDE STATEMENTS-----------------------------------------
#include "IntSequence.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

//---------------------------------------------------------------
// NOTE TO TA: You may notice there is no code within my member
// functions to handle an empty list. This is because, with the
// way I have my program written, the user is never able to
// enter options 2, 3, 4, or 5 on the main menu unless the size
// of the array/sequence is greater than 0.
//---------------------------------------------------------------

// create an iteger array with capacity = INITIAL_CAPACITY
IntSequence::IntSequence() // default constructor
{
    seq = new int[INITIAL_CAPACITY];
    count = 0;
    search_count=0; // initializing search count to 0
}

// create an iteger array with capacity = in_capacity
IntSequence::IntSequence(int in_capacity)
{
    seq = new int[in_capacity];
    count = 0;
    search_count=0; // initializing search count to 0
}

// output a list of options for the user
void IntSequence::printOptions()
{
    cout << "1. Read" << endl;
    cout << "2. Print" << endl;
    cout << "3. Sort" << endl;
    cout << "4. Shuffle" << endl;
    cout << "5. Search" << endl;
    cout << "6. Quit" << endl;
    cout << "Option: ";
}

// does the list exist?
bool IntSequence::doesExist()
{
    bool doesExist;
    if (count >= 1)
    {
        doesExist = true;
    }
    else{
        doesExist = false;
    }
    return doesExist;
}

// print sorting options
void IntSequence::printSortOp()
{
    cout << "1. Selection sort" << endl;
    cout << "2. Insertion sort" << endl;
    cout << "3. Bubble sort" << endl;
    cout << "4. Quit (return to main menu)" << endl;
    cout << "Option: ";
}

// print searching options
void IntSequence::printSearchOp()
{
    cout << "1. Sequential Search" << endl;
    cout << "2. Binary Search" << endl;
    cout << "3. Quit" << endl;
    cout << "Option: ";
}

// insert item into the end of the array; count increased by 1
void IntSequence::insert(int item)
{
    if (count <= capacity)
    {
        capacity = capacity + 2;
        int *copylist = new int[capacity]; // new list to copy values to
        for (int i=0; i<count; i++)
        {
            copylist[i] = seq[i];
        }
        delete seq;
        count++;
        seq = copylist;
        seq[count-1] = item;
    }
}

// display all the items in the array
void IntSequence::print()
{
    if (count==0) // handling empty sequence
    {
        cout << endl;
        cout << "The sequence is currently empty. You can't operate on an empty list." << endl;
    }
    else{
    int *newseq;
    newseq = seq;
    cout << "Sequence: ";
    for (int i=0; i<(count); i++) // for loop printing each index's value
    {
        cout << setw(2) << newseq[i] << " ";
    }
        cout << endl;}
}

// sort the sequence into non-decreasing order
// using Selection Sorting algorithm
void IntSequence::selection_sort()
{
        int min_index;
        for (int i=0; i<(count-1); i++)
        {
            min_index = i;
            for (int j=(i+1); j<(count); j++)
            {
                if (seq[j] < seq[min_index])
                {
                    min_index = j;
                }
            }
            cout << "Min: " << seq[min_index];
            cout << ", swap with " << seq[i] << ": ";
            if (min_index != i)
            {
                int tempval1 = seq[i];
                seq[i] = seq[min_index];
                seq[min_index] = tempval1;
            }
            print();
        }
}

// sort the sequence into non-decreasing order
// using Insertion Sorting algorithm
void IntSequence::insertion_sort()
{
    if (count ==0)
    {
        cout << "Sorry, the sequence is empty. Please press quit to go back." << endl;
    }
    else{
    int key;
    int position;
    for (int i=1; i<(count); i++)
    {
        key = seq[i];
        position = i;
        cout << "Insert " << key << ": ";
        while (position > 0 and seq[position-1] > key)
        {
            seq[position] = seq[position-1];
            position = position - 1;
        }
        seq[position] = key;
        print();
    }}
}

// sort the sequence into non-decreasing order
// using Bubble Sorting algorithm
void IntSequence::bubble_sort()
{
    if (count ==0)
    {
        cout << "Sorry, the sequence is empty. Please press quit to go back." << endl;
    }
    else{
    for (int i=1; i<(count); i++) // was size -1
    {
        for (int j=0; j<(count-1); j++) // was size - 2
        {
            if (seq[j] > (seq[j+1]))
            {
                int tempval = seq[j];
                seq[j] = seq[j+1];
                seq[j+1] = tempval;
            }
        }
        cout << "Iteration "<<i<<": ";
        print();
    }}
}

// bubble sort function without print statements
void IntSequence::bubble_sort_noPrint()
{
    for (int i=1; i<(count); i++)
    {
        for (int j=0; j<(count-1); j++)
        {
            if (seq[j] > (seq[j+1]))
            {
                int tempval = seq[j];
                seq[j] = seq[j+1];
                seq[j+1] = tempval;
            }
        }
    }
    
}

// shuffle the items in the sequence
// generates a random permutation of array elements
void IntSequence::shuffle()
{
    cout << "Shuffled." << endl;
    int random_int;
    int tempval2;
    for (int i=(count-1); i>=1; i--)
    {
        random_int = rand()%(i-0)+0;
        tempval2 = seq[i];
        seq[i] = seq[random_int];
        seq[random_int] = tempval2;
    }
}

// search a target key in the array:
// if found return the index number; if not found return -1
int IntSequence::sequential_search(int key)
{
    
    for (int i=0; i<(count); i++)
    {
        if (key == seq[i])
        {
            return i;
        }
    }
    return -1;
}

// get size function for the sequence
const int IntSequence::getSize()
{
    return count;
}

// get search count function to return the amount of comparisons made
const int IntSequence::getSearchCount()
{
    return search_count; // plus 1 due to implementation of search_count in binary search function
}

// reset search count function so the comparison # doesn't add up each time
void IntSequence::resetSearchCount()
{
    search_count=0;
}

// sort the array into non-decreasing order first, then
// search a target key in the array:
// if found return the index number; if not found return -1
int IntSequence::binary_search(int key, int leftindex, int rightindex)
{
    if (leftindex > rightindex)
    {
        return -1;
    }
    else
    {
        int middle = (leftindex + rightindex) / 2;
        if (seq[middle] > key)
        {
            search_count++; // adds 1 to search count
            return binary_search(key, leftindex, middle-1);
            
        }
        else if (seq[middle] < key)
        {
            search_count++; // adds 1 to search count
            return binary_search(key, middle+1, rightindex);
        }
        else
        {
            search_count++; // adds 1 to search count
            return middle;
        }
    }

}





// Destructor function
IntSequence::~IntSequence()
{
    delete seq;
}