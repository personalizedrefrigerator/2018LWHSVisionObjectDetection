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
	this->point1=new Point2D(0, 0);
	this->point2=new Point2D(0, 0);
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

// Set the points
void Line::setPoints(Point * newPoint1, Point * newPoint2)
{
	// Free memory.
	delete this->point1;
	delete this->point2;

	// Update the points.
	this->point1=newPoint1;
	this->point2=newPoint2;
}

// Get the line's output at a specific point.
int Line::getAt(char dimension1, char dimension2, int location)
{
	// So long as the line has slope on the dimension,
	if(hasSlope(dimension2))
	{
		// Get the slope.
		double slope=getSlope(dimension1, dimension2);

		int result=this->point1->getComponent(dimension1)+slope*(location-this->point1->getComponent(dimension2));

		return result;
	}
	return 0;
}

// Get whether the line has slope at a specific location.
bool Line::getDefinedAt(char dimension, int location)
{
	bool hasSlopeInDimension=hasSlope(dimension);

	if(!hasSlopeInDimension)
	{
		return location == point1->getComponent(dimension);
	}

	return hasSlopeInDimension;
}

// Get the end points.
const Point & Line::getPoint1()
{
	return *point1;
}

const Point & Line::getPoint2()
{
	return *point2;
}

// Deconstruct.
Line::~Line()
{
	// Free memory.
	delete point1;
	delete point2;
}
