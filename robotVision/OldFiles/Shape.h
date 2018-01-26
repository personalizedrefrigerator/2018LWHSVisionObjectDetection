#pragma once
#include "Point3D.h"
#include "Line.h"

// A base class for all shapes. This class is old and is kept for use if needed.
virtual class Shape
{
	public:

	// Define methods all that extend from shape must implement.
	virtual Point3D getCollisionWithLine(Line line) = 0;
	virtual Point3D getNearestPointOnShape(Point3D startingPoint) = 0;
	virtual Line getNormalAt(Point3D pointOnShape) = 0;
};
