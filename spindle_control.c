#include "system.h"
#include "spindle_control.h"
#include "protocol.h"
#include "gcode.h"
#include"fastio.h"

extern void rampsInitCoolant();
extern void rampsInitSpindle();
extern void rampsInitSteppers();
extern void rampsWriteDisable(uint8_t value);
extern void rampsWriteSteps(uint8_t value);
extern void rampsWriteDirections(uint8_t value);
extern void rampsStartSpindle();
extern void rampsStopSpindle();
extern void rampsLeftSpindle();
extern void rampsRightSpindle();


void spindle_init() {
    // On the Uno, spindle enable and PWM are shared. Other CPUs have seperate enable pin.
#ifdef VARIABLE_SPINDLE
    SPINDLE_PWM_DDR |= (1 << SPINDLE_PWM_BIT); // Configure as PWM output pin.
#ifndef CPU_MAP_ATMEGA328P 
    SPINDLE_ENABLE_DDR |= (1 << SPINDLE_ENABLE_BIT); // Configure as output pin.
#endif     
#else
    //SPINDLE_ENABLE_DDR |= (1<<SPINDLE_ENABLE_BIT); // Configure as output pin.
#endif
    // SPINDLE_DIRECTION_DDR |= (1<<SPINDLE_DIRECTION_BIT); // Configure as output pin.
    rampsInitSpindle();
    spindle_stop();
}

void spindle_stop() {
    // On the Uno, spindle enable and PWM are shared. Other CPUs have seperate enable pin.
#ifdef VARIABLE_SPINDLE
    TCCRA_REGISTER &= ~(1 << COMB_BIT); // Disable PWM. Output voltage is zero.
#ifndef CPU_MAP_ATMEGA328P 
    SPINDLE_ENABLE_PORT &= ~(1 << SPINDLE_ENABLE_BIT); // Set pin to low.
#endif
#else
    // SPINDLE_ENABLE_PORT &= ~(1 << SPINDLE_ENABLE_BIT); // Set pin to low.
    rampsStopSpindle();
#endif  
}

void spindle_run(uint8_t direction, float rpm) {
    if (sys.state == STATE_CHECK_MODE) {
        return;
    }

    // Empty planner buffer to ensure spindle is set when programmed.
    protocol_auto_cycle_start(); //temp fix for M3 lockup
    protocol_buffer_synchronize();

    // Halt or set spindle direction and rpm. 
    if (direction == SPINDLE_DISABLE) {

        spindle_stop();

    } else {

        if (direction == SPINDLE_ENABLE_CW) {
            //  SPINDLE_DIRECTION_PORT &= ~(1 << SPINDLE_DIRECTION_BIT);
            rampsLeftSpindle();
        } else {
            //  SPINDLE_DIRECTION_PORT |= (1 << SPINDLE_DIRECTION_BIT);
            rampsRightSpindle();
        }

#ifdef VARIABLE_SPINDLE
        // TODO: Install the optional capability for frequency-based output for servos.
#define SPINDLE_RPM_RANGE (SPINDLE_MAX_RPM-SPINDLE_MIN_RPM)
        TCCRA_REGISTER = (1 << COMB_BIT) | (1 << WAVE1_REGISTER) | (1 << WAVE0_REGISTER);
        TCCRB_REGISTER = (TCCRB_REGISTER & 0b11111000) | 0x02; // set to 1/8 Prescaler
        rpm -= SPINDLE_MIN_RPM;
        if (rpm > SPINDLE_RPM_RANGE) {
            rpm = SPINDLE_RPM_RANGE;
        } // Prevent uint8 overflow
        uint8_t current_pwm = floor(rpm * (255.0 / SPINDLE_RPM_RANGE) + 0.5);
        OCR_REGISTER = current_pwm;

#ifndef CPU_MAP_ATMEGA328P // On the Uno, spindle enable and PWM are shared.
        SPINDLE_ENABLE_PORT |= (1 << SPINDLE_ENABLE_BIT);
#endif
#else   
        // SPINDLE_ENABLE_PORT |= (1 << SPINDLE_ENABLE_BIT);
        rampsStartSpindle();
        
#endif

    }
}
