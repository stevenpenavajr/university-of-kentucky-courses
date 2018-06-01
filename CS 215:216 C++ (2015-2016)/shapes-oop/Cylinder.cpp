// Name: Steven Anker Penava Jr.
// Date: 12/6/15
// Section: CS215-002
// Assignment: Programming Assignment 4
// Purpose: source file for the derived class Cylinder
// File: Cylinder.cpp

// Opening statements
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <fstream>

// Header file inclusions
#include "Shape.h"
#include "Circle.h"
#include "Cylinder.h"
#include "Sphere.h"

// Including math library to use real value for pi 
#define _USE_MATH_DEFINES
#include <math.h>

// Extra variables
double PI_CYL = M_PI;
double volumeCylinder;
double areaCylinder;
double cylRadius;

// Constructor that assigns default values to radius and height
Cylinder::Cylinder()
{
	cylRadius = 1;
	height = 1;
}

// Constructor that assigns radius and height to get_radius() and hei
Cylinder::Cylinder(double r, double hei): Circle(r)
{
	cylRadius = get_radius();
	height = hei;
}

// Compute volume function that returns the value of the volume of the cylinder
double Cylinder::computeVolume()
{
	volumeCylinder = PI_CYL*(get_radius()*get_radius()*height);
	return volumeCylinder;
}

// Compute area function that returns the value of the area of the cylinder
double Cylinder::computeArea()
{
	areaCylinder = (2*PI_CYL*get_radius()*height) + (2*PI_CYL*(get_radius()*get_radius()));
	return areaCylinder;
}

// Display function that displays information about the cylinder
void Cylinder::display()
{
	cout << "Cylinder: (radius = " << get_radius() << ", height = " << height << ")" << endl;
	cout << "The area is: " << computeArea() << endl;
	cout << "The volume is: " << computeVolume() << endl;
	cout << endl;
}

// Expand function to expand the dimensions of the cylinder by a factor
void Cylinder::expand(int factor)
{
	Circle::expand(factor);
	height = height * factor;
}

