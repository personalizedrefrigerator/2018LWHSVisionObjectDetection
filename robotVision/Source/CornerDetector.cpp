// Include necessary libraries.
#include "Shape.h"
#include "Point2D.h"

// Set the shape to detect corners from.
void CornerDetector::setShape(cv::Mat shape)
{
	this->shape=shape;
}
