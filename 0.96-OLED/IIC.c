#include "IIC.h"
/************************************************
函数名称 	: 	IIC_delay
功    能 	: 	IIC延时（按需填写）
参    数 	: 	无
返 回 值 	: 	无
*************************************************/
static void IIC_delay(void)
{
	/*
	u8 t=1;
	while(t--);
	*/
}

/************************************************
函数名称 	: 	IIC_Start
功    能 	: 	发送IIC开始信号
参    数 	: 	无
返 回 值 	: 	无
*************************************************/
void IIC_Start(void)
{
	IIC_SDA_Set();
	IIC_SCL_Set();
	IIC_delay();
	IIC_SDA_Clr();
	IIC_delay();
	IIC_SCL_Clr();
}

/************************************************
函数名称 	: 	IIC_Stop
功    能 	: 	发送IIC结束信号
参    数 	: 	无
返 回 值 	: 	无
*************************************************/
void IIC_Stop(void)
{
	IIC_SDA_Clr();
	IIC_SCL_Set();
	IIC_delay();
	IIC_SDA_Set();
}

/************************************************
函数名称 	: 	IIC_Send_Byte
功    能 	: 	模拟IIC传输字节时序
参    数 	: 	dat:数据
返 回 值 	: 	无
*************************************************/
void IIC_Send_Byte(u8 dat)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		IIC_SCL_Clr();//将时钟信号设置为低电平
		if(dat&0x80)//将dat的8位从最高位依次写入
		{
			IIC_SDA_Set();
    	}
		else
		{
			IIC_SDA_Clr();
   		}
		IIC_delay();
		IIC_SCL_Set();
		IIC_delay();
		IIC_SCL_Clr();
		dat<<=1;
  }
}

/************************************************
函数名称 	: 	IIC_WaitAck
功    能 	: 	等待应答信号
参    数 	: 	无
返 回 值 	: 	无
*************************************************/
void IIC_WaitAck(void)
{
	IIC_SDA_Set();
	IIC_delay();
	IIC_SCL_Set();
	IIC_delay();
	IIC_SCL_Clr();
	IIC_delay();
}
