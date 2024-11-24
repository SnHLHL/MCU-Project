/*
 * input_reading.h
 *
 *  Created on: Oct 21, 2024
 *      Author: phuct
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#include "global.h"

void button_reading(void);

unsigned char is_button_pressed_short(uint8_t index);
unsigned char is_button_pressed_1s(uint8_t index);
unsigned char is_button_pressed_hold(uint8_t index);

// We aim to work with more than one button
#define NO_OF_BUTTONS 3 // Updated to handle 3 buttons

#endif /* INC_INPUT_READING_H_ */
