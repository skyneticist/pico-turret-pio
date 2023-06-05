#ifndef FSM_H
#define FSM_H

#include "pid_controller.h"
#include "stepper.h"
#include "uart.h"

typedef enum {
    IDLE_STATE,
    TRACKING_STATE,
    ERROR_STATE
} State;

extern State current_state;

/// @brief 
/// @param controller_x 
/// @param controller_y 
/// @param stepper_x 
/// @param stepper_y 
void fsm_process(PIDController *controller_x, PIDController *controller_y, Stepper *stepper_x, Stepper *stepper_y);

#endif