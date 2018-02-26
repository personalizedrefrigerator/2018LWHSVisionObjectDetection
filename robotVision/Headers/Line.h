#pragma once
#include "Point.h"
#include "Point2D.h"

// A line, used for intersections with planes and other objects.

class Line
{
	private:
	Point * point1=nullptr;
	Point * point2=nullptr;

	public:
	Line();
	Line(Point * point1, Point * point2);
	double getSlope(char dimension, char dimensionAcross); // Get the slope of the line, across a given dimension.
	void setPoints(Point * point1, Point * point2);
	double getAngle2D();
	bool hasSlope(char dimensionAcross);

	// Get the line at a specified point.
	int getAt(char dimension1, char dimension2, int location);
	bool getDefinedAt(char dimension, int location);
	
	// Get versions of the individual points.
	const Point& getPoint1();
	const Point& getPoint2();
 
	~Line();
};
