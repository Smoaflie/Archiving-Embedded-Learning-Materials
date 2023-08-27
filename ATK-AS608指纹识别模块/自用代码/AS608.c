/********************************************************************************
 * 文 件 名: AS608.c
 * 版 本 号: 第二版
 * 修改作者: Smoaflie
 * 修改日期: 2023年08月27日
 * 功能介绍: 通过UART与AS608模块进行通讯         
 ******************************************************************************
 * 注意事项:	此文件为驱动AS608的模板，如需正常搭配AS608使用，请自主配置如下部分：（使用Ctrl+F搜索"自主配置"）
  AS608.h内：
  "stc89xx.h" 修改为相应主控UART功能的头文件
  定义触摸检测IO口
  定义UART发送函数
  自行配置AS608_JudgeData
  
  该代码遵守 GPL3.0开源协议，仅供学习参考，禁止商用
 *********************************************************************************/

#include "AS608.h"

/************************************************
  函数名称 	: 	AS608_SendHead
  功    能 	: 	发送包的前段部分(包头、地址、标识、长度）
  参    数 	: 	flag：包标识
  length：包长度
  cmd：指令码
  返 回 值 	: 	无
 *************************************************/
void AS608_SendHead(u8 flag,u16 length)
{
	/* 发送包头 */
	UART_SendByte(0xEF);
	UART_SendByte(0x01);
	/* 发送地址 */
	UART_SendByte(AS608Addr>>24);
	UART_SendByte(AS608Addr>>16);
	UART_SendByte(AS608Addr>>8);
	UART_SendByte(AS608Addr);
	/* 发送包标识 */
	UART_SendByte(flag);
	/* 发送包长度 */
	UART_SendByte(length>>8);
	UART_SendByte(length);
}

/************************************************
  函数名称 	: 	AS608_SendCmdPkg
  功    能 	: 	发送不带参数的命令包
  参    数 	: 	flag：包标识
  length：包长度
  cmd：指令码
  返 回 值 	: 	无
 *************************************************/
//发送不带参数的命令包
void AS608_SendCmdPkg(u8 flag,u16 length,u8 cmd)
{
	u16 AS608_Bytes_Sum = (u16)flag+(u16)length+(u16)cmd;			//用以存储包标识至校验和之间所有字节之和(不包括校验和)
	AS608_SendHead(flag,length);	//发送包的前段部分
	/* 发送指令码 */
	UART_SendByte(cmd);
	/* 发送校验和 */
	UART_SendByte(AS608_Bytes_Sum>>8);
	UART_SendByte(AS608_Bytes_Sum);
}

/************************************************
  函数名称 	: 	AS608_SendParamPkg
  功    能 	: 	发送带参数的命令包
  参    数 	: 	flag：包标识
  length：包长度
  cmd：指令码
  data：参数
  返 回 值 	: 	无
 *************************************************/
void AS608_SendParamPkg(u8 flag,u16 length,u8 cmd,u8 *ucstr)
{
	u16 AS608_Bytes_Sum = (u16)flag+(u16)length+(u16)cmd;			//用以存储包标识至校验和之间所有字节之和(不包括校验和)
	AS608_SendHead(flag,length);	//发送包的前段部分
	/* 发送指令码 */
	UART_SendByte(cmd);
	/* 发送数据/参数 */
	length-=3;				//减去 指令码&校验和 的字节数，得到 参数 的长度
	while(length--)
	{
		AS608_Bytes_Sum += *ucstr;
		UART_SendByte(*ucstr++);
	}
	/* 发送校验和 */
	UART_SendByte(AS608_Bytes_Sum>>8);
	UART_SendByte(AS608_Bytes_Sum);
}

/************************************************
  函数名称 	: 	AS608_SendDataPkg
  功    能 	: 	发送数据包
  参    数 	: 	无
  返 回 值 	: 	无
 *************************************************/
