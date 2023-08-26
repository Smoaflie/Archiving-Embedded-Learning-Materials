#ifndef _AS608_H
#define _AS608_H

#include "UART.h"	//自主配置：请修改为相应主控UART功能的头文件

/* 自主配置 */
/* 定义触摸检测IO口 */
//#define AS608_TOUCH GPIO_X	
/* 定义UART发送函数 */
//#define UART_SendByte UART_SendByte	

/* 定义模块地址 */
#define AS608Addr 0XFFFFFFFF 

/* 设置别名 */
/* 常用变量 */
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

/* 常用指令集 */
void AS608_SendDataPkg(uchar flag,uint length,uchar cmd,uchar *data);/* 发送数据包 */
void PS_GetImage(void);	/* 录入图像 */
void PS_GenChar(uchar BufferID);	/* 生成特征 */
void PS_Match(void);	/* 精确比对两枚指纹特征 */
void PS_Search(uchar BufferID,uint StartPage,uint PageNum);/* 搜索指纹 */
void PS_RegModel(void);/* 合并特征（生成模板） */
void PS_StoreChar(uchar BufferID,uint PageID);/* 储存模板 */
void PS_DeletChar(uint PageID,uint N);/* 删除模板 */
void PS_Empty(void);/* 清空指纹库 */
void PS_WriteReg(uchar ID,uchar text);/* 写系统寄存器 */
void PS_ReadSysPara(void);/* 读系统基本参数 */
void PS_HighSpeedSearch(uchar BufferID,uint StartPage,uint PageNum);/* 高速搜索 */
void PS_ValidTempleteNum(void);/* 读有效模板个数 */

/* 其余指令集 */
void PS_LoadChar(uchar BufferID,uint PageID);/* 读出模板 */
void PS_UpChar(uchar BufferID);/* 上传特征或模板 */
void PS_DownChar(uchar BufferID);/* 下载特征或模板 */
void PS_UpImage(void);/* 上传图像 */
void PS_DownImage(void);/* 下载图像 */
void PS_Enroll(void);/* 自动注册模板 */
void PS_Identify(void);/* 自动验证指纹 */
void PS_SetPwd(ulong PassWord);/* 设置口令 */
void PS_VfyPwd(ulong PassWord);/* 验证口令 */
void PS_GetRandomCode(void);/* 采样随机数 */
void PS_SetChipAddr(ulong Addr);/* 设置芯片地址 */
void PS_ReadINFpage(void);/* 读 flash 信息页 */
void PS_Port_Control(uchar Cmd);/* 端口控制 */
void PS_WriteNotepad(uint length,uchar NotePageNum,uchar* content);/* 写记事本 */
void PS_ReadNotepad(uchar page);/* 读记事本 */
void PS_BurnCode(uchar mode);/* 烧写片内 FLASH */
void PS_GenBinImage(uchar BinImgTpye);/* 生成细化指纹图像 */

void PS_UserGPIOCommand(uchar GPIOCx,uchar Status);//用于实现用户 GPIO 输出控制命令（保留）
void PS_ReadIndexTable(uchar PageID);//读索引表（保留）

/* 接收应答包 */
void AS608_JudgeData(uchar *data);/* 分析接收到的应答包 */
#endif	/* _AS608_H */
