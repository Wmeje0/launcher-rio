class Sequence
{
public:
    // Basic method called in TeleopPeriodic
    virtual auto start() -> void{};
    // virtual auto stop() -> void{};

    // These methods returns 1 if the sequence is changing to another one
    virtual auto checkStateChange() -> Sequence*{};
private:
    frc::XboxController pad{0};
};

class LoadRingo : public Sequence
{
public:
    virtual auto start() -> void override;
    virtual auto checkStateChange() -> int{};

    private:
        // Spark Max are temporary, we will change them to Victor & Talons
        frc::PWMSparkMax pickMotor{0};
        frc::DigitalInput ringoLimitSwitch{0};
};

class ToSpeaker : public Sequence
{
public:
    virtual auto start() -> void override;
    virtual auto checkStateChange() -> Sequence*{};

    private:
        // Local Variables
};

class ToAMP : public Sequence
{
public:
    virtual auto start() -> void override;
    virtual auto checkStateChange() -> Sequence*{};

    private:
        // Local variables
};

class ReadyToShootSpeaker : public Sequence
{
public:
    virtual auto start() -> void override;
    virtual auto checkStateChange() -> Sequence*{};

    private:
        // Local variables
        frc::XboxController pad{0};
};

class ReadyToShootAMP : public Sequence
{
public:
    virtual auto start() -> void override;
    virtual auto checkStateChange() -> Sequence*{};

    private:
        // Local variables
};

class AfterShoot : public Sequence
{
public:
    virtual auto start() -> void override;
    virtual auto checkStateChange() -> Sequence*{};

    private:
        // Local variables
};