void AS608_SendDataPkg(u8 flag,u16 length,u8 cmd,u8 *ucstr)
{
	u16 AS608_Bytes_Sum = (u16)flag+(u16)length;			//用以存储包标识至校验和之间所有字节之和(不包括校验和)
	AS608_SendHead(flag,length);	//发送包的前段部分
	/* 发送指令码 */
	UART_SendByte(cmd);
	/* 发送数据/参数 */
	length-=2;				//减去 校验和 的字节数，得到 数据 的长度
	while(length--)
	{
		AS608_Bytes_Sum += *ucstr;
		UART_SendByte(*ucstr++);
	}
	/* 发送校验和 */
	UART_SendByte(AS608_Bytes_Sum>>8);
	UART_SendByte(AS608_Bytes_Sum);
}
/************************************************
  函数名称 	: 	PS_GetImage
  功    能 	: 	探测手指，探测到后录入指纹图像存于 ImageBuffer。
  参    数 	: 	无
  返 回 值 	: 	无
 *************************************************/
void PS_GetImage(void)
{
	AS608_SendCmdPkg(0x01,0x0003,0x01);
}

/************************************************
  函数名称 	: 	PS_GenChar
  功    能 	: 	将 ImageBuffer 中的原始图像生成指纹特征文件存于 CharBuffer1 或 CharBuffer2 
  参    数 	: 	BufferID(特征缓冲区号)
  取 值	:		缓冲区 CharBuffer1、CharBuffer2 的 BufferID 分别为 1h 和 2h，如果指定其他值，按照 CharBuffer2 处理
  返 回 值 	: 	无
 *************************************************/
void PS_GenChar(u8 BufferID)
{
	AS608_SendParamPkg(0x01,0x0004,0x02,&BufferID);
}

/************************************************
  函数名称 	: 	PS_Match
  功    能 	: 	精确比对 CharBuffer1 与 CharBuffer2 中的特征文件
  参    数 	: 	无
  返 回 值 	: 	无
 *************************************************/
void PS_Match(void)
{
	AS608_SendCmdPkg(0x01,0x0003,0x03);
}

/************************************************
  函数名称 	: 	PS_Search
  功    能 	: 	以 CharBuffer1 或 CharBuffer2 中的特征文件搜索整个或部分指纹库。若搜索到，则返回页码。
  参    数 	: 	BufferID(特征缓冲区号)
  StartPage(起始页)
  PageNum（页数） 
  返 回 值 	: 	无
 *************************************************/
void PS_Search(u8 BufferID,u16 StartPage,u16 PageNum)
{
	u8  AS608_data_tmp[5];			//用以暂存 参数
	AS608_data_tmp[0]=BufferID;
	AS608_data_tmp[1]=StartPage>>8;
	AS608_data_tmp[2]=StartPage;
	AS608_data_tmp[3]=PageNum>>8;
	AS608_data_tmp[4]=PageNum;
	AS608_SendParamPkg(0x01,0x0008,0x04,AS608_data_tmp);
}

/************************************************
  函数名称 	: 	PS_RegModel
  功    能 	: 	将 CharBuffer1 与 CharBuffer2 中的特征文件合并生成模板，结果存于 CharBuffer1 与 CharBuffer2。
  参    数 	: 	无
  返 回 值 	: 	无
 *************************************************/
void PS_RegModel(void)
{
	AS608_SendCmdPkg(0x01,0x0003,0x05);
}

/************************************************
  函数名称 	: 	PS_StoreChar
  功    能 	: 	将 CharBuffer1 或 CharBuffer2 中的模板文件存到 PageID 号flash 数据库位置。
  参    数 	: 	BufferID(缓冲区号)
  PageID（指纹库位置号） 
  返 回 值 	: 	无
 *************************************************/
void PS_StoreChar(u8 BufferID,u16 PageID)
{
	u8  AS608_data_tmp[3];			//用以暂存 参数
	AS608_data_tmp[0]=BufferID;
	AS608_data_tmp[1]=PageID>>8;
	AS608_data_tmp[2]=PageID;
	AS608_SendParamPkg(0x01,0x0006,0x06,AS608_data_tmp);
}

