#include "oled.h"
#include "oledfont.h"

//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127

/************************************************
函数名称 	: 	delay_ms
功    能 	: 	延时xms
参    数 	: 	x
返 回 值 	: 	无
*************************************************/
static void delay_ms(unsigned int ms)
{                         
	unsigned int a;
	while(ms)
	{
		a=1800;
		while(a--);
		ms--;
	}
	return;
}

/************************************************
函数名称 	: 	OLED_WR_Byte
功    能 	: 	IIC发送一个字节的命令/数据（包含起止信号）
参		数	:		dat:数据
参      数 	: 		mode:数据/命令标志
	取 值	:		OLED_CMD,表示命令;
					OLED_DATA,表示数据;
返 回 值 	: 	无
*************************************************/
static void OLED_WR_Byte(u8 dat,u8 mode)
{
	IIC_Start();
	IIC_Send_Byte(0x78);	//OLED模块的地址+写模式
	IIC_WaitAck();
	if(mode){IIC_Send_Byte(0x40);}	//告知从机接下来发送的是数据字节
 	 else{IIC_Send_Byte(0x00);}	//告知从机接下来发送的是命令字节
	IIC_WaitAck();
	IIC_Send_Byte(dat);
	IIC_WaitAck();
	IIC_Stop();
}

/************************************************
函数名称 	: 	OLED_Init
功    能 	: 	初始化屏幕
参    数 	: 	无
返 回 值 	: 	无
*************************************************/	    
void OLED_Init(void)
{	
	OLED_WR_Byte(0xAE,OLED_CMD);/* 关闭OLED屏幕 */
	/* 自行配制相应的功能 */
	/* 不配置则按默认值初始化 */
	OLED_WR_Byte(0xAF,OLED_CMD); //开启OLED屏幕
}

/************************************************
函数名称 	: 	OLED_Set_Display_Start_Line
功    能 	: 	设置显示起始行 Set Display Start Line
参    数 	: 	i：起始行(0~63)(reset:0)
返 回 值 	: 	无
*************************************************/	 
void OLED_Set_Display_Start_Line(u8 i)
{
	OLED_WR_Byte(i|0x40,OLED_CMD);
}
/************************************************
函数名称 	: 	OLED_Set_Contrast_Control
功    能 	: 	配置对比度 Set Contrast Control
                复为值为7Fh
参    数 	: 	val：对比度值(0~255)
返 回 值 	: 	无
*************************************************/	    
void OLED_Set_Contrast_Control(u8 val)
{
    OLED_WR_Byte(0x81,OLED_CMD);//控制字节
	OLED_WR_Byte(val,OLED_CMD);//设置对比度数值（0~255)
}

/************************************************
函数名称 	: 	OLED_Set_Memory_Addressing_Mode
功    能 	: 	设置寻址模式 Set Memory Addressing Mode
                复位默认为页面寻址模式
参    数 	: 	mode:
                0:水平寻址;1:垂直寻址;2:页面寻址
返 回 值 	: 	无
*************************************************/
void OLED_Set_Memory_Addressing_Mode(u8 mode)
{
    OLED_WR_Byte(0x20,OLED_CMD);//控制字节
	OLED_WR_Byte(mode,OLED_CMD);//设置寻址模式
}

/************************************************
函数名称 	: 	OLED_Set_Multiplex_Ratio
功    能 	: 	设置多路复用比 Set Multiplex Ratio
                复位默认为63
参    数 	: 	i:(15~63)
返 回 值 	: 	无
*************************************************/
void OLED_Set_Multiplex_Ratio(u8 i)
{
    OLED_WR_Byte(0xA8,OLED_CMD);//控制字节
	OLED_WR_Byte(i,OLED_CMD);//设置多路复用比
}

/************************************************
函数名称 	: 	OLED_Set_Frequency
功    能 	: 	设置显示时钟分频比/振荡器频率 Set Display Clock Divide Ratio/Oscillator Frequency
                复位默认为1
参    数 	: 	ratio:显示时钟的分频比-1(0~15)
                freq:振荡器频率(0~15)
返 回 值 	: 	无
*************************************************/
void OLED_Set_Frequency(u8 ratio,u8 freq)
{
    OLED_WR_Byte(0xd5,OLED_CMD);//控制字节
	OLED_WR_Byte((freq<<4)+ratio,OLED_CMD);
}

