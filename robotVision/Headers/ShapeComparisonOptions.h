#pragma once

// A structure to store options for the Shape class, 
//for comparing its-self to other objects.
//Henry Heino.


struct ShapeComparisonOptions
{
	double colorDeltaMultiplier=1/5.0;
	double sizeDeltaMultiplier=1/10.0;
	double centerPointDeltaMultiplier=1/5.0;
	
	double sizePortion=1/3.0;
	double colorPortion=1/3.0;
	double centerDeltaPortion=1/3.0;
};