/************************************************
  函数名称 	: 	PS_LoadChar
  功    能 	: 	将 flash 数据库中指定 ID 号的指纹模板读入到模板缓冲区 CharBuffer1 或 CharBuffer2
  参    数 	: 	BufferID(缓冲区号)
  PageID(指纹库模板号)
  返 回 值 	: 	无
 *************************************************/
void PS_LoadChar(u8 BufferID,u16 PageID)
{
	u8  AS608_data_tmp[3];			//用以暂存 参数
	AS608_data_tmp[0]=BufferID;
	AS608_data_tmp[1]=PageID>>8;
	AS608_data_tmp[2]=PageID;
	AS608_SendParamPkg(0x01,0x0006,0x07,AS608_data_tmp);
}

/************************************************
  函数名称 	: 	PS_UpChar
  功    能 	: 	将特征缓冲区中的特征文件上传给上位机
  参    数 	: 	BufferID(缓冲区号)
  返 回 值 	: 	无
 *************************************************/
void PS_UpChar(u8 BufferID)
{
	AS608_SendParamPkg(0x01,0x0004,0x08,&BufferID);
}

/************************************************
  函数名称 	: 	PS_DownChar
  功    能 	: 	上位机下载特征文件到模块的一个特征缓冲区
  参    数 	: 	BufferID(缓冲区号)
  返 回 值 	: 	无
 *************************************************/
void PS_DownChar(u8 BufferID)
{
	AS608_SendParamPkg(0x01,0x0004,0x09,&BufferID);
}

/************************************************
  函数名称 	: 	PS_UpImage
  功    能 	: 	将图像缓冲区中的数据上传给上位机
  参    数 	: 	无
  返 回 值 	: 	无
 *************************************************/
void PS_UpImage(void)
{
	AS608_SendCmdPkg(0x01,0x0003,0x0a);
}

/************************************************
  函数名称 	: 	PS_DownImage
  功    能 	: 	上位机下载图像数据给模块
  参    数 	: 	无
  返 回 值 	: 	无
 *************************************************/
void PS_DownImage(void)
{
	AS608_SendCmdPkg(0x01,0x0003,0x0b);
}

/************************************************
  函数名称 	: 	PS_DeletChar
  功    能 	: 	删除 flash 数据库中指定 ID 号开始的 N 个指纹模板
  参    数 	: 	PageID(指纹库模板号)
  N 删除的模板个数
  返 回 值 	: 	无
 *************************************************/
void PS_DeletChar(u16 PageID,u16 N)
{
	u8  AS608_data_tmp[4];			//用以暂存 参数
	AS608_data_tmp[0]=PageID>>8;
	AS608_data_tmp[1]=PageID;
	AS608_data_tmp[2]=N>>8;
	AS608_data_tmp[3]=N;
	AS608_SendParamPkg(0x01,0x0007,0x0c,AS608_data_tmp);
}

/************************************************
  函数名称 	: 	PS_Empty
  功    能 	: 	删除 flash 数据库中所有指纹模板
  参    数 	: 	无
  返 回 值 	: 	无
 *************************************************/
void PS_Empty(void)
{
	AS608_SendCmdPkg(0x01,0x0003,0x0d);
}

/************************************************
  函数名称 	: 	PS_WriteReg
  功    能 	: 	写模块寄存器
  参    数 	: 	ID(详见下方说明)
  text(详见下方说明)
  取 值	:		ID	介绍						N
  4 	波特率控制寄存器	(9600 的倍数 N)
  5 	比对阀值寄存器		(1：level1 2：level2 3：level3 4：level4 5：level5)
  6 	包大小寄存器			(0：32bytes 1：64bytes 2：128bytes 3：256bytes)
  返 回 值 	: 	无
 *************************************************/
void PS_WriteReg(u8 ID,u8 N)
{
	u8  AS608_data_tmp[2];			//用以暂存 参数/数据
	AS608_data_tmp[0]=ID;
	AS608_data_tmp[1]=N;
	AS608_SendParamPkg(0x01,0x0005,0x0e,AS608_data_tmp);
}

