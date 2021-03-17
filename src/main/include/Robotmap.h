#pragma once

// #include <frc/Joystick.h>
#include <frc/XboxController.h>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <rev/CANSparkMax.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <unistd.h>
#include <chrono>
#include <math.h>
#include <iostream>
#include <string>
#include <frc/Timer.h>
#include <frc/ADXL345_SPI.h>
#include <frc/AnalogGyro.h>

/**
 * Local headers
 */
#include "Controlmap.h"
#include "libs/Drivetrain.h"

struct RobotMap {
	frc::XboxController xbox1{ ControlMap::Xbox1Port };

	struct Drivesystem {
		// Left
		rev::CANSparkMax FL{ ControlMap::FL, rev::CANSparkMax::MotorType::kBrushed };
		rev::CANSparkMax BL{ ControlMap::BL, rev::CANSparkMax::MotorType::kBrushed };

		// Right
		rev::CANSparkMax FR{ ControlMap::FR, rev::CANSparkMax::MotorType::kBrushed };
		rev::CANSparkMax BR{ ControlMap::BR, rev::CANSparkMax::MotorType::kBrushed };

		// From our gearbox header
		MotorController leftMotors = MotorController::Group(FL, BL);
		MotorController rightMotors = MotorController::Group(FR, BR);

		frc::Encoder encL{ 0, 1 };
		frc::Encoder encR{ 2, 3 };

		Gearbox LeftGB{ &leftMotors, &encL, 80, 8.24, 0 };
		Gearbox RightGB{ &rightMotors, &encR, 80, 8.24, 0 };

		frc::AnalogGyro gyro{0};

		DrivetrainConfig config{ LeftGB, RightGB, &gyro, 0.60, 1, 0.075, 55};
		// Drivetrain drivetrain{config};

	}; Drivesystem drivesystem;
};