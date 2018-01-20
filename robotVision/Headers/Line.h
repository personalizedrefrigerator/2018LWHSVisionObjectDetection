#pragma once
#include "Point.h"
#include "Point2D.h"

// A line, used for intersections with planes and other objects.

class Line
{
	private:
	Point point1;
	Point point2;

	public:
	Line(Point point1, Point point2);
	double getSlope(char dimension, char dimensionAcross); // Get the slope of the line, across a given dimension.
	double getAngle2D(Point2D at);
	bool getHasSlope(char dimensionAcross);
};