/************************************************
函数名称 	: 	OLED_Set_PreCharge_Period
功    能 	: 	设置预充电周期 Set Pre-charge Period
参    数 	: 	x:上升阶段的周期(0~15) 复位值为2
                y:下降阶段的周期(0~15) 复位值为2
返 回 值 	: 	无
*************************************************/
void OLED_Set_PreCharge_Period(u8 x,u8 y)
{
    OLED_WR_Byte(0xD9,OLED_CMD);//控制字节
	OLED_WR_Byte((y<<4)+x,OLED_CMD);//设置
}

/************************************************
函数名称 	: 	OLED_COM_Config
功    能 	: 	设置COM引脚硬件配置 Set COM Pins Hardware Configuration
参    数 	: 	x:0:顺序COM引脚配置;1:备选COM引脚配置 复位值为1
                y:0/1:禁用/启用 COM左/右重映射 复位值为0
返 回 值 	: 	无
*************************************************/
void OLED_COM_Config(u8 x,u8 y)
{
    OLED_WR_Byte(0xDA,OLED_CMD);//控制字节
	OLED_WR_Byte((x<<4)+(y<<5),OLED_CMD);
}

/************************************************
函数名称 	: 	OLED_Set_Display_Offset
功    能 	: 	设置显示偏移量 Set Display Offset
参    数 	: 	i:垂直偏移量(0~63) (RESET:00)
返 回 值 	: 	无
*************************************************/
void OLED_Set_Display_Offset(u8 i)
{
    OLED_WR_Byte(0xD3,OLED_CMD);//控制字节
	OLED_WR_Byte(i,OLED_CMD);//设置垂直偏移量(0~63)
}
/************************************************
函数名称 	: 	OLED_VCOMH_Deselect_Level
功    能 	: 	设置VCOMH取消选择电平 Set VCOMH Deselect Level
参    数 	: 	i:0:~0.65*VCC;1:~0.77*VCC(RESET);2:0.83*VCC
返 回 值 	: 	无
*************************************************/
void OLED_VCOMH_Deselect_Level(u8 i)
{
    if(i==0)
    {
        OLED_WR_Byte(0xDB,OLED_CMD);//控制字节
	    OLED_WR_Byte(0x00,OLED_CMD);//~ 0.65 x VCC
    }
    else if(i==1)
    {
        OLED_WR_Byte(0xDB,OLED_CMD);//控制字节
	    OLED_WR_Byte(0x20,OLED_CMD);//~ 0.77 x VCC
    }
    else if(i==2)
    {
        OLED_WR_Byte(0xDB,OLED_CMD);//控制字节
	    OLED_WR_Byte(0x30,OLED_CMD);//~ 0.83 x VCC
    }
}

/************************************************
函数名称 	: 	OLED_ColorTurn
功    能 	: 	设置屏幕反相 Set Normal/Inverse Display
				复位值为关闭
参    数 	: 	0:关闭;1:开启
返 回 值 	: 	无
*************************************************/
void OLED_ColorTurn(u8 i)
{
	OLED_WR_Byte(0xA6+i,OLED_CMD);//正常显示
}

/************************************************
函数名称 	: 	OLED_DisplayTurn
功    能 	: 	屏幕翻转
				Set COM Output Scan Direction & 
				Set Segment Re-map
				复位值为正常显示
参    数 	: 	i:0:正常显示;1:翻转180°
				  2:仅水平翻转；3:仅垂直翻转
返 回 值 	: 	无
*************************************************/
void OLED_DisplayTurn(u8 i)
{
	if(i==0)
	{
		OLED_WR_Byte(0xC0,OLED_CMD);
		OLED_WR_Byte(0xA0,OLED_CMD);
	}
	else if(i==1)
	{
		OLED_WR_Byte(0xC8,OLED_CMD);
		OLED_WR_Byte(0xA1,OLED_CMD);
	}
	else if(i==2)
	{
		OLED_WR_Byte(0xC0,OLED_CMD);
		OLED_WR_Byte(0xA1,OLED_CMD);
	}
	else if(i==3)
	{
		OLED_WR_Byte(0xC8,OLED_CMD);
		OLED_WR_Byte(0xA0,OLED_CMD);
	}
}

/************************************************
函数名称 	: 	OLED_Set_Pos
功    能 	: 	设置坐标	Set Column Start Address for Page Addressing Mode
参    数 	: 	x,y
返 回 值 	: 	无
*************************************************/
void OLED_Set_Pos(u8 x, u8 y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD);
}   	  

