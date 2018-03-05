#pragma once

#include "Shape.h"

// A line onject, for storing and detecting lines marked by periodicaly spaced lights.

class LightedLine : public Shape
{
	public:
	LightedLine();

	void detect(); // Detect the line from an image.

	virtual void calculateSignificantPoints() = 0; //TODO Detect points significant to the shape (each indivdiual point of light.

	bool getFound(); // Get whether the line has been found.

	private:
	bool found = false; // Whether the line has been found.
};
