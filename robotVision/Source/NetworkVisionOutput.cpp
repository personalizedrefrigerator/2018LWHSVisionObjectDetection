#include "NetworkVisionOutput.h"

// Construct, with the IP address of the target,
//and the name of its network table.
NetworkVisionOutput::NetworkVisionOutput(std::string ipAddress, std::string tableName)
{
	// Create a new network communication device.
	communicator=new NetworkCommunicator(ipAddress, tableName);
}

// Set the x rotation found.
void NetworkVisionOutput::setXRotation(double newXRotation)
{
	cachedValues.setXRotation(newXRotation);
	communicator->updateValue("xRotation", newXRotation);
}

// Set the found y rotation.
void NetworkVisionOutput::setYRotation(double newYRotation)
{
	cachedValues.setYRotation(newYRotation);
	communicator->updateValue("yRotation", newYRotation);
}

// Set the found pixel size.
void NetworkVisionOutput::setPixelSize(double pixelSize)
{
	cachedValues.setPixelSize(pixelSize);
	communicator->updateValue("pixelSize", pixelSize);
}

// Set the found average color.
void NetworkVisionOutput::setAverageColor(Color averageColor)
{
	cachedValues.setAverageColor(averageColor);
	communicator->updateValue("averageColor", averageColor);
}

// Set the found center location.
void NetworkVisionOutput::setCenterLocation(Point2D centerLocation)
{
	cachedValues.setCenterLocation(centerLocation);
	communicator->updateValue("centerScreenX", centerLocation.x);
	communicator->updateValue("centerScreenY", centerLocation.y);
}

// Copy to another vision output.
void NetworkVisionOutput::copyToOther(VisionOutput& other)
{
	cachedValues.copyToOther(other);
}

// Free memory.
NetworkVisionOutput::~NetworkVisionOutput()
{
	delete communicator;
}
