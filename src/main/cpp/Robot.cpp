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
#include <cameraserver/CameraServer.h>
#include <iostream>
#include <fmt/format.h>
#include <frc/SerialPort.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <networktables/DoubleTopic.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/I2C.h>
#include <ctre/Phoenix.h>

class RingoShooter
{
private:
	frc::PWMSparkMax loader{0};
	frc::PWMSparkMax shooter{9};
	bool isAvailable;
public:
	auto startLoadingSequence() -> void
	{
		if (isAvailable) {
			//TODO
		}
	}
};

class Robot : public frc::TimedRobot
{
	/**
	 * SPARK MAX controllers are intialized over CAN by constructing a CANSparkMax object
	 *
	 * The CAN ID, which can be configured using the SPARK MAX Client, is passed as the
	 * first parameter
	 *
	 * The motor type is passed as the second parameter. Motor type can either be:
	 *  rev::CANSparkMax::MotorType::kBrushless
	 *  rev::CANSparkMax::MotorType::kBrushed
	 *
	 * The example below initializes four brushless motors with CAN IDs 1, 2, 3 and 4. Change
	 * these parameters to match your setup
	 */

	/**
	 * In RobotInit() below, we will group left and right motors using the MotorControllerGroup class.
	 *
	 * For this reason, we only need to pass motor groups to m_robotDrive.
	 * Whatever commands are sent to them will be automatically forwarded to the motors.
	 */

	// WPI_VictorSPX victorSPX1{1};
	// WPI_VictorSPX victorSPX2{2};
	// WPI_VictorSPX victorSPX3{3};
	// WPI_VictorSPX victorSPX4{4};

	// Define MotorControllerGroup objects using references
	// frc::MotorControllerGroup m_leftMotors{victorSPX2, victorSPX3};
	// frc::MotorControllerGroup m_rightMotors{victorSPX1, victorSPX4};

	// frc::DifferentialDrive m_robotDrive{m_leftMotors, m_rightMotors};

	frc::Joystick m_stick{0};

	// frc::XboxController pad{0};

	// short driveMode = 1;

	// Variable speedMulFactor is the value by which the input to the motors is multiplied
	// float speedMulFactor = 0.4;

	// const float dPadSpeed = 0.5;
	// bool squareInputs = false;

public:
	void RobotInit()
	{

		// victorSPX1.Set(ControlMode::PercentOutput, 0);
		// victorSPX2.Set(ControlMode::PercentOutput, 0);
		// victorSPX3.Set(ControlMode::PercentOutput, 0);
		// victorSPX4.Set(ControlMode::PercentOutput, 0);

		/**
		 * The RestoreFactoryDefaults method can be used to reset the configuration parameters
		 * in the SPARK MAX to their factory default state. If no argument is passed, these
		 * parameters will not persist between power cycles
		 */
		// victorSPX1.ConfigFactoryDefault();
		// victorSPX2.ConfigFactoryDefault();
		// victorSPX3.ConfigFactoryDefault();
		// victorSPX4.ConfigFactoryDefault();

		// m_rightMotors.SetInverted(true);
	}

	void TeleopInit()
	{

		// std::cout << "Speed mode set to " << speedMulFactor << ", drive mode set to " << driveMode << "\n";
		// std::cout << "Square inputs set to " << squareInputs << "\n";
	}

	void TeleopPeriodic()
	{
		loader.Set(m_stick.GetY());
		// switch (driveMode)
		// {
		// case 0:
		// 	m_robotDrive.TankDrive(pad.GetLeftY() * speedMulFactor, pad.GetRightY() * speedMulFactor, squareInputs);
		// 	break;
		// case 1:
		// 	m_robotDrive.ArcadeDrive(pad.GetLeftY() * speedMulFactor, pad.GetLeftX() * speedMulFactor, squareInputs);
		// 	break;
		// case 2:
		// 	m_robotDrive.ArcadeDrive(pad.GetLeftY() * speedMulFactor, pad.GetRightX() * speedMulFactor, squareInputs);
		// 	break;
		// case 3:
		// 	if (pad.GetPOV() == 0)
		// 	{
		// 		m_robotDrive.ArcadeDrive(dPadSpeed * speedMulFactor * -1, 0, squareInputs);
		// 	}
		// 	else if (pad.GetPOV() == 90)
		// 	{
		// 		m_robotDrive.ArcadeDrive(0, dPadSpeed * speedMulFactor, squareInputs);
		// 	}
		// 	else if (pad.GetPOV() == 180)
		// 	{
		// 		m_robotDrive.ArcadeDrive(dPadSpeed * speedMulFactor, 0, squareInputs);
		// 	}
		// 	else if (pad.GetPOV() == 270)
		// 	{
		// 		m_robotDrive.ArcadeDrive(0, dPadSpeed * speedMulFactor * -1, squareInputs);
		// 	}
		// 	break;
		// }

		// // If one of the buttons pressed, change the drive mode
		// if (pad.GetAButtonPressed() && driveMode != 0)
		// {
		// 	driveMode = 0;
		// 	std::cout << "Drive mode changed to Tank Drive\n";
		// }
		// if (pad.GetBButtonPressed() && driveMode != 1)
		// {
		// 	driveMode = 1;
		// 	std::cout << "Drive mode changed to Arcade Drive (one joystick)\n";
		// }
		// if (pad.GetXButtonPressed() && driveMode != 2)
		// {
		// 	driveMode = 2;
		// 	std::cout << "Drive mode changed to Arcade Drive (two joysticks)\n";
		// }
		// if (pad.GetYButtonPressed() && driveMode != 3)
		// {
		// 	driveMode = 3;
		// 	std::cout << "Drive mode changed to Simple Drive (d-pad)\n";
		// }

		// // If one of the bumpers were pressed, change the speed
		// if (pad.GetRightBumperPressed() && speedMulFactor < 1)
		// {
		// 	speedMulFactor += 0.2;
		// 	std::cout << "Speed Mode: " << speedMulFactor << "\n";
		// }
		// if (pad.GetLeftBumperPressed() && speedMulFactor > 0.4)
		// {
		// 	speedMulFactor -= 0.2;
		// 	std::cout << "Speed Mode: " << speedMulFactor << "\n";
		// }

		// // If the Back button pressed change the square input
		// if (pad.GetBackButtonPressed())
		// {
		// 	squareInputs = !squareInputs;
		// 	std::cout << "Square Inputs: " << squareInputs << "\n";
		// }
		// if (squareInputs && speedMulFactor <= 0.3)
		// {
		// 	speedMulFactor = 0.4;
		// }
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
