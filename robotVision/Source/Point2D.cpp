#include "Point2D.h"
// The definitions of methods for the Point2D object.
// Henry Heino.

// Construct a Point3D.
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

// Get a component of the point.
double Point2D::getComponent(char componentName)
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

// Get the distance to another.
double Point2D::getDistance(Point2D& other)
{
	double deltaX=(other.x-x), deltaY=(other.y-y);
	return sqrt(deltaX*deltaX + deltaY*deltaY);
}

// Manipulate and get visited.
void Point2D::setVisited(bool setTo)
{
	this->visited=setTo;
}

bool Point2D::getVisited()
{
	return visited;
}
