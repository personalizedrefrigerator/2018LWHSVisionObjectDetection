#include "Point.h"
#include "Line.h"

#include <math.h>
// The definition of functions defined for a line.
//Henry Heino.

#define PI 3.145926535897932384626433

//getSlope(char, char)
//Line(Point3D a, Point3D b)

// The constructor the object.
Line::Line(Point * point1, Point * point2)
{
	// Update the points.
	this->point1=point1;
	this->point2=point2;
}

Line::Line()
{
	// Assign pointers.
	this->point1=new Point2D();
	this->point2=new Point2D();
}

// Get the slope from a to b.
//TODO: Fix errors when deltaRun is 0.
double Line::getSlope(char dimension1, char dimension2)
{
	// Calculate the da.
	double deltaRise=point1->getComponent(dimension1)-point2->getComponent(dimension1);

	// Calculate drun.
	double deltaRun=point1->getComponent(dimension2)-point2->getComponent(dimension2);

	// Return deltaRise / deltaRun.
	return deltaRise/deltaRun;
}

// Get whether the slope exists on a given dimension
//TODO: Fix errors when deltaRun is 0.
bool Line::hasSlope(char dimension)
{
	// Calculate drun.
	double deltaRun=point1->getComponent(dimension)-point2->getComponent(dimension);

	// The slope is only defined if drun != 0.
	return deltaRun != 0;
}

// Get the angle the the line makes.
double Line::getAngle2D()
{
	if(hasSlope('x'))
	{
		double slopedYdX=getSlope('y', 'x');

		//Point2D point2=Point2D(at.getComponent('x')+1, at.getComponent('y')+slopedYdX);

		double angle=atan(slopedYdX/1)+PI;

		return angle;
	}
	return PI/2; // TODO:If PI is undefined, define it to 3.141592653589793.
}

// Deconstruct.
Line::~Line()
{
	// Free memory.
	delete point1;
	delete point2;
}
