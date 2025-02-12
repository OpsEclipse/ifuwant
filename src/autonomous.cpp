#include "functions.hpp"
#include "chassis_config.hpp"

ASSET(red_ring_1_txt);

void red_SAWP() { std::cout << "Running best auton" << std::endl; }
void blue_SAWP() { std::cout << "Running simple auton " << std::endl; }
void red_ring() { 
        chassis.setPose(-58.955, 8.841, 240, false);
        chassis.moveToPoint(-23.744, 22.786, 1000, {.forwards = false});
        clampOn = true;
        chassis.turnToPoint(-23.483, 47.537, 1000);
        chassis.waitUntilDone();
        intake_on = true;
        chassis.moveToPoint(-23.483, 47.537, 1000);
        chassis.follow(red_ring_1_txt, 15, 5000, true);
        clampOn = false;
        intake_on = false;
        chassis.turnToPoint(-23.831, -23.755, 1000, {.forwards = false});
        chassis.moveToPoint(-23.831, -23.755, 2000, {.forwards = false});
        chassis.waitUntil(10);
        clampOn = true;
    }
void blue_ring() { std::cout << "Running skills" << std::endl; }