/*
 * traffic.c
 *
 *  Created on: Oct 21, 2024
 *      Author: phuct
 */

#include "traffic.h"

void setTrafficRed1(){
	HAL_GPIO_WritePin(LED1A_GPIO_Port, LED1A_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED1B_GPIO_Port, LED1B_Pin, GPIO_PIN_SET);
}

void setTrafficAmber1(){
	HAL_GPIO_WritePin(LED1A_GPIO_Port, LED1A_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED1B_GPIO_Port, LED1B_Pin, GPIO_PIN_RESET);
}

void setTrafficGreen1(){
	HAL_GPIO_WritePin(LED1A_GPIO_Port, LED1A_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED1B_GPIO_Port, LED1B_Pin, GPIO_PIN_SET);
}

void setTrafficRed2(){
	HAL_GPIO_WritePin(LED2A_GPIO_Port, LED2A_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED2B_GPIO_Port, LED2B_Pin, GPIO_PIN_SET);
}

void setTrafficAmber2(){
	HAL_GPIO_WritePin(LED2A_GPIO_Port, LED2A_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED2B_GPIO_Port, LED2B_Pin, GPIO_PIN_RESET);
}

void setTrafficGreen2(){
	HAL_GPIO_WritePin(LED2A_GPIO_Port, LED2A_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED2B_GPIO_Port, LED2B_Pin, GPIO_PIN_SET);
}

void setTrafficOff(){
	HAL_GPIO_WritePin(LED1A_GPIO_Port, LED1A_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED1B_GPIO_Port, LED1B_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED2A_GPIO_Port, LED2A_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED2B_GPIO_Port, LED2B_Pin, GPIO_PIN_RESET);
}

