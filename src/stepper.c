#include "stepper.h"
#include "pid_controller.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"

#include <stdio.h>
// #include "hardware/pio.h"
// #include "hardware/dma.h"
// #include "stepper.pio.h"  // Generated PIO header

#define X_STEP_PIN 14
#define X_DIR_PIN 15
#define Y_STEP_PIN 7
#define Y_DIR_PIN 8
#define X_MS1_PIN 10
#define X_MS2_PIN 11
#define Y_MS1_PIN 12
#define Y_MS2_PIN 13

#define X_STEPPER_POSITION_INIT 640
#define Y_STEPPER_POSITION_INIT 460

void stepper_pins_init_all()
{
    gpio_init(X_DIR_PIN);
    gpio_set_dir(X_DIR_PIN, GPIO_OUT);
    gpio_init(X_STEP_PIN);
    gpio_set_dir(X_STEP_PIN, GPIO_OUT);
    gpio_init(Y_DIR_PIN);
    gpio_set_dir(Y_DIR_PIN, GPIO_OUT);
    gpio_init(Y_STEP_PIN);
    gpio_set_dir(Y_STEP_PIN, GPIO_OUT);
    // what about microstep config pins (ms1...)
}

void init_stepper(Stepper *stepper, Axis axis, int delay_ms)
{
    stepper->axis = axis;
    stepper->current_position = stepper->axis == X_AXIS ? X_STEPPER_POSITION_INIT : Y_STEPPER_POSITION_INIT;
    stepper->setpoint = stepper->axis == X_AXIS ? X_SETPOINT_INIT : Y_SETPOINT_INIT;
    stepper->is_stepping = false;
    stepper->steps_remaining = 0;

    // Set up interrupt for stepper motor pin
    // gpio_set_irq_enabled_with_callback(stepper->step_pin, 0x3 | 0x4, true, on_stepper_x);
}

// Function to initialize the PIO program
// uint stepper_pio_init(PIO pio, uint sm, uint pin_out) {
//     // uint offset = pio_add_program(pio, &stepper_program);
//     // stepper_program_init(pio, sm, offset, pin_out);
//     // return offset;
//     printf("stepper pio init would be here but debugging!");
// }

// Function to move the stepper motor a specified number of steps
// void stepper_move_steps(PIO pio, uint sm, int num_steps, uint speed) {
//     stepper_program_set_steps(pio, sm, num_steps);
//     stepper_program_set_speed(pio, sm, speed);
//     pio_sm_exec(pio, sm, pio_encode_isr((void *)NULL));  // Start the stepper movement
// }
