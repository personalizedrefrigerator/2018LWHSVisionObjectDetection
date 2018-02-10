#include "ShapeList.h"

// Initialize the list.
ShapeList::ShapeList()
{
	// Make the vector.
	shapeVector=std::vector<Shape *>(NUMBER_TO_RESERVE);
}

// Add a new shape to the vector.
void ShapeList::add(Shape * newShape)
{
	shapeVector.push_back(newShape);
}

// Remove something at an index in the vector. Delete it.
void ShapeList::remove(unsigned int index)
{
	Shape * currentShape=shapeVector.at(index);
	shapeVector.remove(index);
	delete currentShape;
}

// Clear the list.
void ShapeList::clear()
{
	Shape * current;
	for(unsigned int currentIndex=0; currentIndex<shapeVector.size(); currentIndex++)
	{
		current=shapeVector.at(currentIndex);
		
		// Free the memory.
		delete current;
	}
	
	// Clear the vector.
	shapeVector.clear();
}

// Get the size of the list.
unsigned int ShapeList::getSize()
{
	return shapeVector.size();
}

// Get the list.
const std::vector<Shape *>& ShapeList::getVector()
{
	return shapeVector;
}

// Deconstruct.
ShapeList::~ShapeList()
{
	// Free memory.
	clear();
}
