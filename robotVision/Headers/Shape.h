#pragma once

// A class to store information about general shapes.
//Henry Heino January 22.

// Include necessary standard libraries.
#include <vector>

// Include necessary other libraries.
#include "Point2D.h"
#include "CornerDetector.h"
#include "Color.h"

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
	void calculateCorners(); // TODO: Finish implementing later.
	void calculateCornersCV(); // Find the corners of the shape, using OpenCV.
	
	void drawSelf(cv::Mat outputImage, unsigned int colorsPerPixel); // Draw a version of the shape, for corner detection, etc.
	void drawDebugOutput(cv::Mat outputImage); // Draw output, for debugging purposes.
	
	void setScreenZ(double screenZ); // Set the z position of the screen (focal length, given by OpenCV). TODO: Allow focal length to be accessed from the camera normalizer.

	std::vector<Point2D> getEdges(); // Get the shape's edges.
	std::vector<Point2D> getContents(); // Get the shape's contents.
	unsigned int getContentSize(); // Get the shape's area.
	Point2D getCenter(); // Get the center point.
	Point2D getFirstPoint(); // Get the first point.
	Color getAverageColor(); // Get the average color.

	bool isOnScreen(Point2D point); // Get whether a point is on the screen.

	// Update edges and content.
	void setEdges(std::vector<Point2D> edges); // Set the edges of the shape.
	void setContents(std::vector<Point2D> content); // Set the contents of the shape.
	void setAverageColor(Color newAverageColor); // Set the known average color of the shape.
	void setCenterLocation(Point2D newPosition); // Change the location of the center.

	void fromOther(Shape & other); // Create the current shape from another.

	void setCornerDetector(CornerDetector & cornerDetector); // Set the object used to detect corners.
	CornerDetector & getCornerDetector(); // Get the object used to detect corners.

	double getMatchForShape(Shape &other); // Get how well the other shape seems to match this shape.

	private:
	std::vector<Point2D> edges;
	std::vector<Point2D> contents;
	std::vector<Point2D> corners;
	bool cornersFound=false; // Store whether the corners have been searched for.

	// The center center of the shape.
	Point2D center;

	// The shape's average color.
	Color averageColor=Color(0,0,0);
	
	// The angle to the center of the shape.
	double angleX, angleY;
	
	// The Z position of the screen. Assume 20 units.
	double screenZ=20.0;
	
	// Information involving the screen.
	unsigned int screenWidth=0, screenHeight=0;

	std::vector<unsigned int> distanceSquaredToEdges; // The distance squareds to each edge-point.
	
	// The detector to be used to detect corners.
	CornerDetector cornerDetector=CornerDetector();
};


