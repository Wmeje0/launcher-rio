/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/DigitalInput.h>
#include "rev/CANSparkMax.h"
#include <frc/XboxController.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <cameraserver/CameraServer.h>
#include <iostream>
#include <fmt/format.h>
#include <frc/SerialPort.h>

#include <networktables/DoubleTopic.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/I2C.h>
#include <ctre/Phoenix.h>

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

	WPI_VictorSPX victorSPX1{1};
	WPI_VictorSPX victorSPX2{2};
	WPI_VictorSPX victorSPX3{3};
	WPI_VictorSPX victorSPX4{4};

	WPI_TalonSRX launcherLoadTalon{5}; // IDs temporary, controllers do not exist physically yet
	WPI_TalonSRX launchTalon1{6};
	WPI_TalonSRX launchTalon2{7};

	frc::DigitalInput ringoInLimit{0}; // IDs also temporary
	frc::DigitalInput ringoOutLimit{1}; // IDs also temporary

	// Define MotorControllerGroup objects using references
	frc::MotorControllerGroup m_leftMotors{victorSPX2, victorSPX3};
	frc::MotorControllerGroup m_rightMotors{victorSPX1, victorSPX4};

	frc::DifferentialDrive m_robotDrive{m_leftMotors, m_rightMotors};

	frc::XboxController pad{0};

	frc::SerialPort serialPort{115200, frc::SerialPort::kMXP};

	// frc::Timer m_timer;

	// m_timer.Start();

	short driveMode = 1;

	// Variable speedMulFactor is the value by which the input to the motors is multiplied
	float speedMulFactor = 0.4;

	const float dPadSpeed = 0.5;
	bool squareInputs = false;

	short launcherMode = 0; // 0 - ready for pickup, 1 - loaded, 2 - awaiting ejection confirm, 3 - failiure
	const float launcherSpeed = 1;
	const float loaderSpeed = 0.2;
	frc::Timer launcherWait;
	bool launcherWaitStart = false;

public:
	double x;
	double y;

	nt::DoubleSubscriber xSub;
	nt::DoubleSubscriber ySub;

	void RobotInit()
	{
		victorSPX1.Set(ControlMode::PercentOutput, 0);
		victorSPX2.Set(ControlMode::PercentOutput, 0);
		victorSPX3.Set(ControlMode::PercentOutput, 0);
		victorSPX4.Set(ControlMode::PercentOutput, 0);
		
		launcherLoadTalon.Set(ControlMode::PercentOutput, 0);
		launchTalon1.Set(ControlMode::PercentOutput, 0);
		launchTalon2.Set(ControlMode::Follower, 6);

		/**
		 * The RestoreFactoryDefaults method can be used to reset the configuration parameters
		 * in the SPARK MAX to their factory default state. If no argument is passed, these
		 * parameters will not persist between power cycles
		 */
		victorSPX1.ConfigFactoryDefault();
		victorSPX2.ConfigFactoryDefault();
		victorSPX3.ConfigFactoryDefault();
		victorSPX4.ConfigFactoryDefault();

		launcherLoadTalon.ConfigFactoryDefault();
		launchTalon1.ConfigFactoryDefault();
		launchTalon2.ConfigFactoryDefault();

		m_rightMotors.SetInverted(true);
		launchTalon2.SetInverted(InvertType::OpposeMaster);
	}

	void TeleopInit()
	{
		std::cout << "Speed mode set to " << speedMulFactor << ", drive mode set to " << driveMode << "\n";
		std::cout << "Square inputs set to " << squareInputs << "\n";
		std::cout << "Launcher on" << "\n";
	}

	void TeleopPeriodic()
	{
		char buffer[256];

		//std::cout << x << std::endl;
		std::cout << serialPort.GetBytesReceived() << std::endl;
		// Drive the robot
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

		operateLauncher();
	}

	void AutonomousInit()
	{
		std::cout << "Autonomous enabled" << std::endl;
		// auto inst = nt::NetworkTableInstance::GetDefault();
		// auto table = inst.GetTable("datatable");
		// xSub = table->GetDoubleTopic("cones").Subscribe(0.0);
		// ySub = table->GetDoubleTopic("cubes").Subscribe(0.0);
		// m_timer.Restart();
	}

	void AutonomousPeriodic()
	{
		// if (m_timer.Get() < 2_s) {
		// 	// Drive forwards half speed, make sure to turn input squaring off
		// 	m_robotDrive.ArcadeDrive(0.5, 0.0, false);
		// } else {
		// 	// Stop robot
		// 	m_robotDrive.ArcadeDrive(0.0, 0.0, false);
		// }

		// x = xSub.Get();
		// y = ySub.Get();
		// fmt::print("Cones: {} Cubes: {}\n", x, y);

		// if (x > y)
		// {
		// 	m_robotDrive.TankDrive(-speedMulFactor, -speedMulFactor, squareInputs);
		// } else if (y > x) {
		// m_robotDrive.TankDrive(speedMulFactor, speedMulFactor, squareInputs);
		// }
	}

	void operateLauncher() 
	{
		switch (launcherMode) {
			case 0:
				if (ringoInLimit.Get()) launcherMode = 1;
				launcherLoadTalon.Set(ControlMode::PercentOutput, loaderSpeed);
				launchTalon1.Set(ControlMode::PercentOutput, launcherSpeed);
			case 1:
				if (pad.GetLeftTriggerAxis() >= 0.3) // temporary shot input, subject to change
				{
					launcherMode = 2;
					launcherWait.Start();
				} 
				launcherLoadTalon.Set(ControlMode::PercentOutput, 0);
				launchTalon1.Set(ControlMode::PercentOutput, launcherSpeed);
			case 2:
				if (launcherWait.Get() > 2_s) 
				{
					launcherMode = 3;
					launcherWait.Stop();
					launcherWait.Reset();
				}
				else if (ringoOutLimit.Get()) 
				{
					launcherMode = 0;
					launcherWait.Stop();
					launcherWait.Reset();
				}
				launcherLoadTalon.Set(ControlMode::PercentOutput, loaderSpeed);
				launchTalon1.Set(ControlMode::PercentOutput, launcherSpeed);
			case 3:
				launcherLoadTalon.Set(ControlMode::PercentOutput, 0);
				launchTalon1.Set(ControlMode::PercentOutput, 0);
		}
	}
};

#ifndef RUNNING_FRC_TESTS
int main()
{
	return frc::StartRobot<Robot>();
}
#endif
