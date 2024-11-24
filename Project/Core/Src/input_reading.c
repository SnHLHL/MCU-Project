/*
 * input_reading.c
 *
 *  Created on: Oct 21, 2024
 *      Author: phuct
 */

#include "main.h"
#include "input_reading.h"
#include "global.h"

// Timer interrupt duration is 10ms, so to pass 1 second, we need to jump to the interrupt service routine 100 times
#define DURATION_FOR_AUTO_INCREASING 	100
#define BUTTON_IS_PRESSED 				GPIO_PIN_RESET
#define BUTTON_IS_RELEASED 				GPIO_PIN_SET

// The buffers that store the final result after debouncing
static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];
static GPIO_PinState previousButtonBuffer[NO_OF_BUTTONS];

// We define three buffers for debouncing
static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];

// We define flags for button states
static uint8_t flagForButtonPress1s[NO_OF_BUTTONS];
static uint8_t flagForButtonPressShort[NO_OF_BUTTONS];


// Counter for automatically detecting when a button is pressed more than 1 second
static uint16_t counterForButtonPress1s[NO_OF_BUTTONS];
static uint16_t counterForLongPressInterval[NO_OF_BUTTONS];

void button_reading(void) {
    for (int i = 0; i < NO_OF_BUTTONS; i++) {
        debounceButtonBuffer2[i] = debounceButtonBuffer1[i];

        // Update to handle multiple buttons
        switch(i) {
            case 0:
                debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
                break;
            case 1:
                debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
                break;
            case 2:
                debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin);
                break;
            default:
                break;
        }

        if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i]) {
            buttonBuffer[i] = debounceButtonBuffer1[i]; // Debouncing logic

            if (buttonBuffer[i] == BUTTON_IS_PRESSED) {
                // Button is pressed; we start counting
                if (counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING) {
                    counterForButtonPress1s[i]++;
                    if (counterForButtonPress1s[i] == DURATION_FOR_AUTO_INCREASING) {
                        // Flag is turned on when 1 second has passed since the button was pressed
                        flagForButtonPress1s[i] = 1;
                        flagForButtonPressShort[i] = 0; // Reset short press flag
                        counterForLongPressInterval[i] = 0;
                    }
                } else {
                    // The button is pressed for less than 1 second
                	counterForLongPressInterval[i]++;
                	if (counterForLongPressInterval[i] >= 25) {
						flagForButtonPressShort[i] = 0;
						flagForButtonPress1s[i] = 1; // Reset long press flag
						counterForLongPressInterval[i] = 0;
                	}
                }
            }

            if (buttonBuffer[i] == BUTTON_IS_RELEASED && previousButtonBuffer[i] == BUTTON_IS_PRESSED) {
				// Button has just been released
				if (counterForButtonPress1s[i] > 0 && counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING) {
					// It was a short press
					flagForButtonPressShort[i] = 1;
				}
				// Reset counters and flags on release
				counterForButtonPress1s[i] = 0;
				counterForLongPressInterval[i] = 0;
				flagForButtonPress1s[i] = 0;
			}

			// Store the current button state for the next iteration
			previousButtonBuffer[i] = buttonBuffer[i];
        }
    }
}

// Function to check if button is pressed shorter than 1s
unsigned char is_button_pressed_short(uint8_t index) {
    if (index >= NO_OF_BUTTONS) return 0;
    if (flagForButtonPressShort[index] == 1) {
        flagForButtonPressShort[index] = 0; // Reset the flag
        return 1;
    }
    return 0;
}

// Function to check if button is pressed longer than 1s
unsigned char is_button_pressed_1s(uint8_t index) {
    if (index >= NO_OF_BUTTONS) return 0;
    if (flagForButtonPress1s[index] == 1) {
        flagForButtonPress1s[index] = 0; // Reset the flag
        return 1;
    }
    return 0;
}


