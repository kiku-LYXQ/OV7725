/*
 * sccb.c
 *
 *  Created on: Dec 10, 2020
 *      Author: 陆小泳
 */

#include "sccb.h"
#include "delay.h"

//初始化SCCB接口
//CHECK OK
void SCCB_Init(void)
{

#ifdef SOFT_SCCB
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOB_CLK_ENABLE();

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

 	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
/*
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PC端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;				 // 端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //输输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOC,GPIO_Pin_4|GPIO_Pin_5);						 // 输出高
*/
	SCCB_SDA_OUT();
#else

#if sccb_i2c == hi2c1
		MX_I2C1_Init();
#else
		MX_I2C2_Init();
#endif

#endif


}

//SCCB起始信号
//当时钟为高的时候,数据线的高到低,为SCCB起始信号
//在激活状态下,SDA和SCL均为低电平
void SCCB_Start(void)
{
    SDA_OUT();
    I2C_SDA_UP;
    I2C_SCL_UP;
    delay_us(4);
    I2C_SDA_LOW;        //启动开始信号
    delay_us(4);
    I2C_SCL_LOW;      //钳住I2C总线，准备发送或接收数据
/*
    SCCB_SDA=1;     //数据线高电平
    SCCB_SCL=1;	    //在时钟线高的时候数据线由高至低
    delay_us(50);
    SCCB_SDA=0;
    delay_us(50);
    SCCB_SCL=0;	    //数据线恢复低电平,单操作函数必要
*/
}

