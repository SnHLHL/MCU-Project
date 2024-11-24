/** 
Edit by modify: Ngoc Hang 
**/

#include "stm32f1xx_hal.h"
#include "main.h"
#include "global.h"

extern I2C_HandleTypeDef hi2c1;

void lcd_init (void);   // initialize lcd

void lcd_send_cmd (char cmd);  // send command to the lcd

void lcd_send_data (char data);  // send data to the lcd

void lcd_send_string (char *str);  // send string to the lcd

void lcd_clear_display (void);	//clear display lcd

void lcd_goto_XY (int row, int col); //set proper location on screen

void lcd_update(); // push the string to display to the LCD screen
