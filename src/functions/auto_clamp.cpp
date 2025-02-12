#include "functions.hpp"

void clampCheck(void* param){
    bool check = false;
    int distance = clamp_sensor.get_distance();
    

    while(true){
        distance = clamp_sensor.get();
        //pros::lcd::print(6, "%i", distance);
        if (clampOn && distance < 25 && !current){
            pros::delay(500);
            clamp.set_value(true);
            current = true;
        }
        else if (!clampOn && current){
            clamp.set_value(false);
            current = !current;
            pros::delay(10);
        }

        if (opC){
            break;
        }
        pros::delay(20);
    }
}