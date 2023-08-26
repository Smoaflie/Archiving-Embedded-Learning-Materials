#ifndef _AS608_H
#define _AS608_H

#include "UART.h"	//�������ã����޸�Ϊ��Ӧ����UART���ܵ�ͷ�ļ�

/* �������� */
/* ���崥�����IO�� */
//#define AS608_TOUCH GPIO_X	
/* ����UART���ͺ��� */
//#define UART_SendByte UART_SendByte	

/* ����ģ���ַ */
#define AS608Addr 0XFFFFFFFF 

/* ���ñ��� */
/* ���ñ��� */
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

/* ����ָ� */
void AS608_SendDataPkg(uchar flag,uint length,uchar cmd,uchar *data);/* �������ݰ� */
void PS_GetImage(void);	/* ¼��ͼ�� */
void PS_GenChar(uchar BufferID);	/* �������� */
void PS_Match(void);	/* ��ȷ�ȶ���öָ������ */
void PS_Search(uchar BufferID,uint StartPage,uint PageNum);/* ����ָ�� */
void PS_RegModel(void);/* �ϲ�����������ģ�壩 */
void PS_StoreChar(uchar BufferID,uint PageID);/* ����ģ�� */
void PS_DeletChar(uint PageID,uint N);/* ɾ��ģ�� */
void PS_Empty(void);/* ���ָ�ƿ� */
void PS_WriteReg(uchar ID,uchar text);/* дϵͳ�Ĵ��� */
void PS_ReadSysPara(void);/* ��ϵͳ�������� */
void PS_HighSpeedSearch(uchar BufferID,uint StartPage,uint PageNum);/* �������� */
void PS_ValidTempleteNum(void);/* ����Чģ����� */

/* ����ָ� */
void PS_LoadChar(uchar BufferID,uint PageID);/* ����ģ�� */
void PS_UpChar(uchar BufferID);/* �ϴ�������ģ�� */
void PS_DownChar(uchar BufferID);/* ����������ģ�� */
void PS_UpImage(void);/* �ϴ�ͼ�� */
void PS_DownImage(void);/* ����ͼ�� */
void PS_Enroll(void);/* �Զ�ע��ģ�� */
void PS_Identify(void);/* �Զ���ָ֤�� */
void PS_SetPwd(ulong PassWord);/* ���ÿ��� */
void PS_VfyPwd(ulong PassWord);/* ��֤���� */
void PS_GetRandomCode(void);/* ��������� */
void PS_SetChipAddr(ulong Addr);/* ����оƬ��ַ */
void PS_ReadINFpage(void);/* �� flash ��Ϣҳ */
void PS_Port_Control(uchar Cmd);/* �˿ڿ��� */
void PS_WriteNotepad(uint length,uchar NotePageNum,uchar* content);/* д���±� */
void PS_ReadNotepad(uchar page);/* �����±� */
void PS_BurnCode(uchar mode);/* ��дƬ�� FLASH */
void PS_GenBinImage(uchar BinImgTpye);/* ����ϸ��ָ��ͼ�� */

void PS_UserGPIOCommand(uchar GPIOCx,uchar Status);//����ʵ���û� GPIO ����������������
void PS_ReadIndexTable(uchar PageID);//��������������

/* ����Ӧ��� */
void AS608_JudgeData(uchar *data);/* �������յ���Ӧ��� */
#endif	/* _AS608_H */
