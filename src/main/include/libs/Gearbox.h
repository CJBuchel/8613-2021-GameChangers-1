#pragma once

#include <frc/PowerDistributionPanel.h>
#include <frc/SpeedController.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/RobotController.h>
#include <frc/Encoder.h>

/**
 * Just a voltage framework rather than set framework (better for voltage control)
 */
class VoltageController {
 public:
	/**
	 * Set the voltage of the output.
	 */
	virtual void setVoltage(double voltage) = 0;
	/**
	 * Get the voltage of the output.
	 */
	virtual double getVoltage() = 0;

	/**
	 * Set the output as inverted.
	 */
	virtual void setInverted(bool invert) = 0;
	/**
	 * Get whether the output is inverted
	 */
	virtual bool getInverted() = 0;

	/**
	 * Get the physical port of the Voltage Controller.
	 */
	virtual int getPhysicalPort() = 0;

	/**
	 * Get the current output.
	 */
	virtual double getCurrent() { return frc::PowerDistributionPanel(0).GetCurrent(getPhysicalPort()); };
};


/**
 * Inheriting from voltage controller
 */
class MotorController : public VoltageController {
 public:
	MotorController(frc::SpeedController *speedController) : _speedController(speedController) {}

	void setVoltage(double voltage) override {
		_speedController->Set(voltage / getBusVoltage());
	}

	double getVoltage() override {
		return _speedController->Get() * getBusVoltage();
	}

	void setInverted(bool invert) override {
		_speedController->SetInverted(invert);
	}

	bool getInverted() override {
		return _speedController->GetInverted();
	}

	virtual int getPhysicalPort() override { return -1; };

	double getBusVoltage() {
		return frc::RobotController::GetInputVoltage();
	}

	/**
	 * Template for any type of motors
	 */
	template<typename T, typename ...Args>
	static MotorController Of(Args& ...args) {
		T *t = new T(args...);  // Be warned, does not deallocate!
		return MotorController{t};
	}

	/**
	 * Template for any type and amount of motor controllers
	 */
	template<typename ...Args>
	static MotorController Group(Args& ...args) {
		return Of<frc::SpeedControllerGroup>(args...);
	}

 private:
	frc::SpeedController *_speedController; // Frc already has a speed controller, might as well use it
};

/**
 * Virtual gearbox, used to group mutliple types of motor controllers togethor
 */
struct Gearbox {

	/**
	 * Voltage controller (Motor Controller) CANNOT BE NULL
	 */
	VoltageController *transmission;

	/**
	 * optional encoder
	 */
	frc::Encoder *encoder = nullptr;

	/**
	 * optional encoder ticks per rotation (counts per revolution)
	 */
	double encTicks = 2048;

	/**
	 * optional physical gearbox reduction E.g value:1 ratio
	 */
	double reduction = 1;

	/**
	 * optional encoder offset from it's raw tick state
	 */
	double encoderOffset = 0;

	double getEncoderRotations() {
		assert(encoder != nullptr);
		double ticks = encoder->Get() - encoderOffset;
		return ticks / (double)encTicks;
	};
};