////we aim to work with more than one buttons
//#define NO_OF_BUTTONS 				       3
////timer interrupt duration is 10ms, so to pass 1 second,
////we need to jump to the interrupt service routine 100 time
//#define DURATION_FOR_AUTO_INCREASING	100
//#define BUTTON_IS_PRESSED   			GPIO_PIN_RESET
//#define BUTTON_IS_RELEASED   			GPIO_PIN_SET
//#define BUTTON_PRESSED_MORE_THAN_1s		2
//
//#define BUTTON_PRESSED GPIO_PIN_RESET // 0
//#define BUTTON_RELEASED GPIO_PIN_SET  // 1
////the buffer that the final result is stored after
////debouncing
//static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];
////we define two buffers for debouncing
//static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
//static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];
//static GPIO_PinState debounceButtonBuffer3[NO_OF_BUTTONS];
////we define a flag for a button pressed more than 1 second.
//static uint8_t flagForButtonPress1s[NO_OF_BUTTONS];
////we define counter for automatically increasing the value
////after the button is pressed more than 1 second.
//static uint16_t counterForButtonPress1s[NO_OF_BUTTONS];
//static int buttonState[NO_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};
//static int button_flag[NO_OF_BUTTONS];
//// this function turn on button_flag
//void getKeyProcess(int index){
//	if(index >= 0 && index < NO_OF_BUTTONS){
//		button_flag[index] = 1;
//	}
//}
//// this function turn on flagForButtonPress1s
//void get1sFlag(int index){
//	if(index >= 0 && index < NO_OF_BUTTONS){
//			flagForButtonPress1s[index] = 1;
//		}
//}
//void fsm_input_processing(GPIO_PinState buttonBuffer[], int index){
//	switch(buttonState[index]){
//	case BUTTON_IS_PRESSED:
//		//if button is pressed more than 1s
//		if(counterForButtonPress1s[index] < DURATION_FOR_AUTO_INCREASING){
//			counterForButtonPress1s[index]++;
//			if(counterForButtonPress1s[index] == DURATION_FOR_AUTO_INCREASING){
//				buttonState[index] = BUTTON_PRESSED_MORE_THAN_1s;
//				counterForButtonPress1s[index] = 0;
//				getKeyProcess(index);
//				get1sFlag(index);
//			}
//		}
//		//button is release
//		if(buttonBuffer[index] == BUTTON_RELEASED){
//			buttonState[index] = BUTTON_IS_RELEASED;
//			counterForButtonPress1s[index] = 0;
//		}
//		break;
//	case BUTTON_IS_RELEASED:
//		//button is pressed
//		if(buttonBuffer[index] == BUTTON_PRESSED){
//			buttonState[index] = BUTTON_IS_PRESSED;
//			getKeyProcess(index);
//		}
//		break;
//	case BUTTON_PRESSED_MORE_THAN_1s:
//		// if button is pressed more than 1s and button is continued pressing
//		// it'll execute previous status
//		if(counterForButtonPress1s[index] < DURATION_FOR_AUTO_INCREASING){
//					counterForButtonPress1s[index]++;
//					if(counterForButtonPress1s[index] == DURATION_FOR_AUTO_INCREASING){
//						buttonState[index] = BUTTON_PRESSED_MORE_THAN_1s;
//						counterForButtonPress1s[index] = 0;
//						getKeyProcess(index);
//						get1sFlag(index);
//					}
//				}
//		//button is release
//		if(buttonBuffer[index] == BUTTON_RELEASED){
//			buttonState[index] = BUTTON_IS_RELEASED;
//			counterForButtonPress1s[index] = 0;
//		}
//		break;
//	default:
//		break;
//	}
//}
//void button_reading(void){
//	for(uint8_t i = 0; i < NO_OF_BUTTONS; i++){
//		debounceButtonBuffer3[i] = debounceButtonBuffer2[i];
//		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
//		// Chosing Which button is pressed.
//		switch(i){
//		case 0: // read signal from button0
//			debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
//			break;
//		case 1://  read signal from button0
//			debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
//			break;
//		case 2://  read signal from button0
//			debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin);
//			break;
//		default:
//			break;
//		}
//		if((debounceButtonBuffer3[i] == debounceButtonBuffer2[i]) && (debounceButtonBuffer2[i] == debounceButtonBuffer1[i])){
//			buttonBuffer[i] = debounceButtonBuffer3[i];
//			//call fsm_input_processing() function
//			fsm_input_processing(buttonBuffer,i);
//		}
//
//	}
//}
////determine whether a button is pressed or not
//int is_button_pressed_short(uint8_t index){
//	if(index >= NO_OF_BUTTONS) return 0;
//	if(button_flag[index] == 1){
//		//set button flag value = 0
//		button_flag[index] = 0;
//		return 1;
//	}
//	return 0;
//}
////determine whether a button is pressed more than 1s or not
//int is_button_pressed_1s(uint8_t index){
//	if(index >= NO_OF_BUTTONS) return 0;
//	if(button_flag[index] == 1 && flagForButtonPress1s[index] == 1){
//		//set button value
//		button_flag[index] = 0;
//		flagForButtonPress1s[index] = 0;
//		return 1;
//	}
//	return 0;
//}
