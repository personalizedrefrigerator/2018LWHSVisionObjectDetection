#pragma once

// A class representating the cubes on the field, to be detected by the detector.

// Imports from this project.
#include "Box.h"

class PowerCube : public Box
{
	public:
	PowerCube();
	
	virtual double getMatchForShape(Shape & other);
};
