package org.usfirst.frc.team5827.robot;

public class VisionAuto implements AutonomousManager
{
	private VisionCommunicator communicator;
	
	public VisionAuto()
	{
		System.out.println("Starting Vision Auto.");
		communicator = new VisionCommunicator();
	}
	
	@Override
	public void autonomousPeriodic()
	{
		
	}
	
	@Override
	public void disable()
	{
		communicator.stop();
	}
}
