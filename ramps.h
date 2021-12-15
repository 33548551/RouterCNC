/* 
 * File:   ramps.h
 * Author: arsi
 *
 * Created on September 1, 2014, 4:44 PM
 */
#ifndef RAMPS_H
#define	RAMPS_H


#ifdef	__cplusplus
extern "C" {
#endif

#include"cpu_map.h"
#include<stdint.h>
#include"fastio.h"




    // Ramps PB3 ( MISO/PCINT3 ) Digital pin 50 (MISO) ->Ramps AUX-3 pin 3
    // Ramps PB2 ( MOSI/PCINT2 ) Digital pin 51 (MOSI) ->Ramps AUX-3 pin 4
    // Ramps PB1 ( SCK/PCINT1 ) Digital pin 52 (SCK) -> Ramps AUX-3 pin 5
    // Motor ON PB4 - 10
    // Motor Dir PH6 - 9
    // Coolant PH6 - 8

    

#define X_STEP_PIN         54 //PF0 ( ADC0 )
#define X_DIR_PIN          55 //PF1 ( ADC1 )
#define X_ENABLE_PIN       38 //PD7 ( T0 )

#define Z_STEP_PIN         60 //PF6 ( ADC6 )
#define Z_DIR_PIN          61 //PF7 ( ADC7 )
#define Z_ENABLE_PIN       56 //PF2 ( ADC2 )

#define Y_STEP_PIN         46 //PL3 ( OC5A )
#define Y_DIR_PIN          48 //PL1 ( ICP5 )
#define Y_ENABLE_PIN       62 //PK0 ( ADC8/PCINT16 )

#define SPINDLE_ENABLE_PIN 10
#define SPINDLE_DIRECTION_PIN 9
#define COOLANT_FLOOD_PIN 8

#define CHECK(var,pos) ((var) & (1<<(pos)))

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
    extern void rampsCoolantOn();
    extern void rampsCoolantOff();

    inline void rampsCoolantOn() {
        WRITE(COOLANT_FLOOD_PIN, 1);
    }

    inline void rampsCoolantOff() {
        WRITE(COOLANT_FLOOD_PIN, 0);
    }

    inline void rampsLeftSpindle() {
        WRITE(SPINDLE_DIRECTION_PIN, 1);
    }

    inline void rampsRightSpindle() {
        WRITE(SPINDLE_DIRECTION_PIN, 0);
    }

    inline void rampsStartSpindle() {
        WRITE(SPINDLE_ENABLE_PIN, 1);
    }

    inline void rampsStopSpindle() {
        WRITE(SPINDLE_ENABLE_PIN, 0);
    }

    inline void rampsInitCoolant() {
        SET_OUTPUT(COOLANT_FLOOD_PIN);
    }

    inline void rampsInitSpindle() {
        SET_OUTPUT(SPINDLE_ENABLE_PIN);
        SET_OUTPUT(SPINDLE_DIRECTION_PIN);
    }

/**
     * Perform port direction init for ramps for steppers
     */
    inline void rampsInitSteppers() {
        SET_OUTPUT(X_STEP_PIN);
        SET_OUTPUT(Y_STEP_PIN);
        SET_OUTPUT(Z_STEP_PIN);
        SET_OUTPUT(X_DIR_PIN);
        SET_OUTPUT(Y_DIR_PIN);
        SET_OUTPUT(Z_DIR_PIN);
        SET_OUTPUT(X_ENABLE_PIN);
        SET_OUTPUT(Y_ENABLE_PIN);
        SET_OUTPUT(Z_ENABLE_PIN);
    }

/**
     * Perform set of EN driver signal
     * @param value
     */
    inline void rampsWriteDisable(uint8_t value) {
        if (CHECK(value, STEPPERS_DISABLE_BIT)) {
            WRITE(X_ENABLE_PIN, 1);
            WRITE(Y_ENABLE_PIN, 1);
            WRITE(X_ENABLE_PIN, 1);
        } else {
            WRITE(X_ENABLE_PIN, 0);
            WRITE(Y_ENABLE_PIN, 0);
            WRITE(X_ENABLE_PIN, 0);
        }
    }

/**
     * write stepper pulse
     * @param value
     */
    inline void rampsWriteSteps(uint8_t value) {
        if (CHECK(value, X_STEP_BIT)) {
            WRITE(X_STEP_PIN, 1);
        } else {
            WRITE(X_STEP_PIN, 0);
        }
        if (CHECK(value, Y_STEP_BIT)) {
            WRITE(Y_STEP_PIN, 1);
        } else {
            WRITE(Y_STEP_PIN, 0);
        }
        if (CHECK(value, Z_STEP_BIT)) {
            WRITE(Z_STEP_PIN, 1);
        } else {
            WRITE(Z_STEP_PIN, 0);
        }

    }

/**
     * set stepper direction
     * @param value
     */
    inline void rampsWriteDirections(uint8_t value) {
        if (CHECK(value, X_DIRECTION_BIT)) {
            WRITE(X_DIR_PIN, 1);
        } else {
            WRITE(X_DIR_PIN, 0);
        }
        if (CHECK(value, Y_DIRECTION_BIT)) {
            WRITE(Y_DIR_PIN, 1);
        } else {
            WRITE(Y_DIR_PIN, 0);
        }
        if (CHECK(value, Z_DIRECTION_BIT)) {
            WRITE(Z_DIR_PIN, 0);
        } else {
            WRITE(Z_DIR_PIN, 1);
        }
    }


#ifdef	__cplusplus
}
#endif

#endif	/* RAMPS_H */

