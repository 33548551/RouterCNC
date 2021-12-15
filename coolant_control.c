
#include "system.h"
#include "coolant_control.h"
#include "protocol.h"
#include "gcode.h"
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

void coolant_init() {
    // COOLANT_FLOOD_DDR |= (1 << COOLANT_FLOOD_BIT);
    rampsInitCoolant();
  #ifdef ENABLE_M7
    COOLANT_MIST_DDR |= (1 << COOLANT_MIST_BIT);
  #endif
  coolant_stop();
}


void coolant_stop() {
    // COOLANT_FLOOD_PORT &= ~(1 << COOLANT_FLOOD_BIT);
    rampsCoolantOff();
  #ifdef ENABLE_M7
    COOLANT_MIST_PORT &= ~(1 << COOLANT_MIST_BIT);
  #endif
}


void coolant_run(uint8_t mode)
{
  if (sys.state == STATE_CHECK_MODE) { return; }

  protocol_auto_cycle_start();   //temp fix for M8 lockup
  protocol_buffer_synchronize(); // Ensure coolant turns on when specified in program.
  if (mode == COOLANT_FLOOD_ENABLE) {
        //COOLANT_FLOOD_PORT |= (1 << COOLANT_FLOOD_BIT);
        rampsCoolantOn();

  #ifdef ENABLE_M7  
    } else if (mode == COOLANT_MIST_ENABLE) {
      COOLANT_MIST_PORT |= (1 << COOLANT_MIST_BIT);
  #endif

  } else {
    coolant_stop();
  }
}
