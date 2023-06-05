#include "uart.h"
#include <stdio.h>

void core1_main() {
    while (1) {
        uart_read_data();
        sleep_us(600);
    }
}                                                                  