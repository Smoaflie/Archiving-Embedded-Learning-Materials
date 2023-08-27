/********************************************************************************
  * �� �� ��: main.c
  * �� �� ��: ����
  * �޸�����: Smoaflie
  * �޸�����: 2023��08��27��
  * ���ܽ���:          
  ******************************************************************************
  * ע������:
*********************************************************************************/

#include <REG52.h>
#include "oled.h"
#include "bmp.h"

int main(void)
{
	u8 t=' ';
	OLED_Init();//��ʼ��OLED
	OLED_ColorTurn(1);//0������ʾ��1 ��ɫ��ʾ
  OLED_DisplayTurn(1);//0������ʾ 1 ��Ļ��ת��ʾ
	while(1) 
	{		
		OLED_DrawBMP(0,0,128,64,BMP1);
		delay_ms(500);
		OLED_Clear();
		OLED_ShowChinese(0,0,0,16);//��
		OLED_ShowChinese(18,0,1,16);//��
		OLED_ShowChinese(36,0,2,16);//��
		OLED_ShowChinese(54,0,3,16);//��
		OLED_ShowChinese(72,0,4,16);//��
		OLED_ShowChinese(90,0,5,16);//��
		OLED_ShowChinese(108,0,6,16);//��
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