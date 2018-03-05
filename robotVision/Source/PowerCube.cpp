#include "PowerCube.h"
#include "Color.h"

PowerCube::PowerCube()
{
	// Set the average color.
	setAverageColor(Color(200, 200, 0));
	
	// Set comparison options.
	ShapeComparisonOptions& options=Shape::getShapeComparisonOptions();
	options.sizePortion=0.0;
	options.colorPortion=1.00;
	options.centerDeltaPortion=0.0;
}

// Compare with another shape.
double PowerCube::getMatchForShape(Shape & other)
{
	// Get the match, not based on size.
	double match = Shape::getMatchForShape(other);
	
	match *= 1;
	
	double sizePart = (double) other.getContentSize() / (400.0*400);
	
	if(sizePart > 1.0)
	{
		sizePart = 1.0;
	}
	
	// Increase the match, to reflect the size of the shape.
	match += sizePart;
	match /= 2.0;
	
	return match;
}
