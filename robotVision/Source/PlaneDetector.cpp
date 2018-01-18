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

	// Add points to the plane.
	do
	{
		current=fringe.pop_front();
		
		for(x=-1; x<=1; x++)
		{
			for(y=-1; y<=1; y++)
			{
				if(x == 0 || y == 0)
				{
					continue;
				}
				
				considering=Point2D(current.x+x, current.y+y);

				//TODO: Make color change take direction into account.
				if(isOnImage(considering) && getColorAt(current)-getColorAt(considering) >= colorChangeThreshold)
				{
					fringe.push_back(considering);
					planePoints.push_back(considering);
				}
				else // Otherwise, it is an edge.
				{
					edgePoints2D.push_back(considering);
				}
			}
		}
	}
	while(fringe.size() > 0);
}

void PlaneDetector::showPlaneRegion
