#ifndef limits_h
#define limits_h 


// Initialize the limits module
void limits_init();

void limits_disable();

// Perform one portion of the homing cycle based on the input settings.
void limits_go_home(uint8_t cycle_mask);

// Check for soft limit violations
void limits_soft_check(float *target);

#endif
