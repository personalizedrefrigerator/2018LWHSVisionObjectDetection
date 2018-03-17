#include "GenericVisionOutput.h"

// Construct
GenericVisionOutput::GenericVisionOutput()
{
	// Initialize fields to reasonable values.
	currentXRotation=0;
	currentYRotation=0;
	currentPixelSize=0;
	currentAverageColor=Color(0);
	currentCenterLocation=Point2D(0,0);
}

// Set the x rotation found.
void GenericVisionOutput::setXRotation(double newXRotation)
{
	currentXRotation=newXRotation;
}

// Set the found y rotation.
void GenericVisionOutput::setYRotation(double newYRotation)
{
	currentYRotation=newYRotation;
}

// Set the found pixel size.
void GenericVisionOutput::setPixelSize(double pixelSize)
{
	currentPixelSize=pixelSize;
}

// Set the found average color.
void GenericVisionOutput::setAverageColor(Color averageColor)
{
	currentAverageColor=averageColor;
}

// Set the found center location.
void GenericVisionOutput::setCenterLocation(Point2D centerLocation)
{
	currentCenterLocation=centerLocation;
}

// Set the distance to the object.
void GenericVisionOutput::setDistance(double distance)
{
	currentDistance = distance;
}

// Get the x rotation found.
double GenericVisionOutput::getXRotation()
{
	return currentXRotation;
}

// Get the current y rotation.
double GenericVisionOutput::getYRotation()
{
	return currentYRotation;
}

// Get the current found pixel size.
double GenericVisionOutput::getPixelSize()
{
	return currentPixelSize;
}

// Get the current distance to the object.
double GenericVisionOutput::getDistance()
{
	return currentDistance;
}

// Get the current average color.
Color GenericVisionOutput::getAverageColor()
{
	return currentAverageColor;
}

// Get the current center location.
Point2D GenericVisionOutput::getCenterLocation()
{
	return currentCenterLocation;
}


// Copy to another vision output.
void GenericVisionOutput::copyToOther(VisionOutput& other)
{
	other.setXRotation(currentXRotation);
	other.setYRotation(currentYRotation);
	other.setPixelSize(currentPixelSize);
	other.setAverageColor(currentAverageColor);
	other.setCenterLocation(currentCenterLocation);
	other.setDistance(currentDistance);
}
