#pragma once
// A plane, implementing Shape. The form ax+by+cz=d is used to represent the plane.
//Henry Heino.
#include "Shape.h"
#include "Point3D.h"
#include "Line.h"

class Plane : public Shape // Inherit all public members of the shape.
{
	public:
	Plane(double x, double y, double z);
	inline Point3D getColisionWithLine(Line lineToCheck);
	Point3D getNearestPointOnShape(Point3D firstPoint);
	Line getNormalAt(Point3D findNormalAt);
	private:
	// Constants describing the plane.
	double a, b, c, d;
};
