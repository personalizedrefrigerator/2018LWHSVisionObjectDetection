#pragma once

// A class to output the results of the vision,
//intended for use through the NetworkCommunicator
//class.

// Libraries from this project.
#include "VisionOutput.h"
#include "Color.h"
#include "Point2D.h"

// Standard libraries.
#include <string>

class GenericVisionOutput : public VisionOutput
{
	public:
	GenericVisionOutput();
	void setXRotation(double newXRotation);
	void setYRotation(double newYRotation);
	void setPixelSize(double pixelSize);
	void setAverageColor(Color averageColor);
	void setCenterLocation(Point2D centerLocation);
	void setDistance(double distance);
	double getXRotation();
	double getYRotation();
	double getPixelSize();
	double getDistance();
	Color getAverageColor();
	Point2D getCenterLocation();
	virtual void copyToOther(VisionOutput& other);
	
	private:
	double currentXRotation, currentYRotation, currentPixelSize, currentDistance;
	Color currentAverageColor=Color(0,0,0);
	Point2D currentCenterLocation;
};
