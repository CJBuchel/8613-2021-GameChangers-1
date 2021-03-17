#include "Drivesystem.h"

Drivesystem::Drivesystem(Drivetrain &drivetrain) : _drivetrain(drivetrain) {
	/**
	 * Do logic when you create your drivesystem
	 */
	_leftPower = 0;
	_rightPower = 0;
}

void Drivesystem::updatePeriodic(double dt) {
	_leftPower = 0.5; // Do left power logic here (left joystick)
	_rightPower = 0.5; // Do right power logic here (right joystick)

	_drivetrain.set(_leftPower, _rightPower); // Sets power to the drivetrain, but is only updated in robot periodic
}