#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc/DigitalInput.h>
#include "Sequences.h"

void LoadRingo::start()
{
    if (ringoLimitSwitch.Get())
    {
        pickMotor.Set(0.0);
    }
    else
    {
        pickMotor.Set(1.0);
    }
}

bool LoadRingo::changeToLoadRingo()
{
    return 0;
}

bool LoadRingo::changeToSpeaker()
{
    if (ringoLimitSwitch.Get())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool LoadRingo::changeToLoadRingo()
{
    return 0;
}

bool LoadRingo::changeToLoadRingo()
{
    return 0;
}

bool LoadRingo::changeToLoadRingo()
{
    return 0;
}