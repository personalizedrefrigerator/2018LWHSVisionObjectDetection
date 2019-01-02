package org.usfirst.frc.team5827.robot;

/**
 *  The output from the vision program.
 *  
 * @author 
 *
 */
public class VisionOutput
{
	private double angleToCurrentObject = 0.0;
	private double currentObjectScreenSize = 0.0;
	
	// Get the angle to the current object.
	public double getAngleToObject()
	{
		return angleToCurrentObject;
	}

	// Get the size of the object on the screen.
	public double getObjectScreenSize()
	{
		return currentObjectScreenSize;
	}

	// Get the distance to the object.
	public double getDistanceToObject()
	{
		return 0;
	}
	
	// Set the angle to the object on the screen.
	public void setAngleToObject(double angle)
	{
		angleToCurrentObject = angle;
	}

	// Set the known size of the object on the screen.
	public void setObjectScreenSize(double size)
	{
		currentObjectScreenSize = size;
	}
}