/************************************************
函数名称 	: 	OLED_Display_On
功    能 	: 	开启OLED显示
参    数 	: 	无
返 回 值 	: 	无
*************************************************/
void OLED_Display_On(void)
{
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

/************************************************
函数名称 	: 	OLED_Display_Off
功    能 	: 	关闭OLED显示     
参    数 	: 	无
返 回 值 	: 	无
*************************************************/
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 

/************************************************
函数名称 	: 	OLED_Clear
功    能 	: 	清屏函数,清完屏,整个屏幕是黑色的,和没点亮一样
参    数 	: 	无
返 回 值 	: 	无
*************************************************/
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_Set_Pos(0,i);	//每页的第一列开始
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA);//填充0 
	}
}

/************************************************
函数名称 	: 	OLED_ShowChar
功    能 	: 	在指定位置显示一个字符,包括部分字符
参    数 	: 	x:0~127	; y:0~63	坐标
参		数	:		chr:字符
参		数	:		font:字体
		取 值	:		8:6x8  16:8x16
返 回 值 	: 	无
*************************************************/
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 font)
{      	
	u8 sizex,sizey;
	u8 i;
	if(font==8){sizex=6;sizey=8;}
	else if(font==16){sizex=8;sizey=16;}
	chr-=' ';//得到偏移后的值
	OLED_Set_Pos(x,y);
	for(i=0;i<sizex*(sizey>>3);i++)
	{
		if(i%sizex==0&&sizey!=8) OLED_Set_Pos(x,y++);
		if(sizey==8) OLED_WR_Byte(font_0608[chr][i],OLED_DATA);//6X8字号
		else if(sizey==16) OLED_WR_Byte(font_0816[chr][i],OLED_DATA);//8x16字号
	}
}

/************************************************
函数名称 	: 	OLED_ShowNum
功    能 	: 	显示数字
参    数 	: 	x,y :起点坐标
							num:要显示的数字
							len :数字的位数
							font:字体	8:6*8,16:8*16		  
返 回 值 	: 	无
*************************************************/
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 font)
{         	
	u8 sizex,sizey;
	u8 i;
	if(font==8){sizex=6;sizey=8;}
	else if(font==16){sizex=8;sizey=16;}
	for(i=0;i<len;i++)
	{
		OLED_ShowChar(x,y,(num%10)+'0',font);
		x+=sizex;
		num/=10;
	}
}

/************************************************
函数名称 	: 	OLED_ShowString
功    能 	: 	显示字符串
参    数 	: 	x,y :起点坐标
				chr:要显示的字符串
				font:字体	8:6*8,16:8*16		
返 回 值 	: 	无
*************************************************/
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 font)
{
	u8 sizex,sizey;
	if(font==8){sizex=6;sizey=8;}
	else if(font==16){sizex=8;sizey=16;}
	while (*chr)
	{		
		OLED_ShowChar(x,y,*chr++,sizey);
		x+=sizex;
	}
}

/************************************************
函数名称 	: 	OLED_ShowChinese
功    能 	: 	显示汉字
参    数 	: 	x,y :起点坐标
				no:中文字的字库编号
				font:字体	16:16*16
返 回 值 	: 	无
*************************************************/
void OLED_ShowChinese(u8 x,u8 y,u8 no,u8 font)
{
	u8 sizex,sizey;
	u8 i;
	if(font==16){sizex=16;sizey=16;}
	
	for(i=0;i<sizex*(sizey>>3);i++)
	{
		if(i%sizey==0) OLED_Set_Pos(x,y++);
		if(sizey==16) OLED_WR_Byte(Hzk[no][i],OLED_DATA);//16x16字号
		else return;
	}				
}

/************************************************
函数名称 	: 	OLED_DrawBMP
功    能 	: 	显示图片
参    数 	: 	x,y显示坐标
				sizex,sizey,图片长宽
				BMP：要显示的图片
返 回 值 	: 	无
*************************************************/
void OLED_DrawBMP(u8 x,u8 y,u8 sizex, u8 sizey,u8 BMP[])
{ 	
  u16 j=0;
	u8 i,m;
	sizey=sizey/8+((sizey%8)?1:0);
	for(i=0;i<sizey;i++)
	{
		OLED_Set_Pos(x,i+y);
    	for(m=0;m<sizex;m++)
		{      
			OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
		}
	}
} 






