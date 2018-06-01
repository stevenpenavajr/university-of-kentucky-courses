// Name: Steven A Penava Jr
// Date: 4/27/16
// File: Autocomplete.cpp

// Include(s)
#include "Term.h"
#include "Autocomplete.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <algorithm>
using namespace std;

// Function Definitions

// Initial constructor
Autocomplete::Autocomplete()
{
    // empty, nothing necessary
}

// Initializing the vector of Term objects
Autocomplete::Autocomplete(vector<Term> trms)
{
	terms = trms;
}

// Insert function to add to "terms"
void Autocomplete::insert(Term newterm)
{
    terms.push_back(newterm);
}

long Autocomplete::getSize()
{
    return terms.size();
}

// Function to sort and print the matches to the prefix
void Autocomplete::showAllMatches(int r)
{
    // # of matches total
    int match_count = matchIndexes.size();

    // Standalone vector of just the matches
    vector<Term> matches;

    // Temporary Term object
    Term matchTerm;

    //-----------------------------------------------------------

    // Giving matchTerm the right value and adding it to the matches vector
    for (int i = 0; i < match_count; i++)
    {
        matchTerm.query = terms[matchIndexes[i]].query;
        matchTerm.weight = terms[matchIndexes[i]].weight;
        matches.push_back(matchTerm);
    }

    //--SUB FUNCTION: SHELL SORT---------------------------------------------------------

    clock_t shellStart = clock();

    // Sorting the matches by descending order (Shell sort)
    int i; // assigning variables >>
    int temp;
    int flag = 1;
    int size = matches.size();
    int d = size;
    while (flag || (d > 1))
    {
        flag = 0;
        d = (d+1) / 2;
        for (int i = 0; i < (size - d); i++)
        {
            if (matches[i+d].weight > matches[i].weight) // comparing weights
            {
                long tempW = matches[i+d].weight; // swapping...
                string tempQ = matches[i+d].query;

                matches[i+d].weight = matches[i].weight;
                matches[i+d].query = matches[i].query;

                matches[i].weight = tempW;
                matches[i].query = tempQ;
                flag = 1;
            }
        }
    }
    clock_t shellEnd = clock();
    double elapsed_secs_shell = double(shellEnd-shellStart) / CLOCKS_PER_SEC;
    if (matchIndexes.size() != 0 )
    {
        cout << "Time for sorting all matched terms in desc. order of weight: " << elapsed_secs_shell << " seconds" << endl;
    }   

    //--SUB FUNCTION: PRINT-------------------------------------------------------------
   
    // Checking if the total number of matches is less than the provided
    // number entered by the user
    if (match_count < r)
    {
        cout << "WEIGHT" << setw(3) << '\t' <<  "QUERY" << endl;
        // Only printing the amount of matches there are
        for (int i = 0; i < match_count; i++)
        {
            if (matches[i].weight < 100000)
            {
                cout << matches[i].weight << setw(3) << '\t' << '\t' << matches[i].query<< endl;
            }
            else
            {
                cout << matches[i].weight << setw(3) << '\t' << matches[i].query<< endl;
            }
        }
        // Clearing the vector
        matchIndexes.clear();
        cout << endl;
    }
    else
    {
        cout << "WEIGHT" << setw(3) << '\t' <<  "QUERY" << endl;
        // Printing all the matches (since the # is not less than r)
        for (int i = 0; i < r; i++)
        {
            if (matches[i].weight < 100000)
            {
                cout << matches[i].weight << setw(3) << '\t' << '\t' << matches[i].query<< endl;
            }
            else
            {
                cout << matches[i].weight << setw(3) << '\t' << matches[i].query<< endl;
            }
        }
        // Clearing the vector
        matchIndexes.clear();
        cout << endl;
    }
    
}


void Autocomplete::binarySearch(string key, long left, long right)
{
    // Beginning search clock
    clock_t begin_search = clock();

    // Giving values to the following variables/initializing
    int keySize = key.length();
    long foundIndex;
    long foundIndexTemp;
    int m;

    // Boolean to end the loop when the first match is found
    bool termFound = false;

    // While left is less than right and the boolean variable is false...
    while ( left <= right && termFound == false)
    {
        // Adjusting middle
        m = (left+right) / 2;

        // Checking >
        if (terms[m].query.substr(0,keySize) > key)
        {
            right = m - 1;
            
        }
        // Checking <
        else if (terms[m].query.substr(0, keySize) < key)
        {
            left = m + 1;
           
        }
        // Match...
        else
        {
            matchIndexes.push_back(m);
            termFound = true;
        }
    }

    // Storing the original found index and making another temporary variable
    foundIndex = m;
    foundIndexTemp = foundIndex;

    // RightFound and LeftFound booleans for scanning in each direction
    bool rightFound = true;
    bool leftFound = true;
    
    // Finding the matches to the right of the original
    while (rightFound == true)
    {
        foundIndex++;
        if (terms[foundIndex].query.substr(0,keySize).find(key) != string::npos)
        {
            matchIndexes.push_back(foundIndex); // adding to matches indexes vector
        }
        else
        {
            rightFound = false;
        }
    }

    // Finding the matches to the left of the original
    while (leftFound == true)
    {
        foundIndexTemp--;
        if (terms[foundIndexTemp].query.substr(0,keySize).find(key) != string::npos)
        {
            matchIndexes.push_back(foundIndexTemp); // adding to matches indexes vector
        }
        else
        {
            leftFound = false;
        }
    }

    // Ending search clock
    clock_t end_search = clock();

    // Calculating time elapsed
    double elapsed_secs_search = double(end_search-begin_search) / CLOCKS_PER_SEC;
    cout << "Time for searching all matched terms: " << elapsed_secs_search << " seconds" << endl;
    
}

// Function to sort all the terms in the text file, lexicographically
void Autocomplete::quickSort(long int left, long int right) 
{
      // Giving values to left and right (i and j)
      long int i = left;
      long int j = right;

      // Temporary values
      long int tmpWeight;
      string tmpQuery;

      // Pivot values
      string pivotQuery = terms[(left + right) / 2].query;
      long pivotWeight = terms[(left + right) / 2].weight;
    
      while (i <= j) 
      {
            while (terms[i].query < pivotQuery)
            {
                  i++; // incrementing i if necessary
            }
            while (terms[j].query > pivotQuery)
            {
                  j--; // decrementing j if necessary
            }
            if (i <= j) // swapping..both queries and weights
            {
                  tmpQuery = terms[i].query;
                  tmpWeight = terms[i].weight;

                  terms[i].query = terms[j].query;
                  terms[i].weight = terms[j].weight;
                  
                  terms[j].query = tmpQuery;
                  terms[j].weight = tmpWeight;
                  
                  i++;
                  j--;
            }
      }

      if (left < j)
      {
            quickSort(left, j); // calling again if left < j (recursive)
      }
      if (i < right)
      {
            quickSort(i, right); // calling again if right < i (recursive)
      }
}

