#pragma once

// Include opencv libraries.
#include<opencv2/opencv.hpp>

// Include self-defined libraries.
#include "Point3D.h"
#include "Point2D.h"
#include "Color.h"
#include "Line.h"

#include "PlaneDetectorOptions.h"

// Detect a plane and points on it.
//Henry Heino

class PlaneDetector
{
	public:
	PlaneDetector() {};
	void setImage(cv::Mat image);
	void detectPoints2D();
	void detectSignificantPoints();
	void showPlaneRegion(cv::Mat imageToUse);
	void setFocalLengths(double fX, double fY);// TODO:Implement

	// Manipulate whether a pixel is considered "visited."
	void setVisited(Point2D point, bool setTo);
	bool getVisited(Point2D point);
	void clearVisited();

	unsigned int getSlopeOfEdge(Line &output, unsigned int startIndex, unsigned int numberToConsider); // Returns the points on the line.
	bool getIsFullEdge(unsigned int start, unsigned int stop, unsigned int maxJump);

	Color getColorAt(int x, int y);
	Color getColorAt(Point2D point);
	bool isOnImage(int x, int y);
	bool isOnImage(Point2D point);

	std::vector<Point3D> getSignificantPoints();	// TODO: Implement
	
	void setColorChangeThreshold(double setTo);
	void setAverageChangeThreshold(double setTo);
	void setSignificantPointAccuracy(double setTo);

	// Set options related to the plane detector.
	void setOptions(PlaneDetectorOptions options);

	~PlaneDetector();

	private:
	std::vector<Point2D> significantPoints;
	std::vector<Point2D> edgePoints2D;
	std::vector<Point2D> planePoints;
	cv::Mat image;

	// Initialize focal lengths.
	double fX=10.0, fY=10.0;

	double colorChangeThreshold=15;
	double averageChangeThreshold=48.0;
	double significantPointAccuracy=5.0;

	// An array storing whether any given pixel has been visited.
	std::vector<bool> visited;
	unsigned int visitedLength=0;
};
