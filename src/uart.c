#include "uart.h"
#include "pid_controller.h"
#include "fsm.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "pico/stdlib.h"

const uint LED_PIN = 25;

// hmm - better way?
char uart_buffer[50];
bool new_data_received = false;
volatile bool uart_interrupt_flag = false;

extern volatile float setpoint_x;
extern volatile float setpoint_y;

extern State current_state;

// UART interrupt handler
void on_uart_rx() {
    char received_char;
    debug_led_fast();
    while (uart_is_readable(UART_ID)) {
        received_char = uart_getc(UART_ID);
        uart_buffer[strlen(uart_buffer)] = received_char;

        if (received_char == '\n') {
            debug_led_fast();
            uart_buffer[strlen(uart_buffer) - 1] = '\0';  // Null-terminate the received data
            new_data_received = true;  // Set the flag to indicate new data is received
            uart_interrupt_flag = true;
            break;
        }
    }
}

void uart_init_all() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_put(LED_PIN, 1);
    sleep_ms(500);
    gpio_put(LED_PIN, 0);
    sleep_ms(500);
    gpio_put(LED_PIN, 1);
    sleep_ms(500);

    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    uart_set_hw_flow(UART_ID, false, false);  // Disable hardware flow control

    // Set up UART interrupt
    uint32_t uart_irq = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;
    irq_set_exclusive_handler(uart_irq, on_uart_rx);
    irq_set_enabled(uart_irq, true);
    uart_set_irq_enables(UART_ID, true, false);  // Enable receive interrupt, disable transmit interrupt

    gpio_put(LED_PIN, 1);
    sleep_ms(800);
    gpio_put(LED_PIN, 0);
    sleep_ms(800);
    gpio_put(LED_PIN, 1);
    sleep_ms(800);
    gpio_put(LED_PIN, 0);
    sleep_ms(800);
    gpio_put(LED_PIN, 1);
    sleep_ms(800);
    gpio_put(LED_PIN, 0);
    sleep_ms(800);
}

void uart_read_data() {
    if (uart_interrupt_flag) {
        uart_interrupt_flag = false;
        new_data_received = true;
        sscanf(uart_buffer, "%f %f", &setpoint_x, &setpoint_y);
        memset(uart_buffer, 0, sizeof(uart_buffer));  // Clear the buffer
        current_state = TRACKING_STATE;
    } else {
        debug_led_slow();
        new_data_received = false;
        printf("new_data_received: %d\n", new_data_received);
        current_state = IDLE_STATE;
        uart_interrupt_flag = false; // not sure if I would need this
    }
}

void debug_led_fast()
{
    gpio_put(LED_PIN, 0);
    sleep_ms(250);
    gpio_put(LED_PIN, 1);
    sleep_ms(500);
}

void debug_led_slow()
{
    gpio_put(LED_PIN, 0);
    sleep_ms(1500);
    gpio_put(LED_PIN, 1);
    sleep_ms(1500);
}