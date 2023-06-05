#include "core1.h"
#include "pid_controller.h"
#include "stepper.h"
#include "pico/binary_info.h"

int main()
{
    // bi_decl(bi_program_description("First Blink"));
    // bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));
    
    stdio_init_all();
    uart_init_all();

    PIDController controller_x, controller_y;
    pid_controller_init_all(&controller_x, 0.5f, 0.0f, 0.0f);
    pid_controller_init_all(&controller_y, 0.5f, 0.0f, 0.0f);

    Stepper stepper_x, stepper_y;
    init_stepper(&stepper_x, X_AXIS, 10);
    init_stepper(&stepper_y, Y_AXIS, 10);

    // start RP2040 second core (core_1)
    multicore_launch_core1(core1_main);

    while (1) {
        fsm_process(&controller_x, &controller_y, &stepper_x, &stepper_y);
        sleep_us(20);  // Non-blocking delay to reduce CPU usage
    }

    return 0;
}
