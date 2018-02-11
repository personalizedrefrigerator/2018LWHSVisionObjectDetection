#include "ShapeLoader.h"

// Include the serialization namespace for its functions.
#include "Serialize.h"

// Set the file name to be used for loading and saving files.
void ShapeLoader::setFileName(std::string newFileName)
{
	fileName=newFileName;
	
	// Note that the file name has been set.
	fileNameSet=true;
}

// Set the shape to be used.
void ShapeLoader::setShape(Shape * shapeToUse)
{
	currentShape=shapeToUse;
	
	// Note that the shape has been set.
	shapeSet=true;
}

// Load the shape. True on success.
bool load()
{
	// If the shape wasn't set, or the file name wasn't set, exit.
	if(!shapeSet || !fileNameSet)
	{
		return false;
	}	
	
	// Make a file input stream.
	std::ifstream fileInputStream
	
	// Open it from the current file name.
	fileInputStream.open(fileName);
	
	// If the file exists and can be read from,
	if(fileInputStream.good())
	{
		// Define strings to contain the string versions of each part of the shape.
		std::string colorString, centerString, comparisonOptionsString, edgesString, contentsString;
	
		// Read these from the lines of the file.
		std::getLine(fileInputStream, colorString);
		std::getLine(fileInputStream, centerString);
		std::getLine(fileInputStream, comparisonOptionsString);
		std::getLine(fileInputStream, edgesString);
		std::getLine(fileInputStream, contentsString);
	
		// Close the stream.
		fileInputStream.close();
		
		// Parse the serialized options.
		Color averageColor = recallSerializedColor(colorString);
		Point2D center = recallSerializedPoint2D(centerString);
		ShapeComparisonOptions comparisonOptions = recallSerializedShapeComparisonOptions(comparisonOptionsString);
		std::vector<Point2D> edges = recallSerializedVectorOfPoint2Ds(edgesString);
		std::vector<Point2D> contents = recallSerializedVectorOfPoint2Ds(contentsString);
		
		// Set values of the current shape based on these options.
		currentShape->setCenterLocation(center);
		currentShape->setAverageColor(averageColor);
		currentShape->setShapeComparisonOptions(comparisonOptions);
		currentShape->setEdges(edges);
		currentShape->setContents(contents);
		
		// Return true for success.
		return true;
	}
	else
	{
		// Note that this was unsuccessful.
		return false;
	}
}

// Save the shape.
void save()
{
	// If the shape wasn't set, or the file name wasn't set, exit.
	if(!shapeSet || !fileNameSet)
	{
		return false;
	}
	
	// Create a file output stream.
	std::ofstream fileOutput;
	
	// Open it.
	fileOutput.open(fileName);
	
	// Put the average color into the output.
	fileOutput << serializeColor(currentShape->getAverageColor()) << '\n';
	
	// Put the center location into the file output.
	fileOutput << serializePoint2D(currentShape->getCenter()) << '\n';
	
	// Put the shape comparison options into the vector.
	fileOutput << serializeShapeComparisonOptions(currentShape->getShapeComparisonOptions()) << '\n';
	
	// Put the edges into the file.
	fileOutput << serializePoint2DVector(currentShape->getEdges()) << '\n';
	
	// Put the contents into the vector.
	fileOutput << serializePoint2DVector(currentShape->getContents()) << '\n';
	
	// Close the output stream.
	fileOutput.close();
}
