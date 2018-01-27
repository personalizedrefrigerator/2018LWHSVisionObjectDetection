#pragma once

// A class to store information about general shapes.
//Henry Heino January 22.

// Include necessary standard libraries.
#include <vector>

// Include necessary other libraries.
#include "Point2D.h"
#include "CornerDetector.h"

// Include OpenCV libraries.
#include<opencv2/opencv.hpp>

class Shape
{
	public:
	Shape();
	Shape(std::vector<Point2D> edges, std::vector<Point2D> contents);
	~Shape();
	
	// Calculate the corners and center point.
	void calculateCenterAndOkScreenSize();
	void calculateAngle(); // Calculate the angle to the center of the shape.
	void calculateCorners(); // Finish implementing later.
	void calculateCornersCV(); 
	
	void drawSelf(cv::Mat outputImage, unsigned int colorsPerPixel);
	
	void setScreenZ(double screenZ);

	std::vector<Point2D> getEdges();
	std::vector<Point2D> getContents();
	
	void setCornerDetector(CornerDetector cornerDetector);

	private:
	std::vector<Point2D> edges;
	std::vector<Point2D> contents;
	std::vector<Point2D> corners;
	bool cornersFound=false; // Store whether the corners have been searched for.

	// The center center of the shape.
	Point2D center;
	
	// The angle to the center of the shape.
	double angleX, angleY;
	
	// The Z position of the screen. Assume 20 units.
	double screenZ=20.0;
	
	// Information involving the screen.
	unsigned int screenWidth=0, screenHeight=0;

	std::vector<unsigned int> distanceSquaredToEdges; // The distance squareds to each edge-point.
	
	// The detector to be used to detect corners.
	CornerDetector * cornerDetector=new CornerDetector();
}


