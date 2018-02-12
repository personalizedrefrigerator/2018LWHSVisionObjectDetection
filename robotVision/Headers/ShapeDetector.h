#pragma once

// Henry Heino. A class for detecting shapes, dealing with object tracking, etc.

// Include classes part of this project.
#include "Shape.h"
#include "PlaneDetector.h"
#include "VisitedList.h"
#include "ShapeList.h"

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
	
	void setComparisonShapes(ShapeList * newComparisonShapeList); // Set the comparison shape list. The client is now responsable for memory managment of this.
	void addComparisonShape(Shape newShape); // Add a shape to compare with.
	void addComparisonShape(Shape * newShape); // Add a pointer to a shape to compare with. DANGER: THIS SHAPE WILL BE DELETED WHEN THIS OBJECT IS DELETED!
	void clearComparisonShapes(); // Clear shapes to compare with.

	void clearFoundShapes(); // Clear the found shapes.
	
	ShapeList& getFoundShapes(); // Get the shapes found.
	ShapeList& getComparisonShapes(); // Get the comparison shapes.

	// Set options related to the plane detector.
	void setPlaneDetectorOptions(PlaneDetectorOptions options);
	
	~ShapeDetector(); // Free memory.

	private: // Private members.
	ShapeList foundShapes; // The shapes found by the detector.
	ShapeList * comparisonShapes; // The shapes to search for.
	bool responsableForComparisonShapes=true;
	
	VisitedList visited; // The list of points visited.
	PlaneDetector detector; // The shape detector.
	cv::Mat image; // The image to operate on.
};
