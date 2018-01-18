#pragma once
// A class storing a simple point, and opperations related to this.
// Henry Heino

class Point2D
{
	// This is, for now, essentialy a struct, to store information about a point.
	//Add applicable methods, if needed, later.
	public:
	double x;
	double y;


	Point3D(double x, double y);

	// Get the component of the vector on the specified dimension.
	double getComponent(char componentName);

	void setVisited(bool setTo);
	bool getVisited();
	private:
	bool visited=false;
};
