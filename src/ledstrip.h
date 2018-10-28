/**
 * @file ledstrip.h
 *
 * LED strip definitions and function declarations.
 */

#pragma once

#include "rgb.h"

#define NLED 50

void blank(rgb *, uint16_t);
void display(rgb *, uint16_t, char *);
void flash(rgb *, uint16_t);
void light(rgb *, uint16_t, char);
