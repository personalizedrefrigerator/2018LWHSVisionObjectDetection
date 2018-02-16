#include "ShapeDetector.h"

#include <iostream>

// Constructor.
ShapeDetector::ShapeDetector()
{
	foundShapes.clear();
	
	// Create the comparison shape list.
	comparisonShapes=new ShapeList();
}

// Detect all shapes possible.
void ShapeDetector::detectAllShapes()
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

	unsigned int deltaX=image.cols/4;
	unsigned int deltaY=image.rows/4;
	
	// For every pixel,
	for(x=0; x<image.cols; x+=deltaX)
	{
		for(y=x % 5; y<image.rows; y+=deltaY)
		{
			currentPoint.x=x;
			currentPoint.y=y;

			// If the pixel hasn't been visited.
			if(!visited.getVisited(currentPoint))
			{
				Shape * currentShape=new Shape();
				detector.detectPoints2D(currentPoint);
				detector.outputToShape(*currentShape);
				currentShape->calculateCenterAndOkScreenSize();

				// Add the current shape to those found.
				foundShapes.push_back(currentShape);

				// Add those visited.
				visited.addVisitedItemsFromOther(detector.getVisitedList());
			}
		}
	}

}

// Find possible other shapes, based on a given. Add these to the list of found shapes.
void ShapeDetector::findProbableShapes()
{
	clearFoundShapes();
	
	// Create a variable to store the number of shapes to compare with.
	unsigned int numberOfComparisonShapes = comparisonShapes->size();

	// Create a variable to store the index in the shapes to compare with.
	unsigned int indexInShapesToComapreWith = 0;
	
	
	// Give the plane detector the image.
	detector.setImage(image);
	
	// Create a variable to store the current, lastframe shape.
	Shape* currentLastframeShape;
	
	// Create variables to store information related to the shape from the last frame.
	Point2D firstPointOfLastShape,
		centerOfLastShape;
	
	for(indexInShapesToComapreWith = 0; indexInShapesToComapreWith < numberOfComparisonShapes; indexInShapesToComapreWith++)
	{
		// Get the shape at the index to compare with.
		currentLastframeShape = comparisonShapes->at(indexInShapesToComapreWith);


		// Find points related to that shape
		// Find a shape. A NEW shape.
		Shape currentShape1, currentShape2;


		// Get points on the shape, to be used to find possible other shapes.
		firstPointOfLastShape = currentLastframeShape->getFirstPoint();
		centerOfLastShape = currentLastframeShape->getCenter();


		// Detect from the center.
		detector.detectPoints2D(centerOfLastShape);
		detector.outputToShape(currentShape1);
		
		// Add the current shape to those found.
		foundShapes.push_back(currentShape1);
		
		
		// Detect from the other point.
		detector.detectPoints2D(firstPointOfLastShape);
		detector.outputToShape(currentShape2);
		
		// Add the current shape to those found.
		foundShapes.push_back(currentShape2);

	}
}

// Look for the target in the shapes found. Ignore if match < worstMatch.
//Returns true on success.
bool ShapeDetector::findTargetAndUpdate(Shape &result, double worstMatch)
{

	// Go through all shapes found, ask the target for a comparison.
	unsigned int numberOfShapes=foundShapes.size();

	// Find at least one shape.
	if(numberOfShapes == 0)
	{
		// Find probable other shapes wanted by the client.
		findProbableShapes();
	}
	
	numberOfShapes=foundShapes.size();

	double rating=0.0;

	// Create a variable to store the greatest rating.
	double greatestRating=worstMatch-10;

	// Create a pointer to point to the current shape comparing to other shapes.
	Shape* currentComparisonShape;
	
	// Create a pointer to point to the current shape found by the detector.
	Shape* currentDetectorShape;

	// Create a variable to store the index of the greatest rating.
	unsigned int indexOfGreatestRating=0;
	
	// The index in the shpes to compare with.
	unsigned int indexInComparisonShapes=0;
	unsigned int indexOfGreatestComparisonShape=0;
	
	// Create a variable to store the number of shapes to compare with.
	unsigned int numberOfComparisonShapes=comparisonShapes->size();

	// For every shape found by the shape detector.
	for(unsigned int shapeIndex = 0; shapeIndex<numberOfShapes; shapeIndex++)
	{
		currentDetectorShape = foundShapes.at(shapeIndex);
		
		// For every shape in those to compare the found shape with.
		for(indexInComparisonShapes = 0; indexInComparisonShapes < numberOfComparisonShapes; indexInComparisonShapes++)
		{
			currentComparisonShape = comparisonShapes->at(indexInComparisonShapes);

			rating = currentComparisonShape->getMatchForShape(*currentDetectorShape);

			// If this rating is the best so far, note this.
			if(rating > greatestRating && currentDetectorShape->getContentSize() > 0)
			{
				greatestRating=rating;
				indexOfGreatestRating=shapeIndex;
				indexOfGreatestComparisonShape=indexInComparisonShapes;
			}
		}
	}
	//std::cout << "Shapes found: "<<numberOfShapes << "\n";
	//std::cout << "Greatest " << greatestRating << "\n";

	// If the greatest rating was good enough,
	if(greatestRating >= worstMatch)
	{
		mostRecentComparisonShape=comparisonShapes->at(indexOfGreatestComparisonShape);
		result.fromOther(*foundShapes.at(indexOfGreatestRating)); // Copy from the best rated.
		return true;
	}

	// Otherwise, nothing was found.
	return false;
}

// Set the comparison shape list. The client is now responsable for memory managment of this.
void ShapeDetector::setComparisonShapes(ShapeList * newComparisonShapeList)
{
	// If managing comparisonShapes,
	if(responsableForComparisonShapes)
	{
		std::cout << "\n FREE comparisonShapes.";
		delete comparisonShapes;
		std::cout << " DONE.";
	}
	
	// Note that the client is now responsable for managing the comparison shapes.
	responsableForComparisonShapes=false;
	
	// Re-assign the pointer.
	comparisonShapes=newComparisonShapeList;
}

// Add a shape to compare with.
void ShapeDetector::addComparisonShape(Shape newShape)
{
	comparisonShapes->push_back(newShape);
}

// Add a pointer to a shape to compare with (DANGER this shape WILL be deleted when
//this object is deleted).
void ShapeDetector::addComparisonShape(Shape * shape)
{
	comparisonShapes->push_back(shape);
}

// Clear the shapes to compare with.
void ShapeDetector::clearComparisonShapes()
{
	comparisonShapes->clear();
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

// Get the found shapes list.
ShapeList& ShapeDetector::getFoundShapes()
{
	return foundShapes;
}

// Get the comparison shapes list.
ShapeList& ShapeDetector::getComparisonShapes()
{
	return *comparisonShapes;
}

// Return the shape most recently compared to another and matched.
Shape& ShapeDetector::getLastComparedComparisonShape()
{
	return *mostRecentComparisonShape;
}

// Free memory.
ShapeDetector::~ShapeDetector()
{
	// If managing comparisonShapes,
	if(responsableForComparisonShapes)
	{
		std::cout << "\n FREE comparisonShapes (in deconstructor).";
		delete comparisonShapes;
		std::cout << " DONE.";
	}
}
