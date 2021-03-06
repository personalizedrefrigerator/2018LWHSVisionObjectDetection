#pragma once

// A structure to store options for the PlaneDetector class.

struct PlaneDetectorOptions
{
	double colorChangeThreshold=25;
	double averageChangeThreshold=48.0;
	double significantPointAccuracy=3.0;

	unsigned int startingPixels=25;
	
	int pixelDeltaX=3,
	    pixelDeltaY=2;
};
