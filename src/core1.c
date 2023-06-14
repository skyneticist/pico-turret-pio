#include "uart.h"
#include <stdio.h>

void core1_main() {
    while (1) {
        // How to run interrupt on this other core when 
        // not running an infinite loop to update it?
        
        // uart_read_data(); 
        sleep_us(600);
    }
}                                                                 