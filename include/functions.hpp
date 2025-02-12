#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep

// Controller
extern pros::Controller controller;

// Motor groups
extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

// Inertial Sensor
extern pros::Imu imu;

// Pneumatics
extern pros::ADIDigitalOut clamp;
extern pros::ADIDigitalOut doinker;
extern pros::ADIDigitalOut rush;

// Other motors
extern pros::Motor intake1;
extern pros::Motor intake2;
extern pros::Motor lb1;

// Rotation sensor
extern pros::Rotation ladyBrownRotation;

//Distance sensor
extern pros::Distance clamp_sensor;

// Optical sensor
extern pros::Optical optical;

// Team color
extern char team_color;

// State flags
extern bool intake_on;
extern bool reversed;
extern bool auton;
extern bool opC;

extern float targetTheta;
extern float exitRange;

extern bool clampOn;
extern bool current;
extern bool ringStop;
extern bool is_ring_stopped;

extern int sequenceStep;

extern bool is_stuck;

// Functions
void LBpidTask(void* param);
void is_stuck_check(void* param);
void color_check(void* param);
void clampCheck(void* param);
void clampCheck(void* param);

void red_SAWP();
void blue_SAWP();
void red_ring();
void blue_ring();


#endif