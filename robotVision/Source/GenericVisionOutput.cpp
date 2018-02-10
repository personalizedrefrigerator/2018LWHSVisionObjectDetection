#include "GenericVisionOutput.h"

// Construct
GenericVision::GenericVision()
{
	// Initialize fields to reasonable values.
	currentXRotation=0;
	currentYRotation=0;
	currentPixelSize=0;
	currentAverageColor=0;
	currentCenterLocation=0;
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
	currentCemterLocation=centerLocation;
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

// Get the current average color.
Color GenericVisionOutput::getAverageColor()
{
	return currentAverageColor;
}

// Get the current center location.
Point2D GenericVisionOutput::getCenterLocation()
{
	return currentCenerLocation;
}


// Copy to another vision output.
void GenericVisionOutput::outputToOther(VisionOutput& other)
{
	other.setXRotation(currentXRotation);
	other.setYRotation(currentYRotation);
	other.setPixelSize(currentPixelSize);
	other.setAverageColor(currentAverageColor);
	other.setCenterLocation(currentCenterLocation);
}
