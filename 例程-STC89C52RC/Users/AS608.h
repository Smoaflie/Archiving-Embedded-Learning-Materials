#ifndef __AS608_H
#define __AS608_H

#include "UART.h"	//�������ã����޸�Ϊ��Ӧ����UART���ܵ�ͷ�ļ�

/* �������� */
/* ���崥�����IO�� */
//#define AS608_TOUCH GPIO_X	
/* ����UART���ͺ��� */
//#define UART_SendByte UART_SendByte	

/* ����ģ���ַ */
#define AS608Addr 0XFFFFFFFF 
/* ���峣�ñ������� */
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long


/* ����ָ� */
void AS608_SendDataPkg(u8 flag,u16 length,u8 cmd,u8 *ucstr);/* �������ݰ� */
void PS_GetImage(void);	/* ¼��ͼ�� */
void PS_GenChar(u8 BufferID);	/* �������� */
void PS_Match(void);	/* ��ȷ�ȶ���öָ������ */
void PS_Search(u8 BufferID,u16 StartPage,u16 PageNum);/* ����ָ�� */
void PS_RegModel(void);/* �ϲ�����������ģ�壩 */
void PS_StoreChar(u8 BufferID,u16 PageID);/* ����ģ�� */
void PS_DeletChar(u16 PageID,u16 N);/* ɾ��ģ�� */
void PS_Empty(void);/* ���ָ�ƿ� */
void PS_WriteReg(u8 ID,u8 text);/* дϵͳ�Ĵ��� */
void PS_ReadSysPara(void);/* ��ϵͳ�������� */
void PS_HighSpeedSearch(u8 BufferID,u16 StartPage,u16 PageNum);/* �������� */
void PS_ValidTempleteNum(void);/* ����Чģ����� */

/* ����ָ� */
void PS_LoadChar(u8 BufferID,u16 PageID);/* ����ģ�� */
void PS_UpChar(u8 BufferID);/* �ϴ�������ģ�� */
void PS_DownChar(u8 BufferID);/* ����������ģ�� */
void PS_UpImage(void);/* �ϴ�ͼ�� */
void PS_DownImage(void);/* ����ͼ�� */
void PS_Enroll(void);/* �Զ�ע��ģ�� */
void PS_Identify(void);/* �Զ���ָ֤�� */
void PS_SetPwd(u32 PassWord);/* ���ÿ��� */
void PS_VfyPwd(u32 PassWord);/* ��֤���� */
void PS_GetRandomCode(void);/* ��������� */
void PS_SetChipAddr(u32 Addr);/* ����оƬ��ַ */
void PS_ReadINFpage(void);/* �� flash ��Ϣҳ */
void PS_Port_Control(u8 Cmd);/* �˿ڿ��� */
void PS_WriteNotepad(u8 NotePageNum,u8* content);/* д���±� */
void PS_ReadNotepad(u8 page);/* �����±� */
void PS_BurnCode(u8 mode);/* ��дƬ�� FLASH */
void PS_GenBinImage(u8 BinImgTpye);/* ����ϸ��ָ��ͼ�� */

void PS_UserGPIOCommand(u8 GPIOCx,u8 Status);//����ʵ���û� GPIO ����������������
void PS_ReadIndexTable(u8 PageID);//��������������

/* ����Ӧ��� */
void AS608_JudgeData(u8 *ucstr);/* �������յ���Ӧ��� */
#endif	/* __AS608_H */
