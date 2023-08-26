#ifndef __UART_H
#define __UART_H

#include <REGX52.H>
#include "AS608.h"

#define UART_MAX_RECV_LEN 50	//最大接收缓存字节数
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long
	


//串口初始化
void UART_Init(u16 band_rate);
//定时器0初始化
void Timer0Init(void);
//串口发送一个字节
void UART_SendByte(u8 ucch);
//串口发送字符串
void UART_SendStr(u8 *ucstr);

#endif	/* __UART_H */