//SCCB停止信号
//当时钟为高的时候,数据线的低到高,为SCCB停止信号
//空闲状况下,SDA,SCL均为高电平
void SCCB_Stop(void)
{
    SDA_OUT();            //sda线输出
    I2C_SDA_LOW;         //发送结束条件的数据信号
    I2C_SCL_LOW;
    delay_us(4);         //结束条件建立时间大于4μ
    I2C_SCL_UP;         //发送I2C总线结束信号
    I2C_SDA_UP;
    delay_us(4);
/*
    SCCB_SDA=0;
    delay_us(50);
    SCCB_SCL=1;
    delay_us(50);
    SCCB_SDA=1;
    delay_us(50);
*/
}
//产生NA信号
void SCCB_No_Ack(void)
{
    SDA_OUT();
    I2C_SDA_UP;
    delay_us(1);
    I2C_SCL_UP;
    delay_us(4);
    I2C_SCL_LOW;
    delay_us(4);
/*
	delay_us(50);
	SCCB_SDA=1;
	SCCB_SCL=1;
	delay_us(50);
	SCCB_SCL=0;
	delay_us(50);
	SCCB_SDA=0;
	delay_us(50);
*/
}
//SCCB,写入一个字节
//返回值:0,成功;1,失败.
uint8_t SCCB_WR_Byte(uint8_t dat)
{
    unsigned char t;
    uint8_t con = 0;

    SDA_OUT();
    I2C_SCL_LOW;
    for(t=0;t<8;t++)
    {
       if((dat&0x80)>>7)
       	I2C_SDA_UP;
       else
       	I2C_SDA_LOW;
       dat<<=1;
		delay_us(2);   //对TEA5767这三个延时都是必须的
		I2C_SCL_UP;
		delay_us(2);
		I2C_SCL_LOW;
		delay_us(2);
    }

    SDA_IN();
    I2C_SDA_UP;       //释放数据线，准备接收应答
    delay_us(1);
    I2C_SCL_UP;                //CPU驱动SCL = 1, 此时器件会返回ACK应答
    delay_us(1);

    while(I2C_SDA == GPIO_PIN_SET)    //CPU读取SDA口线状态
    {
        con++;
        if(con>250)
        {
        	SCCB_Stop();
            return 1;     //无应答信号
        }
    }

    I2C_SCL_LOW;
    delay_us(1);
  	return 0;             //有应答

/*
	uint8_t j,res;
	for(j=0;j<8;j++) //循环8次发送数据
	{
		if(dat&0x80)SCCB_SDA=1;
		else SCCB_SDA=0;
		dat<<=1;
		delay_us(50);
		SCCB_SCL=1;
		delay_us(50);
		SCCB_SCL=0;
	}
	SCCB_SDA_IN();		//设置SDA为输入
	delay_us(50);
	SCCB_SCL=1;			//接收第九位,以判断是否发送成功
	delay_us(50);
	if(SCCB_READ_SDA)res=1;  //SDA=1发送失败，返回1
	else res=0;         //SDA=0发送成功，返回0
	SCCB_SCL=0;
	SCCB_SDA_OUT();		//设置SDA为输出
	return res;
*/
}
//SCCB 读取一个字节
//在SCL的上升沿,数据锁存
//返回值:读到的数据
uint8_t SCCB_RD_Byte(void)
{
	unsigned char temp;
	unsigned char dat;
	I2C_SDA_UP;                     //释放总线准备接收
	SDA_IN();
	for(temp=0x80;temp!=0;temp>>=1)
	{
		delay_us(1);
	    I2C_SCL_UP;
	    if(I2C_SDA==1)
	    {
	    	dat|=temp;
	    }
	    else
	    {
	        dat&=~temp;
	    }
	    I2C_SCL_LOW;
	}
	return dat;
/*
	uint8_t temp=0,j;
	SCCB_SDA_IN();		//设置SDA为输入
	for(j=8;j>0;j--) 	//循环8次接收数据
	{
		delay_us(50);
		SCCB_SCL=1;
		temp=temp<<1;
		if(SCCB_READ_SDA)temp++;
		delay_us(50);
		SCCB_SCL=0;
	}
	SCCB_SDA_OUT();		//设置SDA为输出
	return temp;
*/
}
//写寄存器
//返回值:0,成功;1,失败.
uint8_t SCCB_WR_Reg(uint8_t reg,uint8_t data)
{
#ifdef SOFT_I2C
	uint8_t res=0;
	SCCB_Start(); 					//启动SCCB传输
	if(SCCB_WR_Byte(SCCB_ID))res=1;	//写器件ID
	delay_us(100);
  	if(SCCB_WR_Byte(reg))res=1;		//写寄存器地址
	delay_us(100);
  	if(SCCB_WR_Byte(data))res=1; 	//写数据
  	SCCB_Stop();
  	return	res;
#else
  	if(HAL_I2C_Mem_Write(&sccb_i2c, SCCB_ID << 1, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, 0xf) == HAL_OK)
  		return 1;
  	else
  		return 0;
#endif
}
//读寄存器
//返回值:读到的寄存器值
uint8_t SCCB_RD_Reg(uint8_t reg)
{
#ifdef SOFT_I2C
	uint8_t val=0;
	SCCB_Start(); 				//启动SCCB传输
	SCCB_WR_Byte(SCCB_ID);		//写器件ID
	delay_us(100);
  	SCCB_WR_Byte(reg);			//写寄存器地址
	delay_us(100);
	SCCB_Stop();
	delay_us(100);
	//设置寄存器地址后,才是读
	SCCB_Start();
	SCCB_WR_Byte(SCCB_ID|0X01);	//发送读命令
	delay_us(100);
  	val=SCCB_RD_Byte();		 	//读取数据
  	SCCB_No_Ack();
  	SCCB_Stop();
  	return val;
#else
  	uint8_t val = 0;
  	HAL_I2C_Mem_Read(&sccb_i2c, SCCB_ID << 1, reg, I2C_MEMADD_SIZE_8BIT, &val, 1, 0xf);
  	return val;
#endif
}

/*******************************************************************************
* 函 数 名         : SDA_OUT
* 函数功能         : SDA 设置为输出
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void SDA_OUT(void)
{

/*    标准库使用，修改端口引脚可用
  GPIO_InitTypeDef GPIO_InitTypeStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  GPIO_InitTypeStruct.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_InitTypeStruct.GPIO_Pin=GPIO_Pin_7;
  GPIO_InitTypeStruct.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&GPIO_InitTypeStruct);
*/

  /*    HAL库使用，HAL库注意要把初始化函数的静态标记去掉    */
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = I2C_SDA_Pin;                    //使用STM3cubemx是定义好的SDA_Pin为GPIO_PIN_8的标签
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed =  GPIO_SPEED_FREQ_HIGH;;
  HAL_GPIO_Init(I2C_PinGROUP, &GPIO_InitStruct);
}


/*******************************************************************************
* 函 数 名         : SDA_IN
* 函数功能         : SDA 设置为输入
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void SDA_IN(void)
{

  /*    HAL库使用,HAL库注意要把初始化函数的静态标记去掉    */
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = I2C_SDA_Pin    ;                    //使用STM3cubemx是定义好的SDA_Pin为GPIO_PIN_8的标签
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(I2C_PinGROUP, &GPIO_InitStruct);
}
