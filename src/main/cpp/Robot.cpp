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
	Sequence *lr;
	WPI_VictorSPX victorSPX1{1}, victorSPX2{2}, victorSPX3{3}, victorSPX4{4};

	// Define MotorControllerGroup objects using references
	frc::MotorControllerGroup m_leftMotors{victorSPX2, victorSPX3}, m_rightMotors{victorSPX1, victorSPX4};
	frc::DifferentialDrive m_robotDrive{m_leftMotors, m_rightMotors};

	frc::XboxController pad{0};

	short driveMode = 1;
	double speedMulFactor = 1.0;

	// Variable speedMulFactor is the value by which the input to the motors is multiplied float speedMulFactor = 0.4;

	const float dPadSpeed = 0.5;
	bool squareInputs = false;

public:
	void RobotInit()
	{
		lr = new LoadRingo();
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
		std::cout << "Speed mode set to " << speedMulFactor << ", drive mode set to " << driveMode << "\n";
		std::cout << "Square inputs set to " << squareInputs << "\n";
	}

	void TeleopPeriodic()
	{
		lr->start();
		if (pad.GetAButtonPressed())
		{
			if (!lr->enabled)
				lr->enabled = true;
			else
				lr->enabled = false;
		}

		switch (driveMode)
		{
		case 0:
			m_robotDrive.TankDrive(pad.GetLeftY() * speedMulFactor, pad.GetRightY() * speedMulFactor, squareInputs);
			break;
		case 1:
			m_robotDrive.ArcadeDrive(pad.GetLeftY() * speedMulFactor, pad.GetLeftX() * speedMulFactor, squareInputs);
			break;
		case 2:
			m_robotDrive.ArcadeDrive(pad.GetLeftY() * speedMulFactor, pad.GetRightX() * speedMulFactor, squareInputs);
			break;
		case 3:
			if (pad.GetPOV() == 0)
			{
				m_robotDrive.ArcadeDrive(dPadSpeed * speedMulFactor * -1, 0, squareInputs);
			}
			else if (pad.GetPOV() == 90)
			{
				m_robotDrive.ArcadeDrive(0, dPadSpeed * speedMulFactor, squareInputs);
			}
			else if (pad.GetPOV() == 180)
			{
				m_robotDrive.ArcadeDrive(dPadSpeed * speedMulFactor, 0, squareInputs);
			}
			else if (pad.GetPOV() == 270)
			{
				m_robotDrive.ArcadeDrive(0, dPadSpeed * speedMulFactor * -1, squareInputs);
			}
			break;
		}

		// If one of the buttons pressed, change the drive mode
		if (pad.GetAButtonPressed() && driveMode != 0)
		{
			driveMode = 0;
			std::cout << "Drive mode changed to Tank Drive\n";
		}
		if (pad.GetBButtonPressed() && driveMode != 1)
		{
			driveMode = 1;
			std::cout << "Drive mode changed to Arcade Drive (one joystick)\n";
		}
		if (pad.GetXButtonPressed() && driveMode != 2)
		{
			driveMode = 2;
			std::cout << "Drive mode changed to Arcade Drive (two joysticks)\n";
		}
		if (pad.GetYButtonPressed() && driveMode != 3)
		{
			driveMode = 3;
			std::cout << "Drive mode changed to Simple Drive (d-pad)\n";
		}

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

	void AutonomousInit()
	{
	}

	void AutonomousPeriodic()
	{
	}
};

#ifndef RUNNING_FRC_TESTS
int main()
{
	return frc::StartRobot<Robot>();
}
#endif
