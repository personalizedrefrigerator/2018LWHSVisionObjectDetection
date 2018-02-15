#include "Vector3D.h"
#include <math.h>

// TODO: Add meaningful comments, completed in a rush. Z is up.

Vector3D::Vector3D(double startingX, double startingY, double startingZ)
{
	x=startingX;
	y=startingY;
	z=startingZ;
}

double Vector3D::getMagnitude()
{
	if(!magnitudeCalculated)
	{
		shadowLength=sqrt(x*x+y*y);
		magnitude=sqrt(shadowLength*shadowLength+z*z);

		magnitudeCalculated=true;
	}

	return magnitude;
}

double Vector3D::getAngle()
{
	if(thetaCalculated) // If the angle, theta, has been calculated,
	{
		return theta;
	}

	// If the magnitude has not been calculated,
	if(!magnitudeCalculated)
	{
		// Calculate it!
		getMagnitude();
	}

	// Then,
	theta=acos(shadowLength/magnitude); // Calculate theta using the "shadow" - the
					//projection of the line from start to end (the resultant) 
					//onto the plane that vector-component x lies on.
	thetaCalculated=true;

	return theta;
}

double Vector3D::getShadowAngle()
{
	if(shadowAngleCalculated)
	{
		return shadowTheta;
	}

	if(!magnitudeCalculated)
	{
		getMagnitude();
	}

	shadowTheta=acos(x/shadowLength);

	return shadowTheta;
}

double Vector3D::getX()
{
	return x;
}

double Vector3D::getY()
{
	return y;
}

double Vector3D::getZ()
{
	return z;
}

void Vector3D::setValues(double newX, double newY, double newZ)
{
	x=newX;
	y=newY;
	z=newZ;

	thetaCalculated=false;
	shadowAngleCalculated=false;
	magnitudeCalculated=false;
}

void Vector3D::setValuesFromLengthAndAngles(double magnitude, double theta, double shadowTheta)
{
	this->magnitude=magnitude;
	this->theta=theta;
	this->shadowTheta=shadowTheta;
	thetaCalculated=true;
	shadowAngleCalculated=true;
	magnitudeCalculated=true;

	shadowLength=l*cos(theta);
	x=cos(shadowTheta)*shadowLength;
	y=sin(shadowTheta)*shadowLength;
	z=sin(theta)*magnitude;
}
