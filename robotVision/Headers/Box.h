#pragma once

// A class for getting information about, speciffically, a box projected into 2D space.

// Include libararies from this project.
#include "Shape.h"
#include "Line.h"

// A box. Takes a list of corners.
class Box : public Shape
{
	public:
	// Define constructors.
	Box(Shape & startingShape) : Shape(startingShape) {}; // Define the box based on a Shape object.
	Box(double cameraPitch, Shape & startingShape) : Shape(startingShape), cameraAngle(cameraPitch) {}; // Define the box based on the camera's pitch and the starting shape.
	Box(double cameraPitch) : cameraAngle(cameraPitch) {}; // Define the box based on just the camera's angle.
	Box() {}; // Define the box with no arguments.
	
	Line getVerticalSide(bool side); // Get one of the vertical sides of the box. False is left, true is right.
	
	double getDistance(); // Get the distance to the box.
	
	void setScreenZ(double screenZ); // Set the screen's Z position.
	void setCameraPitch(double angle); // Set the camera's forward rotation.
	
	private:
	double cameraAngle=0.0;
}
