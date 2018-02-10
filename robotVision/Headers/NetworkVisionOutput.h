#pragma once

// A class to output the results of the vision application over the network.
//Henry Heino

// Libraries from this project.
#include "VisionOutput.h"
#include "NetworkCommunicator.h"

// Standard libraries.
#include <string>

class NetworkVisionOutput : public VisionOutput
{
	public:
	NetworkVisionOutput(std::string ipAddress, std::string tableName);
	void setXRotation(double newXRotation);
	void setYRotation(double newYRotation);
	void setPixelSize(double pixelSize);
	void setAverageColor(Color averageColor);
	void setCenterLocation(Point2D centerLocation);
	void outputToOther(VisionOutput& other);
	~NetworkVisionOutput();
	
	private:
	NetworkCommunicator * communicator;
	GenericVisionOutput cachedValues;
};
