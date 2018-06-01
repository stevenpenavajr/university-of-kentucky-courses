// Name: Steven Anker Penava Jr.
// Date: 12/6/15
// Section: CS215-002
// Assignment: Programming Assignment 4
// Purpose: header file for the derived class Cylinder
// File: Cylinder.h

// Header file inclusions
#include "Shape.h"
#include "Circle.h"

// Opening statements
#ifndef CYLINDER_H
#define CYLINDER_H

// Defining the derived class
class Cylinder:public Circle
{
public:
	Cylinder(); // constructor
	Cylinder(double r, double hei); // constructor with parameters for radius and height
	virtual double computeVolume(); // compute volume function
	virtual double computeArea(); // compute area function
	virtual void display(); // display function
	virtual void expand(int factor); // expand function
private: // private variables
	double height;
};
#endif // ending statement for class definition