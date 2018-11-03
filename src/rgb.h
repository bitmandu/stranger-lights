/**
 * @file rgb.h
 *
 * RGB color data types and definitions.
 */

#pragma once

#include <avr/io.h>

/**
 * RGB values in the in-memory order of the LED strip (sometimes GRB).
 */
struct __attribute__ ((__packed__)) rgb
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

typedef struct rgb rgb;

#define APRICOT {255, 215, 180}
#define AQUA {0, 255, 255}
#define BLACK {0, 0, 0}
#define BLUE {0, 130, 200}
#define BROWN {170, 110, 40}
#define CYAN {70, 240, 240}
#define FUCHSIA {255, 0, 255}
#define GRAY {128, 128, 128}
#define GREEN {60, 180, 75}
#define LAVENDER {230, 190, 255}
#define LIME {210, 245, 60}
#define MAGENTA {240, 50, 230}
#define MAROON {128, 0, 0}
#define MINT {170, 255, 195}
#define NAVY {0, 0, 128}
#define OLIVE {128, 128, 0}
#define ORANGE {245, 130, 48}
#define PINK {250, 190, 190}
#define PURPLE {145, 30, 180}
#define RED {230, 23, 75}
#define SILVER {192, 192, 192}
#define TEAL {0, 128, 128}
#define WHITE {255, 255, 255}
#define YELLOW {255, 225, 25}
