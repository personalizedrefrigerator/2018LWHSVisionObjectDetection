#include "Color.h"

#include <math.h>

Color::Color(unsigned char r, unsigned char g, unsigned char b)
{
	this->r=r;
	this->b=b;
	this->g=g;
}

Color::Color(unsigned char gray)
{
	this->r=gray;
	this->g=gray;
	this->b=gray;
}


// TODO: Finish implementation.
int Color::getColor()
{
	if(r > g && r > b)
	{
		if(b < r-100 && g < r-100)
		{
			return RED;
		}
	}

	if(r == g && g == b)
	{
		return GRAY;
	}
}


// Get red, green, and blue components of the color.
unsigned char Color::getR()
{
	return r;
}

unsigned char Color::getG()
{
	return g;
}

unsigned char Color::getB()
{
	return b;
}

double Color::operator-(Color other)
{
	unsigned int deltaR=(unsigned int)r-other.r;
	unsigned int deltaG=(unsigned int)g-other.g;
	unsigned int deltaB=(unsigned int)b-other.b;
	return sqrt(deltaR*deltaR + deltaG*deltaG + deltaB*deltaB);
}

Color Color::operator/(double divideBy)
{
	unsigned char newRed, newGreen, newBlue;
	newRed=(unsigned char)(r/divideBy);
	newGreen=(unsigned char)(g/divideBy);
	newBlue=(unsigned char)(b/divideBy);
	
	return Color(newRed, newGreen, newBlue);
}

Color Color::operator+(Color sumWith)
{
	unsigned char newRed, newGreen, newBlue;
	newRed=(unsigned char)(r + sumWith.getR());
	newGreen=(unsigned char)(g + sumWith.getG());
	newBlue=(unsigned char)(b + sumWith.getB());
	
	return Color(newRed, newGreen, newBlue);
}

void Color::operator+=(Color sumWith)
{
	r+=sumWith.getR();
	g+=sumWith.getG();
	b+=sumWith.getB();
}
