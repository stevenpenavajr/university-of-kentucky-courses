// Name: Steven Anker Penava Jr.
// Date: 12/6/15
// Section: CS215-002
// Assignment: Programming Assignment 4
// Purpose: header file for the derived class Rectangle
// File: Rectangle.h

// Opening statements for class definition
#ifndef RECTANGLE_H
#define RECTANGLE_H

// Header file inclusions
#include "Shape.h"

// Defining the derived class
class Rectangle:public Shape
{
public:
	Rectangle(); // constructor
	Rectangle(double len, double wid); // constructor with parameters for length and width
	virtual double computeArea(); // compute area function
	virtual void display(); // display function
	virtual void expand(int factor); // expand function
	double get_length();
	double get_width();
private: // private variables
	double length, width;
};
#endif // ending statement for class definition