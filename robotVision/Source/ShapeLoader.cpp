#include "ShapeLoader.h"

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

// Load the shape.
void load()
{
	// Open a file input stream.
	
}

// Save the shape.
void save()
{
	// Create a file output stream.
	std::ofstream fileOutput;
	
	// Open it.
	fileOutput.open(fileName);
	
	// 
}
