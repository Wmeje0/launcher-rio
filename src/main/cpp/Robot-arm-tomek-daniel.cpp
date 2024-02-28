#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc/DigitalInput.h>
#include "Robot-arm-tomek-daniel.hpp"

void RobotArm::armMain() {
    match armState {
        case ArmState::ToPickup:
            if (armPos == ArmPos::High || armPos = ArmPos::MovingHigh) {
                armMoveLow();
            }
            if (limitLauncher.get()) {
                armState = ArmState::ToSpeaker;
            }
            if (pad.GetAButtonPressed()) {
                switchPickMotorState();
            }
        // write rest according to pseudocode, I will do that at home
    }
}