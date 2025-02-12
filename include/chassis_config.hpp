#ifndef CHASSIS_CONFIG_HPP
#define CHASSIS_CONFIG_HPP

// Include necessary headers for the types you're using
#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep

// Declare rotation sensors as extern
extern pros::Rotation horizontalEnc;  // Rotation sensor for the horizontal wheel
extern pros::Rotation verticalEnc;    // Rotation sensor for the vertical wheel

// Declare tracking wheels as extern
extern lemlib::TrackingWheel horizontal;  // Horizontal tracking wheel
extern lemlib::TrackingWheel vertical;    // Vertical tracking wheel

// Declare drivetrain as extern
extern lemlib::Drivetrain drivetrain;  // Drivetrain object

// Declare controller settings for linear and angular motion as extern
extern lemlib::ControllerSettings linearController;  // Linear motion controller settings
extern lemlib::ControllerSettings angularController;  // Angular motion controller settings

// Declare odometry sensors as extern
extern lemlib::OdomSensors sensors;  // Odometry sensor group

// Declare input curves for throttle and steering as extern
extern lemlib::ExpoDriveCurve throttleCurve;  // Throttle input curve
extern lemlib::ExpoDriveCurve steerCurve;     // Steering input curve

// Declare chassis as extern
extern lemlib::Chassis chassis;  // Chassis object

#endif // CHASSIS_CONFIG_HPP
