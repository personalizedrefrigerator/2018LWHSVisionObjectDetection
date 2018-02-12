#pragma once

// A list of shapes, implemented through pointers,
//handling all related memory managment.

// Include libraries from this project.
#include "Shape.h"

// Include standard libraries.
#include <vector>

// A wrapper for std::vector.

class ShapeList
{
	static const unsigned int NUMBER_TO_RESERVE=5;
	public:
	ShapeList(); // Make a new shape list.
	void add(Shape * shapeToAdd); // Add a shape to the list.
	void push_back(Shape * shapeToAdd); // Add a shape to the list.
	void push_back(Shape& shapeToAdd); // Add a copy of a shape to the list.
	void remove(unsigned int index); // Remove.
	void clear(); // Clear.
	Shape*& at(unsigned int index); // Get the shape-list at an element. Return a refrence to a pointer.
	unsigned int getSize();
	unsigned int size(); // The same as getSize().
	const std::vector<Shape*>& getVector(); // Get a refrence to the vector.
	void setHandlingMemoryManagment(bool setTo); // Set whether handling memory managment.
	~ShapeList(); // Delete.
	
	private:
	bool handlingMemoryManagment=true; // Whether this list is responsable for freeing all refrences to shapes when destroyed.
	std::vector<Shape*> shapeVector; // The list.
};
