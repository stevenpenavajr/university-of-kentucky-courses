// Name: Steven Anker Penava Jr.
// Date: 12/6/15
// Section: CS215-002
// Assignment: Programming Assignment 4
// Purpose: source file for the derived class Rectangle
// File: Rectangle.cpp

// Header file inclusions
#include "Rectangle.h"
#include "Shape.h"

// Opening statements
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <fstream>

// Extra variable(s)
double areaRectangle;

// Constructor that assigns default values to the length and the width
Rectangle::Rectangle()
{
	length = 1;
	width = 1;
}

// Constructor that assigns the values of length and width to the parameter values
Rectangle::Rectangle(double len, double wid)
{
	length = len;
	width = wid;
}

// Compute area function that returns the rectangle's area
double Rectangle::computeArea()
{
	areaRectangle = length * width;
	return areaRectangle;
}

// Display function that displays the information about the rectangle
void Rectangle::display()
{
	cout << "Rectangle: (length = " << length << ", width = " << width << ")" << endl;
	cout << "The area is: " << computeArea() << endl;
	cout << endl;
}

// Expand function that expands the dimensions of the rectangle by a factor
void Rectangle::expand(int factor)
{
	length = length * factor;
	width = width * factor;
}

double Rectangle::get_length()
{
	return length;
}

double Rectangle::get_width()
{
	return width;
}