#pragma once
// A class storing a simple point, and opperations related to this.
// Henry Heino

class Point3D : public Point
{
	// This is, for now, essentialy a struct, to store information about a point.
	//Add applicable methods, if needed, later.
	public:
	double x;
	double y;
	double z;

	Point3D(double x, double y, double z);

	// Get the component of the vector on the specified dimension.
	double getComponent(char componentName);
};
