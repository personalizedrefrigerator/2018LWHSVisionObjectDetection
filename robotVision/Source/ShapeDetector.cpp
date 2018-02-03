#include "ShapeDetector.h"


// Constructor.
ShapeDetector::ShapeDetector()
{
	foundShapes.clear();
}

// Detect all shapes possible.
void ShapeDetector::detectShapes()
{
	// Clear shapes found previously and reset visited.
	foundShapes.clear();

	visited.clear();
	visited.setSize(image.cols, image.rows);


	// Give the plane detector the image.
	detector.setImage(image);


	// Initialize loop variables.
	unsigned int x, y;

	Point2D currentPoint;

	unsigned int deltaX=image.cols/40;
	unsigned int deltaY=image.rows/20;
	
	// For every pixel,
	for(x=0; x<image.cols; x+=deltaX)
	{
		for(y=x/deltaX; y<image.rows; y+=deltaY)
		{
			currentPoint.x=x;
			currentPoint.y=y;

			// If the pixel hasn't been visited.
			if(!visited.getVisited(currentPoint))
			{
				Shape currentShape;
				detector.detectPoints2D(currentPoint);
				detector.outputToShape(currentShape);
				currentShape.calculateCenterAndOkScreenSize();

				// Add the current shape to those found.
				foundShapes.push_back(currentShape);

				// Add those visited.
				visited.addVisitedItemsFromOther(detector.getVisitedList());
			}
		}
	}

}

// Look for the target in the shapes found. Ignore if match < worstMatch.
//Returns true on success.
bool ShapeDetector::findTargetAndUpdate(Shape &target, double worstMatch)
{

	// Go through all shapes found, ask the target for a comparison.
	unsigned int numberOfShapes=foundShapes.size();

	// Find at least one shape.
	if(numberOfShapes == 0)
	{
		// Give the plane detector the image.
		detector.setImage(image);

		// Find a shape.
		Shape currentShape;

		Point2D point1=target.getFirstPoint(),
			point2=target.getCenter();

		// Detect from the center.
		detector.detectPoints2D(point2);
		detector.outputToShape(currentShape);
		
		
		// Add the current shape to those found.
		foundShapes.push_back(currentShape);
		
		// Detect from the other point.
		detector.detectPoints2D(point1);
		detector.outputToShape(currentShape);
		
		
		// Add the current shape to those found.
		foundShapes.push_back(currentShape);

		numberOfShapes+=2;
	}
	

	double rating=0.0;

	// Create a variable to store the greatest rating.
	double greatestRating=worstMatch-10;

	// Create a variable to store the index of the greatest rating.
	unsigned int indexOfGreatestRating=0;

	for(unsigned int shapeIndex=0; shapeIndex<numberOfShapes; shapeIndex++)
	{
		Shape & currentShape=foundShapes.at(shapeIndex);

		rating=target.getMatchForShape(currentShape);

		// If this rating is the best so far, note this.
		if(rating >= greatestRating)
		{
			greatestRating=rating;
			indexOfGreatestRating=shapeIndex;
		}
	}

	double difference=greatestRating-worstMatch;

	// If the greatest rating was good enough,
	if(difference >= 0)
	{
		target.fromOther(foundShapes.at(indexOfGreatestRating)); // Copy from the best rated.
		return true;
	}

	// Otherwise, nothing was found.
	return false;
}

// Set the image.
void ShapeDetector::setImage(cv::Mat newImage)
{
	image=newImage;
}

// Set the plane detector's options.
void ShapeDetector::setPlaneDetectorOptions(PlaneDetectorOptions options)
{
	detector.setOptions(options);
}

// Clear the found shapes.
void ShapeDetector::clearFoundShapes()
{
	foundShapes.clear();
}
