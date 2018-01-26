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

// Include math.
#include <math.h>
#define PI 3.1415926535897932384626433

// Set the plane detector's image.
void PlaneDetector::setImage(cv::Mat image)
{
	this->image=image;
}

// Run BFS, to find points that could be on the plane.
void PlaneDetector::detectPoints2D()
{
	// DFS, starting at bottom.
	std::deque<Point2D> fringe;
	//fringe.reserve(image.rows*image.cols);

	// Choose a point at the center of the screen.
	Point2D current=Point2D(image.rows/2, image.cols/2);

	// Initialize/clear arrays.
	planePoints.clear();
	edgePoints2D.clear();
	
	// Add the current to the fringe.
	fringe.push_back(current);
	planePoints.push_back(current);
	
	// Define variables.
	Point2D considering=Point2D(0, 0);
	int x, y, times=0;

	// Clear what has been visited.
	clearVisited();

	Color mainColor=getColorAt(current);

	unsigned int totalR=0;
	unsigned int totalG=0;
	unsigned int totalB=0;

	Color currentColor=Color(0, 0, 0);

	unsigned int fringeSize=1;

	// Add points to the plane.
	do
	{
		times++;
		current=fringe.back();
		fringe.pop_back();
		fringeSize-=1;
		setVisited(current, true);

		currentColor=getColorAt(current);
		totalR+=currentColor.getR();
		totalG+=currentColor.getG();
		totalB+=currentColor.getB();
		mainColor=Color(totalR/times, totalG/times, totalB/times);

		//std::cout << "START" << fringe.size() << "\n";
		for(x=-1; x<=1; x++)
		{
			for(y=-1; y<=1; y++)
			{
				if(x == 0 && y == 0)
				{
					continue;
				}
				
				considering=Point2D(current.x+x, current.y+y);

				// If it hasn't been seen already,
				if(!getVisited(considering))
				{
					setVisited(considering, true);
					//std::cout << isOnImage(considering) << "\n";
					//TODO: Make color change take direction into account.
					if(isOnImage(considering) && (getColorAt(current)-getColorAt(considering) <= colorChangeThreshold && getColorAt(current)-mainColor <= averageChangeThreshold || times < 20))
					{
						fringe.push_front(considering);
						fringeSize++;
						planePoints.push_back(considering);

						//std::cout << "ADDED " << fringe.size() << "," << considering.x << "," << considering.y << "\n";
					}
					else if(isOnImage(considering))// Otherwise, so long as on the image, it is an edge.
					{
						edgePoints2D.push_back(considering);
					}
				}
			}
		}

		//std::cout << fringe.size() << "\n";
	}
	while(fringeSize > 0);
}

