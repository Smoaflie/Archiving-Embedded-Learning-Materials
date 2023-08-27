#ifndef __UART_H
#define __UART_H

#include <REGX52.H>
#include "AS608.h"

#define UART_MAX_RECV_LEN 50	//�����ջ����ֽ���
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long
	


//���ڳ�ʼ��
void UART_Init(u16 band_rate);
//��ʱ��0��ʼ��
void Timer0Init(void);
//���ڷ���һ���ֽ�
void UART_SendByte(u8 ucch);
//���ڷ����ַ���
void UART_SendStr(u8 *ucstr);

#endif	/* __UART_H */
