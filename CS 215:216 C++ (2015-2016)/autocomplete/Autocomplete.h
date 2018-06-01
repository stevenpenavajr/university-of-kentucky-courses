// Name: Steven A Penava Jr
// Date: 4/27/16
// File: Autocomplete.h

// Include(s)
#include <vector>
#include "Term.h"
#include <ctime>
#include <fstream>
using namespace std;

// Include Guards
#ifndef AUTOCOMP_H
#define AUTOCOMP_H

class Autocomplete
{
public:
	Autocomplete();
		// ↳ Default Constructor
	Autocomplete(vector<Term> trms);
		// ↳ Constructor to initialize the vector of terms
    void insert(Term newterm);
    	// ↳ Insert function to insert Term objects into "terms"
    void showAllMatches(int r);
		// ↳ Function to show all the matches, in sorted order
    long getSize();
        // ↳ getSize function for timing the object creation
    void quickSort(long int left, long int right);
        // ↳ Shell sort function for efficient searching
    void binarySearch(string key, long left, long right);
        // ↳ Binary search function to complete search more efficiently


private:
    vector<Term> terms;
    	// ↳ Vector for Term objects
    vector<int> matchIndexes;
    	// ↳ Vector for the indexes of the prefixes matches
};

// Ending Include Guard
#endif