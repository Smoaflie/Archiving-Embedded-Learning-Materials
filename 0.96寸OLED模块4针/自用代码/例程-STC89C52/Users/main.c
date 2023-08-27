/********************************************************************************
  * 文 件 名: main.c
  * 版 本 号: 初版
  * 修改作者: Smoaflie
  * 修改日期: 2023年08月27日
  * 功能介绍:          
  ******************************************************************************
  * 注意事项:
*********************************************************************************/

#include <REG52.h>
#include "oled.h"
#include "bmp.h"

int main(void)
{
	u8 t=' ';
	OLED_Init();//初始化OLED
	OLED_ColorTurn(1);//0正常显示，1 反色显示
  OLED_DisplayTurn(1);//0正常显示 1 屏幕翻转显示
	while(1) 
	{		
		OLED_DrawBMP(0,0,128,64,BMP1);
		delay_ms(500);
		OLED_Clear();
		OLED_ShowChinese(0,0,0,16);//可
		OLED_ShowChinese(18,0,1,16);//自
		OLED_ShowChinese(36,0,2,16);//定
		OLED_ShowChinese(54,0,3,16);//义
		OLED_ShowChinese(72,0,4,16);//的
		OLED_ShowChinese(90,0,5,16);//内
		OLED_ShowChinese(108,0,6,16);//容
		OLED_ShowString(8,2,"Smoaflie",16);
		OLED_ShowString(20,4,"2023/08/027",16);
		OLED_ShowString(0,6,"ASCII:",16);  
		OLED_ShowString(63,6,"CODE:",16);
		OLED_ShowChar(48,6,t,16);
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(103,6,t,3,16);
		delay_ms(500);
		OLED_Clear();
	}	  
	
}