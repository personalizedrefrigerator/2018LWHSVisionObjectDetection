#include "ShapeList.h"

#include <iostream>

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

// Push a new shape to the end of the vector (the same as add).
void ShapeList::push_back(Shape * newShape)
{
	add(newShape);
}

// Push a copy of a shape into the array. Be careful with this.
void ShapeList::push_back(Shape& newLocalShape)
{
	Shape * newShape=new Shape();
	newShape->fromOther(newLocalShape);
	add(newShape);
}

// Remove something at an index in the vector. Delete it.
void ShapeList::remove(unsigned int index)
{
	// Get the shape, then remove it from the vector.
	Shape * currentShape=shapeVector.at(index);
	shapeVector.erase(shapeVector.begin()+index);
	
	// If handling memory managment and the shape isn't null,
	if(handlingMemoryManagment && currentShape != nullptr && currentShape != 0)
	{
		std::cout << "\nFree at index " << index;
		// Free the memory.
		delete currentShape;
	}
}

// Clear the list.
void ShapeList::clear()
{
	Shape * current;
	for(unsigned int currentIndex=0; currentIndex<shapeVector.size(); currentIndex++)
	{
		current=shapeVector.at(currentIndex);
		
		// If dealing with memory managment and the pointer isn't null,
		if(handlingMemoryManagment && current != nullptr && current != 0)
		{
			// Free the memory.
			delete current;
		}
	}
	
	// Clear the vector.
	shapeVector.clear();
}

// Set whether handling memory managment.
void ShapeList::setHandlingMemoryManagment(bool setTo)
{
	handlingMemoryManagment=setTo;
}

// Get the size of the list.
unsigned int ShapeList::getSize()
{
	return shapeVector.size();
}

// Get the size of the list, the same as ShapeList::getSize().
unsigned int ShapeList::size()
{
	return getSize();
}

// Get an element at a location.
Shape*& ShapeList::at(unsigned int index)
{
	return shapeVector.at(index);
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
