#pragma once

// Henry Heino. A class for detecting shapes, dealing with object tracking, etc.

// Include classes part of this project.
#include "Shape.h"
#include "PlaneDetector.h"
#include "VisitedList.h"

// Standard libraries.
#include <vector>

class ShapeDetector
{
	public: // Public members.
	ShapeDetector(); // Constructor.
	void detectShapes(); // Detect all possible shapes.
	bool findTargetAndUpdate(Shape &searchFor, double worstMatch); // Look for target in the found shapes. Ignore if the match rating is less than worstMatch.
	void setImage(cv::Mat newImage);

	void clearFoundShapes(); // Clear the found shapes.

	// Set options related to the plane detector.
	void setPlaneDetectorOptions(PlaneDetectorOptions options);

	private: // Private members.
	std::vector<Shape> foundShapes;
	VisitedList visited;
	PlaneDetector detector;
	cv::Mat image;
};
