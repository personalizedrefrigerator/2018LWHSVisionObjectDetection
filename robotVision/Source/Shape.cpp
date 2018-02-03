// Include the necessary libraries.
#include "Shape.h"

#include <math.h>

#define E 2.718281828
#define PI 3.1415926535897932384626433

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

	// Create a variable to store the number of points.
	unsigned int numberOfPoints=this->contents.size(), pointIndex=0;

	// So long as there were points to consider,
	if(numberOfPoints > 0)
	{
		// Find the average x and y values of the shape.

		// Create variables to accumulate the sum, then to be used to find the average x and y.
		double averageX=0, averageY=0;

		// Create a variable to store the current point.
		Point2D currentPoint;


		// For every point on the shape.
		for(pointIndex=0; pointIndex < numberOfPoints; pointIndex++)
		{
			// Store the current point.
			currentPoint=this->contents.at(pointIndex);

			// Add its x and y components to the accumulator.
			
			// So long as the point's x and y are greater than 0.
			
			if(currentPoint.x >= 0 && currentPoint.y >= 0)
			{
				averageX+=currentPoint.x;
				averageY+=currentPoint.y;
			}
			
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
		averageX /= numberOfPoints;
		averageY /= numberOfPoints;

		// Store these in the center point.
		center=Point2D(averageX, averageY);
	}
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
void Shape::calculateAngle(unsigned int screenWidth, unsigned int screenHeight)
{
	// Find the x and y parts of the position.
	double x=center.x-screenWidth/2;
	double y=center.y-screenHeight/2;
	
	// Compute the x and y parts of the angle.
	angleX=atan(x/screenZ);
	angleY=atan(y/screenZ);
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
			outputImage.at<unsigned char>(currentPoint.y, currentPoint.x*colorsPerPixel+colorIndex)=205-colorIndex*50;
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
			outputImage.at<unsigned char>(currentPoint.y, currentPoint.x*colorsPerPixel+colorIndex)=(abs(sin(pointIndex))*256);
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
		cv::circle(outputImage, cv::Point(currentCorner.x, currentCorner.y), 5, cv::Scalar(0, 255, 100, 200), 2, 8, 0); // 8 is line type.
	}

	// Draw a circle at the center.

	// As long as the center is on the screen,
	if(isOnScreen(center))
	{
		// Draw a circle at the center point, cv::Scalar stores the color. 8 is the line type. 2 is the line width.
		cv::circle(outputImage, cv::Point(center.x, center.y), 5, cv::Scalar(255, 0, 100, 200), 2, 8, 0);
		
		calculateAngle(outputImage.cols, outputImage.rows);
		
		// Draw text indicating the size and angle.
		std::stringstream outputText;
		outputText << "Size: ";
		outputText << contents.size() << ". ";
		outputText << "ANGLE: " <<  angleX*180/PI << ", " << angleY*180/PI;
		// Font 2.
		putText(outputImage, outputText.str(), cv::Point(center.x-50, center.y), 2, 0.35, cv::Scalar(0,0,255, 200));
	}

	// If there is a first point,
	if(getContentSize() > 0)
	{
		// Get the first point.
		Point2D firstPoint=getFirstPoint();

		// As long as the first point is on the screen.
		if(isOnScreen(firstPoint))
		{
			// Draw a circle at the first point.
			cv::circle(outputImage, cv::Point(firstPoint.x, firstPoint.y), 5, cv::Scalar(255, 100, 255, 200), 2, 8, 0);
		}
	}
}

// Get the first point on the shape.
Point2D Shape::getFirstPoint()
{
	if(contents.size() > 0)
	{
		return contents.at(0);
	}
	else
	{
		return Point2D(0,0);
	}
}

// Get whether a point could be on the screen.
bool Shape::isOnScreen(Point2D point)
{
	return point.x >= 0 && point.y >= 0 && point.x < screenWidth && point.y < screenHeight;
}

// Calculate the corners of the shape using OpenCV's corner detector.
void Shape::calculateCornersCV()
{
	// Create an empty image, assuming the screen size has been found.
	cv::Mat outputImage=cv::Mat::zeros(screenHeight, screenWidth, CV_8UC3);
	
	// Draw the shape onto an empty image.
	drawSelf(outputImage, 3);
	
	// Detect the corners.
	corners=cornerDetector.detectCorners(outputImage);
}

// Get how well the shape matches another.
double Shape::getMatchForShape(Shape & other)
{
	double result=0.0;
	
	// Base how well it matches on the distance from the center,
	Point2D otherCenter=other.getCenter();
	Point2D myCenter=getCenter();

	double deltaX=otherCenter.x-myCenter.x;
	double deltaY=otherCenter.y-myCenter.y;

	// Compute the distance squared between the two.
	double distanceSquaredToCenter=deltaX*deltaX+deltaY*deltaY;

	double averageColorDifference=other.getAverageColor()-getAverageColor();

	double sizeDifference=getContentSize() - other.getContentSize();
	sizeDifference*=sizeDifference;

	// Average the results of the sigmoid function on the distance to the center, the size difference, and the average color difference.
	result+=1/(pow(E, -E + distanceSquaredToCenter/30)+1);
	result+=1/(pow(E, -E + averageColorDifference/30)+1);
	result+=1/(pow(E, -E + sizeDifference/30)+1);
	result/=3;

	return result;
}

// Create the shape from another.
void Shape::fromOther(Shape & other)
{
	setAverageColor(other.getAverageColor());
	setEdges(other.getEdges());
	setContents(other.getContents());
	setCenterLocation(other.getCenter());
}

// Get the shape's edges.
std::vector<Point2D> Shape::getEdges()
{
	return edges;
}

// Get the shape's contents.
std::vector<Point2D> Shape::getContents()
{
	return contents;
}

// Get the center point.
Point2D Shape::getCenter()
{
	return center;
}

// Get the average color.
Color Shape::getAverageColor()
{
	return averageColor;
}

// Get the corner detector.
CornerDetector & Shape::getCornerDetector()
{
	return this->cornerDetector;
}

// Get the shape's area.
unsigned int Shape::getContentSize()
{
	return contents.size();
}

// Set the edges and contents.
void Shape::setEdges(std::vector<Point2D> edges)
{
	this->edges=edges;
}

void Shape::setContents(std::vector<Point2D> content)
{
	this->contents=content;
}

// Set the shape's average color.
void Shape::setAverageColor(Color newAverageColor)
{
	averageColor=newAverageColor;
}

// Set the center point's location.
void Shape::setCenterLocation(Point2D newPosition)
{
	center=newPosition;
}

// Set the screen's Z position.
void Shape::setScreenZ(double screenZ)
{
	this->screenZ=screenZ;
}

// Set the corner detector.
void Shape::setCornerDetector(CornerDetector &cornerDetector)
{
	this->cornerDetector=cornerDetector;
}

// On deconstruction.
Shape::~Shape()
{
	// Free pointers
}
