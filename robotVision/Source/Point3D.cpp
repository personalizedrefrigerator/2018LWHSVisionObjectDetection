#include "Point3D.h"

// The definitions of methods for the Point3D object.
//

// Construct a Point3D.
Point3D::Point3D(double x, double y, double z)
{
	this->x=x;
	this->y=y;
	this->z=z;
}

Point3D::Point3D()
{
	x=0;
	y=0;
	z=0;
}

// Construct from another Point3D.
Point3D::Point3D(const Point3D& other)
{
	x=other.x;
	y=other.y;
	z=other.z;
}

// Assign this point to another.
Point3D& Point3D::operator=(const Point3D& other)
{
	x=other.x;
	y=other.y;
	z=other.z;
	
	return *this;
}

// Get a component of the point.
double Point3D::getComponent(char componentName) const
{
	switch(componentName)
	{
		case 'x':
			return x;
		break;
		case 'y':
			return y;
		break;
		case 'z':
			return z;
		break;
		default:
			return 0; // Return 0. The point has no components in greater than 3 dimensions.
	}
}
