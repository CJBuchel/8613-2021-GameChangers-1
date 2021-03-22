
#ifndef Intake_8613
#define Intake_8613


#include <rev/CANSparkMax.h>

typedef Motor rev::CANSparkMax;


class Intake
{
public:
    Intake(Motor *motor);
    ~Intake();

    void Spin(float spd) {
        motor->Set(spd);
    }
protected:
private:
    Motor *motor;
};

#endif
