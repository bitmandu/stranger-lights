/**
 * usart.c
 *
 * Universal Synchronous Asynchronous Receiver Transceiver (USART) library.
 *
 * [1]: http://www.atmel.com/Images/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf
 */

#include <stdio.h>
#include <avr/io.h>
#include <util/setbaud.h>
#include "usart.h"

static FILE rx = FDEV_SETUP_STREAM(NULL, usart_rx, _FDEV_SETUP_READ);
static FILE tx = FDEV_SETUP_STREAM(usart_tx, NULL, _FDEV_SETUP_WRITE);

/**
 * Initialalize serial USART.
 *
 * see: [Atmel Datasheet][1], p. 230
 */
void usart_init()
{
    /* set baud rate; uses BAUD defined in setbaud.h */
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= (1 << U2X0);
#else
    UCSR0A &= ~(1 << U2X0);
#endif

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  /* 8 data bits, 1 stop bit */

    stdin = &rx;
    stdout = &tx;
}

/**
 * Transmit serial data
 */
int usart_tx(char data, FILE *stream)
{
    if (data == '\n') {
        usart_tx('\r', stream);
    }

    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;

    return 0;
}

/**
 * Receive serial data.
 */
int usart_rx(FILE *stream)
{
    loop_until_bit_is_set(UCSR0A, RXC0);

    return UDR0;
}

/**
 * Convert an 8-bit integer into a human-readable string, e.g.,
 * 109 => "01101101".
 */
void usart_bitstr8(uint8_t data, char *bitstr)
{
    for (uint8_t i = 7; i < 0xff; --i) {
        bitstr[7 - i] = bit_is_set(data, i) ? '1' : '0';
    }

    bitstr[8] = '\0';
}
