#include "robodash/api.h"
#include "functions.hpp"
#include "chassis_config.hpp"

rd::Selector selector({
    {"Red Ring Side auton", &red_ring},
    {"Blue Ring Side auton", &blue_ring},
    {"Red SAWP", &red_SAWP},
    {"Blue SAWP", &blue_SAWP},
});

rd::Console console;

rd_view_t *rd_view_create(const char *name);
void rd_view_focus(rd_view_t *name);

//rd::Console hi;


void initialize() {
    selector.focus();
    //pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors

    optical.set_led_pwm(95);


    // thread to for brain screen and position logging
    pros::Task screenTask([&]() {
        while (true) {
            //print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            

            
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });

    pros::Task isStuckTask(
        is_stuck_check,
        nullptr,
        "stuck task"
    );

    pros::Task clampTask(
        clampCheck,
        nullptr,
        "clamp task"
    );

    pros::Task color_check_task(
        color_check,
        nullptr,
        "color check task"
    );

}

void disabled() {}

void competition_initialize() {}

// get a path used for pure pursuit
// this needs to be put outside a function
ASSET(example2_txt); // '.' replaced with "_" to make c++ happy

int autonRoute = 2;
void autonomous() {
    
    if (autonRoute == 0){
        //red goal rush
        intake_on = false;
        chassis.moveToPoint(0, 41.5, 1000, {.earlyExitRange = 1});
        pros::delay(500);
        doinker.set_value(true);
        chassis.waitUntilDone();
        doinker.set_value(false);
        pros::delay(100);
        chassis.moveToPoint(0, 30, 1000, {.forwards = false});
        chassis.waitUntilDone();
        doinker.set_value(true);
        pros::delay(400);
        chassis.turnToHeading(91, 1000, {.maxSpeed = 90});
        pros::delay(50);
        doinker.set_value(false);
        chassis.moveToPoint(-13.5, 33.6, 1000, {.forwards = false, .maxSpeed = 40});
        chassis.waitUntilDone();
        clamp.set_value(true);
        pros::delay(200);
        intake_on = true;
        chassis.moveToPoint(17.5, 33.1, 2000);
        chassis.waitUntilDone();
        pros::delay(600);
        chassis.moveToPoint(-3.6, 33.2, 1000, {.forwards = false});
        chassis.turnToHeading(171, 1000);
        
        chassis.waitUntilDone();
        doinker.set_value(true);
        chassis.moveToPoint(0.6, 13.5, 2000, {.minSpeed = 60, .earlyExitRange = 3});
        chassis.waitUntil(15);
        intake1.move(0);
        intake2.move(0);
        clamp.set_value(false);
        chassis.swingToHeading(108, DriveSide::LEFT, 1000);
        chassis.moveToPoint(29, 0.5, 1000);
        chassis.turnToHeading(28, 1000);
        chassis.waitUntil(20);
        doinker.set_value(false);
        //pros::delay(500);
        chassis.turnToHeading(160, 1000);
        chassis.waitUntilDone();
        pros::delay(50);
        chassis.setPose(0, 0, 0);
        chassis.moveToPoint(0, -30, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 5});
        chassis.swingToHeading(90, DriveSide::LEFT, 1000, {.minSpeed = 30, .earlyExitRange = 15});
        chassis.swingToHeading(10, DriveSide::LEFT, 1000);
        chassis.moveToPoint(0, -40, 1000, {.forwards = false});
    }
    if (autonRoute == 1){
        
        //Red side ring rush
        
        //targetTheta = 180;
        //lb1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        //exitRange = 40;

    }
    if (autonRoute == 2){
        //blue ring rush
        rush.set_value(true);
        chassis.moveToPoint(0, 43.5, 1000, {.minSpeed = 60, .earlyExitRange = 1});
        chassis.moveToPoint(0, 20, 1000, {.forwards = false, .maxSpeed = 40});
        chassis.swingToHeading(-27, DriveSide::RIGHT, 700, {.minSpeed = 10, .earlyExitRange = 0.5});
        chassis.moveToPoint(3.96, 24.8, 800, {.forwards = false});
        chassis.waitUntilDone();
        rush.set_value(false);
        pros::delay(100);
        chassis.moveToPoint(9.2, 12, 1000, {.forwards = false});
        
        chassis.turnToPoint(-16.9, 33.2, 1000, {.forwards = false});
        chassis.moveToPoint(-16.9, 33.2, 1000, {.forwards = false, .maxSpeed = 60});
        chassis.waitUntilDone();
        pros::delay(100);
        
        clamp.set_value(true);
        chassis.moveToPose(-14.5, 29.3, 63.5, 700);
        chassis.waitUntilDone();
        intake_on = true;
        chassis.moveToPoint(10.3, 44.1, 2000, {.maxSpeed = 45});
        chassis.moveToPoint(2, 37.38, 1000, {.forwards = false});
        chassis.turnToPoint(-6.4, -10.4, 1000);
        chassis.waitUntilDone();
        targetTheta = 16;
        exitRange = 0.2;
        lb1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        chassis.moveToPoint(-6.25, -6.3, 1000);
        chassis.waitUntilDone();
        targetTheta = 16;
        exitRange = 1;
        lb1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        chassis.moveToPoint(-4.6, 2, 1000, {.forwards = false});

        chassis.turnToHeading(254, 1000);
        chassis.waitUntilDone();
        chassis.setPose(0, 0, 0);
        chassis.moveToPoint(-102, 35, 1000, {.maxSpeed = 60});
        chassis.turnToHeading(220, 1000);
        
        //chassis.swingToHeading(90, DriveSide::LEFT, 300);
    }
    if(autonRoute == 9){
        intake_on = true;
    }
}


/**
 * Runs in driver control
 */
void opcontrol() {

    pros::Task lbPidTask(
        LBpidTask,
        nullptr,
        "LB PID Task"
    );
    
    optical.set_led_pwm(0);

    opC = true;
    auton = false;

    bool doinkerState = false;
    bool rushState = false;

    ringStop = false;

    while (true) {
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        if (current){
            chassis.arcade(leftY, rightX, false, 0.45);
        }
        else{
            chassis.arcade(leftY, rightX, false, 0.18);
        }
        


        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
            current = !current; // Toggle piston state
            clamp.set_value(current);
        } 

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
            doinkerState = !doinkerState; // Toggle piston state
            doinker.set_value(doinkerState);
        } 

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
            rushState = !rushState; // Toggle piston state
            rush.set_value(rushState);
        }

        // Intake control
        
            if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
                //intake_on = true;
                if(!is_stuck){
                    reversed = false;
                    intake1.move(-127);
                    intake2.move(127);
                }
                
            } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
                reversed = true;
                intake1.move(127);
                intake2.move(-127);
            }
            
            else {
                reversed = false;
                intake1.move(0);
                intake2.move(0);
            }
        

        pros::delay(15);  // Small delay to avoid overwhelming the system
}
}