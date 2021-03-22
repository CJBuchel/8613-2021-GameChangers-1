#pragma once

#include "Gearbox.h"
#include <frc/interfaces/Gyro.h>
#include <networktables/NetworkTableInstance.h>

struct DrivetrainConfig {
	Gearbox &leftDrive; // Left gearbox
	Gearbox &rightDrive; // right gearbox

	/**
	 * Optional gyroscope to add to drivetrain
	 */
	frc::Gyro *gyro;

	/**
	 * distance between left and right wheels in meters
	 */
	double trackWidth;

	/**
	 * The trackdepth, from front of robot to back of robot, in metres.
	 */
	double trackdepth;

	/**
	 * The wheel radius, in metres
	 */
	double wheelRadius;

	/**
	 * The mass of the robot chassis, in kg
	 */
	double mass;

	/**
	 * reverse drivetrain
	 */
	bool reversed = false;

	std::string name = "<Drivetrain>";
};

class Drivetrain {
 public:
	Drivetrain(DrivetrainConfig config) : _config(config) {};

	/**
	 * Setters
	 */
	void set(double leftPower, double rightPower) {
		setVoltage(leftPower * 12, rightPower * 12);
	};

	void setVoltage(double left, double right) {
		_voltage = std::pair<double, double>{ left, right };
	};

	void setInverted(bool inverted = false) {
		if (inverted != _config.reversed) {
			_config.reversed = inverted;
			_config.leftDrive.transmission->setInverted(!_config.leftDrive.transmission->getInverted());
			_config.rightDrive.transmission->setInverted(!_config.rightDrive.transmission->getInverted());
		}
	};

	void output2NT(bool output) {
		_output2NT = output;
	}

	/**
	 * Getters
	 */
	Gearbox &getLeft() {
		return !_config.reversed ? _config.leftDrive : _config.rightDrive;
	};

	Gearbox &getRight() {
		return !_config.reversed ? _config.rightDrive : _config.leftDrive;
	};

	bool getInverted() { return _config.reversed; };
	DrivetrainConfig &getConfig() { return _config; };

	/**
	 * Get distance in meters
	 */
	double getLeftDistance() {
		auto gb = this->getLeft();

		assert(gb.encoder != nullptr);
		return (gb.getEncoderRotations() * M_PI * 2 * _config.wheelRadius)/gb.reduction;
	};

	/**
	 * Get right distance in meters
	 */
	double getRightDistance() {
		auto gb = this->getRight();

		assert(gb.encoder != nullptr);
		return (gb.getEncoderRotations() * M_PI * 2 * _config.wheelRadius)/gb.reduction;
	};

	/**
	 * Update the drivetrain loop
	 */
	void update() {
		this->getLeft().transmission->setVoltage(_voltage.first);
		this->getRight().transmission->setVoltage(_voltage.second);
		if (_output2NT) { ntOutput(); };
	};

 private:
	DrivetrainConfig _config;
	bool _output2NT = false;
	std::pair<double, double> _voltage;

	void ntOutput() {
		nt::NetworkTableInstance::GetDefault().GetTable("Drivetrain")->GetEntry("LeftPower").SetDouble(_voltage.first);
		nt::NetworkTableInstance::GetDefault().GetTable("Drivetrain")->GetEntry("RightPower").SetDouble(_voltage.second);
		nt::NetworkTableInstance::GetDefault().GetTable("Drivetrain")->GetEntry("Gyro").SetDouble(_config.gyro->GetAngle());
		nt::NetworkTableInstance::GetDefault().GetTable("Drivetrain")->GetEntry("LeftEnc").SetDouble(this->getLeftDistance());
		nt::NetworkTableInstance::GetDefault().GetTable("Drivetrain")->GetEntry("RightEnc").SetDouble(this->getRightDistance());
	}
};