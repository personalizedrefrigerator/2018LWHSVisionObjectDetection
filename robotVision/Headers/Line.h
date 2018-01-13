#pragma once
#include "Point3D.h"

// A line, used for intersections with planes and other objects.

class Line
{
	private:
	Point3D point1;
	Point3D point2;

	public:
	Line(Point3D point1, Point3D point2);
	double getSlope(char dimension, char dimensionAcross); // Get the slope of the line, across a given dimension.
};
