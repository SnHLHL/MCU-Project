/*
 * global.h
 *
 *  Created on: Oct 21, 2024
 *      Author: phuct
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "timer.h"
#include "traffic.h"
#include "input_reading.h"
#include "fsm_automatic.h"
#include "fsm_manual.h"

extern int status;
extern int blink_status;

extern int preTimeRed;
extern int preTimeGreen;
extern int preTimeAmber;

extern int timeRED;
extern int timeGREEN;
extern int timeAMBER;

extern int tmpRED;
extern int tmpGREEN;
extern int tmpAMBER;

extern int defaultTimeRed;
extern int defaultTimeGreen;
extern int defaultTimeAmber;

#define INIT 1
#define AUTO_RED_GREEN 2
#define AUTO_RED_AMBER 3
#define AUTO_GREEN_RED 4
#define AUTO_AMBER_RED 5

#define MAN_MODE1 10
#define MAN_MODE2 11
#define MAN_MODE3 12
#define MAN_MODE4 13

#define SET_MODE1 14
#define SET_MODE2 15
#define SET_MODE3 16

char buffer1[32];
char buffer2[32];

#endif /* INC_GLOBAL_H_ */
