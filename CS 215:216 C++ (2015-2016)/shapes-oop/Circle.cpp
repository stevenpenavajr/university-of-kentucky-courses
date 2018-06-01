// Name: Steven Anker Penava Jr.
// Date: 12/6/15
// Section: CS215-002
// Assignment: Programming Assignment 4
// Purpose: source file for the derived class Circle
// File: Circle.cpp

// Header file inclusions
#include "Shape.h"
#include "Circle.h"
#include "Cylinder.h"
#include "Sphere.h"

// Opening statements
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <fstream>
#include <cmath>

// Including math library to use real value for pi
#define _USE_MATH_DEFINES
#include <math.h>

// Extra variables needed
double CIRCLE_PI = M_PI;
double areaCircle;

// Constructor that assigns a default value to radius
Circle::Circle()
{
	radius = 1;
}

// Constructor that assigns radius to the parameter value r
Circle::Circle(double r)
{
	radius = r;
}

// Compute Area function that returns the value of the area of the circle
double Circle::computeArea()
{
	areaCircle = CIRCLE_PI * (radius * radius);
	return areaCircle;
}

// Display function that displays information about the circle
void Circle::display()
{
	cout << "Circle: (radius = " << radius << ")" << endl;
	cout << "The area is: " << computeArea() << endl;
	cout << endl;
}

// Expand function that expands the radius by a factor parameter
void Circle::expand(int factor)
{
	radius = radius * factor;
}

double Circle::get_radius()
{
	return radius;
}