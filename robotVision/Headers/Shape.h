#pragma once

// A class to store information about general shapes.
//Henry Heino January 22.

// Include necessary standard libraries.
#include <vector>

// Include necessary other libraries.
#include "Point2D.h"


class Shape
{
	public:
	Shape();
	Shape(std::vector<Point2D> edges, std::vector<Point2D> contents);
	
	// Calculate the corners and center point.
	void calculateCenter();
	void calculateCorners()

	std::vector<Point2D> getEdges();
	std::vector<Point2D> getContents();

	private:
	std::vector<Point2D> edges;
	std::vector<Point2D> contents;

	// The center center of the shape.
	Point2D center;

	std::vector<Point2D> corners;
	bool cornersFound=false; // Store whether the corners have been searched for.

	std::vector<unsigned int> distanceSquaredToEdges; // The distance squareds to each edge-point.
}


