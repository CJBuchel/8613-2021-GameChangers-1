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

/*

#include "Robot.h"



// Robot Logic (runs when robot is on regardless of below functions)
void Robot::RobotInit() {


}

void Robot::RobotPeriodic() {
	// Constantly looping code after robot has turned on. (Cannot control motors in here as they are locked until teleop/auto/test is started)
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
}
void Robot::TeleopPeriodic() {
	float lx = j->GetRawAxis(left_stick_x);
	float ly = j->GetRawAxis(left_stick_y);
	float rx = j->GetRawAxis(right_stick_x);
	float ry = j->GetRawAxis(right_stick_y); 
	bool is_pref_switch_l = j->GetRawButton(left_stick);
	bool is_pref_switch_r = j->GetRawButton(right_stick);
	if (mode == tank_drive_mode) {
		DriveTrain::TankDrive(ly,ry);
	}
	else if (mode == arcade_drive_mode) {
		// Joystick switching preference
		// Mode switching
		t_pref_now = std::chrono::system_clock::now();
		if (!is_pref_switch_l && !is_pref_switch_r) {
			t_pref_last_press = t_pref_now;
			pref_shifted = false;
		}
		std::chrono::duration<double> duration_elapsed_pref = t_pref_now - t_pref_last_press;
		double time_dif2 = duration_elapsed_pref.count();
		if (time_dif2 > press_delay && !pref_shifted) { 
			if (pref == left_pref && is_pref_switch_r) {
				pref = right_pref;
				std::cout << "PREF: Right" << std::endl;
			}
			else if (pref == right_pref && is_pref_switch_l) {
				pref = left_pref;
				std::cout << "PREF: LEFT" << std::endl;
			}
			
			pref_shifted = true;
		}

		DriveTrain::ArcadeDrive(int pref, float lx, float ly, float rx, float ry);
		
	}
	else {
		mode = tank_drive_mode; // First drive mode
	}

	// Mode switching
	t_mode_now = std::chrono::system_clock::now();
	bool is_mode_switch = j->GetRawButton(7);
	
	if (!is_mode_switch) {
		t_mode_last_press = t_mode_now;
		mode_shifted = false;
	}
	std::chrono::duration<double> duration_elapsed_mode = t_mode_now - t_mode_last_press;
	double time_dif2 = duration_elapsed_mode.count();
	if (time_dif2 > press_delay && !mode_shifted) { 
		if (mode == tank_drive_mode) {
			mode = arcade_drive_mode;
			std::cout << "MODE: Arcade" << std::endl;
		}
		else if (mode == arcade_drive_mode) {
			mode = tank_drive_mode;
			std::cout << "MODE: Tank" << std::endl;
		}
		
		mode_shifted = true;
	}
	// D Pad controls for virtual gearbox
	t_gear_now = std::chrono::system_clock::now();
	int dpad_direction = j->GetPOV(0);

	if (dpad_direction != dpad_right && dpad_direction != dpad_left) {
		t_gear_last_press = t_gear_now;
		gear_shifted = false;
	}
	std::chrono::duration<double> duration_elapsed_gear = t_gear_now - t_gear_last_press;
	double time_dif1 = duration_elapsed_gear.count();
	if (time_dif1 > press_delay && !gear_shifted) { // value may have to be fine tuned as to ensure it only changes gear once per dpad press.
		if (dpad_direction == dpad_right) {
			DriveTrain::AddToGear(gear_increment);
		}
		if (dpad_direction == dpad_left) {
			DriveTrain::AddToGear(-gear_increment);
		}
		gear_shifted = true;
	}

}

// Test Logic 
void Robot::TestInit() {}
void Robot::TestPeriodic() {}

*/

