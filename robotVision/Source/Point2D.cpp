#include "Point2D.h"
// The definitions of methods for the Point2D object.
//The Point2D object is a basic point container object.

// Construct a Point2D.
Point2D::Point2D(double x, double y)
{
	this->x=x;
	this->y=y;
}

Point2D::Point2D(const Point2D& makeFrom)
{
	this->x=makeFrom.x;
	this->y=makeFrom.y;
}

Point2D::Point2D(const Point& makeFrom)
{
	x = makeFrom.getComponent('x');
	y = makeFrom.getComponent('y');
}

Point2D& Point2D::operator=(const Point2D& other)
{
	x = other.x;
	y = other.y;
	
	return *this;
}

// Get a component of the point.
double Point2D::getComponent(char componentName) const
{
	switch(componentName)
	{
		case 'x':
			return x;
		break;
		case 'y':
			return y;
		break;
		break;
		default:
			return 0; // Return 0. The point has no components in greater than 3 dimensions.
	}
}

// Comparison methods.
bool Point2D::operator==(const Point2D& other)
{
	// Return whether the x and y components are roughly equal.
	return (int)(other.x*comparisonFactor) == (int)(x*comparisonFactor) && (int)(other.y*comparisonFactor) == (int)(y*comparisonFactor);
}

bool Point2D::operator!=(const Point2D& other)
{
	return !(operator==(other));
}

// Get the distance to another.
double Point2D::getDistance(Point2D& other)
{
	double deltaX=(other.x-x), deltaY=(other.y-y);
	return sqrt(deltaX*deltaX + deltaY*deltaY);
}

// Get the distance-squared to another.
double Point2D::getDistanceSquared(Point2D& other)
{
	double deltaX=(other.x-x), deltaY=(other.y-y);
	return deltaX*deltaX + deltaY*deltaY;
}

// Manipulate and get visited.
void Point2D::setVisited(bool setTo)
{
	this->visited=setTo;
}

bool Point2D::getVisited() const
{
	return visited;
}
