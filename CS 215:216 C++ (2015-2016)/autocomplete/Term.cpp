// Name: Steven A Penava Jr
// Date: 4/27/16
// File: Term.cpp

// Include(s)
#include "Term.h"
#include "Autocomplete.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

// Function Definitions

// Initial constructor
Term::Term()
{
	query="";
	weight = 0;
}

// Giving query and weight their proper values
Term::Term(string que, long wei)
{
	this->query = que;
	this->weight = wei;
}