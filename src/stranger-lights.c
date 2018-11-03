/**
 * @file stranger-lights.c
 *
 * Stranger Things alphabet message wall.
 */

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "ledstrip.h"
#include "rgb.h"
#include "pins.h"
#include "usart.h"

#define MSG_SIZE 64

int main(void)
{
    usart_init();
    DDR |= (1 << PIN);

    char message[MSG_SIZE];

    rgb *leds;
    leds = (rgb *) calloc(sizeof(rgb), NLED);

    printf("--[ stranger-lights ]--\r\n");

    for (;;)
    {
        fgets(message, MSG_SIZE, stdin);

        // string is terminated with "...\r\0"; remove the \r
        message[strlen(message) - 1] = '\0';
        printf("received: %s\r\n", message);

        if (message[0] == '~') {
            flash(leds, NLED);
        } else {
            display(leds, NLED, message);
        }
    }

    free(leds);
    return 0;
}
