/*
 * delay.c
 *
 *  Created on: Dec 10, 2020
 *      Author: 陆小泳
 */

#include "delay.h"
#include "tim.h"

/*******************************************************************************
* 函 数 名         : delay_us
* 函数功能         : 延时函数，延时us
* 输    入         : i
* 输    出         : 无
*******************************************************************************/
void delay_us(uint16_t i)
{
	__HAL_TIM_SET_COUNTER(&htim3, 0);

	HAL_TIM_Base_Start(&htim3);

	while (__HAL_TIM_GET_COUNTER(&htim3) <= i);

	HAL_TIM_Base_Stop(&htim3);
}

