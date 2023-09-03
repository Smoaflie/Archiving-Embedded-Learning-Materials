#ifndef __OLED_H
#define __OLED_H

#include "REG52.h"		
#include "IIC.h"


 
#define  u8 unsigned char 
#define  u16 unsigned int
#define  u32 unsigned int
	
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

//OLED配置函数
void OLED_Set_Memory_Addressing_Mode(u8 mode);/* 设置寻址模式 */
void OLED_Set_Multiplex_Ratio(u8 i);/* 设置多路复用比 */
void OLED_Set_Frequency(u8 ratio,u8 freq);/* 设置显示时钟分频比/振荡器频率 */
void OLED_Set_PreCharge_Period(u8 x,u8 y);/* 设置预充电周期 */
void OLED_COM_Config(u8 x,u8 y);/* 设置COM引脚硬件配置 */
void OLED_Set_Display_Offset(u8 i);/* 设置显示偏移量 */
void OLED_VCOMH_Deselect_Level(u8 i);/* 设置VCOMH取消选择电平 */

//OLED控制用函数
void OLED_Init(void);/* 初始化屏幕 */
void OLED_Set_Contrast_Control(u8 val);/* 设置对比度 */
void OLED_ColorTurn(u8 i);/* 屏幕反显 */
void OLED_DisplayTurn(u8 i);/* 屏幕旋转 */
void OLED_Set_Pos(u8 x, u8 y);/* 设置坐标 */
void OLED_Display_On(void);/* 开启OLED显示 */
void OLED_Display_Off(void);/* 关闭OLED显示  */
void OLED_Clear(void);/* 清屏 */
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 font);/* 在指定位置显示一个字符 */
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 font);/* 显示数字 */
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 font);/* 显示字符串 */
void OLED_ShowChinese(u8 x,u8 y,u8 no,u8 font);/* 显示汉字 */
void OLED_DrawBMP(u8 x,u8 y,u8 sizex, u8 sizey,u8 *BMP);/* 显示图片 */


#endif  
	 



