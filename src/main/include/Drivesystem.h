#pragma once

#include "RobotMap.h"
#include "libs/Drivetrain.h"

class Drivesystem {
 public:
	Drivesystem(Drivetrain &drivetrain);
	void updatePeriodic(double dt);

 private:
	Drivetrain &_drivetrain;
	double _leftPower, _rightPower;
};