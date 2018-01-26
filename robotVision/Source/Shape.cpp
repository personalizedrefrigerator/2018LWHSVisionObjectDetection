// Include the necessary libraries.
#include "Shape.h"

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

// Calculate the center of the shape.
void Shape::calculateCenter()
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
	}

	// Find the average x and y positions by dividing the accumulated sum by the number of points
	//considered.
	averageX /= this->contents.size();
	averageY /= this->contents.size();

	// Store these in the center point.
	center=Point2D((int)averageX, (int)averageY);
}

// Calculate the shape's corners.
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
	bool lastWasIncreasing, firstTime=true;
	
	// Create a variable to store the last distance-squared.
	unsigned int lastDistanceSquared;

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

			// Calculate
		}
		else
		{ // Otherwise,

			unsigned int difference=distanceSquared-lastDistanceSquared;
			if(difference >= 0)
			{
				
			}
		}

		// Update the last distance-squared.
		lastDistanceSquared=currentDistanceSquared;
	}
}