/************************************************
  函数名称 	: 	PS_ReadSysPara
  功    能 	: 	读取模块的基本参数（波特率，包大小等）。 
  参数表前 16 个字节存放了模块的基本通讯和配置信息，称为模块的基本参数
  参    数 	: 	无
  返 回 值 	: 	无
 *************************************************/
void PS_ReadSysPara(void)
{
	AS608_SendCmdPkg(0x01,0x0003,0x0f);
}

/************************************************
  函数名称 	: 	PS_Enroll
  功    能 	: 	采集一次指纹注册模板，在指纹库中搜索空位并存储，返回存储ID
  参    数 	: 	无
  返 回 值 	: 	无
 *************************************************/
void PS_Enroll(void)
{
	AS608_SendCmdPkg(0x01,0x0003,0x10);
}

/************************************************
  函数名称 	: 	PS_Identify
  功    能 	: 	自动采集指纹，在指纹库中搜索目标模板并返回搜索结果。 
  参    数 	: 	无
  返 回 值 	: 	无
 *************************************************/
void PS_Identify(void)
{
	AS608_SendCmdPkg(0x01,0x0003,0x11);
}

/************************************************
  函数名称 	: 	PS_SetPwd
  功    能 	: 	设置模块握手口令
  参    数 	: 	PassWord：密码
  返 回 值 	: 	无
 *************************************************/
void PS_SetPwd(u32 PassWord)
{
	AS608_SendParamPkg(0x01,0x0007,0x12,&PassWord);
}

/************************************************
  函数名称 	: 	PS_VfyPwd
  功    能 	: 	验证模块握手口令 
  参    数 	: 	PassWord
  返 回 值 	: 	无
 *************************************************/
void PS_VfyPwd(u32 PassWord)
{
	AS608_SendParamPkg(0x01,0x0007,0x13,&PassWord);
}

/************************************************
  函数名称 	: 	PS_GetRandomCode
  功    能 	: 	令芯片生成一个随机数并返回给上位机
  参    数 	: 	无
  返 回 值 	: 	无
 *************************************************/
void PS_GetRandomCode(void)
{
	AS608_SendCmdPkg(0x01,0x0003,0x14);
}

/************************************************
  函数名称 	: 	PS_SetChipAddr
  功    能 	: 	设置芯片地址 
  参    数 	: 	Addr
  返 回 值 	: 	无
 *************************************************/
void PS_SetChipAddr(u32 Addr)
{
	AS608_SendParamPkg(0x01,0x0007,0x15,&Addr);
}

/************************************************
  函数名称 	: 	PS_ReadINFpage
  功    能 	: 	读取 FLASH Information Page 所在的信息页(512bytes)
  参    数 	: 	无
  返 回 值 	: 	无
 *************************************************/
void PS_ReadINFpage(void)
{
	AS608_SendCmdPkg(0x01,0x0003,0x16);
}

/************************************************
  函数名称 	: 	PS_Port_Control
  功    能 	: 	对 USB 通讯端口进行开关控制。
  参    数 	: 	Cmd
  取 值	:		0 关闭端口;1 开启端口
  返 回 值 	: 	无
 *************************************************/
void PS_Port_Control(u8 Cmd)
{
	AS608_SendParamPkg(0x01,0x0004,0x17,&Cmd);
}

/************************************************
  函数名称 	: 	PS_WriteNotepad
  功    能 	: 	模块内部为用户开辟了 256bytes 的 FLASH 空间用于存放用户数据，该存储空间称为用户记事本，该记事本逻辑上被分成 16 个页，写记事本命令用于写入用户的 32bytes 数据到指定的记事本页。
  参    数 	: 	length(写入信息大小) 
  NotePageNum(页码) 
  content(用户信息)
  返 回 值 	: 	无
 *************************************************/
