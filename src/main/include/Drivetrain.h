#ifndef DriveTrain_8613
#define DriveTrain_8613

#include "frc/Joystick.h"
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <rev/CANSparkMax.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <vector>
#include <utility>
#include <chrono>

class DriveTrain
{
public:
    DriveTrain();
    void AddMotor(int CANaddr, rev::CANSparkMax* motor, int DrivetrainSide);
    void TankDrive(float left, float right);
	void ArcadeDrive(int pref, float lx, float ly, float rx, float ry);
	void SetGear(float GearInput);
	void AddToGear(float Increment);
private:
    std::vector< std::pair< rev::CANSparkMax*, int > > motors;
    std::chrono::time_point<std::chrono::system_clock> t_gear_now;
	std::chrono::time_point<std::chrono::system_clock> t_gear_last_press;
	std::chrono::time_point<std::chrono::system_clock> t_mode_now;
	std::chrono::time_point<std::chrono::system_clock> t_mode_last_press;
	std::chrono::time_point<std::chrono::system_clock> t_pref_now;
	std::chrono::time_point<std::chrono::system_clock> t_pref_last_press;

    int pref;
	int left_pref = 0;
	int right_pref = 1;

    int mode; // mode value for driving type
	int tank_drive_mode = 0;
	int arcade_drive_mode = 1;

    float motor_lspeed = 0; // default starting motor speed
	float motor_rspeed = 0;

    float gear_increment = 0.125; // increments of gear multiplier
	float gear = 0.5; // default gear setting

	int left_side = 1;
	int right_side = 0;

	float deadband_threshold = 0.1; // Threshold where motors are set to 0 e.g. 0.1 -> between -0.1 and 0.1 motors set to 0.
};

#endif