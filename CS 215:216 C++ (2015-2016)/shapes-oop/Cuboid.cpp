// Name: Steven Anker Penava Jr.
// Date: 12/6/15
// Section: CS215-002
// Assignment: Programming Assignment 4
// Purpose: source file for the derived class Cuboid
// File: Cuboid.cpp

// Opening statements
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <fstream>

// Header file inclusions
#include "Cuboid.h"
#include "Rectangle.h"

// Extra constants/variables
double areaCuboid;
double volumeCuboid;
double cubLength;
double cubWidth;

// Constructor that assigns default values to length, width, and height
Cuboid::Cuboid()
{
	cubLength = 1;
	cubWidth = 1;
	height = 1;
}

// Constructor that assigns length, width, and height to get_length() and get_width() and hei
Cuboid::Cuboid(double len, double wid, double hei):Rectangle(len, wid)
{
	cubLength = get_length();
	cubWidth = get_width();
	height = hei;
}

// Compute volume function that returns the volume of the cuboid
double Cuboid::computeVolume()
{
	volumeCuboid = get_length() * get_width() * height;
	return volumeCuboid;
}

// Compute area function that returns the area of the cuboid
double Cuboid::computeArea()
{
	areaCuboid = (2*get_width()*get_length()) + (2*get_length()*height) + (2*height*get_width());
	return areaCuboid;
}

// Display function that displays information about the cuboid
void Cuboid::display()
{
	cout << "Cuboid: (length = " << get_length() << ", " << "width = " << get_width() << ", " << "height = " << height << ")" << endl;
	cout << "The area is: " << computeArea() << endl;
	cout << "The volume is " << computeVolume() << endl;
	cout << endl;
}

// Expand function that expands the length, width, and height by a factor
void Cuboid::expand(int factor)
{
	Rectangle::expand(factor);
	height*=factor;

}

