#pragma once

// Include opencv libraries.
#include<opencv2/opencv.hpp>

// Include self-defined libraries.
#include "Point3D.h"
#include "Point2D.h"
#include "Color.h"
#include "Line.h"

// Detect a plane and points on it.
//Henry Heino

class PlaneDetector
{
	public:
	void setImage(cv::Mat image);
	void detectPoints2D();
	void detectSignificantPoints();
	void showPlaneRegion(cv::Mat imageToUse);// TODO:Implement
	void setFocalLengths(double fX, double fY);// TODO:Implement

	// Manipulate whether a pixel is considered "visited."
	void setVisited(Point2D point, bool setTo);
	bool getVisited(Point2D point);
	void clearVisited();

	Line getSlopeOfEdge(unsigned int startIndex, unsigned int numberToConsider);// TODO:Implement

	Color getColorAt(int x, int y);
	Color getColorAt(Point2D point);
	bool isOnImage(int x, int y);
	bool isOnImage(Point2D point);

	std::vector<Point3D> getSignificantPoints();	

	~PlaneDetector();

	private:
	std::vector<Point2D> significantPoints;
	std::vector<Point2D> edgePoints2D;
	std::vector<Point2D> planePoints;
	cv::Mat image;

	// Initialize focal lengths.
	double fX=10.0, fY=10.0;

	int colorChangeThreshold=20;

	// An array storing whether any given pixel has been visited.
	bool * visited=nullptr;
	unsigned int visitedLength=0;
	unsigned int visitedByteLength=0;
};
