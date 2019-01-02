/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package org.usfirst.frc.team5827.robot;

import com.ctre.phoenix.motorcontrol.can.WPI_TalonSRX;

import edu.wpi.first.wpilibj.IterativeRobot;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.smartdashboard.SendableChooser;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the IterativeRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the build.properties file in the
 * project.
 */
public class Robot extends IterativeRobot {
	private static final float limitingK = .40f; // 
	private static final String kDefaultAuto = "Default";
	private static final String kCustomAuto = "My Auto";
	private String m_autoSelected;
	private SendableChooser<String> m_chooser = new SendableChooser<>();
	private AutonomousManager autoManager; // Manages the currently selected autonomous program. Initialized in autonomousInit.

	Joystick joy;
	WPI_TalonSRX motor1;
	WPI_TalonSRX motor2;
	WPI_TalonSRX motor3;
	WPI_TalonSRX motor4;
	/**
	 * This function is run when the robot is first started up and should be
	 * used for any initialization code.
	 */
	@Override
	public void robotInit() {
		m_chooser.addDefault("Default Auto", kDefaultAuto);
		m_chooser.addObject("My Auto", kCustomAuto);
		SmartDashboard.putData("Auto choices", m_chooser);
		motor1 = new WPI_TalonSRX(1);
		motor2 = new WPI_TalonSRX(2);
		motor3 = new WPI_TalonSRX(3);
		motor4 = new WPI_TalonSRX(4);
		joy = new Joystick(0);
		
	}

	/**
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * getString line to get the auto name from the text box below the Gyro
	 *
	 * <p>You can add additional auto modes by adding additional comparisons to
	 * the switch structure below with additional strings. If using the
	 * SendableChooser make sure to add them to the chooser code above as well.
	 * 
	 * The selected autonomous program is initialized in this method.
	 */
	@Override
	public void autonomousInit() {
		m_autoSelected = m_chooser.getSelected();
		// autoSelected = SmartDashboard.getString("Auto Selector",
		// defaultAuto);
		System.out.println("Auto selected: " + m_autoSelected);
		
		// Init selected autonomous.
		switch(m_autoSelected)
		{
			// IF vision autonomous is selected,
			case kCustomAuto:
				autoManager = new VisionAuto();
				break;
				
			default: // Debugging: Select Vision auto anyways.
				autoManager = new VisionAuto();
				break;
		}
	}

	/**
	 * This function is called periodically during autonomous.
	 */
	@Override
	public void autonomousPeriodic() {
		switch (m_autoSelected) {
			case kCustomAuto:
				autoManager.autonomousPeriodic();
				break;
				
			default:                                                                                     
				break;
		}
	}

	/**
	 * Filter the input from the joystick,
	 * maps to [0.0, 1.0] for a given input.
	 */
	protected double mapJoystickInput(double input)
	{
		double output = Math.pow(input,2) * Math.signum(input) * limitingK;
		
		return output;
	}
	
	/**
	 * Gets the filtered output from a joystick.
	 */
	protected double getFilteredAxisValue(int axisIndex)
	{
		return mapJoystickInput(joy.getRawAxis(axisIndex));
	}
	
	//public double get
	
	/**
	 * This function is called periodically during operator control.
	 */
	@Override
	public void teleopPeriodic() {
			double pow = joy.getRawAxis(3) - joy.getRawAxis(2);
			double mappedpow = mapJoystickInput(pow);
			double turn = mapJoystickInput(joy.getRawAxis(4))*1.2;
			
			motor1.set(mappedpow + turn);
			motor2.set(mappedpow + turn);
			motor3.set(-mappedpow + turn);
			motor4.set(-mappedpow + turn);
			
			
			/*
			motor1.set(getFilteredAxisValue(5));
			motor2.set(getFilteredAxisValue(5));
			motor6.set(getFilteredAxisValue(5));
			motor3.set(-getFilteredAxisValue(1));
			motor4.set(-getFilteredAxisValue(1));
			motor5.set(-getFilteredAxisValue(1));
			*/
	}
	
	/**
	 * This function is called periodically during test mode.
	 */
	@Override
	public void testPeriodic() {
	}
}
