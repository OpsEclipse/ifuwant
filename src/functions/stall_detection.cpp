#include "functions.hpp"

void is_stuck_check(void* param) {
    float intake_torque = 0;
    float angle = 0;

    while (true){
        intake_torque = intake1.get_torque();
        //pros::lcd::print(6, "%f", intake_torque);

        if (intake_torque > 0.34 && abs(intake1.get_actual_velocity()) < 1 && !reversed){
            is_stuck = true;
            intake1.move(60);
            pros::delay(100);
            intake1.move(0);
            
        }
        else{
            is_stuck = false;
            pros::delay(30);
        }
    }

}