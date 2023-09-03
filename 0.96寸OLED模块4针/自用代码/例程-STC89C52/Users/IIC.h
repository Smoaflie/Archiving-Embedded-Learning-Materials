#ifndef __IIC_H
#define __IIC_H

#include "REG52.h"		  	 
 
#define  u8 unsigned char 
#define  u16 unsigned int
#define  u32 unsigned int

sbit IIC_SCL=P1^0;//SCL
sbit IIC_SDA=P1^1;//SDA
sbit IIC_RES =P1^2;//RES

//-----------------IIC端口定义----------------

#define IIC_SCL_Clr() IIC_SCL=0
#define IIC_SCL_Set() IIC_SCL=1

#define IIC_SDA_Clr() IIC_SDA=0
#define IIC_SDA_Set() IIC_SDA=1

#define IIC_RES_Clr() IIC_RES=0
#define IIC_RES_Set() IIC_RES=1

void IIC_Start(void);//发送IIC开始信号
void IIC_Stop(void);//发送IIC结束信号
void IIC_Send_Byte(u8 dat);//模拟IIC传输字节时序
void IIC_WaitAck(void);//等待应答信号


#endif /* __IIC_H */