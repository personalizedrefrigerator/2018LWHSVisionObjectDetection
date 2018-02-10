#pragma once

// A vision application class,
//the main vision application.

// Standard libs.
// None.

// Libraries from this program.
#include "Shape.h"
#include "ShapeList.h"
#include "VisionOutput.h"

// Include OpenCV libraries.
#include <opencv2/opencv.hpp>

class VisionApplication
{
	public:
	void runFrame(cv::Mat image, VisionOutput & dataOutput); // Run a single part of the loop.
	
	void setShowDebugOutput(bool setDebug); // Set whether this class should show debugging output.
						// e.g. Modifying the input image to show shapes that are
						// being
	
	private:
	void addFoundShape(Shape * newShape); // Add a shape.
	void removeFoundShape(unsigned int index); // Remove a shape, at an index.
	void clearFoundShapes();
	
	bool showDebugOutput=false;
	
	NetworkCommunicator networkCommunicator; // A variable to communicate with other parts of the robot.
	ShapeList foundShapes; // The list of shapes found by the application.
	
	ShapeDetector detector; // A shape detector, to detect individual shapes.
}
