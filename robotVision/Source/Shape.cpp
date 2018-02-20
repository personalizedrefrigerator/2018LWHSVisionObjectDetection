// Include the necessary libraries.
#include "Shape.h"
#include "VisitedList.h"
#include "ListHelper.h"
#include "ObjectSortingContainer.h"

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

// Calculate the shape's corners, wioth a minimum distance between the corners of minDistanceSquared. Accuracy is the number of times a corner must be seen to be considered a corner. TODO: Test this.
void Shape::calculateCorners(double minDistanceSquared, unsigned int accuracy)
{
	// Be sure that the edges are sorte so the points touch each other. 

	// Clear the corners array.
	corners.clear();

	
	// Create a variable to store the current point.
	Point2D currentPoint;

	// Create a variable to store the current angle.
	double theta=0.0;
	
	// Create a variable storing how much to increment theta with every jump.
	double deltaTheta=0.1;
	
	// Create variables for the slope and intercepts of the lines.
	double b, m; // y=mx+b form.
	
	// Create a variable to store the current index in points.
	unsigned int currentPointIndex;
	
	// Create a variable to store the number of points to loop through - so edges.size() isn't repeatedly called.
	unsigned int numberOfPoints = edges.size();
	
	// Create variables to store the projected x and y parts of the position.
	double projectedX, projectedY;
	
	// Create a variable to store the smallest x or y and a variable to store the greatest.
	double smallestX=0.0;
	double greatest=0.0;
	bool smallestXFound=false;
	bool greatestFound=false;
	
	// Create variables to store the index of the greatest and smallest points.
	unsigned int greatestIndex, smallestIndex;
	
	// Create variables to store the point at the greatest and smallest comparison value.
	Point2D pointAtSmallest, pointAtGreatest;
	
	// Create a variable to store the current comparison factor.
	double currentComparisonFactor=0.0;
	
	// Create a visited list. 
	std::vector<unsigned short> visited;
	
	visited.resize(numberOfPoints, 0);
	
	// For every angle,
	for(theta = 0.1; theta <= 2*PI; theta+=deltaTheta)
	{
		// Set m to tan(theta) because tan(theta) = o / a = rise / run of the slope triangle with an angle theta.
		m = tan(theta);
		
		// Find b from y=m(x-xS)+yS form, where m is tan(theta). xS is the center's x position. yS is the center's y position.
		b = -center.x*m + center.y;
		
		smallestXFound=false;
		greatestFound=false;
		
		// Project all points onto the line.
		for(currentPointIndex = 0; currentPointIndex < numberOfPoints; currentPointIndex++)
		{
			// Store the current point.
			currentPoint = edges.at(currentPointIndex);
			
			// Find the projected x and y.
			projectedX = (m*currentPoint.y + b*m - currentPoint.x) / (m*m + 1); // Found by setting y2 = (-1/m)(x+xS)+yS equal to y=mx+b and solving.
			projectedY = m*projectedX + b; // Substitute projectedX into y=mx+b.
			
			// Set the comparison factor to the x value.
			currentComparisonFactor = projectedX;
			
			// If the smallest, note this.
			if(currentComparisonFactor <= smallestX || !smallestXFound)
			{
				// The smallest has been found.
				smallestXFound=true;
				
				// Update the smallest.
				smallestX=currentComparisonFactor;
				
				// Update the point at the smallest.
				pointAtSmallest=currentPoint;
				
				// Update the index.
				smallestIndex=currentPointIndex;
			}
			
			// If the greatest, note this.
			if(currentComparisonFactor >= greatest || !greatestFound)
			{
				// The smallest has been found.
				greatestFound=true;
				
				// Update the smallest.
				greatest=currentComparisonFactor;
				
				// Update the point at the smallest.
				pointAtGreatest=currentPoint;
				
				// Update the index.
				greatestIndex=currentPointIndex;
			}
		}
		
		// So long as seen a given number of times before,
		if(visited.at(smallestIndex) == accuracy)
		{
			// Add the point at the smallest and the point at the greatest to the corners.
			corners.push_back(pointAtSmallest);
		}
		
		// So long as seen a given number of times before,
		if(visited.at(greatestIndex) == accuracy)
		{
			// Add the point at the smallest and the point at the greatest to the corners.
			corners.push_back(pointAtGreatest);
		}
		
		// Note that all were visited another time.
		visited.at(smallestIndex)++;
		visited.at(greatestIndex)++;
	}
	
	// Create a variable to store the number of corners.
	unsigned int numberOfCorners=corners.size();
	
	// Create a list to store the points to be removed.
	std::vector<bool> toRemove;
	toRemove.resize(numberOfCorners, false);
	
	Point2D currentCorner, otherCorner;
	
	unsigned int currentIndex, otherIndex;
	
	// Create a variable to store the distance between the current and another point.
	double distanceSquared;
	
	// Create a variable to store the number of corners to remove.
	unsigned int cornersToRemove=0;
	
	// Create variables to store the distances to the center.
	double currentDistanceSquaredToCenter=0, otherDistanceSquaredToCenter=0;
	
	// For every corner.
	for(currentIndex = 0; currentIndex < numberOfCorners; currentIndex++)
	{
		// So long as this corner isn't to be removed,
		if(!toRemove.at(currentIndex))
		{
			// Store the current corner.
			currentCorner=corners.at(currentIndex);
			
			// Find its distance to the center.
			currentDistanceSquaredToCenter=currentCorner.getDistanceSquared(center);
		
			// For every other corner,
			for(otherIndex=0; otherIndex < numberOfCorners; otherIndex++)
			{
				// So long as the corner isn't to be removed.
				if(!toRemove.at(otherIndex) && otherIndex != currentIndex)
				{
					// Store the other corner.
					otherCorner=corners.at(otherIndex);
					
					// Find the other's distance-squared to the center.
					otherDistanceSquaredToCenter=otherCorner.getDistanceSquared(center);
					
					// Calculate the distance squared.
					distanceSquared=otherCorner.getDistanceSquared(currentCorner);
					
					// If the distance is less than the min distance,
					if(distanceSquared < minDistanceSquared)
					{
						// If the current if further from the center than the other.
						if(currentDistanceSquaredToCenter > otherDistanceSquaredToCenter)
						{
							// Set the corner to be removed.
							toRemove.at(otherIndex) = true;
							cornersToRemove++;
						}
						else // Otherwise, set the current to be removed and break.
						{
							toRemove.at(currentIndex) = true;
							cornersToRemove++;
							
							// This corner will be removed! No need to continue comparing it to others.
							break;
						}
					}
				}
			}
		}
	}
	
	// Remove the corners that were to be removed.
	
	std::vector<Point2D> newCorners;
	newCorners.reserve(numberOfCorners-cornersToRemove);
	
	// For all corners,
	for(currentIndex = 0; currentIndex < numberOfCorners; currentIndex++)
	{
		// If not to be removed,
		//add it to the result.
		if(!toRemove.at(currentIndex))
		{
			newCorners.push_back(corners.at(currentIndex));
		}
	}
	
	
	// Set the corners to the new corners.
	corners=newCorners;
}

