#pragma once

// A list of shapes, implemented through pointers,
//handling all related memory managment.

// Include standard libraries.
#include <vector>

// A wrapper for std::vector.

class ShapeList
{
	static const unsigned int NUMBER_TO_RESERVE=5;
	public:
	ShapeList(); // Make a new shape list.
	void add(Shape * shapeToAdd); // Add a shape to the list.
	void remove(unsigned int index); // Remove.
	void clear(); // Clear.
	unsigned int getSize();
	const std::vector<Shape*>& getVector(); // Get a refrence to the vector.
	~ShapeList(); // Delete.
	
	private:
	std::vector<Shape*> shapeList; // The list.
}