// Detect points considered "significant." Where the angle between the current and the last changes more than a specified value.
void PlaneDetector::detectSignificantPoints()
{
	significantPoints.clear();

	unsigned int numberOfPixelsConsidering=15;

	double accuracy=significantPointAccuracy;

	double averageChange;
	double maxDifference;

	Line nextLine, previousLine;

	bool firstTime=true;
	double currentEdgeSlope, lastEdgeSlope;

	double angle, lastAngle;

	// Create a variable to store the number of pixels actualy
	//touching the line.
	unsigned int pixelsOnLine, pixelsOnPreviousLine;

	int maximum=edgePoints2D.size()-(int)numberOfPixelsConsidering;


	//std::cout << "Go through all of the edges, C at a time.\n";
	for(int pixelIndex=numberOfPixelsConsidering; pixelIndex < maximum; pixelIndex+=1)
	{
		// Get the slope of the current edge (the current pixel and the next
		//numberOfPixelsConsidering).
		pixelsOnPreviousLine=getSlopeOfEdge(previousLine, pixelIndex-numberOfPixelsConsidering, pixelIndex);
		pixelsOnLine=getSlopeOfEdge(nextLine, pixelIndex, numberOfPixelsConsidering);
		//nextLine.freeMemory=true; // The points in the line can be freed from memory on deconstruct.
		// Get the angle the line makes with the horizontal axis.
		angle=nextLine.getAngle2D();
		lastAngle=previousLine.getAngle2D();

		// Get the slope of the current part of the edge.
		currentEdgeSlope=angle; // TODO: If PI is undefined, #define it. PI ~= 3.1415926535898

		/*if(currentEdgeSlope > PI/2)
		{
			currentEdgeSlope=PI-currentEdgeSlope;
		}*/

		if(!firstTime)
		{
			
			if(!getIsFullEdge(pixelIndex-numberOfPixelsConsidering, pixelIndex+numberOfPixelsConsidering, 1))
			{
				continue;
			}

			if((int)(currentEdgeSlope*accuracy) != (int)(lastAngle*accuracy) && pixelsOnLine >= numberOfPixelsConsidering*1/3 && pixelsOnPreviousLine >= numberOfPixelsConsidering*1/3)
			{
				// Add the pixel to the significant points.
				significantPoints.push_back(edgePoints2D.at(pixelIndex));
			}
		}
		else
		{
			firstTime=false;
		}

		// Update the previous versions,
		//lastEdgeSlope=currentEdgeSlope;
		//previousLine=nextLine;
	}
}

// Get whether an edge is full.
bool PlaneDetector::getIsFullEdge(unsigned int start, unsigned int stop, unsigned int maxJump)
{
	bool firstTime=true;
	Point2D point, previousPoint;
	unsigned int pointIndex, deltaX, deltaY;

	for(pointIndex=0; pointIndex<edgePoints2D.size(); pointIndex++)
	{
		point=edgePoints2D.at(pointIndex);
		if(!firstTime)
		{
			deltaX=abs(point.x-previousPoint.x);
			deltaY=abs(point.y-previousPoint.y);
			if(deltaX > maxJump || deltaY > maxJump)
			{
				return false;
			}
		}
		else
		{
			firstTime=true;
		}
		previousPoint=point;
	}
	return true;
}

// Draw the detected plane and other information found onto the provided image. Provide a color image.
void PlaneDetector::showPlaneRegion(cv::Mat image)
{
	Point2D point;
	int c,
		pointIndex;

	for(pointIndex=0; pointIndex<planePoints.size(); pointIndex++)
	{
		point=planePoints.at(pointIndex);

		if(point.y < 0 || point.y >= image.rows || point.x < 0 || point.x >= image.cols)
		{
			continue;
		}

		for(c=0; c<3; c++)
		{
			image.at<unsigned char>(point.y, point.x*3+c)=205-c*50;
		}
	}

	for(pointIndex=0; pointIndex<edgePoints2D.size(); pointIndex++)
	{
		point=edgePoints2D.at(pointIndex);

		if(point.y < 0 || point.y >= image.rows || point.x < 0 || point.x >= image.cols)
		{
			continue;
		}

		for(c=0; c<3; c++)
		{
			image.at<unsigned char>(point.y, point.x*3+c)=0+(sin(pointIndex)*256);
		}
	}

	for(pointIndex=0; pointIndex<significantPoints.size(); pointIndex++)
	{
		point=significantPoints.at(pointIndex);

		if(point.y < 0 || point.y >= image.rows || point.x < 0 || point.x >= image.cols)
		{
			continue;
		}

		cv::circle(image, cv::Point(point.x, point.y), 5, cv::Scalar(0, 255, 100, 200), 2, 8, 0); // 8 is line type.
	}
}

// Note that a point was visited.
void PlaneDetector::setVisited(Point2D point, bool visited)
{
	unsigned int index=point.x+point.y*image.cols;

	if(isOnImage(point) && index<visitedLength)
	{
		this->visited.at(index)=visited;
	}
}

// Get whether a point was visited.
bool PlaneDetector::getVisited(Point2D point)
{
	unsigned int index=point.x+point.y*image.cols;

	if(isOnImage(point) && index<visitedLength)
	{
		return visited.at(index);
	}

	return true;
}

