// Include the necessary libraries.
#include "Shape.h"

#include <math.h>

// Construct the shape, taking the edges and contents.
Shape::Shape(std::vector<Point2D> edges, std::vector<Point2D> contents)
{
	// Store the edges and corners.
	this->edges=edges;
	this->contents=contents;

	// Clear the corners array.
	this->corners.clear();
}

// Construct the shape, from no data.
Shape::Shape()
{
	// Clear the arrays.
	this->edges.clear();
	this->contents.clear();
	this->corners.clear();
}

// Calculate the center of the shape and a screen size that will work when displaying the image.
void Shape::calculateCenterAndOkScreenSize()
{
	// Find the average x and y values of the shape.

	// Create variables to accumulate the sum, then to be used to find the average x and y.
	double averageX, averageY;

	// Create a variable to store the current point.
	Point2D currentPoint;

	// For every point on the shape.
	for(int pointIndex=0; pointIndex < this->contents.size(); pointIndex++)
	{
		// Store the current point.
		currentPoint=this->contents.at(pointIndex);

		// Add its x and y components to the accumulator.
		averageX+=currentPoint.x;
		averageY+=currentPoint.y;
		
		// If larger than the current screen size, update that.
		if(currentPoint.x > screenWidth)
		{
			screenWidth=currentPoint.x;
		}
		
		if(currentPoint.y > screenHeight)
		{
			screenHeight=currentPoint.y;
		}
	}

	// Find the average x and y positions by dividing the accumulated sum by the number of points
	//considered.
	averageX /= this->contents.size();
	averageY /= this->contents.size();

	// Store these in the center point.
	center=Point2D((int)averageX, (int)averageY);
}

// Calculate the shape's corners. TODO: Finish this.
void Shape::calculateCorners()
{
	// Be sure that the edges are sorte so the points touch each other. 

	// Clear the corners array.
	corners.clear();

	// Clear the distanceSquaredToEdges array.
	distanceSquaredToEdges.clear();


	// Calculate the distance-squareds from the center.
	
	// Create a variable to store the current point.
	Point2D currentPoint;

	// Create a variable to store the current distance.
	unsigned int currentDistanceSquared;

	// Create a variable to store the delta x and y between the current point and another.
	int deltaX, deltaY;

	// Create a variable to store the number of edge points for which the slope has been increasing or decreasing.
	unsigned int edgePointsWithSameIncreasing=0;

	// Create variables to store whether the distance-squared was increasing the last time,
	//and whether it is the 1st time through the loop.
	bool lastWasIncreasing, firstTime=true, secondTime=true;
	
	// Create a variable to store the last distance-squared.
	unsigned int lastDistanceSquared, lastDistanceDifference;
	
	// Keep track of the number of points 

	// For every point on the edge.
	for(int pointIndex=0; pointIndex < this->edges.size(); pointIndex++)
	{
		// Store the current point.
		currentPoint=this->edges.at(pointIndex);

		// Find the delta X and delta Y between the current point and the center.
		deltaX=currentPoint.x-center.x;
		deltaY=currentPoint.y-center.y;
		
		// Find the distance squared between the current point and the center.
		currentDistanceSquared=deltaX*deltaX + deltaY*deltaY;

		// Add this distance to an array of distance-squareds.
		distanceSquaredToEdges.push_back(currentDistanceSquared);

		// If the first time through the loop,
		if(firstTime)
		{
			// It will no longer be the first time through the loop.
			firstTime=false;
		}
		else
		{ // Otherwise,

			unsigned int difference=currentDistanceSquared-lastDistanceSquared;
			/*if(difference >= 0)
			{
				lastWasIncreasing = true;
			}*/
			
			if(!secondTime)
			{
				// If the positivity is different between
				//the current and last distance,
				if(difference < 0 ^ lastDistanceDifference < 0)
				{
					
				}
			}
			
			secondTime=false;

			// Store the last difference.
			lastDistanceDifference=difference;
		}

		// Update the last distance-squared.
		lastDistanceSquared=currentDistanceSquared;
	}
}

// Calculate the angle to the center of the shape.
void Shape::calculateAngle()
{
	angleX=atan(center.x/screenZ);
	angleY=atan(center.y/screenZ);
}

// Draw the shape.
void Shape::drawSelf(cv::Mat outputImage, unsigned int colorsPerPixel)
{
	// Create variables to store the current position in the edges, and in the contents.
	unsigned int pointIndex, colorIndex;
	
	// Create a variable to store the current point.
	Point2D currentPoint;
	
	// For every pixel in the contents.
	for(pointIndex=0; pointIndex<contents.size(); pointIndex++)
	{
		currentPoint=contents.at(pointIndex);
		
		if(currentPoint.y < 0 || currentPoint.y >= outputImage.rows || currentPoint.x < 0 || currentPoint.x >= outputImage.cols)
		{
			continue;
		}

		for(colorIndex=0; colorIndex<colorsPerPixel; colorIndex++)
		{
			outputImage.at<unsigned char>(currentPoint.y, currentPoint.x*3+colorIndex)=205-colorIndex*50;
		}
	}
	
	// For every pixel on the edges,
	for(pointIndex=0; pointIndex<edges.size(); pointIndex++)
	{
		currentPoint=edges.at(pointIndex);

		// Don't draw the pixel if it's off the screen.
		if(currentPoint.y < 0 || currentPoint.y >= outputImage.rows || currentPoint.x < 0 || currentPoint.x >= outputImage.cols)
		{
			continue;
		}

		// For the blue, green, and red components of the color.
		for(colorIndex=0; colorIndex<colorsPerPixel; colorIndex++)
		{
			outputImage.at<unsigned char>(currentPoint.y, currentPoint.x*3+colorIndex)=(sin(pointIndex)*256);
		}
	}
}

// Draw a representation of the shape, including the center point.
void Shape::drawDebugOutput(cv::Mat outputImage)
{
	// Draw the contents and edges.
	drawSelf(outputImage, 3);
	
	// Create a variable to store the index in the array of corners.
	unsigned int cornerIndex=0;

	// Create a variable to store the current corner.
	Point2D currentCorner;

	// Draw the corners.
	for(cornerIndex=0; cornerIndex < corners.size(); cornerIndex++)
	{
		currentCorner=corners.at(cornerIndex);

		// Draw a circle at the current point, cv::Scalar stores the color. 8 is the line type. 2 is the line width.
		cv::circle(image, cv::Point(currentCorner.x, currentCorner.y), 5, cv::Scalar(0, 255, 100, 200), 2, 8, 0); // 8 is line type.
	}
}

// Calculate the corners of the shape using OpenCV's corner detector.
void Shape::calculateCornersCV()
{
	// Create an empty image, assuming the screen size has been found.
	cv::Mat outputImage=cv::Mat::zeros(screenHeight, screenWidth, CV_8UC1);
	
	// Draw the shape onto an empty image.
	drawSelf(outputImage, 1);
	
	// Detect the corners.
	corners=cornerDetector->detectCorners(outputImage);
}

// Set the screen's Z position.
void Shape::setScreenZ(double screenZ)
{
	this->screenZ=screenZ;
}

// Set the corner detector.
void Shape::setCornerDetector(CornerDetector * cornerDetector)
{
	this->cornerDetector=cornerDetector;
}

// On deconstruction.
Shape::~Shape()
{
	delete cornerDetector;
}
