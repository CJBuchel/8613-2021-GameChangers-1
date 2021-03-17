#include "Robot.h"

double currentTimeStamp, lastTimeStamp, dt;

// Robot Logic (runs when robot is on regardless of below functions)
void Robot::RobotInit() {
	drivetrain = new Drivetrain(robotMap.drivesystem.config); // Initialize a new drivetrain
	drivetrain->getConfig().leftDrive.transmission->setInverted(true); // Invert one side
	drivetrain->getConfig().rightDrive.transmission->setInverted(false);
	drivetrain->output2NT(true); // Output drivetrain values to network tables, (goes to shuffleboard or smart dashboard)

	drivesystem = new Drivesystem(*drivetrain); // initialize your drivesystem logic and pass drivetrain in
}

void Robot::RobotPeriodic() {
	// Constantly looping code after robot has turned on. (Cannot control motors in here as they are locked until teleop/auto/test is started)
	drivetrain->update(); // Global drivetrain update (doesn't matter if it's in auto or teleop, the drivetrain updates the power set to it. Wheras drivesystem is our logic for specific things, teleop or auto)
}

// Dissabled Robot Logic
void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

// Auto Robot Logic
void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

// Manual Robot Logic
void Robot::TeleopInit() {
	// Might want to zero encoders or something when you start teleop
	drivetrain->getLeft().encoder->Reset();
	drivetrain->getRight().encoder->Reset();
}

void Robot::TeleopPeriodic() {
	currentTimeStamp = frc::Timer::GetFPGATimestamp();
	dt = currentTimeStamp - lastTimeStamp;

	drivesystem->updatePeriodic(dt);

	lastTimeStamp = currentTimeStamp;
}

// Test Logic 
void Robot::TestInit() {}
void Robot::TestPeriodic() {}

/**
 * Don't touch these lines
 */
#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif

