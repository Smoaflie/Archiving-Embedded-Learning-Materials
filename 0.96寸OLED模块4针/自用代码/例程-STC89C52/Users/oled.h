#ifndef __OLED_H
#define __OLED_H

#include "REG52.h"		  	 
 
#define  u8 unsigned char 
#define  u16 unsigned int
#define  u32 unsigned int
	
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

sbit OLED_SCL=P1^0;//SCL
sbit OLED_SDA=P1^1;//SDA
sbit OLED_RES =P1^2;//RES

//-----------------OLED端口定义----------------

#define OLED_SCL_Clr() OLED_SCL=0
#define OLED_SCL_Set() OLED_SCL=1

#define OLED_SDA_Clr() OLED_SDA=0
#define OLED_SDA_Set() OLED_SDA=1

#define OLED_RES_Clr() OLED_RES=0
#define OLED_RES_Set() OLED_RES=1

void delay_ms(unsigned int ms);

//OLED控制用函数
void OLED_Init(void);/* 初始化屏幕 */
void OLED_ColorTurn(u8 i);/* 屏幕反显 */
void OLED_DisplayTurn(u8 i);/* 屏幕旋转180度 */
void OLED_Set_Pos(u8 x, u8 y);/* 设置坐标 */
void OLED_Display_On(void);/* 开启OLED显示 */
void OLED_Display_Off(void);/* 关闭OLED显示  */
void OLED_Clear(void);/* 清屏 */
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 sizey);/* 在指定位置显示一个字符 */
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 sizey);/* 显示数字 */
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 sizey);/* 显示字符串 */
void OLED_ShowChinese(u8 x,u8 y,u8 no,u8 sizey);/* 显示汉字 */
void OLED_DrawBMP(u8 x,u8 y,u8 sizex, u8 sizey,u8 BMP[]);/* 显示图片 */


#endif  
	 



