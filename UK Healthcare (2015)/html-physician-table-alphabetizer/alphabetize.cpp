// AUTHOR: Steven A Penava Jr
// DATE: 06/28/2016
// GITHUB: stevenpenavajr
// WEBSITE: http://stevenpenavajr.me
//
// HTML PHYSICIAN/CREDENTIAL TABLE ALPHABETIZER
// PURPOSE: This program takes a text file as input. The text file must consist of an HTML table with some data.
// The purpose is to sort a table that contains doctors and their titles - make sure they are formatted like this:
// "First Last, [TITLE]" - TITLE being MD, M.D., PhD, etc...
//
// NOTE: The input file format must have: <table ...><tbody> at top, <tr> enclosed tags as full separate lines, and 
// </tbody></table> at bottom.

// Includes===========//
#include <iostream>   
#include <string>     
#include <vector>     
#include <fstream>    
using namespace std;  
//====================//

//=========Global Variables==============================//
string filename;            // File title				 
string line;                // String for generic line  
fstream inFile;             // Input file object		 
fstream outFile;            // Output file object		 
vector<string> names;       // Vector for physican names 
vector<string> lines;       // Vector for HTML lines	 
string outFileName;         // Name of output file       
string tableInfo;           // Table settings (tbody)	 
vector<string> titles;      // List of titles for search 
//=======================================================//

// Bubble Sort function to sort last names alphabetically
void bubble_sort(vector<string> &names, vector<string> &lines, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n - i - 1; ++j)
		{
	  		if (names[j] > names[j + 1])
			{
			    string temp1 = names[j];
			    string temp2 = lines[j];
			    names[j] = names[j + 1];
			    lines[j] = lines[j+1];
			    names[j + 1] = temp1;
			    lines[j+1] = temp2;
			}
		}
	}
}	

// Function to add docs' last names to vector
void appendDoc(string title)
{
	int commaIndex = line.find(title);
	int firstChar = commaIndex;
	int counter = 0;

	while (line.at(firstChar) != ' ')
	{
		firstChar--;
		counter++;
	}

	string lastName = line.substr(firstChar+1, counter-1);
	names.push_back(lastName);
	lines.push_back(line);
}

// Asking for input file
void askForFile()
{
	cout << "Enter the name of the file: ";
	getline(cin >> ws, filename);
	inFile.open(filename);
}

// Running each append func
void addAllDocs(vector<string> allTitles)
{
	int size = allTitles.size();
	if (line.length() > 0)
	{
		for (int i = 0; i < size; i++)
		{
			if (line.find(allTitles[i]) != std::string::npos)
			{
				appendDoc(allTitles[i]);
			}
		}
	}
}

vector<string> getTitlesToSearchFor()
{
	string title;
	vector<string> titleList;
	cout << "Please enter titles for the program to search for." << endl;
	cout << "Make sure your doctors are listed in this manner in the text file: Name LastName, [TITLE]" << endl;
	cout << endl;
	cout << "Type Q or q to finish entering. Remember to format same way you did with HTML text." << endl;
	cout << "Example - to add MD doctors: type 'MD' or 'M.D.' if you had periods." << endl;
	while (title != "Q")
	{
		cout << "Enter: ";
		getline(cin >> ws, title);
		titleList.push_back(", "+title);
	}
	titleList.pop_back();
	return titleList;
}

// Asking for output file name
string askForOutputName()
{
	string yourFileName;
	cout << "What would you like to name your text file? Exclude file extension." << endl;
	cout << "Enter: ";
	getline(cin >> ws, yourFileName);
	return yourFileName;
}

// Asking for table style
string askForTableCode()
{
	string tableCode;
	cout << "Please enter the <table> tag followed by the <tbody> tag. I will add the closing tags." << endl;
	cout << "Example: <table border=\"0\" style=\"width: 549px; height: 788px;\"><tbody>" << endl;
	cout << "Enter: ";
	getline(cin >> ws, tableCode);
	return tableCode;
}

// Driver function (creates vectors of names and lines, sorts)
int main()
{
	cout << endl;
	cout << "Welcome. This program was written by Steven Penava Jr." <<endl;
	cout << "http://stevenpenavajr.me" << endl;
	cout << endl;

	askForFile();

	titles = getTitlesToSearchFor();

	while(getline(inFile, line))
	{
		addAllDocs(titles);
	}

	bubble_sort(names, lines, names.size());

	outFileName = askForOutputName() + ".txt";

	tableInfo = askForTableCode();

	outFile.open(outFileName, fstream::out);

	outFile << tableInfo << endl;

	for (int i=0; i<names.size(); i++)
	{
		outFile << lines[i] << endl;
		outFile << endl;
	}

	outFile << "</tbody></table>" << endl;
	
	outFile.close();

	return 0;
	
}