// Clear the array of visited pixels.
void PlaneDetector::clearVisited()
{
	visited.clear();

	visitedLength=image.rows*image.cols;
	visited.resize(visitedLength, false);
	//visitedByteLength=visitedLength*sizeof(bool);
}

// Check whether a point is on the image.
bool PlaneDetector::isOnImage(int x, int y)
{
	bool isOnImage=x >= 0 && y >= 0 && x < image.cols && y<image.rows;
	return isOnImage;
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

// Find the average slope of an edge. Return the number of points on the edge.
unsigned int PlaneDetector::getSlopeOfEdge(Line &output, unsigned int startIndex, unsigned int numberOfPointsToConsider)
{
	if(numberOfPointsToConsider == 0 || startIndex+numberOfPointsToConsider >= edgePoints2D.size())
	{
		output.setPoints(new Point2D(0, 0), new Point2D(0, 0));
		return 0;
	}

	unsigned int pixelsOnLine=0;
	double averagedX=0.0;
	double averagedY=0.0;

	double previousX=edgePoints2D.at(startIndex).x, previousY=edgePoints2D.at(startIndex).y;

	Point2D currentPoint;
	for(int index=startIndex+1; index<startIndex+numberOfPointsToConsider && index < edgePoints2D.size(); index++)
	{
		currentPoint=edgePoints2D.at(index);
		averagedX+=currentPoint.x-previousX;
		averagedY+=currentPoint.y-previousY;

		// TODO: Store edgePoints2D.at(index) in a seprate variable.
		previousX=currentPoint.x;
		previousY=currentPoint.y;
	}
	averagedX/=numberOfPointsToConsider;
	averagedY/=numberOfPointsToConsider;

	//auto point1= std::make_shared<Point2D>(edgePoints2D.at(startIndex).x, edgePoints2D.at(startIndex).y);
// point1.get() // this will return a raw pointer
	
	Point2D * point1=new Point2D(edgePoints2D.at(startIndex).x, edgePoints2D.at(startIndex).y);
	Point2D * point2=new Point2D(point1->x+averagedX, point1->y+averagedY);

	// Update the points on the output.
	output.setPoints(point1, point2);

	// Create variables to store the current x and y position.
	int currentX, currentY;

	// Create a variable to store the y podition of the current part of the line.
	int lineY;

	// For every pixel on the line,
	for(int index=startIndex; index<startIndex+numberOfPointsToConsider && index < edgePoints2D.size(); index++)
	{
		currentPoint=edgePoints2D.at(index);
		
		currentX=currentPoint.x;
		currentY=currentPoint.y;

		if(output.getDefinedAt('x', currentX))
		{
			lineY=output.getAt('y', 'x', currentX);

			if((int)(lineY/10) == (int)(currentY/10))
			{
				pixelsOnLine++;
			}
		}
		
	}

	return pixelsOnLine;
}

// Set the maximum color distance change for a point to still be considered a part of the object.
void PlaneDetector::setColorChangeThreshold(double setTo)
{
	colorChangeThreshold=setTo;
}

// Set the maximum color distance from.
void PlaneDetector::setAverageChangeThreshold(double setTo)
{
	averageChangeThreshold=setTo;
}

// Set the accuracy for detecting significant points.
void PlaneDetector::setSignificantPointAccuracy(double setTo)
{
	significantPointAccuracy=setTo;
}

// Set options based on a PlaneDetectorOptions object.
void PlaneDetector::setOptions(PlaneDetectorOptions options)
{
	setColorChangeThreshold(options.colorChangeThreshold);
	setAverageChangeThreshold(options.averageChangeThreshold);
	setSignificantPointAccuracy(options.significantPointAccuracy);
}

// Deconstruct the detector.
PlaneDetector::~PlaneDetector()
{
	// Free any pointers here.
}
