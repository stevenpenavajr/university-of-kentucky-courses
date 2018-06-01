// Name: Steven Anker Penava Jr.
// Date: 12/6/15
// Section: CS215-002
// Assignment: Programming Assignment 4
// Purpose: header file for the derived class Sphere
// File: Sphere.h

// Opening statements
#ifndef SPHERE_H
#define SPHERE_H

// Header file inclusions
#include "Circle.h"
#include "Shape.h"

// Defining the derived class
class Sphere:public Circle
{
public:
	Sphere(); // constructor
	Sphere(double r); // constructor with parameter for radius
	virtual double computeVolume(); // compute volume function
	virtual double computeArea(); // compute area function
	virtual void display(); // display function
	virtual void expand(int factor); // expand function
private: // private variables
};
#endif // ending statement for class definition