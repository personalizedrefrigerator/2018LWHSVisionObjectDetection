#pragma once

// A class for manipulating and accessing Vectors in 3 dimensional space.

class Vector3D
{
	public:
	Vector3D(double x, double y, double z); // Construct the vector.

	double getMagnitude();
	double getAngle();
	double getShadowAngle();
	double getX();
	double getY();
	double getZ();

	void setValues(double x, double y, double z);
	void setValuesFromLengthAndAngles(double magnitude, double angle1, double shadowAngle);

	private:
	double x, y, z, theta, magnitude, shadowLength, shadowTheta;
	bool thetaCalculated=false, shadowAngleCalculated=false, magnitudeCalculated=false;
};
