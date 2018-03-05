#pragma once

// Include hdaders from this project.
#include "Color.h"
#include "Point2D.h"
#include "VisitedList.h"

// Include openCV libraries.
#include<opencv2/opencv.hpp>

// A base class for all detectors.

class Detector
{
	public:
	virtual void detectPoints2D() = 0; // All detectors should be able to detect objects.
	virtual void detectPoints2D(Point2D startingPoint) = 0; // Detect the points on the image, starting at a soecific starting point.

	inline Color getColorAt(int x, int y); // Get the color at a point..
	inline Color getColorAt(Point2D point); // Get the color at a point.

	// Set the image and get whether a point is on the image.
	inline void setImage(cv::Mat image);
	inline bool isOnImage(Point2D point);
	inline bool isOnImage(int x, int y);

	// Manipulate whether a pixel is considered "visited."
	inline void setVisited(Point2D point, bool setTo);
	inline bool getVisited(Point2D point);
	inline VisitedList& getVisitedList();
	inline void clearVisited();

	protected:
	VisitedList visited; // The list of visited points. Be sure to call setVisited(width, height) after getting an image.
	cv::Mat image;
};

// Set the detector's image.
void Detector::setImage(cv::Mat image)
{
	this->image=image;
}

// Note that a point was visited.
void Detector::setVisited(Point2D point, bool isVisited)
{
	this->visited.setVisited(point, isVisited);
}

// Clear the array of visited pixels.
void Detector::clearVisited()
{
	visited.clear();
	visited.setSize(image.cols, image.rows);
}

// Get whether a point was visited.
bool Detector::getVisited(Point2D point)
{
	return visited.getVisited(point);
}

// Get the color at a point on the stored image.
Color Detector::getColorAt(int x, int y)
{
	unsigned char * ptr=image.ptr<unsigned char>(y);
	
	// TODO: Detect the format (e.g. HSV, RGB, BGR) of the image and act accordingly.
	unsigned char blue=ptr[x*3],
			green=ptr[x*3+1],
			red=ptr[x*3+1];

	return Color(red, green, blue);
}


// Get the color at a Point2D.
Color Detector::getColorAt(Point2D point)
{
	return getColorAt(point.x, point.y);
}

// Get the visited list.
VisitedList& Detector::getVisitedList()
{
	return visited;
}

// Check whether a point is on the image.
bool Detector::isOnImage(int x, int y)
{
	bool isOnImage=x >= 0 && y >= 0 && x < image.cols && y<image.rows;
	return isOnImage;
}

// Check whether a Point2D is on the image.
bool Detector::isOnImage(Point2D point)
{
	return isOnImage(point.x, point.y);
}

