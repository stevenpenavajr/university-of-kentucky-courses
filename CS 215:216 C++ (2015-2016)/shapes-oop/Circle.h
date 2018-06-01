// Name: Steven Anker Penava Jr.
// Date: 12/6/15
// Section: CS215-002
// Assignment: Programming Assignment 4
// Purpose: header file for the derived class Circle
// File: Circle.h

// Header file inclusions
#include "Shape.h"
#include "Sphere.h"

// Opening statements for class definition
#ifndef CIRCLE_H
#define CIRCLE_H

// Defining the derived class
class Circle:public Shape
{
public:
	Circle(); // constructor
	Circle(double r); // constructor with parameter for radius
	virtual double computeArea(); // compute area function
	virtual void display(); // display function
	virtual void expand(int factor); // expand function
	double get_radius();
private: // private variables
	double radius;
};
#endif // ending statement for class definition