// Trim the total number of corners down to a specific amount.
void Shape::trimCorners(unsigned int numberOfNewCorners)
{
	// Create a list to store the sorted corners
	std::vector< ObjectSortingContainer<Point2D> > newCornersList;
	
	// Resize the list.
	newCornersList.reserve(corners.size());
	
	// Create a variable to store the current point's distance to the center.
	double distanceToCenter;
	
	// Pack the corners into the list.
	for(unsigned int index=0; index < corners.size(); index++)
	{
		Point2D& currentCorner=corners.at(index);
		
		distanceToCenter=center.getDistanceSquared(currentCorner);
		
		newCornersList.push_back(ObjectSortingContainer<Point2D>(distanceToCenter, &corners.at(index)));
	}
	
	// Sort the corners, greatest distance to smallest distance.
	ListHelper::mergeSort<Point2D>(newCornersList, false);
	
	std::vector<Point2D> newCorners;
	newCorners.resize(numberOfNewCorners);
	
	// Unpack the corners from the sorted list.
	for(unsigned int index=0; index<numberOfNewCorners; index++)
	{
		newCorners.at(index)=*newCornersList.at(index).baseObject;
	}
	
	// Update corners.
	corners=newCorners;
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
			outputImage.at<unsigned char>(currentPoint.y, currentPoint.x*colorsPerPixel+colorIndex)=colorIndex*50;
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
			outputImage.at<unsigned char>(currentPoint.y, currentPoint.x*colorsPerPixel+colorIndex)=200;
		}
	}
}

