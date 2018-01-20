#pragma once

// A structure to store options for the PlaneDetector class.

struct PlaneDetectorOptions
{
	double colorChangeThreshold=15;
	double averageChangeThreshold=48.0;
	double significantPointAccuracy=3.0;
};
