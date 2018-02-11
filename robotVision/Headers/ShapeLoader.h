#pragma once

// A class for loading and writing shapes to files.
//Henry Heino

// Include the standard libraries to be used.
#include <string>

class ShapeLoader
{
	public:
	void setFileName(std::string name);
	void setShape(Shape * shapeToUse);
	bool load(); // Load the shape, true on success.
	void save(); // Save the shape.
	private:
	// The file name and shape to be saved and loaded.
	std::string fileName;
	Shape * currentShape=nullptr;
	bool fileNameSet=false, shapeSet=false;
};