// Draw a representation of the comparison of the shape to another,
void Shape::drawComparisonDebugOutput(cv::Mat outputImage, Shape & other)
{
	// TODO: Implement.
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

		std::stringstream numberToS;
		numberToS << cornerIndex;

		// Draw a circle at the current point, cv::Scalar stores the color. 8 is the line type. 2 is the line width.
		cv::circle(outputImage, cv::Point(currentCorner.x, currentCorner.y), 5, cv::Scalar(0, 255, 100, 200), 2, 8, 0); // 8 is line type.
		putText(outputImage, numberToS.str(), cv::Point(currentCorner.x, currentCorner.y), 2, 0.5, cv::Scalar(0,0,0, 255));
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
		//outputText << "Size: ";
		//outputText << contents.size() << ". ";
		//outputText << "ANGLE: " <<  angleX*180/PI << ", " << angleY*180/PI;
		outputText << (int)averageColor.getR() << "," << (int)averageColor.getG() << ", " << (int)averageColor.getB();
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

void Shape::compareAndFilterCorners(const std::vector<Point2D>& previousCorners, Point2D otherCenter)
{
	Point2D currentCorner;
	Point2D currentOtherCorner;
	
	double maxDistance=otherCenter.getDistance(center)*3;
	
	std::vector<Point2D> newCorners;
	
	int i;
	
	// For every corner.
	for(i=0; i < corners.size() && i < previousCorners.size(); i++)
	{
		currentCorner=corners.at(i);
		currentOtherCorner=previousCorners.at(i);
		
		if(currentCorner.getDistance(currentOtherCorner) < maxDistance)
		{
			newCorners.push_back(currentCorner);
		}
	}
	
	corners=newCorners;
}

// Output the corners to a given vector. Run findcorners first.
void Shape::getCorners(std::vector<Point2D>& outputVector)
{
	// Resize the output to the length of the corner vector.
	outputVector.resize(corners.size());
	
	// For every corner.
	for(int i=0; i < corners.size(); i++)
	{
		// Add the corner to the output.
		outputVector.push_back(corners.at(i));
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

// Run the comparison function, for comparing the current shape to another.
double Shape::comparisonFunction(double input)
{
	// The result is a transformed sigmoid function.
	double result=1/(pow(E, -E + input)+1);
	
	return result;
}

// Get how well the shape matches another.
double Shape::getMatchForShape(Shape &other)
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
	result+=comparisonOptions.sizePortion * comparisonFunction(distanceSquaredToCenter*comparisonOptions.sizeDeltaMultiplier);
	result+=comparisonOptions.colorPortion * comparisonFunction(averageColorDifference*comparisonOptions.colorDeltaMultiplier);
	result+=comparisonOptions.centerDeltaPortion * comparisonFunction(sizeDifference*comparisonOptions.centerPointDeltaMultiplier);

	return result;
}

// Create the shape from another.
void Shape::fromOther(Shape & other)
{
	setAverageColor(other.getAverageColor());
	setEdges(other.getEdges());
	setContents(other.getContents());
	setCenterLocation(other.getCenter());
	
	setShapeComparisonOptions(other.getShapeComparisonOptions());
}

// Get the options used to compare this shape to another.
ShapeComparisonOptions& Shape::getShapeComparisonOptions()
{
	return comparisonOptions;
}

// Set the options used for comparing shapes.
void Shape::setShapeComparisonOptions(ShapeComparisonOptions newOptions)
{
	comparisonOptions=newOptions;
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

// Get the shape's x rotation.
double Shape::getXAngle()
{
	return angleX;
}

// Get the shape's y rotation.
double Shape::getYAngle()
{
	return angleY;
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