void PS_WriteNotepad(u8 NotePageNum,u8* content)
{
	u8 length = 0x0024;
	u16 AS608_Bytes_Sum = (u16)0x01+(u16)0x0024+(u16)0x18+(u16)NotePageNum;			//用以存储包标识至校验和之间所有字节之和(不包括校验和)
	AS608_SendHead(0x01,0x0024);	//发送包的前段部分
	/* 发送指令码 */
	UART_SendByte(0x18);
	/* 发送页码(参数) */
	UART_SendByte(NotePageNum);
	/* 发送用户信息 */
	length-=4;	//减去 指令码&页码&校验和 的字节数，得到 参数 的长度
	while(length--)
	{
		AS608_Bytes_Sum += *content;
		UART_SendByte(*content++);
	}
	/* 发送校验和 */
	UART_SendByte(AS608_Bytes_Sum>>8);
	UART_SendByte(AS608_Bytes_Sum);
}

/************************************************
  函数名称 	: 	PS_ReadNotepad
  功    能 	: 	读取 FLASH 用户区的 128bytes 数据 
  参    数 	: 	page(要读取的页码)
  取 值	:		x (x=0~15)
  返 回 值 	: 	无
 *************************************************/
void PS_ReadNotepad(u8 page)
{
	AS608_SendParamPkg(0x01,0x0004,0x19,&page);
}

/************************************************
  函数名称 	: 	PS_BurnCode
  功    能 	: 	上位机下载代码数据并写入 FLASH
  参    数 	: 	mode(模式)
  取 值	:		0:仅进行信息页升级;1:完整升级
  返 回 值 	: 	无
 *************************************************/
void PS_BurnCode(u8 mode)
{
	AS608_SendParamPkg(0x01,0x0004,0x1a,&mode);
}

/************************************************
  函数名称 	: 	PS_HighSpeedSearch
  功    能 	: 	以 CharBuffer1 或 CharBuffer2 中的特征文件高速搜索整个或部分指纹库。若搜索到，则返回页码。
  参    数 	: 	BufferID(特征缓冲区号)
  StartPage(起始页)
  PageNum（页数）
  返 回 值 	: 	无
 *************************************************/
void PS_HighSpeedSearch(u8 BufferID,u16 StartPage,u16 PageNum)
{
	u8  AS608_data_tmp[5];			//用以暂存 参数
	AS608_data_tmp[0]=BufferID;
	AS608_data_tmp[1]=StartPage>>8;
	AS608_data_tmp[2]=StartPage;
	AS608_data_tmp[3]=PageNum>>8;
	AS608_data_tmp[4]=PageNum;
	AS608_SendParamPkg(0x01,0x0008,0x1b,AS608_data_tmp);
}

/************************************************
  函数名称 	: 	PS_GenBinImage
  功    能 	: 	对图像缓冲区中的指纹图像进行处理并生成细化指纹图像
  参    数 	: 	BinImgTpye
  取 值	:		0：二值化图像 
  1：不含特征点标识的细化图像  
  2 或其他：带有特征点标识的细化图像
  返 回 值 	: 	无
 *************************************************/
void PS_GenBinImage(u8 BinImgTpye)
{
	AS608_SendParamPkg(0x01,0x0004,0x1c,&BinImgTpye);
}

/************************************************
  函数名称 	: 	PS_ValidTempleteNum
  功    能 	: 	读有效模板个数
  参    数 	: 	无
  返 回 值 	: 	无
 *************************************************/
void PS_ValidTempleteNum(void)
{
	AS608_SendCmdPkg(0x01,0x0003,0x1d);
}

/************************************************
  函数名称 	: 	PS_UserGPIOCommand
  功    能 	: 	用于实现用户 GPIO 输出控制命令（保留）
  参    数 	: 	GPIOCx：不同 Sensor 可控制的 GPIOC 不同，请根据参考设计原理图设置； 
  Status：0，表示输出低低电平；1，表示输出高电平；
  返 回 值 	: 	无
 *************************************************/
void PS_UserGPIOCommand(u8 GPIOCx,u8 Status)
{
	u8  AS608_data_tmp[5];			//用以暂存 参数
	AS608_data_tmp[0]=GPIOCx;
	AS608_data_tmp[1]=Status;
	AS608_SendParamPkg(0x01,0x0005,0x1e,AS608_data_tmp);
}

