#include "Box.h"

// Include headers from this project.
#include "ObjectSortingContainer.h"
#include "ListHelper.h"
#include "MathHelper.h"

// Include standard libraries.
#include <sstream>
#include <iostream>
#include <math.h>

// See Box.h for the constructors.

// Get one of the box's vertical sides.
std::vector<Point2D> Box::getVerticalSide(bool side)
{
	// Pack the corners into an array.
	std::vector<Point2D>& corners = getCornersRefrence();

	// So long as there are at least 2 corners,
	if(corners.size() >= 2)
	{

		unsigned int sortableListSize = corners.size();

		std::vector< ObjectSortingContainer<Point2D> > sortedCorners;
		sortedCorners.reserve(sortableListSize);

		for(unsigned int index = 0; index < sortableListSize; index++)
		{
			Point2D& currentCorner = corners.at(index);

			sortedCorners.push_back(ObjectSortingContainer<Point2D>(currentCorner.x, &currentCorner));
		}

		// Sort the corners, greatest x to least x if side is true, otherwise, least to greatest.
		ListHelper::mergeSort<Point2D>(sortedCorners, !side);

		// Create a vector to store the result and add the points to it.
		std::vector<Point2D> result;
		
		result.push_back(Point2D(*sortedCorners.at(0).baseObject));
		result.push_back(Point2D(*sortedCorners.at(1).baseObject));

		// Return the result.
		return result;
	}


	// Otherwise, generate a vector,
	std::vector<Point2D> result;
	
	// Resize it to length 2.
	result.resize(2);
	
	// Return the result.
	return result;
}

// Set the camera's pitch.
void Box::setCameraPitch(double angle)
{
	cameraAngle = angle;
}

// Set the screen's Z position.
void Box::setScreenZ(double screenZ)
{
	this->screenZ = screenZ;
}

// Set the box's world height.
void Box::setWorldHeight(double height)
{
	this->worldHeight = height;
}

// Get the distance from a point to the camera. The point is assumed to be on the plane of the screen.
double Box::getDistanceToPointFromCamera(Point2D point)
{
	//double angleToX = getXAngleToPoint(point.x),
	//	angleToY = getYAngleToPoint(point.y);

	// Get the delta x and y to the point.
	double x = point.x - screenWidth/2,
		y = point.y - screenHeight/2;

	// Convert this into a distance.
	double distance = sqrt(x*y + y*y + screenZ*screenZ); // Assuming cameraX and Y are 0.
}

// Get the distance to the box.
double Box::getDistance()
{
	// Find the points on the side to use.
	std::vector<Point2D> side = getVerticalSide(true);
	
	// Ensure side is of length 2.
	side.resize(2);

	// Find the box-angle (radians). 
	double theta4 = boxAngleToPlane - (PI/2 - cameraAngle);
	
	// Get the line points.
	Point2D point1 = side.at(0),
		point2 = side.at(1);
	

	double distanceToPoint1 = getDistanceToPointFromCamera(point1),
		distanceToPoint2 = getDistanceToPointFromCamera(point2);
	

	// Calculate the slopes.
	double m1 = (point1.y - cameraPosition.y)/(screenZ - cameraPosition.z),
		m2 = (point2.y - cameraPosition.y)/(screenZ - cameraPosition.z);
	
		
	double deltaZ = screenZ - cameraPosition.z;
	double m1X = (point1.x - cameraPosition.x)/deltaZ;
	double m1Y = (point1.y - cameraPosition.y)/deltaZ;
	double m2X = (point2.x - cameraPosition.x)/deltaZ;
	double m2Y = (point2.y - cameraPosition.y)/deltaZ;
	
	
	double deltaSlopeX = m1X - m2X,
		deltaX = point1.x - point2.x,
		deltaSlopeY = m1Y - m2Y,
		deltaY = point1.y - point2.y;
	
	
	double projectedHeight = worldHeight*sin(theta4);
	
	
	double a, b, c;
	a = deltaSlopeX*deltaSlopeX + deltaSlopeY*deltaSlopeY;
	b = 2*(deltaSlopeY*deltaY + deltaSlopeX*deltaX);
	c = deltaX*deltaX + deltaY*deltaY - projectedHeight*projectedHeight;
	
	
	MathHelper::QuadraticResult result = MathHelper::solveQuadratic(a, b, c);
	
	// Calculate the distance.
	//double distance = projectedHeight/(m1-m2);
	double distance = result.solution2;
	
	
	if(result.solution1 < distance)
	{
		distance = result.solution1;
	}

	
	// Multiply the distance by the found conversion factor.
	distance *= conversionFactor;

	return distance;
}

// Set the screen's size.
void Box::setScreenSize(double width, double height)
{
	screenWidth = width;
	screenHeight = height;
	findCameraPosition();
}

// Calculate the camera's position.
void Box::findCameraPosition()
{
	cameraPosition.x = screenWidth / 2;
	cameraPosition.y = screenHeight / 2;
	cameraPosition.z = 0;
}

// Convert internal units objectDistanceFromScreen is assumed to start at the camera..
void Box::convertUnits(double objectDistanceFromScreen, double actualHeight, double registeredHeight)
{
	double k = actualHeight/registeredHeight;
	double l = screenZ * k;
	conversionFactor = objectDistanceFromScreen/l;
}

// Calculate the box's significant points. Overriden from Shape.
void Box::calculateSignificantPoints()
{
	Shape::calculateSignificantPoints(); // The same as calculating those for a general shape,
	
	// ... but trim the number used to 4.
	trimCorners(4);
}

// Draw oputput to an image, for debugging purposes.
void Box::drawDebugOutput(cv::Mat outputImage)
{
	Shape::drawDebugOutput(outputImage);
	
	std::stringstream distanceStream;
	distanceStream << "Distance: " << getDistance(); // Don't wory about re-calculation of corners, this is just a debug output.
	
	
	// Render the current side.
	std::vector<Point2D> side = getVerticalSide(true);
	for(unsigned int i = 0; i < side.size(); i++)
	{
		Point2D & currentPoint = side.at(i);
		// Draw a circle at the current point, cv::Scalar stores the color. 8 is the line type. 2 is the line width.
		cv::circle(outputImage, cv::Point(currentPoint.x, currentPoint.y), 5, cv::Scalar(100, 100, 200, 200), 2, 8, 0); // 8 is line type.
	}
	
	distanceStream << ", dy " << side.at(0).y - side.at(1).y;
	
	putText(outputImage, distanceStream.str(), cv::Point(center.x, center.y-50), 2, 0.75, cv::Scalar(0, 250, 100, 200));
}
