#ifndef __AS608_H
#define __AS608_H

#include "UART.h"	//自主配置：请修改为相应主控UART功能的头文件

/* 自主配置 */
/* 定义触摸检测IO口 */
//#define AS608_TOUCH GPIO_X	
/* 定义UART发送函数 */
//#define UART_SendByte UART_SendByte	

/* 定义模块地址 */
#define AS608Addr 0XFFFFFFFF 
/* 定义常用变量别名 */
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long


/* 常用指令集 */
void AS608_SendDataPkg(u8 flag,u16 length,u8 cmd,u8 *ucstr);/* 发送数据包 */
void PS_GetImage(void);	/* 录入图像 */
void PS_GenChar(u8 BufferID);	/* 生成特征 */
void PS_Match(void);	/* 精确比对两枚指纹特征 */
void PS_Search(u8 BufferID,u16 StartPage,u16 PageNum);/* 搜索指纹 */
void PS_RegModel(void);/* 合并特征（生成模板） */
void PS_StoreChar(u8 BufferID,u16 PageID);/* 储存模板 */
void PS_DeletChar(u16 PageID,u16 N);/* 删除模板 */
void PS_Empty(void);/* 清空指纹库 */
void PS_WriteReg(u8 ID,u8 text);/* 写系统寄存器 */
void PS_ReadSysPara(void);/* 读系统基本参数 */
void PS_HighSpeedSearch(u8 BufferID,u16 StartPage,u16 PageNum);/* 高速搜索 */
void PS_ValidTempleteNum(void);/* 读有效模板个数 */

/* 其余指令集 */
void PS_LoadChar(u8 BufferID,u16 PageID);/* 读出模板 */
void PS_UpChar(u8 BufferID);/* 上传特征或模板 */
void PS_DownChar(u8 BufferID);/* 下载特征或模板 */
void PS_UpImage(void);/* 上传图像 */
void PS_DownImage(void);/* 下载图像 */
void PS_Enroll(void);/* 自动注册模板 */
void PS_Identify(void);/* 自动验证指纹 */
void PS_SetPwd(u32 PassWord);/* 设置口令 */
void PS_VfyPwd(u32 PassWord);/* 验证口令 */
void PS_GetRandomCode(void);/* 采样随机数 */
void PS_SetChipAddr(u32 Addr);/* 设置芯片地址 */
void PS_ReadINFpage(void);/* 读 flash 信息页 */
void PS_Port_Control(u8 Cmd);/* 端口控制 */
void PS_WriteNotepad(u8 NotePageNum,u8* content);/* 写记事本 */
void PS_ReadNotepad(u8 page);/* 读记事本 */
void PS_BurnCode(u8 mode);/* 烧写片内 FLASH */
void PS_GenBinImage(u8 BinImgTpye);/* 生成细化指纹图像 */

void PS_UserGPIOCommand(u8 GPIOCx,u8 Status);//用于实现用户 GPIO 输出控制命令（保留）
void PS_ReadIndexTable(u8 PageID);//读索引表（保留）

/* 接收应答包 */
void AS608_JudgeData(u8 *ucstr);/* 分析接收到的应答包 */
#endif	/* __AS608_H */
