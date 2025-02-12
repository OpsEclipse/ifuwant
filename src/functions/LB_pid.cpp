#include "functions.hpp"


lemlib::PID armPID(2.5, 0, 1);

void LBpidTask(void* param) {
        float currentTheta = 0;
        float prevMotorPower = 0;
        exitRange = 40;
        float error = 0.0f;
        float allianceS = false;
        pros::delay(25);

        while(true){

            if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {

                allianceS = false;
                sequenceStep = (sequenceStep + 1) % 4;

                switch (sequenceStep) {
                    case 1:
                        targetTheta = 16;
                        lb1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
                        exitRange = 0.2;
                        break;
                    case 9:
                        targetTheta = 60;
                        lb1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
                        exitRange = 5;
                        break;
                    case 2:
                        targetTheta = 170;
                        lb1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
                        exitRange = 40;
                        break;
                }
            }

            if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
                    if (allianceS == false){
                        targetTheta = 230;
                        lb1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
                        exitRange = 5;
                    }
                    else{
                        sequenceStep = 0;
                        targetTheta = 0;
                        lb1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
                        exitRange = 10;
                    }
                    allianceS = !allianceS;
            }


                currentTheta = (float)ladyBrownRotation.get_angle() / 100;

                if (currentTheta > 350){
                    currentTheta = currentTheta - 360;
                }
                // Get output from PID (Target - Actual (Accounts for gear ratio))
                

                error = targetTheta - currentTheta;
                
                if (fabs(error) > exitRange) {
                    double out = armPID.update(error);
                    
                    lb1.move_voltage(out * 100);  // Output to motor
                } 
                else if (sequenceStep == 2 && fabs(error) < 30){
                        sequenceStep = 0;
                        targetTheta = 0;
                        exitRange = 40;
                }
                else{lb1.brake();}  // Stop the motor when within range with said brake mode
                
                pros::delay(40);  // Don't hog the CPU
            
        } 

    
}