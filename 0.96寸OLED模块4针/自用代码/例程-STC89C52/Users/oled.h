#ifndef __OLED_H
#define __OLED_H

#include "REG52.h"		  	 
 
#define  u8 unsigned char 
#define  u16 unsigned int
#define  u32 unsigned int
	
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

sbit OLED_SCL=P1^0;//SCL
sbit OLED_SDA=P1^1;//SDA
sbit OLED_RES =P1^2;//RES

//-----------------OLED�˿ڶ���----------------

#define OLED_SCL_Clr() OLED_SCL=0
#define OLED_SCL_Set() OLED_SCL=1

#define OLED_SDA_Clr() OLED_SDA=0
#define OLED_SDA_Set() OLED_SDA=1

#define OLED_RES_Clr() OLED_RES=0
#define OLED_RES_Set() OLED_RES=1

void delay_ms(unsigned int ms);

//OLED�����ú���
void OLED_Init(void);/* ��ʼ����Ļ */
void OLED_ColorTurn(u8 i);/* ��Ļ���� */
void OLED_DisplayTurn(u8 i);/* ��Ļ��ת180�� */
void OLED_Set_Pos(u8 x, u8 y);/* �������� */
void OLED_Display_On(void);/* ����OLED��ʾ */
void OLED_Display_Off(void);/* �ر�OLED��ʾ  */
void OLED_Clear(void);/* ���� */
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 sizey);/* ��ָ��λ����ʾһ���ַ� */
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 sizey);/* ��ʾ���� */
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 sizey);/* ��ʾ�ַ��� */
void OLED_ShowChinese(u8 x,u8 y,u8 no,u8 sizey);/* ��ʾ���� */
void OLED_DrawBMP(u8 x,u8 y,u8 sizex, u8 sizey,u8 BMP[]);/* ��ʾͼƬ */


#endif  
	 



