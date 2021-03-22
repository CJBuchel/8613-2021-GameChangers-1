#ifndef Arm8613
#define Arm8613
#include <rev/CANSparkMax.h>
#include <frc/DigitalInput.h>

typedef Motor rev::CANSparkMax;

class Arm
{
public:
    Arm(Motor *motor, DigitalInput *top, DigitalInput *btm, DigitalInput *toptop, DigitalInput *btmbtm) 
    : motor(motor), top(top), btm(btm), toptop(toptop), btmbtm(btmbtm) {

    }

    ~Arm() {
        // all good here
    }

    void Stop() {
        armstate = asSTOP;
        speed = 0;
    }

    void Move(float spd) { 
        armstate = asMOVE; speed = spd;
    }
    
    void MoveToTop(float spd)  { 
        armstate = asMOVETO; speed = spd; 
    }
    
    void MoveToBtm(float spd)  {
        armstate = asMOVETO; speed = spd; 
    }
    
    void Update() {
        if( (top->Get() || toptop->Get()) && speed > 0 || 
            (btm->Get() || btmbtm->Get()) && speed < 0) {
                armstate = asSTOP; 
        }
        switch (armstate) {
            case asMOVETO: 
                motor->Set(speed); 
                break;
            case asMOVE: 
                motor->Set(speed); 
                break;
            case asSTOP: 
            default: 
                motor->Set(0); 
                break;
        }

        if(armstate <= asMOVE) armstate = asSTOP;
    }
protected:
private:
    Motor *motor;
    DigitalInput *top, *btm;  // operating limits
    DigitalInput *toptop, *btmbtm; // hard stop limits
    enum {asSTOP = 0, asMOVE, asMOVETO} armstate = asSTOP;
    float speed = 0;
};

#endif