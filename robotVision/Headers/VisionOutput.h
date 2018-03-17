#pragma once

// Include classes used as arguments for this.
#include "Color.h"
#include "Point2D.h"

// A virtual base class for all classes attempting to get output from the VisionApplication.

class VisionOutput
{
	public:
	virtual void setXRotation(double xRotation) = 0;
	virtual void setYRotation(double yRotation) = 0;
	virtual void setPixelSize(double pixelSize) = 0;
	virtual void setAverageColor(Color averageColor) = 0;
	virtual void setCenterLocation(Point2D centerLocation) = 0;
	virtual void setDistance(double distance) = 0;
	virtual void copyToOther(VisionOutput& other) = 0;
};
