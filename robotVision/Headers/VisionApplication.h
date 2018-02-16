#pragma once

// A vision application class,
//the main vision application.

// Standard libs.
// None.

// Libraries from this program.
#include "Shape.h"
#include "ShapeList.h"
#include "VisionOutput.h"
#include "VisionInputParameters.h"
#include "ShapeDetector.h"

// Include OpenCV libraries.
#include <opencv2/opencv.hpp>

class VisionApplication
{
	public:
	VisionApplication(); // Construct.
	void runFrame(cv::Mat image, VisionOutput & dataOutput, VisionInputParameters & options); // Run a single part of the loop.
	
	void setShowDebugOutput(bool setDebug); // Set whether this class should show debugging output.
						// e.g. Modifying the input image to show shapes currently being tracked.
	
	bool loadDefaultShapes(); // Load the comparison shapes.
	
	private:
	void findShapes(cv::Mat image); // Find shapes in the input image
	bool showDebugOutput=false; // Whether the input image to runFrame should be modified, for debugging.
	bool trackingObjects=false;
	
	bool definedPreviousCorners=false;
	
	Shape * currentShape=new Shape();
	Shape trackingShape;
	
	Point2D previousCenter;
	
	std::vector<Point2D> previousCorners;
	
	ShapeList foundShapes; // The list of shapes found by the application.
	ShapeList shapesToCompare;
	
	ShapeDetector detector; // The shape detector.
	ShapeDetector tracker; // The shape tracker.
};
