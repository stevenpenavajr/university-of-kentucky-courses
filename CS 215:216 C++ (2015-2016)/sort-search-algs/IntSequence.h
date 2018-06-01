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
// File: IntSequence.h (header file for IntSequence source)
//---------------------------------------------------------------

//---------------------------------------------------------------
// NOTE TO TA: You may notice there is no code within my member
// functions to handle an empty list. This is because, with the
// way I have my program written, the user is never able to
// enter options 2, 3, 4, or 5 on the main menu unless the size
// of the array/sequence is greater than 0.
//---------------------------------------------------------------

#ifndef INTSEQUENCE_H
#define INTSEQUENCE_H

const int INITIAL_CAPACITY = 5;

class IntSequence
{
public:
    // create an iteger array with capacity = INITIAL_CAPACITY
    IntSequence();		// default constructor
    
    // create an iteger array with capacity = in_capacity
    IntSequence(int in_capacity);
    
    // print the list of options
    void printOptions();
    
    // does the list exist?
    bool doesExist();
    
    void printSortOp();
    
    void printSearchOp();
    
    // insert item into the end of the array; count increased by 1
    void insert(int item);
    
    // display all the items in the array
    void print();
    
    // sort the sequence into non-decreasing order
    // using Selection Sorting algorithm
    void selection_sort();
    
    // sort the sequence into non-decreasing order
    // using Insertion Sorting algorithm
    void insertion_sort();
    
    // sort the sequence into non-decreasing order
    // using Bubble Sorting algorithm
    void bubble_sort();
    
    // shuffle the items in the sequence
    // generates a random permutation of array elements
    void shuffle();
    
    // search a target key in the array:
    // if found return the index number; if not found return -1
    int sequential_search(int key);
    
    // sort the array into non-decreasing order first, then
    // search a target key in the array:
    // if found return the index number; if not found return -1
    int binary_search(int key, int leftindex, int rightindex);
    
    // get size function
    const int getSize();
    
    // bubble sort function that doesn't print
    void bubble_sort_noPrint();
    
    // get search count function (comparison #)
    const int getSearchCount();
    
    // reset search count function
    void resetSearchCount();
    
    // destructor
    ~IntSequence();
    
    // more member functions here ...
    
private:
    int capacity;    // the capacity of the array
    int count;	  // actual num of items in the array
    int* seq;	  // the pointer points at the first item in the array
    int search_count; // comparison # counter
};

#endif /* IntSequence_h */
