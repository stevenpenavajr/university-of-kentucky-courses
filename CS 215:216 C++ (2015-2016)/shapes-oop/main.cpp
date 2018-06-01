// Name: Steven Anker Penava Jr.
// Date: 12/6/15
// Section: CS215-002
// Assignment: Programming Assignment 4
// Purpose: to practice designing classes and working with objects and virtual functions
// File: main.cpp

// Opening include statements
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
using namespace std;

// Header File Inclusions
#include "Shape.h"
#include "Circle.h"
#include "Cuboid.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Rectangle.h"

// Max surface area function that takes a vector of pointers to objects of Shape
// that tells the user which shape object has the biggest surface area
void maxSurfaceArea(vector<Shape*> shapes_vector)
{
	int mPlaceHolder = 0; // placeholder for the index (shape object) with maximum area
	double max_sa = shapes_vector[0]->computeArea(); // max area = first shape's area (called computeArea) (temporary)
	double temp_sa; // temporary surface area to be used in the comparison of surface area

	// For loop that iterates through each pointer to object in shapes_vector
	for (int i=0; i<shapes_vector.size(); i++)
	{
		temp_sa = shapes_vector[i] -> computeArea(); // assigning the temporary max surface area equal to the current iterated index's area
		// If the temporary surface area is greater than the current max...
		if (temp_sa > max_sa)
		{
			mPlaceHolder = i; // assigning max place holder to that index 
			max_sa = temp_sa; // making a new max surface area (equal to the temporary surface area)
		}

	}

	// Displaying the information to the user
	cout << endl;
	cout << "The shape with the largest SURFACE AREA is: " << endl;
	shapes_vector[mPlaceHolder]->display();
	cout << endl;

}

// Expand all function that takes a vector of pointers to objects of Shape
// and a multiplier that expands all the shape's dimensions by that factor
void expandAll(vector<Shape*> shapes_vector, int multiplier)
{
	// For loop that iterates through the vector
	for (int i=0; i<shapes_vector.size(); i++)
	{
		// calling the expand function for each object
		shapes_vector[i]->expand(multiplier);
	}
}

// Function to convert string to double (uses atof)
double string2double(string shapeDimension_string)
{
	double dimensionDouble = atof(shapeDimension_string.c_str());
	return dimensionDouble;
}

