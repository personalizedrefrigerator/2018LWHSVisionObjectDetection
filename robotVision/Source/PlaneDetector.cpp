#include "PlaneDetector.h"

// Include opencv libraries.
#include<opencv2/opencv.hpp>

// Standard libs.
#include<queue>

// Include self-defined libraries.
#include "Point3D.h"
#include "Point2D.h"
#include "Color.h"

// Set the plane detector's image.
void PlaneDetector::setImage(cv::Mat image)
{
	this->image=image;
}

// Run BFS, to find points that could be on the plane.
void PlaneDetector::detectPoints2D()
{
	// BFS, starting at bottom.
	std::queue<Point2D> fringe;

	// Choose a point at the very bottom.
	Point2D current=Point2D(image.rows-1, image.cols/2);

	// Initialize/clear arrays.
	planePoints.clear();
	edgePoints2D.clear();
	
	// Add the current to the fringe.
	fringe.push_back(current);
	planePoints.push_back(current);
	
	// Define variables.
	Point2D considering;
	int x, y;

	// Clear what has been visited.
	clearVisited();

	// Add points to the plane.
	do
	{
		current=fringe.pop_front();
		setVisited(current, true);
		
		for(x=-1; x<=1; x++)
		{
			for(y=-1; y<=1; y++)
			{
				if(x == 0 || y == 0)
				{
					continue;
				}
				
				considering=Point2D(current.x+x, current.y+y);

				// If it hasn't been seen already,
				if(!getVisited(considering))
				{
					//TODO: Make color change take direction into account.
					if(isOnImage(considering) && getColorAt(current)-getColorAt(considering) >= colorChangeThreshold)
					{
						fringe.push_back(considering);
						planePoints.push_back(considering);
					}
					else if(isOnImage(considering))// Otherwise, so long as on the image, it is an edge.
					{
						edgePoints2D.push_back(considering);
					}
				}
			}
		}
	}
	while(fringe.size() > 0);
}

// Detect points considered "significant." Where the angle between the current and the last changes more than a specified value.
void PlaneDetector::detectSignificantPoints()
{
	significantPoints.clear();

	unsigned int numberOfPixelsConsidering=7;

	double accuracy=3.0;

	double averageChange;
	double maxDifference;

	Line previousLine, nextLine;

	bool firstTime=true;
	double currentEdgeSlope, lastEdgeSlope;



	// Go through all of the edges, C at a time.
	for(int pixelIndex=0; pixelIndex < edgePoints2D.size(); pixelIndex++)
	{
		nextLine=getSlopeOfEdge(pixelIndex, numberOfPixelsConsidering);

		// Get the slope of the current part of the edge.
		currentEdgeSlope=nextLine.getAngleFromHorizontal() % PI; // TODO: If PI is undefined, #define it. PI ~= 3.1415926535898

		if(currentEdgeSlope > PI/2)
		{
			currentEdgeSlope=PI-currentEdgeSlope;
		}

		if(!firstTime)
		{
			firstTime=false;

			if((int)(currentEdgeSlope*accuracy) != (int)(lastEdgeSlope*accuracy))
			{
				// Add the pixel to the significant points.
				significantPoints.push_back(edgePoints2D.at(pixelIndex));
			}
		}

		// Update the previous versions,
		lastEdgeSlope=currentEdgeSlope;
		previousLine=nextLine;
	}
}
