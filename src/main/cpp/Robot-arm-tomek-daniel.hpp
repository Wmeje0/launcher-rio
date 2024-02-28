#include <frc/DigitalInput.h>
#include <frc/XboxController.h>
#include <frc/AnalogInput.h>
#include <ctre/Phoenix.h>

class RobotArm {
    frc::DigitalInput limitLauncher;
    frc::DigitalInput limitArmSpeaker;
    frc::DigitalInput limitArmAmp;
    frc::AnalogInput distanceSensor;

    WPI_TalonSRX motorArm1; // add more motors as needed
    frc::XboxController pad;

    ArmState armState;
    ArmPos armPos;

    public:
        // 
        void armMain();
        void switchPickMotorState();
        void distanceSensorSwitch(bool onOff);
        void shoot();
        void armMoveLow();
        void armMoveHigh();
};

enum class ArmState {
    ToSpeaker;
    ToPickup;
    ToAmp;
    ToShotSpeaker;
    ToShotAmp;
    AfterShot;
};

enum class ArmPos {
    Low;
    MovingLow;
    MovingHigh;
    High;
}