// Main Function
int main()
{
	system("Color CF");
	// Misc Variable Declarations & Definitions
	string fileTitle;            // user-entered filename
	fstream actualFile;          // actual file
	bool okEnter = true;         // boolean variable used in input validation
	int tryCount = 0;            // counter for number of attempts when opening the file
	bool endRun = false;         // boolean variable to signify when the program ends
	string line;                 // line variable used in getting the line
	string delim = " ";          // space used as delimiter
	int offset;                  // empty integer variable used in locating information with circle, cuboid, etc...
	vector<Shape*> shapes;       // vector of pointers to objects of Shape base class
	int uMultiplier;             // user multiplier variable for expand function at end
	bool goodMultiplier = false; // boolean variable for whether or not the user input is good for multiplier

	// Variable Definitions - Shape names (self explanatory)
	string circleStr = "Circle";
	string cuboidStr = "Cuboid";
	string cylinderStr = "Cylinder";
	string rectangleStr = "Rectangle";
	string sphereStr = "Sphere";

	// Variable Declarations - Shape lines
	string circLine;   // circle line
	string cubLine;    // cuboid line
	string cylinLine;  // cylinder line
	string rectLine;   // rectangle line
	string sphLine;    // sphere line

	// Variable Declarations - Dimension strings
	string rectLenStr;  // rectangle length
	string rectWidStr;  // rectangle width
	string circRadStr;  // circle radius
	string cubLenStr;   // cuboid length
	string cubWidStr;   // cuboid width
	string cubHeiStr;   // cuboid height
	string sphRadStr;   // sphere radius
	string CylRadStr;   // cylinder radius
	string CylHeiStr;   // cylinder height

	// Variable Declarations - Area & volume (self explanatory)
	double rectangleArea;
	double circleArea;
	double cubeArea, cubeVolume;
	double sphereArea, sphereVolume;
	double cylinderArea, cylinderVolume;

	// Message to user (with fancy box for viewing pleasure)
	cout << "   _____ __ __   ____  ____   ___  _____"<< endl;
	cout << "  / ___/|  |  | /    ||    \\ /  _]/ ___/"<< endl;
	cout << " (   \\_ |  |  ||  o  ||  o  )  [_(   \\_ "<< endl;
	cout << "  \\__  ||  _  ||     ||   _/    _]\\__  |"<< endl;
	cout << "  /  \\ ||  |  ||  _  ||  | |   [_ /  \\ |"<< endl;
	cout << "  \\    ||  |  ||  |  ||  | |     |\\    |"<< endl;
	cout << "   \\___||__|__||__|__||__| |_____| \\___|" << endl;
	cout << endl;
	cout << "A shape object manipulation program by Steven Penava" << endl;
	cout << endl;
	
	// Message to user
	cout << "Follow the instructions." << endl;
	cout << endl;

	// Asking for filename
	cout << "Enter the name of the text file containing the shape information that you want to open: ";
	cin >> fileTitle;
	cout << endl;

	// Attempt to open file
	actualFile.open(fileTitle);

	// Handling error in opening file (file doesn't exist, etc.)
	while (actualFile.fail())
	{
		tryCount++; // add one to the attempt counter
		
		// first attempt + message
		if (tryCount == 1)
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Sorry, but there was no file with name "+fileTitle+" found. Try again. You have two more attempts." << endl;
			cout << endl;
			cout << "Enter the name of the text file containing the shape information that you want to open: ";
			cin >> fileTitle;
			actualFile.open(fileTitle);
		}

		// second attempt + message
		if (tryCount == 2)
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << endl;
			cout << "Sorry, but there was no file with name "+fileTitle+" found. Try again. You have one more attempt." << endl;
			cout << endl;
			cout << "Enter the name of the text file containing the shape information that you want to open: ";
			cin >> fileTitle;
			actualFile.open(fileTitle);
		}

		// third attempt + message (and quitting the program)
		if (tryCount == 3)
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << endl;
			cout << "Sorry, but there was no file with name "+fileTitle+" found. Exiting program now..." << endl;
			cout << endl;
			actualFile.open(fileTitle);
			okEnter = false;
			endRun = true;
			system("pause");
			return 0;

		}
	}

	// Handling file open success
	if (!actualFile.fail())
	{
		// while the name exists...
		while (!actualFile.eof())
		{
			// getline to get the lines of the file
			getline(actualFile, line);

			// if any line starts with "Circle" (uses offest variable)
			if (offset = line.find(circleStr, 0) != string::npos)
			{
				// Storing the contents of the line in circLine
				circLine = line;

				// Getting radius in its own string
				int space_indexCirc = circLine.find(delim);
				string circLine2 = circLine.substr(space_indexCirc+1, 40);
				int space_indexCirc2 = circLine2.find(delim);

				// Circle radius in string form and double form
				circRadStr = circLine2.substr(space_indexCirc2+1, circLine2.length()); 
				double circleRadius = string2double(circRadStr); 

				// Handling invalid number
				if (circleRadius <= 0)
				{
					cout << "ERROR: The given radius for this circle is 0 or less. Cannot compute desired information." << endl;
				}
				else
				{
					// Creating object Circle1
					Circle Circle1(circleRadius);
				
					// Printing the info about the shape
					Circle1.display();

					// Adding it to the shapes vector
					Circle * CircleObj = new Circle(circleRadius);
					shapes.push_back(CircleObj);

					
				}
			}

			// if any line starts with "Cuboid" (uses offest variable)
			if (offset = line.find(cuboidStr, 0) != string::npos)
			{
				// Storing the contents of the line in cubLine
				cubLine = line;

				// Getting length, width, and height in their own string
				int space_indexCub = cubLine.find(delim);
				string cubLine2 = cubLine.substr(space_indexCub+1, 40);
				int space_indexCub2 = cubLine2.find(delim);
				string cubLine3 = cubLine2.substr(space_indexCub2+1, 40);
				int space_indexCub3 = cubLine3.find(delim);
				string cubLine4 = cubLine3.substr(space_indexCub3+1, 40);
				int space_indexCub4 = cubLine4.find(delim);

				// Cuboid length, width, and height in string form and double form
				cubLenStr = cubLine2.substr(0, space_indexCub2);
				cubWidStr = cubLine3.substr(0, space_indexCub3);
				cubHeiStr = cubLine4.substr(0, space_indexCub4);
				double cubeLength = string2double(cubLenStr);
				double cubeWidth = string2double(cubWidStr);
				double cubeHeight = string2double(cubHeiStr);

				// Handling invalid numbers
				if (cubeLength <= 0 || cubeWidth <= 0 || cubeHeight <= 0)
				{
					cout << "ERROR: Either the length, width, or height of the cuboid is 0 or less. Cannot compute desired information." << endl;
				}
				else
				{
					// Creating the cuboid object Cuboid1
					Cuboid Cuboid1(cubeLength, cubeWidth, cubeHeight);

					// Printing the info about the shape
					Cuboid1.display();

					// Adding it to the shapes vector
					Cuboid * CuboidObj = new Cuboid(cubeLength, cubeWidth, cubeHeight);
					shapes.push_back(CuboidObj);
				}
			}

			// if any line starts with "Rectangle" (uses offest variable)
			if (offset = line.find(rectangleStr, 0) != string::npos)
			{
				// Storing the contents of the line in rectLine
				rectLine = line;

				// Getting length and width in their own string (without title)
				int space_indexRect = rectLine.find(delim);
				string rectLine2 = rectLine.substr(space_indexRect+1, 40);
				int space_indexRect2 = rectLine2.find(delim);
				
				// Rectangle length and width in string form and double form
				rectLenStr = rectLine2.substr(0, space_indexRect2);
				rectWidStr = rectLine2.substr(space_indexRect2+1, rectLine2.length());
				double rectangleLength = string2double(rectLenStr);
				double rectangleWidth = string2double(rectWidStr);

				// Handling invalid numbers 
				if (rectangleLength <= 0 || rectangleWidth <= 0)
				{
					cout << "ERROR: Either the length or width of the rectangle is 0 or less. Cannot compute desired information." << endl;
				}
				else
				{
					// creating the rectangle object Rectangle1
					Rectangle Rectangle1(rectangleLength, rectangleWidth);

					// printing the info about the shape
					Rectangle1.display();

					// Adding it to the shapes vector
					Rectangle * RectangleObj = new Rectangle(rectangleLength, rectangleWidth);
					shapes.push_back(RectangleObj);
				}
			}

			// if any line starts with "Sphere" (uses offest variable)
			if (offset = line.find(sphereStr, 0) != string::npos)
			{
				// Storing the contents of the line in sphLine
				sphLine = line;

				// Getting the radius in its own string
				int space_indexSph = sphLine.find(delim);
				string sphLine2 = sphLine.substr(space_indexSph+1, 40);
				int space_indexSph2 = sphLine2.find(delim);

				// Sphere radius in string form and double form
				sphRadStr = sphLine2.substr(0, space_indexSph2);
				double sphereRadius = string2double(sphRadStr);

				// Handling invalid number
				if (sphereRadius <= 0)
				{
					cout << "ERROR: The radius of the sphere is 0 or less. Cannot compute desired information." << endl;
				}
				else
				{
					// Creating the sphere object Sphere1
					Sphere Sphere1(sphereRadius);

					// Printing the info about the shape
					Sphere1.display();

					// Adding it to the shapes vector
					Sphere * SphereObj = new Sphere(sphereRadius);
					shapes.push_back(SphereObj);
				}
			}

			// if any line starts with "Cylinder" (uses offest variable)
			if (offset = line.find(cylinderStr, 0) != string::npos)
			{
				// Storing the contents of the line in cylinLine
				cylinLine = line;

				// Getting the radius and height in their own string
				int space_indexCyl = cylinLine.find(delim);
				string cylinLine2 = cylinLine.substr(space_indexCyl+1, 40);
				int space_indexCyl2 = cylinLine2.find(delim);

				// Cylinder radius and height in string form and double form
				CylRadStr = cylinLine2.substr(0, space_indexCyl2);
				CylHeiStr = cylinLine2.substr(space_indexCyl2+1, cylinLine2.length());
				double cylinderRadius = string2double(CylRadStr);
				double cylinderHeight = string2double(CylHeiStr);

				// Handling invalid numbers
				if (cylinderHeight <= 0 || cylinderRadius <= 0)
				{
					cout << "ERROR: The height or radius of the cylinder is 0 or less. Cannot compute desired information." << endl;
				}
				else
				{
					// Creating the cylinder object Cylinder1
					Cylinder Cylinder1(cylinderRadius, cylinderHeight);

					// Printing the info about the shape
					Cylinder1.display();

					// Adding it to the shapes vector
					Cylinder * CylinderObj = new Cylinder(cylinderRadius, cylinderHeight);
					shapes.push_back(CylinderObj);
				}
			}
		}
	}

	// Calling the max surface area function to display shape with largest surface area
	maxSurfaceArea(shapes);

	// Asking the user for a factor to multiply the dimensions by (and validating the input)
	cout << "Please input a positive integer to be used as a multiplier to expand the dimensions of the listed shapes: ";
	while (goodMultiplier == false)
	{
		cin >> uMultiplier;
		if (cin.fail() || uMultiplier <= 0)
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "That input is invalid. Try again: ";
		}
		else
		{
			goodMultiplier = true;
		}
	}

	// Calling the expand all function with the user's multiplier as a parameter
	expandAll(shapes, uMultiplier);
	cout << endl;

	// Printing the new shapes' dimensions
	cout << "New shape dimensions:" << endl;
	cout << endl;
	for (int i=0; i < shapes.size(); i++)
	{
		shapes[i]->display(); // calling display for each object
	}

	// Calling max surface area again (since it did so in the example run on the website)
	maxSurfaceArea(shapes);

	// Setting endRun = true (signifying the end of the program)
	endRun = true;

	// Exit statements
	if (endRun == true)
	{
		cout << "Thanks for using this program. Goodbye." << endl;
		actualFile.close(); // closing the file

		// Destroying all the items in the vector
		for (int i=0; i<shapes.size(); i++)
		{
			delete shapes[i];
		}
	}
	
	// Pausing and returning 0
	system("pause");
	return 0;
}
