// Name: Steven Anker Penava Jr.
// Date: 12/6/15
// Section: CS215-002
// Assignment: Programming Assignment 4
// Purpose: source file for the derived class Sphere
// File: Sphere.cpp

// Header file inclusions
#include "Shape.h"
#include "Sphere.h"
#include "Circle.h"

// Opening statements
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <fstream>

// Including math library to use real value for pi 
#define _USE_MATH_DEFINES
#include <math.h>

// Extra variables/constants
double PI_SPH = M_PI;
double volumeSphere;
double areaSphere;
double sphRadius;
const double four3rds = 4.0/3.0;

// Constructor that assigns default value to radius
Sphere::Sphere()
{
	sphRadius = 1;
}

// Constructor that assigns radius value to r
Sphere::Sphere(double r):Circle(r)
{
	sphRadius = get_radius();
}

// Compute volume function that returns the volume of the sphere
double Sphere::computeVolume()
{
	volumeSphere = (four3rds)*PI_SPH*(get_radius()*get_radius()*get_radius());
	return volumeSphere;
}

// Compute area function that returns the area of the sphere
double Sphere::computeArea()
{
	areaSphere = (4)*PI_SPH*(get_radius()*get_radius());
	return areaSphere;
}

// Display function that displays the information about the sphere
void Sphere::display()
{
	cout << "Sphere: (radius = " << get_radius() << ")" << endl;
	cout << "The area is: " << computeArea() << endl;
	cout << "The volume is: " << computeVolume() << endl;
	cout << endl;
}

// Expand function that expands the radius by a factor
void Sphere::expand(int factor)
{
	Circle::expand(factor);
}