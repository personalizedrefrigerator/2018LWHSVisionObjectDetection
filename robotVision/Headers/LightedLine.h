#pragma once

// Headers from this project.
#include "Shape.h"
#include "Point2D.h"
#include "Shape.h"
#include "Detector.h"

// A line onject, for storing and detecting lines marked by periodicaly spaced lights.

class LightedLine : public Shape, public Detector
{
	public:
	LightedLine();

	void detectPoints2D(); // Detect the line from an image.
	void detectPoints2D(Point2D startingPoint); // Detect the line from an image.

	void calculateSignificantPoints(); //TODO Detect points significant to the shape (each indivdiual point of light.

	bool getFound(); // Get whether the line has been found.

	private:
	bool found = false; // Whether the line has been found.
};
