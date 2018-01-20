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

double Color::operator-(Color other)
{
	short deltaR=(short)r-other.r;
	short deltaG=(short)g-other.g;
	short deltaB=(short)b-other.b;
	return sqrt(deltaR*deltaR + deltaG*deltaG + deltaB*deltaB);
}
