class Sequence
{
protected:
    frc::PWMSparkMax rightMotor{0};
    frc::PWMSparkMax leftMotor{9};
    frc::DigitalInput limitSwitch{0};

public:
    bool enabled;
    virtual auto start() -> void{};
    virtual auto stop() -> void{};
};

class LoadRingo : public Sequence
{
public:
    virtual auto start() -> void override;
    virtual auto stop() -> void override;
};

class MoveArm : public Sequence
{
public:
    virtual auto start() -> void override;
    virtual auto stop() -> void override;
};

class ShootRingo : public Sequence
{
public:
    virtual auto start() -> void override;
    virtual auto stop() -> void override;
};