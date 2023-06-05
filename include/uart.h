#ifndef UART_H
#define UART_H

#include "hardware/uart.h"

#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_RX_PIN 0
#define UART_TX_PIN 1

void uart_init_all();
void on_uart_rx();
void uart_read_data();

#endif
