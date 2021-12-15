// GRBL RAMPS 1.4 port
// 
//**************************************************************************************
// Ramps 1.4         |    GRBL                             |    Test
// Eje X             |   Eje X                             |     OK
// Eje Z             |   Eje Y x2 (clonado)                |     OK
// Eje Y             |   Eje Z                             |     OK
// Ramps AUX-3 pin 3 |   min X                             |     OK
// Ramps AUX-3 pin 4 |   min Y                             |     OK
// Ramps AUX-3 pin 5 |   min Z                             |     not tested
// D10               |   motor ON                          |     not tested
// D9                |   motor direction                   |     not tested
// D8                |   coolant on                        |     not tested
//***************************************************************************************
// PARA LA MAQUINA SE A CAMBIADO EL PIN DEL PUERTO DE  LOS  EJES Y  ,  Z , 
// LOS LIMITES NO SE HAN  MODIFICADO   
// 

#include <system.h>
#include <nuts_bolts.h>
#include <eeprom.h>
#include <gcode.h>

#include <config.h>
#include <defaults.h>
#include <settings.h>
#include <fastio.h>

#include <stepper.h>
#include <planner.h>
#include <report.h>
#include <serial.h>
#include <cpu_map.h>
#include <limits.h>
#include <motion_control.h>
#include <spindle_control.h>
#include <protocol.h>
#include <probe.h>
#include <print.h>
#include <coolant_control.h>
