#pragma once

// Include headers from this project.
#include "PlaneDetectorOptions.h"

// Input parameters for the vision system.

struct VisionInputParameters
{
	double focalLengthX=100.0;
	double focalLengthY=100.0;
	
	double worstMatchRating=0.23; // The worst a shape can be rated, compared to another, and still be considered the same.
	
	PlaneDetectorOptions surfaceDetectionOptions; // Options for a plane detector, the object that detects shapes.
};
