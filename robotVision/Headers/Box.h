#pragma once

// A class for getting information about, speciffically, a box projected into 2D space. This should have only 4 detected corners.

// Include libararies from this project.
#include "Shape.h"
#include "Line.h"
#include "Point3D.h"
#include "Point2D.h"

// Include OpenCV libraries.
#include<opencv2/opencv.hpp>

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
	
	virtual void calculateSignificantPoints();
	virtual void drawDebugOutput(cv::Mat outputImage); // Draw a representation of the shape to the given image, for debugging purposes.
	
	double getDistance(); // Get the distance to the box.
	double getDistanceToPointFromCamera(Point2D point); // Get the distance from a point to the camera.

	// Run these methods before attempting calculations.
	void setScreenZ(double screenZ); // Set the screen's Z position.
	void setScreenSize(double width, double height);
	void setWorldHeight(double height); // Set the box's world height.
	void convertUnits(double objectDistanceFromScreen, double actualHeight, double registeredHeight); // Convert inernally used units.
	void setCameraPitch(double angle); // Set the camera's forward rotation (in radians).
	void findCameraPosition();
	
	private:
	double cameraAngle=0.0;
	double worldHeight=1.0;
	double screenZ=20.0;
	//double screenWidth=0, Implemented in Shaoe,h.
	//	screenHeight=0;
	double conversionFactor = 1;
	double boxAngleToPlane = 0;
	Point3D cameraPosition;
};
