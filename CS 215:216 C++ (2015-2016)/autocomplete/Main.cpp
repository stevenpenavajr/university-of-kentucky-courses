// Name: Steven A Penava Jr
// Date: 4/27/16
// File: Main.cpp

// Time is displayed for creating objects, sorting all terms, and searching matches.

// Include(s)
#include "Term.h"
#include "Autocomplete.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <stdlib.h> 
#include <stdexcept>
#include <ctime>
using namespace std;

// Global Variables
string prefix;
fstream file;

// Main Function
int main(int argc, char* argv[])
{
	// Introduction
	cout << "Welcome to the AutoComplete Program!" << endl;
	cout << "This program was written by Steven Penava." << endl;
	cout << endl;

	// Checking argument count
	if (argc != 3)
	{
		cout << "This program takes two arguments. Run it again." << endl;
		return 0;
	}
	else
	{
        // Creating variable for the result count (to be used later)
		const char* resultCountString = argv[2];
		int resultCount = atoi(resultCountString);
        
        // Creating c string variable for the file name
		const char* filename = argv[1];
        
        // Attempting to open file and checking if it exists in the directory
		file.open(filename);
		if (!file.is_open())
		{
			cout << "File not found. Restart." << endl;
			return 0;
		}
        
        // If the file does exist, the program starts to run
		else
		{
			// Creating an Autocomplete object to use insert function
            Autocomplete autocompTerm;
            
            // Creating string/char variables for the line (scanned in text), delimiter, and newline
			string line;
			string delim = "\t";
			char newline = '\n';
            
            // Creating string variable to be used in Term object
			string term;

			// Starting clock variable (for object creation timing)
			clock_t begin_objects = clock();

			// Looping through whole text file
			for (int i = 0; getline(file, line); i++)
			{
				long weight = atol((line.substr(0,line.find(delim))).c_str()); // converting str numbers to weight
				term = line.substr(line.find(delim), line.find(newline)); // singling out the term
				term.erase(0, term.find_first_not_of(" \t\r\n")); // erasing whitespace

				Term termFromList(term, weight); // creating object with string and long values
				autocompTerm.insert(termFromList); // inserting the object into the list
			}

			// Ending clock variable (for object creation timing)
			clock_t end_objects = clock();

			// Calculating the time elapsed
			double elapsed_secs_objects = double(end_objects-begin_objects) / CLOCKS_PER_SEC;

			// Outputting time info
			cout << "Created " << autocompTerm.getSize() << " Term objects in " << elapsed_secs_objects << " seconds" << endl;

			// Assigning values to left and right for sort
			long left = 0;
			long right = autocompTerm.getSize() - 1;

			// Staring clock for sorting
			clock_t begin_sort = clock();

			// Calling quick sort
			autocompTerm.quickSort(left, right);

			// Ending clock for sorting
			clock_t end_sort = clock();

			// Calculating the time elapsed
			double elapsed_secs_sort = double(end_sort-begin_sort) / CLOCKS_PER_SEC;
			cout << "Time for sorting all terms: " << elapsed_secs_sort << " seconds" << endl;
			cout << endl;
            
			do
			{
				// Assigning values to left and right for binary search
				long left = 0;
				long right = autocompTerm.getSize() - 1;

				// Getting user input
				cout << "Please enter your search ('exit' to quit): ";
				cin >> prefix; 

				// Calling Binary Search algorithm
                autocompTerm.binarySearch(prefix, left, right);

                // Ending search clock
                clock_t end_search = clock();

                // Calling show matches function
                autocompTerm.showAllMatches(resultCount); // calling show matches function to print results and handle other vectors

			} while (prefix != "exit");
		}

		// Closing the program if the user inputs "exit"
		if (prefix == "exit")
		{
			cout << "Thanks for using this program." << endl;
			file.close();
			return 0;
		}
	}
}
