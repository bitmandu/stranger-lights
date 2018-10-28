/**
 * usart.h
 */

#ifndef USART_H
#define USART_H

#include <stdio.h>

void usart_init();
void usart_bitstr8(uint8_t, char*);
int usart_rx(FILE*);
int usart_tx(char, FILE*);

#endif
