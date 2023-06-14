#include "uart.h"
#include "pid_controller.h"
#include "fsm.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "pico/stdlib.h"

const uint LED_PIN = 25;

// hmm - better way?
char uart_buffer[50];

extern volatile float setpoint_x;
extern volatile float setpoint_y;

extern State current_state;

// UART interrupt handler
void on_uart_rx() {
    led_debug(2);
    char received_char;
    while (uart_is_readable(UART_ID)) {
        received_char = uart_getc(UART_ID);
        uart_buffer[strlen(uart_buffer)] = received_char;

        if (received_char == '\n') {
            led_debug(4);
            uart_buffer[strlen(uart_buffer) - 1] = '\0';  // Null-terminate the received data
            sscanf(uart_buffer, "%f %f", &setpoint_x, &setpoint_y);
            memset(uart_buffer, 0, sizeof(uart_buffer));  // Clear the buffer
            current_state = TRACKING_STATE;

            break;
        }
    }
    current_state = IDLE_STATE;
}

void uart_init_all() {
    led_debug(1);
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    uart_set_hw_flow(UART_ID, false, false);  // Disable hardware flow control

    // Set up UART interrupt
    uint32_t uart_irq = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;
    irq_set_exclusive_handler(uart_irq, on_uart_rx); // Set interrupt handler on interrupt channel
    irq_set_enabled(uart_irq, true); // Enable the interrupt
    uart_set_irq_enables(UART_ID, true, false);  // Enable uart receive interrupt, disable transmit interrupt
}

void led_debug(int flash_count) {
    while (flash_count > 0) {
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
    }
}
