#ifndef spindle_control_h
#define spindle_control_h 


// Initializes spindle pins and hardware PWM, if enabled.
void spindle_init();

// Sets spindle direction and spindle rpm via PWM, if enabled.
void spindle_run(uint8_t direction, float rpm);

// Kills spindle.
void spindle_stop();

#endif
