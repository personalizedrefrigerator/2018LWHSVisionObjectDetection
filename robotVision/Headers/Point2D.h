#pragma once
#include "Point.h"

#include <math.h>

// A class storing a simple point, and opperations related to this.

class Point2D : public Point
{
	private:
	// Comparison factors (for comparing doubles).
	const double comparisonFactor = 1000;

	// This is, for now, essentialy a struct, to store information about a point.
	//Add applicable methods, if needed, later.
	public:
	double x;
	double y;


	Point2D(double x, double y);
	Point2D(const Point2D&);
	Point2D(const Point&);
	Point2D& operator=(const Point2D& other);
	Point2D() {};
	
	bool operator!=(const Point2D& other);
	bool operator==(const Point2D& other);

	// Get the component of the vector on the specified dimension.
	double getComponent(char componentName) const;

	void setVisited(bool setTo);
	bool getVisited() const;
	
	virtual double getDistance(Point2D& other);
	double getDistanceSquared(Point2D& other);
	private:
	bool visited=false;
};
