#include "DriveTrain.h"

float clamp(float x, float l = -1.0f, float u = 1.0f) {
	return (x<u) ? ((x>l) ? (x) : (l)) : (u);
}

DriveTrain::DriveTrain() {
    t_gear_last_press = std::chrono::system_clock::now();
	t_mode_last_press = std::chrono::system_clock::now();
    mode = arcade_drive_mode;
	pref = left_pref;
}

void DriveTrain::SetGear(float GearInput) {
	gear = GearInput;
	gear = clamp(gear);
	std::cout << "GEAR: " << gear << std::endl;
}

void DriveTrain::AddToGear(float Increment) {
	gear += Increment;
	gear = clamp(gear);
	std::cout << "GEAR: " << gear << std::endl;
}

void DriveTrain::AddMotor(int CANaddr, enum MotorType, int DriveTrainSide) {
    motors.push_back(std::make_pair<rev::CANSparkMax*,int>(new rev::CANSparkMax(CANaddr, MotorType),DriveTrainSide));
}

void DriveTrain::TankDrive(float ly, float ry) {
	// cap motor speed
	motor_lspeed = clamp(ly)*gear;
	motor_rspeed = clamp(ry)*gear;

	// Set motors to be correct speeds
    for (auto& m : motors) {
        if (m.second == left_side) {
            m.first->Set(motor_lspeed);
        }
        else if (m.second == right_side) {
            m.first->Set(motor_rspeed);
        }
		else {
			std::cout << "ERROR: Invalid value for motor DriveTrainSide" << std::endl;
		}
    }
}

void DriveTrain::ArcadeDrive(int pref, float lx, float ly, float rx, float ry) {
	// Calculate motor speeds
	float x = 0;
	float y = 0;
	if (fabs(lx) < deadband_threshold && fabs(ly) < deadband_threshold && pref == left_pref) {
		x = rx;
		y = ry;
		float theta = atan2(y,-x);
		float radius = pow(x*x+y*y,0.5);
		motor_lspeed = radius*cos(theta-M_PI/4);
		motor_rspeed = -radius*sin(theta-M_PI/4);
	}
	else if (fabs(rx) < deadband_threshold && fabs(ry) < deadband_threshold && pref == right_pref) {
		x = lx;
		y = ly;
		float theta = atan2(y,-x);
		float radius = pow(x*x+y*y,0.5);
		motor_lspeed = radius*cos(theta-M_PI/4);
		motor_rspeed = -radius*sin(theta-M_PI/4);
	}
	else if (pref == left_pref) {
		x = lx;
		y = ly;
		float theta = atan2(y,-x);
		float radius = pow(x*x+y*y,0.5);
		motor_lspeed = radius*cos(theta-M_PI/4);
		motor_rspeed = -radius*sin(theta-M_PI/4);
	}
	else if (pref == right_pref) {
		x = rx;
		y = ry;
		float theta = atan2(y,-x);
		float radius = pow(x*x+y*y,0.5);
		motor_lspeed = radius*cos(theta-M_PI/4);
		motor_rspeed = -radius*sin(theta-M_PI/4);
	}
	// cap motor speed
	motor_lspeed = clamp(ly)*gear;
	motor_rspeed = clamp(ry)*gear;
	// Set motors to be correct speeds
    for (auto& m : motors) {
        if (m.second == left_side) {
            m.first->Set(motor_lspeed);
        }
        else if (m.second == right_side) {
            m.first->Set(motor_rspeed);
        }
    }
}
