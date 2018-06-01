// Name: Steven A Penava Jr
// Date: 4/27/16
// File: Term.h

// Include(s)
#include <string>
#include <vector>
#include <ctime>
using namespace std;

// Include Guards
#ifndef TERM_H
#define TERM_H

class Term
{
public:
	Term(); 
		// ↳ Default Constructor
    Term(string que, long wei);
		// ↳ Initialize with the given query & weight
	friend class Autocomplete; 
		// ↳ Autocomplete is a friend class of Term
private:
    string query;
    	// ↳ String variable for the query part of the objects
	long weight;
		// ↳ Long integer variable for the weight part of the objects
};

// Ending Include Guard
#endif