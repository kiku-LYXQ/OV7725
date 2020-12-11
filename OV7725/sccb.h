/*
 * sccb.h
 *
 *  Created on: Dec 10, 2020
 *      Author: 陆小泳
 */

#ifndef SCCB_H_
#define SCCB_H_

#include "gpio.h"
#include "i2c.h"

#define sccb_i2c hi2c1

#define I2C_PinGROUP GPIOB
#define I2C_SCL_Pin GPIO_PIN_9
#define I2C_SDA_Pin GPIO_PIN_8

#define I2C_SCL_UP  HAL_GPIO_WritePin(I2C_PinGROUP,I2C_SCL_Pin,GPIO_PIN_SET)
#define I2C_SCL_LOW  HAL_GPIO_WritePin(I2C_PinGROUP,I2C_SCL_Pin,GPIO_PIN_RESET)

#define I2C_SDA_UP  HAL_GPIO_WritePin(I2C_PinGROUP,I2C_SDA_Pin,GPIO_PIN_SET)
#define I2C_SDA_LOW  HAL_GPIO_WritePin(I2C_PinGROUP,I2C_SDA_Pin,GPIO_PIN_RESET)

#define I2C_SDA HAL_GPIO_ReadPin(I2C_PinGROUP,I2C_SDA_Pin)
#define I2C_SCL HAL_GPIO_ReadPin(I2C_PinGROUP,I2C_SCL_Pin)

//////////////////////////////////////////////////////////////////////////////////

#define SCCB_SDA_IN()  {GPIOC->CRL&=0XFF0FFFFF;GPIOC->CRL|=0X00800000;}
#define SCCB_SDA_OUT() {GPIOC->CRL&=0XFF0FFFFF;GPIOC->CRL|=0X00300000;}

//IO操作函数
/*
#define SCCB_SCL    		PCout(4)	 	//SCL
#define SCCB_SDA    		PCout(5) 		//SDA

#define SCCB_READ_SDA    	PCin(5)  		//输入SDA
*/
#define SCCB_ID   			0X42  			//OV7670的ID

///////////////////////////////////////////

void SCCB_Init(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_No_Ack(void);
uint8_t SCCB_WR_Byte(uint8_t dat);
uint8_t SCCB_RD_Byte(void);
uint8_t SCCB_WR_Reg(uint8_t reg,uint8_t data);
uint8_t SCCB_RD_Reg(uint8_t reg);

void SDA_OUT(void);                //*    SDA 设置为输出
void SDA_IN(void);                //*    SDA 设置为输入

#endif /* SCCB_H_ */
