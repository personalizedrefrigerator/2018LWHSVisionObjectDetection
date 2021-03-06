#pragma once

// A class to store information about general shapes.
//January 22.

// Include necessary standard libraries.
#include <vector>

// Include necessary other libraries.
#include "Point2D.h"
#include "CornerDetector.h"
#include "Color.h"

// Include options structures.
#include "ShapeComparisonOptions.h"

// Include OpenCV libraries.
#include<opencv2/opencv.hpp>


class Shape
{
	friend class Box;
	public:
	Shape();
	Shape(std::vector<Point2D> edges, std::vector<Point2D> contents);
	Shape(Shape & other);
	~Shape();

	// Calculate the corners and center point.
	void calculateCenterAndOkScreenSize();
	void calculateAngle(unsigned int screenWidth, unsigned int screenHeight); // Calculate the angle to the center of the shape.
	void calculateCorners(double minDistanceSquared, unsigned int accuracy, double changeInAngle); // Find the shape's corners, without using OpenCV.
	void calculateCornersCV(); // Find the corners of the shape, using OpenCV.
	virtual void calculateSignificantPoints();
	void trimCorners(unsigned int newCorners); // Trim the number of corners on the shape to a new amount (i.e., keep the furthest 4).

	void drawSelf(cv::Mat outputImage, unsigned int colorsPerPixel); // Draw a version of the shape, for corner detection, etc.
	void drawComparisonDebugOutput(cv::Mat outputImage, Shape & other); // Draw debug output for the comparison of this shape to another.
	virtual void drawDebugOutput(cv::Mat outputImage); // Draw output, for debugging purposes.

	void setScreenZ(double screenZ); // Set the z position of the screen (focal length, given by OpenCV).
	void setScreenSize(double width, double height); // Set the size of the screen.

	std::vector<Point2D> getEdges(); // Get the shape's edges.
	std::vector<Point2D> getContents(); // Get the shape's contents.
	unsigned int getContentSize(); // Get the shape's area.
	unsigned int getEdgesSize(); // Get the size of the edge points.
	Point2D getCenter(); // Get the center point.
	Point2D getFirstPoint(); // Get the first point.
	Color getAverageColor(); // Get the average color.
	double getScreenArea(); // Get the estimated number of pixels on the screen.
	double getScreenZ(); // Get the z position of the screen relative to the camera.
	double getScreenWidth(); // Get the set width of the screen.
	double getScreenHeight(); // Get the set height of the screen.
	double getXAngle(); // Get the angle to the shape's center from the center of the screen, accross the x-axis. Set screen z first.
	double getYAngle(); // Get the angle to the shape's center from the screen's center, accross the y-axis. Set screen z first.
	std::vector<Point2D> getCornersCopy(); // Get a copy of the corners array.
	double getXAngleToPoint(double point); // Get the x angle to a point.
	double getYAngleToPoint(double point); // Get the y angle to a given point.
	void getCorners(std::vector<Point2D>& outputVector); // Output corners to outputVector.
	void compareAndFilterCorners(const std::vector<Point2D>& previousCorners, Point2D otherCenter); // Compare the current corners to the previous, filtering those that barely match.


	bool isOnScreen(Point2D point); // Get whether a point is on the screen.

	// Update edges and content.
	void setEdges(std::vector<Point2D> edges); // Set the edges of the shape.
	void setContents(std::vector<Point2D> content); // Set the contents of the shape.
	void setAverageColor(Color newAverageColor); // Set the known average color of the shape.
	void setCenterLocation(Point2D newPosition); // Change the location of the center.

	void fromOther(Shape & other); // Create the current shape from another.

	void setCornerDetector(CornerDetector & cornerDetector); // Set the object used to detect corners.
	void setShapeComparisonOptions(ShapeComparisonOptions newOptions); // Set the options for comparing this to another shape.


	CornerDetector & getCornerDetector(); // Get the object used to detect corners.

	virtual double getMatchForShape(Shape & other); // Get how well the other shape seems to match this shape.
	ShapeComparisonOptions& getShapeComparisonOptions(); // Get options for comparing this and another shape.

	protected:
	std::vector<Point2D>& getCornersRefrence() { return corners; }; // Get a refrence to the list of corners.

	private:
	double comparisonFunction(double input); // Run the comparison function, with input as its input.

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

	// The options for comparing this and another shape.
	ShapeComparisonOptions comparisonOptions;
};


