#pragma once
#include "Point.h"
// A class storing a simple point, and opperations related to this.
// Henry Heino

class Point2D : public Point
{
	// This is, for now, essentialy a struct, to store information about a point.
	//Add applicable methods, if needed, later.
	public:
	double x;
	double y;


	Point2D(double x, double y);
	Point2D(const Point2D&);
	Point2D() {};

	// Get the component of the vector on the specified dimension.
	double getComponent(char componentName);

	void setVisited(bool setTo);
	bool getVisited();
	private:
	bool visited=false;
};
