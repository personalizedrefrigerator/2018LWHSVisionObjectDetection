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
	void detectAllShapes(); // Detect all possible shapes.
	void findProbableShapes(); // Find all probable shapes.
	bool findTargetAndUpdate(Shape &result, double worstMatch); // Look for target in the found shapes. Ignore if the match rating is less than worstMatch.
	void setImage(cv::Mat newImage);
	
	void setComparisonShapes(std::vector<Shape> shapesToUse); // Set the shapes to compare.
	void addComparisonShape(Shape newShape); // Add a shape to compare with.
	void clearComparisonShapes(); // Clear shapes to compare with.

	void clearFoundShapes(); // Clear the found shapes.

	// Set options related to the plane detector.
	void setPlaneDetectorOptions(PlaneDetectorOptions options);

	private: // Private members.
	std::vector<Shape> foundShapes; // The shapes found by the detector.
	std::vector<Shape> comparisonShapes; // The shapes to search for.
	
	VisitedList visited; // The list of points visited.
	PlaneDetector detector; // The plane detector.
	cv::Mat image; // The image to operate on.
};
