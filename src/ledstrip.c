/**
 * @file ledstrip.c
 *
 * Functions to constrol the LED strip.
 */

#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include "ledstrip.h"
#include "pinout.h"
#include "rgb.h"
#include "ws2811.h"

static const uint8_t MAP[26] = {49, 48, 47, 46, 45, 44, 43, 42,
                                32, 33, 34, 35, 36, 37, 38, 39, 40,
                                30, 29, 28, 27, 26, 25, 24, 23, 22};

static const rgb COLOR[NLED] = {
    BLACK, BLACK, BLACK, BLACK, BLACK,
    BLACK, BLACK, BLACK, BLACK, BLACK,
    BLACK, BLACK, BLACK, BLACK, BLACK,
    BLACK, BLACK, BLACK, BLACK, BLACK,
    BLACK, BLACK, GREEN, BLUE, RED,
    BLUE, YELLOW, LAVENDER, GREEN, PURPLE,
    BLUE, RED, YELLOW, LAVENDER, GREEN,
    PURPLE, BLUE, RED, YELLOW, LAVENDER,
    GREEN, PURPLE, BLUE, RED, YELLOW,
    LAVENDER, GREEN, PURPLE, BLUE, RED};

/**
 * Turn off LEDs.
 *
 * @param leds LED RGB array
 * @param n Number of LEDs
 */
void blank(rgb *leds, uint16_t n)
{
    memset(leds, 0, n*sizeof(rgb));
    send(leds, n, PIN);
}

/**
 * Display a message string.
 *
 * @param leds LED RGB array
 * @param n Number of LEDs
 * @param message Message to display
 */
void display(rgb *leds, uint16_t n, char *message)
{
    for (uint8_t i = 0; i < strlen(message); ++i) {
        light(leds, n, message[i]);
        _delay_ms(1125);

        blank(leds, n);
        _delay_ms(85);
    }
}

/**
 * Flash all LEDs.
 *
 * @param leds LED RGB array
 * @param n Number of LEDs
 */
void flash(rgb *leds, uint16_t n)
{
    for (uint8_t k = 0; k < 3; ++k) {
        for (uint8_t i = 0; i < n; ++i) {
            leds[i] = COLOR[i];
        }

        send(leds, n, PIN);
        _delay_ms(150);

        blank(leds, n);
        _delay_ms(85);
    }
}

/**
 * Turn on LED for a letter.
 *
 * @param leds LED RGB array
 * @param n Number of LEDs
 * @param letter Letter to turn on
 */
void light(rgb *leds, uint16_t n, char letter)
{
    uint8_t i = MAP[letter - 'a'];

    memset(leds, 0, n*sizeof(rgb));
    leds[i] = COLOR[i];
    send(leds, n, PIN);
}
