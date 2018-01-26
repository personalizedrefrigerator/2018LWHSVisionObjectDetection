#pragma once

// The definitions for methods describing a plane.

// Construct a plane, using constants.
Plane::Plane(double xMultiplier, double yMultiplier, double zMultiplier, double constant)
{
	this->a=xMultiplier;
	this->b=yMultiplier;
	this->c=zMultiplier;
	this->d=constant;
}







