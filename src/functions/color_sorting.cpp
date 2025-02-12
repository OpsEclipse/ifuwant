#include "functions.hpp"


void color_check(void* param) {
    // Variables for RGB values
    float hue = 0;
    int x = 0;

    while (true) {
        // Read RGB values from the optical sensor
        auto k = optical.get_proximity();
        auto c = optical.get_rgb();
        
        if (!is_stuck){
            is_ring_stopped = false;
            if ((k > 60 && c.brightness > 0.05) && (c.red > c.blue) == (team_color == 'B')) { // ((team_color == 'R' && hue > 137) || (team_color == 'B' && hue < 22))
                // Wrong color detected: Reject object
                pros::delay(160);
                intake1.move(120); 
                pros::delay(200);
            } 
            else if(ringStop){
                if ((k > 60 && c.brightness > 0.05) && (c.red > c.blue) == (team_color == 'B') || x > 300){
                    intake1.move(0);
                    while (ringStop){
                        is_ring_stopped = true;
                        pros::delay(200);
                    }
                }
                else{
                    x++;
                    intake1.move(-95);
                }
                
            }
            else {
                // Correct color detected or no wrong color
                if (intake_on) {
                    intake1.move(-127); // Keep the intake running forward
                } else if (!reversed){
                    intake1.move(0);   // Stop the intake if not needed
                }
            }
        }

        

        // Small delay to avoid overwhelming the system
        pros::delay(10);
        if (opC){
            break;
        }
    }
}