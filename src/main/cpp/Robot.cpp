/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/XboxController.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <iostream>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <ctre/Phoenix.h>
#include <frc/DigitalInput.h>
#include "Sequences.h"

class Robot : public frc::TimedRobot
{
	// This refernence contains the instance of the current sequence class
	Sequence *currentSequence;
	// Victor controllers classes used to drive the robot
	WPI_VictorSPX victorSPX1{1}, victorSPX2{2}, victorSPX3{3}, victorSPX4{4};

	// Define MotorControllerGroup objects using references
	frc::MotorControllerGroup m_leftMotors{victorSPX2, victorSPX3}, m_rightMotors{victorSPX1, victorSPX4};
	frc::DifferentialDrive m_robotDrive{m_leftMotors, m_rightMotors};

	// Xbox pad class
	frc::XboxController pad{0};

	// Variable speedMulFactor is the value by which the input to the motors is multiplied float speedMulFactor = 0.4;
	double speedMulFactor = 1.0;

	const float dPadSpeed = 0.5;
	bool squareInputs = false;

public:
	void RobotInit()
	{
		// Prepare and config the controllers
		victorSPX1.Set(ControlMode::PercentOutput, 0);
		victorSPX2.Set(ControlMode::PercentOutput, 0);
		victorSPX3.Set(ControlMode::PercentOutput, 0);
		victorSPX4.Set(ControlMode::PercentOutput, 0);

		victorSPX1.ConfigFactoryDefault();
		victorSPX2.ConfigFactoryDefault();
		victorSPX3.ConfigFactoryDefault();
		victorSPX4.ConfigFactoryDefault();

		m_rightMotors.SetInverted(true);
	}

	void TeleopInit()
	{
		// Robot starts by LoadRingo sequence
		currentSequence = new LoadRingo();

		std::cout << "Loading Ringo!" << "\n";
		std::cout << "Speed mode set to " << speedMulFactor << ", drive mode set to " << driveMode << "\n";
		std::cout << "Square inputs set to " << squareInputs << "\n";
	}

	void TeleopPeriodic()
	{
		// This is the main method called every 20 ms
		
		// Controll the arm & the shooter:

		// Start the current sequence
		currentSequence->start();
		
		// Check if the sequence is changing
		if (currentSequence->changeToLoadRingo()) currentSequence = new LoadRingo();
		if (currentSequence->changeToSpeaker()) currentSequence = new ToSpeaker();
		if (currentSequence->changeToAMP()) currentSequence = new ToAMP();
		if (currentSequence->changeToReadyShoot()) currentSequence = new ReadyToShoot();
		if (currentSequence->changeAfterShoot()) currentSequence = new AfterShoot();

		// Controll the base:
		Drive();
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

private:
	void Drive()
	{
		// Drive the robot
		m_robotDrive.TankDrive(pad.GetLeftY() * speedMulFactor, pad.GetRightY() * speedMulFactor, squareInputs);

		// If one of the bumpers were pressed, change the speed
		if (pad.GetRightBumperPressed() && speedMulFactor < 1)
		{
			speedMulFactor += 0.2;
			std::cout << "Speed Mode: " << speedMulFactor << "\n";
		}
		if (pad.GetLeftBumperPressed() && speedMulFactor > 0.4)
		{
			speedMulFactor -= 0.2;
			std::cout << "Speed Mode: " << speedMulFactor << "\n";
		}

		// If the Back button pressed change the square input
		if (pad.GetBackButtonPressed())
		{
			squareInputs = !squareInputs;
			std::cout << "Square Inputs: " << squareInputs << "\n";
		}
		if (squareInputs && speedMulFactor <= 0.3)
		{
			speedMulFactor = 0.4;
		}
	}
};

#ifndef RUNNING_FRC_TESTS
int main()
{
	return frc::StartRobot<Robot>();
}
#endif
