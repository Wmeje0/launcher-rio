class Sequence
{
public:
    // Basic method called in TeleopPeriodic
    virtual auto start() -> void{};
    // virtual auto stop() -> void{};

    // These methods returns 1 if the sequence is changing to another one
    virtual auto changeToLoadRingo() -> bool{};
    virtual auto changeToSpeaker() -> bool{};
    virtual auto changeToAMP() -> bool{};
    virtual auto changeToReadyShoot() -> bool{};
    virtual auto changeAfterShoot() -> bool{};
};

class LoadRingo : public Sequence
{
public:
    virtual auto start() -> void override;
    virtual auto changeToLoadRingo() -> bool override{};
    virtual auto changeToSpeaker() -> bool override{};
    virtual auto changeToAMP() -> bool override{};
    virtual auto changeToReadyShoot() -> bool override{};
    virtual auto changeAfterShoot() -> bool override{};

    private:
        // Spark Max are temporary, we will change them to Victor & Talons
        frc::PWMSparkMax pickMotor{0};
        frc::DigitalInput ringoLimitSwitch{0};
};

class ToSpeaker : public Sequence
{
public:
    virtual auto start() -> void override;
    virtual auto changeToLoadRingo() -> bool override{};
    virtual auto changeToSpeaker() -> bool override{};
    virtual auto changeToAMP() -> bool override{};
    virtual auto changeToReadyShoot() -> bool override{};
    virtual auto changeAfterShoot() -> bool override{};

    private:
        // Local variables
};

class ToAMP : public Sequence
{
public:
    virtual auto start() -> void override;
    virtual auto changeToLoadRingo() -> bool override{};
    virtual auto changeToSpeaker() -> bool override{};
    virtual auto changeToAMP() -> bool override{};
    virtual auto changeToReadyShoot() -> bool override{};
    virtual auto changeAfterShoot() -> bool override{};

    private:
        // Local variables
};

class ReadyToShoot : public Sequence
{
public:
    virtual auto start() -> void override;
    virtual auto changeToLoadRingo() -> bool override{};
    virtual auto changeToSpeaker() -> bool override{};
    virtual auto changeToAMP() -> bool override{};
    virtual auto changeToReadyShoot() -> bool override{};
    virtual auto changeAfterShoot() -> bool override{};

    private:
        // Local variables
};

class AfterShoot : public Sequence
{
public:
    virtual auto start() -> void override;
    virtual auto changeToLoadRingo() -> bool override{};
    virtual auto changeToSpeaker() -> bool override{};
    virtual auto changeToAMP() -> bool override{};
    virtual auto changeToReadyShoot() -> bool override{};
    virtual auto changeAfterShoot() -> bool override{};

    private:
        // Local variables
};