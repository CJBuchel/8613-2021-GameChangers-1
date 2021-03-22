#pragma once
#include "frc/Joystick.h"

struct ControlMap {

	/**
	 * Controllers
	 */
	static const int Xbox1Port = 0, Xbox2Port = 1;
	static constexpr frc::Joystick *j = new frc::JoyStick(0);
	
	/**
	 * Drivetrain
	 */
	static const int FL = 0, BL = 1, FR = 2, BR = 3;



	std::chrono::time_point<std::chrono::system_clock> t_gear_now;
	std::chrono::time_point<std::chrono::system_clock> t_gear_last_press;
	std::chrono::time_point<std::chrono::system_clock> t_mode_now;
	std::chrono::time_point<std::chrono::system_clock> t_mode_last_press;
	std::chrono::time_point<std::chrono::system_clock> t_pref_now;
	std::chrono::time_point<std::chrono::system_clock> t_pref_last_press;
	static constexpr float lacceleration = 1; // acceleration in time it takes to get to max speed
	static constexpr float racceleration = 1;
	float motor_lspeed = 0; // default starting motor speed
	float motor_rspeed = 0;
	int mode; // mode value for driving type
	enum DriveMode { tank_drive_mode = 0, 
					 arcade_drive_mode };
	static constexpr float gear_increment = 0.125; // increments of gear multiplier
	float gear = 0.5;
	enum DpadDirection { dpad_up = 0, 
		   				 dpad_right = 90, 
		   				 dpad_down = 180, 
		   				 dpad_left = 270 }; 
	static constexpr float deadband_threshold = 0.1; // Threshold where motors are set to 0 e.g. 0.1 -> between -0.1 and 0.1 motors set to 0.
	static constexpr float press_delay = 0.01; // time of button press before code responds

	enum joystick_axis {
		left_stick_x = 0,
		left_stick_y,
		left_trigger,
		right_trigger,
		right_stick_x,
		right_stick_y,
		NUM_AXIS };

	enum joystick_btn {
		button_a = 1,
		button_b,
		button_x,
		button_y,
		left_bumper,
		right_bumper,
		back, // also left arrow
		start, // also right arrow
		left_stick,
		right_stick,
		NUM_BUTTONS };

	bool gear_shifted = false;
	bool mode_shifted = false;
	bool pref_shifted = false;

	int pref;
	enum ArcadePreference {
		left_pref = 0,
		right_pref };
};