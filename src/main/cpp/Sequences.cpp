#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc/DigitalInput.h>
#include "Sequences.h"

void LoadRingo::Update()
{
    if (ringoLimitSwitch.Get())
    {
        pickMotor.Set(1.0);
    }
}

Sequence* LoadRingo::checkStateChange() {
    if (ringoLimitSwitch.Get())
    {
        return new ToSpeaker;
    }
    else
    {
        return this;
    }
}


Sequence* ToSpeaker::checkStateChange() {
    if (pad.getAButtonPressed()) // button subject to change
    { 
        return new ToAMP;
    } 
    else if (pad.getBButtonPressed()) // button subject to change 
    {
        return new ReadyToShootSpeaker;
    }
    else 
    {
        return this;
    }
}

Sequence* ToAMP::checkStateChange() {
    if (pad.getAButtonPressed()) // button subject to change
    { 
        return new ToSpeaker;
    } 
    else if (pad.getBButtonPressed()) // button subject to change 
    {
        return new ReadyToShootAMP;
    }
    else 
    {
        return this;
    }
}

Sequence* ReadyToShootSpeaker::checkStateChange() {
    if (pad.getLeftTriggerAxis() > 0.3 && pad.getRifhtTriggerAxis() > 0.3)
    { 
        return new LoadRingo;
    } 
    else 
    {
        return this;
    }
}

Sequence* AfterShot::checkStateChange() {
    if (pad.getAButtonPressed())
    { 
        return new LoadRingo;
    } 
    else 
    {
        return this;
    }
}

Sequence* ReadyToShootAMP::checkStateChange() {
    if (pad.getLeftTriggerAxis() > 0.3 && pad.getRifhtTriggerAxis() > 0.3)
    { 
        return new AfterShoot;
    } 
    else 
    {
        return this;
    }
}

