#ifndef STEPPER_H
#define STEPPER_H

#include <stdio.h>
#include "pico/stdlib.h"

typedef enum {
    X_AXIS,
    Y_AXIS
} Axis;

typedef enum {
    FWD,
    REV
} StepDirection;

typedef struct {
    Axis axis;
    bool is_stepping;
    int step_pin;
    int dir_pin; // should pins be uint??
    StepDirection current_direction;
    float current_position;
    float setpoint;
    int steps_remaining;  // Number of steps remaining to be executed
    int delay_ms;         // Delay between steps in milliseconds
} Stepper;

typedef struct Stepper_Driver
{
    int steps_to_take;
    int dir_pin;
    int step_pin;
    int fullstep;
    // PIO stm_pio;
    int stm_sm;
};

// void stepper_gpio_init()
// {

// }

/// @brief 
void stepper_pins_init_all();

/// @brief 
/// @param stepper 
/// @param axis 
/// @param delay_ms 
void init_stepper(Stepper *stepper, Axis axis, int delay_ms);
#endif