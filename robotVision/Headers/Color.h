#pragma once

//Henry Heino, a class for storing and abstracting colors.

class Color
{
	public:

	// Define operators.
	bool operator<(Color other);
	bool operator>(Color other);
	double operator-(Color other);

	Color(unsigned char r, unsigned char g, unsigned char b);
	Color(unsigned char grayscaleColor);
	
	int getColor();	
	enum {RED, GREEN, YELLOW, BLUE, GRAY, WHITE, BLACK};
	
	bool getColorIsLight();
	
	// Define access to r, g, and b when needed.
	unsigned char getGray();
	private:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char gray;

	unsigned char brightThreshold=200;
	bool isLight;
	bool isLightDefined=false;
};
