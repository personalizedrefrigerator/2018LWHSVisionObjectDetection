#pragma once

// A class to output the results of the vision.
//Henry Heino

// Libraries from this project.
#include "VisionOutput.h"

// Standard libraries.
#include <string>

class NetworkVisionOutput : public VisionOutput
{
	public:
	GenericVisionOutput();
	void setXRotation(double newXRotation);
	void setYRotation(double newYRotation);
	void setPixelSize(double pixelSize);
	void setAverageColor(Color averageColor);
	void setCenterLocation(Point2D centerLocation);
	double getXRotation();
	double getYRotation();
	double getPixelSize();
	Color getAverageColor();
	Point2D getCenterLocation();
	void outputToOther(VisionOutput& other);
	
	private:
	double currentXRotation, currentYRotation, currentPixelSize, currentAverageColor, currentCenterLocation;
};
