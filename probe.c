#include "system.h"
#include "settings.h"
#include "probe.h"

// Inverts the probe pin state depending on user settings.
uint8_t probe_invert_mask;


// Probe pin initialization routine.
void probe_init() 
{
 PROBE_DDR &= ~(PROBE_MASK); // Configure as input pins
  if (bit_istrue(settings.flags,BITFLAG_INVERT_PROBE_PIN)) { 
    PROBE_PORT &= ~(PROBE_MASK); // Normal low operation. Requires external pull-down.
    probe_invert_mask = 0;
  } else {
    PROBE_PORT |= PROBE_MASK;    // Enable internal pull-up resistors. Normal high operation.
    probe_invert_mask = PROBE_MASK; 
  }
}


// Returns the probe pin state. Triggered = true. Called by gcode parser and probe state monitor.
uint8_t probe_get_state() { return((PROBE_PIN & PROBE_MASK) ^ probe_invert_mask); }


// Monitors probe pin state and records the system position when detected. Called by the
// stepper ISR per ISR tick.
// NOTE: This function must be extremely efficient as to not bog down the stepper ISR.
void probe_state_monitor()
{
  if (sys.probe_state == PROBE_ACTIVE) { 
    if (probe_get_state()) {
      sys.probe_state = PROBE_OFF;
      memcpy(sys.probe_position, sys.position, sizeof(float)*N_AXIS);
      bit_true(sys.execute, EXEC_FEED_HOLD);
    }
  }
}
