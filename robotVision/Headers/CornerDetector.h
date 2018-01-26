#pragma once
// A class wrapping functions for finding the corners of an object.
//Henry Heino.

// Include necessary standard libraries.
#include <vector>

// Include necessary other libraries.
#include "Shape.h"
#include "Point2D.h"

// Include OpenCV headers.
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>

class CornerDetector
{
	public:
	void setShape(cv::Mat shape);
	void detectCorners();

	std::vector<Point2D> getCorners();

	private:
	cv::Mat currentShape;
	std::vector<Point2D> corners;
}
