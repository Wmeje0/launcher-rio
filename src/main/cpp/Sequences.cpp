#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc/DigitalInput.h>
#include "Sequences.h"

void LoadRingo::start()
{
    if (enabled)
    {
        if (limitSwitch.Get())
        {
            rightMotor.Set(0.0);
            leftMotor.Set(0.0);
        }
        else
        {
            rightMotor.Set(1.0);
            leftMotor.Set(1.0);
        }
    }
    else
        stop();
}

void LoadRingo::stop()
{
    rightMotor.Set(0.0);
    leftMotor.Set(0.0);
}