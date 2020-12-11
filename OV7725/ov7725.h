/*
 * ov7725.h
 *
 *  Created on: Dec 10, 2020
 *      Author: 陆小泳
 */

#ifndef OV7725_H_
#define OV7725_H_

#include "stdint.h"

#define OV7725_MID				0X7FA2
#define OV7725_PID				0X7721

#define OV7725_WRST		PAout(0)		//写指针复位
#define OV7725_RCK		PAout(1)		//读数据时钟
#define OV7725_RRST		PAout(4)  		//读指针复位
#define OV7725_CS		PAout(11)  		//片选信号(OE)
#define OV7725_WREN		PAout(12)		//写入FIFO使能
#define OV7725_VSYNC  	PAin(15)		//同步信号检测IO

#define OV7725_DATA   GPIOB->IDR&0x00FF //数据输入端口
/////////////////////////////////////////

uint8_t   OV7725_Init(void);
void OV7725_Light_Mode(uint8_t mode);
void OV7725_Color_Saturation(int8_t sat);
void OV7725_Brightness(int8_t bright);
void OV7725_Contrast(int8_t contrast);
void OV7725_Special_Effects(uint8_t eft);
void OV7725_Window_Set(uint16_t width,uint16_t height,uint8_t mode);

#endif /* OV7725_H_ */
