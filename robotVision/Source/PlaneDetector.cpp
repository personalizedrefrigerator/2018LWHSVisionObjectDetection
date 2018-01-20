#include "PlaneDetector.h"

// Include opencv libraries.
#include<opencv2/opencv.hpp>

// Standard libs.
#include<queue>
#include<cstdlib>

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
		currentEdgeSlope=nextLine.getAngle2D(edgePoints2D.at(pixelIndex)) % PI; // TODO: If PI is undefined, #define it. PI ~= 3.1415926535898

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

// Note that a point was visited.
void PlaneDetector::setVisited(Point2D point, bool visited)
{
	unsigned int index=point.x+point.y*image.cols;

	if(isOnImage(point) && visited != nullptr && index<visitedLength)
	{
		visited[index]=visited;
	}
}

// Get whether a point was visited.
bool PlaneDetector::getVisited(Point2D point)
{
	unsigned int index=point.x+point.y*image.cols;

	if(isOnImage(point) && visited != nullptr && index<visitedLength)
	{
		return visited[index];
	}

	return true;
}

// Clear the array of visited pixels.
void PlaneDetector::clearVisited()
{
	if(visited != nullptr)
	{
		free(visited);
	}

	visitedLength=image.rows*image.cols;

	visitedByteLength=visitedLength*sizeof(bool);

	// TODO: Check this, sizeof(bool) might be 1/3...
	visited=(bool *)malloc(visitedByteLength);

	memset(visited, false, visitedByteLength);
}

// Check whether a point is on the image.
bool PlaneDetector::isOnImage(int x, int y)
{
	bool isOnImage=x >= 0 && y >= 0 && x < image.cols && y<image.rows;
}

// Check whether a Point2D is on the image.
bool PlaneDetector::isOnImage(Point2D point)
{
	return isOnImage(point.x, point.y);
}

// Get the color at a location.
Color PlaneDetector::getColorAt(int x, int y)
{
	unsigned char * ptr=image.ptr<unsigned char>(y);
	
	// TODO: Detect the format of the image and act accordingly.
	unsigned char blue=ptr[x*3],
			green=ptr[x*3+1],
			red=ptr[x*3+1];

	return Color(red, green, blue);
}

// Get the color at a Point2D.
Color PlaneDetector::getColorAt(Point2D point)
{
	return getColorAt(point.x, point.y);
}

// Find the average slope of an edge.
Line PlaneDetector::getSlopeOfEdge(unsigned int startIndex, unsigned int numberOfPointsToConsider)
{
	if(numberOfPointsToConsider == 0 || startIndex+numberOfPointsToConsider >= edgePoints2D.size())
	{
		return Line(Point2D(0, 0), Point2D(0, 0));
	}
	double averagedX=0.0;
	double averagedY=0.0;

	double previousX=edgePoints2D.at(startIndex).x, previousY=edgePoints2D.at(startIndex).y;

	for(int index=startIndex+1; index<startIndex+numberOfPointsToConsider; index++)
	{
		averagedX+=edgePoints2D.at(index).x-previousX;
		averagedY+=edgePoints2D.at(index).y-previousY;

		// TODO: Store edgePoints2D.at(index) in a seprate variable.
		previousX=edgePoints2D.at(index).x;
		previousY=edgePoints2D.at(index).y;
	}
	averagedX/=numberOfPointsToConsider;
	averagedY/=numberOfPointsToConsider;

	Point2D point1=edgePoints2D.at(startIndex);
	Point2D point2=Point2D(point1.x+averagedX, point2.y+averagedY);

	Line result=Line(point1, point2);
	return result;
}

// Deconstruct the detector.
PlaneDetector::~PlaneDetector()
{
	if(visited != nullptr)
	{
		free(visited);
	}
}
