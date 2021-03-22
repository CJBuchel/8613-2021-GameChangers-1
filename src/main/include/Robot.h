#ifndef Robot_8613
#define Robot_8613

/**
 * Linear access pipeline Controlmap()->RobotMap()->SubSystems()->Robot()
 */

/**
 * Robotmap, access to controlmap and motor controllers
 */
#include "RobotMap.h"

/**
 * Subsystems
 */
#include "Drivesystem.h"

class Robot : public frc::TimedRobot {
public:
	// Public stuff
	void RobotInit() override;
	void RobotPeriodic() override;

	void AutonomousInit() override;
	void AutonomousPeriodic() override;

	void TeleopInit() override;
	void TeleopPeriodic() override;

	void DisabledInit() override;
	void DisabledPeriodic() override;

	void TestInit() override;
	void TestPeriodic() override;

private:
	RobotMap robotMap;

	Drivesystem *drivesystem; // Our drivesystem logic for telop and auto
	Drivetrain *drivetrain; // Our generic drivetrain class
};



#endif
