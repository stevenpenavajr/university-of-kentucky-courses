// Name: Steven Anker Penava Jr.
// Date: 12/6/15
// Section: CS215-002
// Assignment: Programming Assignment 4
// Purpose: header file for the derived class Cuboid
// File: Cuboid.h

// Header file inclusions
#include "Shape.h"
#include "Rectangle.h"

// Opening statements
#ifndef CUBOID_H
#define CUBOID_H

// Defining the derived class
class Cuboid:public Rectangle
{
public:
	Cuboid(); // constructor
	Cuboid(double len, double wid, double hei); // constructor with parameters for length, width, height
	virtual double computeVolume(); // compute volume function
	virtual double computeArea(); // compute area function
	virtual void display(); // display function
	virtual void expand(int factor); // expand function
private: // private variables
	double height;
};
#endif // ending statement for class definition