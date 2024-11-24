/*
 * fsm_automatic.c
 *
 *  Created on: Oct 22, 2024
 *      Author: phuct
 */

#include "fsm_automatic.h"

void fsm_automatic_run(){
	switch(status){
	case INIT:
		//-----INIT: the status is assigned AUTO_RED_GREEN-----//
		//assign timeRED, timeGREEN, timeAMBER
		//assign tmpRED, tmpAMBER, tmpGREEN
		setTrafficOff();
		status = AUTO_RED_GREEN;
		setTimer1(defaultTimeGreen*1000); //Multiply by 1000 as we input with unit second
		timeRED = defaultTimeRed;
		timeGREEN = defaultTimeGreen;
		tmpRED = defaultTimeRed;
		tmpAMBER = defaultTimeAmber;
		tmpGREEN = defaultTimeGreen;
		setTimer2(1000);
		sprintf(buffer1, "Road1: %.2f", (float)timeRED--);
		sprintf(buffer2, "Road2: %.2f", (float)timeGREEN--);
		break;
	case AUTO_RED_GREEN:
		//-----AUTO_RED_GREEN: Red LEDs in Road 1 is ON while Green LEDs in Road 2 is ON-----//
		//if timer1_flag = 1, switch the green light to amber light by status AUTO_RED_AMBER
		//and update the ClockBuffer for displaying the timer for Amber and Red
		//if timer2_flag = 1, update and start counting timer for Red and Green
		//if BUTTON1 is pressed, move to MAN_MODE2
		setTrafficRed1();
		setTrafficGreen2();
		if(timer1_flag == 1){
			status = AUTO_RED_AMBER;
			setTimer1(defaultTimeAmber*1000);
			timeAMBER = defaultTimeAmber;
//			updateClockBuffer(timeRED--,timeAMBER--);
			sprintf(buffer1, "Road1: %.2f", (float)timeRED--);
			sprintf(buffer2, "Road2: %.2f", (float)timeAMBER--);
			setTimer2(1000);
		}
		if(timer2_flag == 1){
//			timeRED--;
//			timeGREEN--;
//			updateClockBuffer(timeRED--,timeGREEN--);
			sprintf(buffer1, "Road1: %.2f", (float)timeRED--);
			sprintf(buffer2, "Road2: %.2f", (float)timeGREEN--);
			setTimer2(1000);
		}
		if(is_button_pressed_short(0) == 1){
			setTimer1(500);
			status = MAN_MODE2;
			setTimer4(5000);
			sprintf(buffer1, "Mode: Manual 2");
			sprintf(buffer2, "TimeRED: %.2f", (float)tmpRED);
		}
		if(is_button_pressed_1s(0) == 1){
			setTimer1(250);
			status = MAN_MODE2;
			sprintf(buffer1, "Mode: Manual 2");
			sprintf(buffer2, "TimeRED: %.2f", (float)tmpRED);
		}
		if(is_button_pressed_short(1) == 1){
			setTimer1(1000);
			status = SET_MODE1;
			sprintf(buffer1, "Mode: Setting 1");
			sprintf(buffer2, "TimeRED: %.2f", (float)tmpRED);
		}
		break;
	case AUTO_RED_AMBER:
		//-----AUTO_RED_AMBER: Red LEDs in Road 1 is ON while Amber LEDs in Road 2 is ON-----//
		//if timer1_flag = 1, switch the red light to green light; and amber light to red light by status AUTO_GREEN_RED
		//and update the ClockBuffer for displaying the timer for Green and Red
		//if timer2_flag = 1, update and start counting timer for Red and Amber
		//if BUTTON1 is pressed, move to MAN_MODE2
		setTrafficRed1();
		setTrafficAmber2();
		if(timer1_flag == 1){
			status = AUTO_GREEN_RED;
			setTimer1(defaultTimeGreen*1000);
			timeGREEN = defaultTimeGreen;
			timeRED = defaultTimeRed;
//			updateClockBuffer(timeGREEN--,timeRED--);
			sprintf(buffer1, "Road1: %.2f", (float)timeGREEN--);
			sprintf(buffer2, "Road2: %.2f", (float)timeRED--);
			setTimer2(1000);
		}
		if(timer2_flag == 1){
//			timeRED--;
//			timeAMBER--;
//			updateClockBuffer(timeRED--,timeAMBER--);
			sprintf(buffer1, "Road1: %.2f", (float)timeRED--);
			sprintf(buffer2, "Road2: %.2f", (float)timeAMBER--);
			setTimer2(1000);
		}
		if(is_button_pressed_short(0) == 1){
			setTimer1(250);
			status = MAN_MODE2;
			setTimer4(5000);
			sprintf(buffer1, "Mode: Manual 2");
			sprintf(buffer2, "TimeRED: %.2f", (float)tmpRED);
		}
		if(is_button_pressed_1s(0) == 1){
			setTimer1(250);
			status = MAN_MODE2;
			sprintf(buffer1, "Mode: Manual 2");
			sprintf(buffer2, "TimeRED: %.2f", (float)tmpRED);
		}
		if(is_button_pressed_short(1) == 1){
			setTimer1(1000);
			status = SET_MODE1;
			sprintf(buffer1, "Mode: Setting 1");
			sprintf(buffer2, "TimeRED: %.2f", (float)tmpRED);
		}
		break;
	case AUTO_GREEN_RED:
		//-----AUTO_GREEN_RED: Green LEDs in Road 1 is ON while Red LEDs in Road 2 is ON-----//
		//if timer1_flag = 1, switch the green light to red light by status AUTO_AMBER_RED
		//and update the ClockBuffer for displaying the timer for Amber and Red
		//if timer2_flag = 1, update and start counting timer for Green and Red
		//if BUTTON1 is pressed, move to MAN_MODE2
		setTrafficGreen1();
		setTrafficRed2();
		if(timer1_flag == 1){
			status = AUTO_AMBER_RED;
			setTimer1(defaultTimeAmber*1000);
			timeAMBER = defaultTimeAmber;
//			updateClockBuffer(timeAMBER--,timeRED--);
			sprintf(buffer1, "Road1: %.2f", (float)timeAMBER--);
			sprintf(buffer2, "Road2: %.2f", (float)timeRED--);
			setTimer2(1000);
		}
		if(timer2_flag == 1){
//			timeGREEN--;
//			timeRED--;
//			updateClockBuffer(timeGREEN--,timeRED--);
			sprintf(buffer1, "Road1: %.2f", (float)timeGREEN--);
			sprintf(buffer2, "Road2: %.2f", (float)timeRED--);
			setTimer2(1000);
		}
		if(is_button_pressed_short(0) == 1){
			setTimer1(250);
			status = MAN_MODE2;
			setTimer4(5000);
			sprintf(buffer1, "Mode: Manual 2");
			sprintf(buffer2, "TimeRED: %.2f", (float)tmpRED);
		}
		else if(is_button_pressed_1s(0) == 1){
			setTimer1(250);
			status = MAN_MODE2;
			sprintf(buffer1, "Mode: Manual 2");
			sprintf(buffer2, "TimeRED: %.2f", (float)tmpRED);
		}
		if(is_button_pressed_short(1) == 1){
			setTimer1(1000);
			status = SET_MODE1;
			sprintf(buffer1, "Mode: Setting 1");
			sprintf(buffer2, "TimeRED: %.2f", (float)tmpRED);
		}
		break;
	case AUTO_AMBER_RED:
		//-----AUTO_AMBER_RED: Amber LEDs in Road 1 is ON while Red LEDs in Road 2 is ON-----//
		//if timer1_flag = 1, switch the amber light to red light; and red light to green light by status AUTO_RED_GREEN
		//and update the ClockBuffer for displaying the timer for Red and Green
		//if timer2_flag = 1, update and start counting timer for Amber and Red
		//if BUTTON1 is pressed, move to MAN_MODE2
		setTrafficAmber1();
		setTrafficRed2();
		if(timer1_flag == 1){
			status = AUTO_RED_GREEN;
			setTimer1(defaultTimeGreen*1000);
			timeRED = defaultTimeRed;
			timeGREEN = defaultTimeGreen;
//			updateClockBuffer(timeRED--,timeGREEN--);
			sprintf(buffer1, "Road1: %.2f", (float)timeRED--);
			sprintf(buffer2, "Road2: %.2f", (float)timeGREEN--);
			setTimer2(1000);
		}
		if(timer2_flag == 1){
//			timeRED--;
//			timeAMBER--;
//			updateClockBuffer(timeAMBER--, timeRED--);
			sprintf(buffer1, "Road1: %.2f", (float)timeAMBER--);
			sprintf(buffer2, "Road2: %.2f", (float)timeRED--);
			setTimer2(1000);
		}
		if(is_button_pressed_short(0) == 1){
			setTimer1(250);
			status = MAN_MODE2;
			setTimer4(5000);
			sprintf(buffer1, "Mode: Manual 2");
			sprintf(buffer2, "TimeRED: %.2f", (float)tmpRED);
		}
		if(is_button_pressed_1s(0) == 1){
			setTimer1(250);
			status = MAN_MODE2;
			sprintf(buffer1, "Mode: Manual 2");
			sprintf(buffer2, "TimeRED: %.2f", (float)tmpRED);
		}
		if(is_button_pressed_short(1) == 1){
			setTimer1(1000);
			status = SET_MODE1;
			sprintf(buffer1, "Mode: Setting 1");
			sprintf(buffer2, "TimeRED: %.2f", (float)tmpRED);
		}
		break;
	default:
		break;
	}
}
