#include "functions.hpp"
#include "chassis_config.hpp"

// tracking wheels
// horizontal tracking wheel encoder. Rotation sensor, port 20, not reversed
pros::Rotation horizontalEnc(12);
// vertical tracking wheel encoder. Rotation sensor, port 11, reversed
pros::Rotation verticalEnc(-19);
// horizontal tracking wheel. 2.75" diameter, 5.75" offset, back of the robot (negative)
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_275, 0);
// vertical tracking wheel. 2.75" diameter, 2.5" offset, left of the robot (negative)
lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_275, 0.5);

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              11, // 11 inch track width
                              lemlib::Omniwheel::NEW_275, // using new 4" omnis
                              600, // drivetrain rpm is 600
                              4 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
lemlib::ControllerSettings linearController(6.3, // proportional gain (kP)//
                                            0, // integral gain (kI) 
                                            25, // derivative gain (kD) //
                                            0, // anti windup
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            4, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            0 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(2.8, // proportional gain (kP) //2.8
                                             0, // integral gain (kI)
                                             25.5, // derivative gain (kD) //25.5
                                             0, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             5, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// sensors for odometry
lemlib::OdomSensors sensors(&vertical, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            &horizontal, // horizontal tracking wheel
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttleCurve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steerCurve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// motor groups
pros::MotorGroup leftMotors({-6, 7, 8},pros::MotorGearset::blue); // left motor group - ports 3 (reversed), 4, 5 (reversed)
pros::MotorGroup rightMotors({1, -2, -3}, pros::MotorGearset::blue); // right motor group - ports 6, 7, 9 (reversed)

// Inertial Sensor on port 17
pros::Imu imu(11);

//Pneumatics (pros::ADIDigitalOut _NAME_ (ADI_PORT))
pros::ADIDigitalOut clamp('H');
pros::ADIDigitalOut doinker('G');
pros::ADIDigitalOut rush('F');

//Other motors
pros::Motor intake1(-14, pros::MotorGearset::blue);
pros::Motor intake2(-10, pros::MotorGearset::green);

pros::Motor lb1 (21, pros::MotorGearset::green);

//rotation sensor
pros::Rotation ladyBrownRotation(15); //make sure you get the right port
pros::Distance clamp_sensor(13);

//optical
pros::Optical optical(16);

//current team color
char team_color = 'B';

bool intake_on = false;
bool reversed = false;

bool auton = false;
bool opC = false;

float targetTheta = 0;
float exitRange = 0;

bool clampOn = false;
bool current = false;

bool ringStop = false;
bool is_ring_stopped = false;

int sequenceStep = 0;

bool is_stuck = false;