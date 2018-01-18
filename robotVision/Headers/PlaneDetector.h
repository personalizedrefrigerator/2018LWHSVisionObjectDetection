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
	void showPlaneRegion(cv::Mat imageToUse);
	void setFocalLengths(double fX, double fY);

	Line getSlopeOfEdge(unsigned int startIndex, unsigned int numberToConsider);

	Color getColorAt(int x, int y);
	Color getColorAt(Point2D point);
	bool isOnImage(int x, int y);
	bool isOnImage(Point2D point);

	std::vector<Point3D> getSignificantPoints();	

	private:
	std::vector<Point3D> significantPoints;
	std::vector<Point2D> edgePoints2D;
	std::vector<Point2D> planePoints;
	cv::Mat image;

	// Initialize focal lengths.
	double fX=10.0, fY=10.0;

	int colorChangeThreshold=20;
};