/************************************************
  函数名称 	: 	PS_ReadIndexTable
  功    能 	: 	读取录入模版的索引表。 （保留）
  参    数 	: 	PageID:索引表页码, 页码 0,1,2,3 分别对应模版从 0-256，256-512，
  512-768，768-1024 的索引，每 1 位代表一个模版，1 表示对应存储区域
  的模版已经录入，0 表示没录入。
  返 回 值 	: 	无
 *************************************************/
void PS_ReadIndexTable(u8 PageID)
{
	AS608_SendParamPkg(0x01,0x0004,0x1f,&PageID);
}

/************************************************
  函数名称 	: 	AS608_JudgeData
  功    能 	: 	搭配UART使用，分析接收到的数据，提取其中的确认码及数据（如果存在）
  参    数 	: 	data：接收到的数据
  返 回 值 	: 	无
 *************************************************/
/*			确认码的含义：
  {0x00, "       OK       "},
  {0x01, " 数据包接收错误 "},
  {0x02, "传感器上没有手指"},
  {0x03, "录入指纹图像失败"},
  {0x04, " 指纹太干或太淡 "},
  {0x05, " 指纹太湿或太糊 "},
  {0x06, "  指纹图像太乱  "},
  {0x07, " 指纹特征点太少 "},
  {0x08, "  指纹不匹配    "},
  {0x09, " 没有搜索到指纹 "},
  {0x0a, "   特征合并失败 "},
  {0x0b, "地址序号超出范围"},
  {0x10, "  删除模板失败  "},
  {0x11, " 清空指纹库失败 "},
  {0x15, "缓冲区内无有效图"},
  {0x18, " 读写FLASH出错  "},
  {0x19, "   未定义错误   "},
  {0x1a, "  无效寄存器号  "},
  {0x1b, " 寄存器内容错误 "},
  {0x1c, " 记事本页码错误 "},
  {0x1f, "    指纹库满    "},
  {0x20, "    地址错误    "}
 */
void AS608_JudgeData(u8 *ucstr)
{
	u16 AS608_Check_Sum;	//存储应答包的校验和
	u16 AS608_Bytes_Sum;	//存储计算出的校验和
	u16 length;					//存储包长度
	u8 result;					//存储确认码
	/* 检验应答包格式 */
	if(*ucstr==0xEF && *(ucstr+1)==0x01 && *(ucstr+2)==(u8)(AS608Addr>>24) && *(ucstr+3)==(u8)(AS608Addr>>16) && *(ucstr+4)==(u8)(AS608Addr>>8) && *(ucstr+5)==(u8)(AS608Addr) && *(ucstr+6)==0x07)
	{
		/* 确认是AS608应答包，开始检验校验和 */
		length = (*(ucstr+7)<<8) + *(ucstr+8);	//获取包长度
		AS608_Check_Sum = (*(ucstr+7+length)<<8) + *(ucstr+7+length+1);//获取校验和
		/* 计算校验和 */
		AS608_Bytes_Sum = 0x07;	//先加上包标识
		while(length--)	
		{
			AS608_Bytes_Sum += *(ucstr+7+length);	
		}
		
		/* 比对校验和 */
		if(AS608_Bytes_Sum==AS608_Check_Sum)	/* AS608_Bytes_Sum!=0,即校验和不正确，检验失败 */
		{
			/* 校验和检测成功 */
			/* 分析确认码 */
			result = *(ucstr+9);	//获取确认码
			if(result==0x00){
				//自主配置，执行相应操作
			}else{
				//自主配置，执行相应操作
			}
			
			/* 处理数据，可选 */
			length = (*(ucstr+7)<<8) + *(ucstr+8);	//获取包长度
			if(length>0x03)	//包长度>3，代表应答包携带了额外数据
			{
				//自主配置，执行相应操作
			}
		}
		else{	
			/* FAIL */
			//自主配置，执行相应操作
		}
	}
	else{		/* 不符合应答包格式 */
		/* FAIL */
		//自主配置，执行相应操作
	}
}

