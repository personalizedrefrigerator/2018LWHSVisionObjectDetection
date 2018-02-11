#pragma once

// Functions relating to the serialization of objects.

// Include needed standard libraries.
#include <string>

// Include OpenCV libraries.
#include <opencv2/opencv.hpp>

// Include libraries from this project.
#include "Point2D.h"
#include "Color.h"
#include "ShapeComparisonOptions.h"

namespace Serialize
{
	// Store and recall pairs of real numbers.
	std::string std::string serializeRealPair(double x, double y);
	Point2D recallSerializedRealPair(std::string input);
	
	// Serialize and recall OpenCV sizes.
	std::string serializeSize(cv::Size input);
	cv::Size recallSerializedSize(std::string input);
	
	// Serialize and recall OpenCV matricies.
	std::string serializeMatrix(cv::Mat input);
	cv::Mat recallSerializedMatrix(std::string input);
	
	// Serialize and recall colors.
	std::string serializeColor(Color input);
	Color recallSerializedColor(std::string input);
	
	// Serialize and recall Point2Ds.
	std::string serializePoint2D(Point2D point);
	Point2D recallSerializedPoint2D(std::string input);
	
	// Serialize and recall vectors of Point2Ds.
	std::string serializePoint2DVector(std::vector<Point2D> input);
	std::vector<Point2D> recallSerializedVectorOfPoint2Ds(std::string input);
	
	// Serialize and recall shape comparison options.
	std::string serializeShapeComparisonOptions(ShapeComparisonOptions options);
	ShapeComparisonOptions recallSerializedShapeComparisonOptions(std::string input);
	
	// Other methods relating to strings.
	std::vector<std::string> split(std::string input, char splitCharacter); // Split a string into parts, separated by the splitCharacter.
	unsigned int getOccurencesOfCharacter(std::string input, char characterToFind); // Get the number of times a character occurs in a string.
};
