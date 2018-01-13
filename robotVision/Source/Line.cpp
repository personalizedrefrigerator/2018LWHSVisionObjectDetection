#pragma once
#include "Point3D.h"
// The definition of functions defined for a line.
//Henry Heino.

//getSlope(char, char)
//Line(Point3D a, Point3D b)

// The constructor the object.
Line::Line(Point3D point1, Point3D point2)
{
	// Update the points.
	this->point1=point1;
	this->point2=point2;
}

// Get the slope from a to b.
//TODO: Fix errors when deltaRun is 0.
double Line::getSlope(char dimension1, char dimension2)
{
	// Calculate the da.
	double deltaRise=point1.getComponent(dimension1)-point2.getComponent(dimension1);

	// Calculate drun.
	double deltaRun=point1.getComponent(dimension2)-point2.getComponent(dimension2);

	// Return deltaRise / deltaRun.
	return deltaRise/deltaRun;
}
