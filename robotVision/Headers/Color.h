#pragma once

// Include Vector3D.
#include "Vector3D.h"

//A class for storing and abstracting colors.

class Color
{
	public:

	// Define operators.
	bool operator<(Color other);
	bool operator>(Color other);
	double operator-(Color other);
	Color operator/(double other);
	Color operator+(Color other);
	void operator+=(Color other);

	Color(unsigned char r, unsigned char g, unsigned char b);
	Color(unsigned char grayscaleColor);
	
	int getColor();	
	enum {RED, GREEN, YELLOW, BLUE, GRAY, WHITE, BLACK};
	
	double getColorAngle(); // Get the angle the red, green, and blue components of a 3D vector make.
	double getColorShadowAngle();
	
	bool getColorIsLight();
	
	Vector3D& getVector(); // Changing the vector does not change the color.
	
	// Define access to r, g, and b when needed.
	unsigned char getGray();
	unsigned char getR();
	unsigned char getG();
	unsigned char getB();
	private:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char gray;
	
	Vector3D innerVector=Vector3D(0,0,0);

	unsigned char brightThreshold=200;
	bool isLight;
	bool isLightDefined=false;
};
