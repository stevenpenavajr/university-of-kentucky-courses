// CODE GIVEN FROM CS215 SITE

// Name: Steven Anker Penava Jr.
// Date: 12/6/15
// Section: CS215-002
// Assignment: Programming Assignment 4
// Purpose: header file for the base class Shape
// File: Shape.h

// Opening statements for base class definition
#ifndef SHAPE_H
#define SHAPE_H

// Defining the base class
class Shape
{
 public:
	Shape() {}
	virtual double computeArea()=0; 
	virtual void expand(int factor)=0;
	virtual void display()=0;
	virtual ~Shape() {}
};
#endif // ending statement for class definition