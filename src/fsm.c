#include "fsm.h"
#include "global.h"
#include <stdio.h>
#include "pico/stdlib.h"
// #include "hardware/pio.h"
// #include "hardware/dma.h"
#include "stepper.h"
// #include "stepper.pio.h"  // Generated PIO header

float deltaTime = 0.1f;
extern State current_state;

void fsm_process(PIDController *controller_x, PIDController *controller_y, Stepper *stepper_x, Stepper *stepper_y)
{
    float output_x;
    float output_y;

    extern volatile float setpoint_x;
    extern volatile float setpoint_y;

    // PIO pio = pio0;

    // uint sm_x = 0;
    // stepper_pio_init(pio, sm_x, X_STEP_PIN);

    // uint sm_y = 0;
    // stepper_pio_init(pio, sm_y, Y_STEP_PIN);

    switch (current_state) {
        case IDLE_STATE:
            printf("FSM__IDLE_STATE\n");
            break;

        case TRACKING_STATE:
            // Perform tracking and stepper motor control based on the setpoint_x and setpoint_y values
            // Adjust stepper motors to track the object
            // ...

            output_x = update_pid_controller(&controller_x, setpoint_x, stepper_x->current_position, deltaTime);
            output_y = update_pid_controller(&controller_y, setpoint_y, stepper_y->current_position, deltaTime);

            // step_stepper_motor(&stepper_x, output_x, 10);
            // step_stepper_motor(&stepper_y, output_y, 10);

            // // Move the X stepper motor 100 steps at a speed of 1000 steps per second
            // stepper_move_steps(pio, sm_x, output_x, 1000);

            // // Move the Y stepper motor 100 steps at a speed of 1000 steps per second
            // stepper_move_steps(pio, sm_y, output_y, 1000);

            printf("output_x: %f", output_x);
            printf("output_y: %f", output_y);

            char x_string;
            fprintf(x_string, "%f", stepper_x->current_position);

            char y_string;
            fprintf(y_string, "%e", stepper_y->current_position);

            char xy_string;
            strcpy(xy_string, x_string);
            strcat(xy_string, " "); // newline here?
            strcat(xy_string, y_string);
            strcat(xy_string, "\n");

            // might not be the best place to put this
            uart_puts(UART_ID, xy_string);
            // sleep_us ???
            
            // Transition back to the idle state
            current_state = IDLE_STATE;
            break;

        case ERROR_STATE:
            // Handle error conditions
            // ...
            break;
    }
}
