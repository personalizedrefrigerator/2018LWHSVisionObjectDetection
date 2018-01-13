// The definitions of methods for the Point3D object.
// Henry Heino.

// Construct a Point3D.
Point3D::Point3D(double x, double y, double z)
{
	this->x=x;
	this->y=y;
	this->z=z;
}

// Get a component of the point.
double Point3D::getComponent(char componentName)
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
