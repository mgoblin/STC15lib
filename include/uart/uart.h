#pragma once

#include <stdint.h>

#define BAUD 115200

void uart_init();
void uart_send_byte(uint8_t data);
uint8_t uart_receive_byte();

int putchar(int ch);
int getchar(void);
