/****************************Copyright (c)*********************************************                                     
**
**               (c) Copyright 2006-2008, hui lian. luo, china, zj. hz 
**                            All Rights Reserved
**
**							  深圳市英蓓特信息技术有限公司
**                            http://www.embedinfo.com
**                            博格达科技有限公司
**                            http://www.bogodtech.com                         
**
**--------------文件信息--------------------------------------------------------------
** 文 件 名: uart.c
** 创 建 人: 罗辉联 	
** 创建日期: 2007年12月28日
** 描    述: uart函数实体部分
** 技术顾问: 楼东武(副教授)  浙江大学信电系
**
**---------- 版本信息------------------------------------------------------------------
** 版    本: V1.0
** 说    明: uart 相关函数主要是UART配置
**
**-------------------------------------------------------------------------------------
**************************************************************************************/












/* Includes ------------------------------------------------------------------*/
#include "config.h"




#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

















#ifdef UART_ENABLE
/* Private typedef -----------------------------------------------------------*/
typedef char * uart_va_list; 
/* Private define ------------------------------------------------------------*/
#define uart_sizeof_int(n)   		((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))
#define uart_va_start(ap,v)  		(ap = (uart_va_list)&v +uart_sizeof_int(v)) 
#define uart_va_arg(ap,t)    		(*(t *)((ap += uart_sizeof_int(t)) - uart_sizeof_int(t))) 
#define uart_va_end(ap)      		(ap = (uart_va_list)0) 
#define UART_SEND_BYTE(ch)			USART_SendChar(USART1, (u8*)ch)
#define UART_TX_LEN 128

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Public  variables ---------------------------------------------------------*/

/****************************************************************************************
** 函数名称: UART_onfiguration
** 功能描述: UART1配置
**  打印用的

uart2 使用DMA 模式  发射 来操作

空闲 模式  接收  一段时间 

** 参    数: None
** 返 回 值: None       
** 作　  者: 罗辉联
** 日  　期: 2008年1月7日
**---------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
**--------------------------------------------------------------------------------------
****************************************************************************************/

#if 1
void UART_onfiguration (void)  
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;						
  
  /* Enable USART1 clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE);

  /* Configure USARTx_Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure USARTx_Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* USARTx configuration ------------------------------------------------------*/
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStructure.USART_Clock = USART_Clock_Disable;
  USART_InitStructure.USART_CPOL = USART_CPOL_Low;
  USART_InitStructure.USART_CPHA = USART_CPHA_2Edge;
  USART_InitStructure.USART_LastBit = USART_LastBit_Disable;
  
  /* Configure the USARTx */ 
  USART_Init(USART1, &USART_InitStructure);

  /* Enable the USART Receive interrupt: this interrupt is generated when the 
   USART1 receive data register is not empty */
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  /* Enable the USARTx */
  USART_Cmd(USART1, ENABLE);            
}
#endif

/****************************************************************************************
** 函数名称: USART_SendChar
** 功能描述: UART1 发送字符
** 参    数: USARTx: 串口号,  Data: 待发送数据
** 返 回 值: None       
** 作　  者: 罗辉联
** 日  　期: 2008年1月7日
**---------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void USART_SendChar(USART_TypeDef* USARTx, u8* Data)
{
	//U8 i;
  /* Transmit Data */
  USARTx->DR = (Data[0]);
	//for(i=0;i<100;i++);
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);  
}


#endif

/*********************************************************************************************************
;** 函数名称: printf
;** 功能描述: 以查询的方式向串口发送字符串
;** 
;** 参    数: format: 将要发送的字符串USART_SendData(USART1);
;**  
;** 返 回 值: 无
;**         
;** 作　  者: 李海军
;** 日  　期: 2006年5月21日
;**-------------------------------------------------------------------------------------------------------
;** 修 改 人: 
;** 日　  期: 
;**------------------------------------------------------------------------------------------------------
;********************************************************************************************************/

/*


void printf(char * format, ...)
{

#ifndef UART_ENABLE
	return ;
#else
	char *			s = 0;
	int 				d = 0, i = 0;	
	unsigned char		ch[sizeof(int) * 2 + 2] = {0};
	uchar ff[10];
	float f=0.0;
	char buff [7];
	int m=0;
	uchar n=0,k=0;
	uart_va_list 		ap = 0;
	U8 huiche = 0x0d;
	U8 huanhang = 0x0a;
		
	uart_va_start(ap, format);
	
	while (* format) 
	{
		if (* format != '%') 
		{
			UART_SEND_BYTE(format++);
			continue;
		}
		switch (*(++format)) 
		{
			case 's':
			case 'S':				
				s = uart_va_arg(ap, char *);
				for ( ; *s; s++) 
				{
					UART_SEND_BYTE(s);
				}
				break;
			case 'c':
			case 'C':				
				UART_SEND_BYTE(uart_va_arg(ap, char));
				break;	
			case 'd':
			case 'D':				
				d = uart_va_arg(ap, int);
				for(i = 0; i < sizeof(int) * 2; i++)
				{
					ch[i] = (unsigned char)(d&0x0f) + '0';
					if(ch[i] > '9')
						ch[i] += 7; 
					d >>= 4;		
				}

				ch[i++] 	= 'x';
				ch[i]		= '0';

				for(i = sizeof(int) * 2 + 2; i > 0; i--)
					UART_SEND_BYTE(&ch[i -1]);
				break;
			case 'f':
			case 'F':				
				f = uart_va_arg(ap, float);
				if (f<0.0)
				{
					ff[0]='-';
					UART_SEND_BYTE(ff);
					f=-f;
					
				}
				d=(int)(f*100);
				m=d;
				for(;m>0;)
				{
					n++;
					m=m/10;	
				}
				m=n;
				for(;n>0;n--)
				{
					buff[n-1]=d%10+'0';
					d=d/10;
				}
				for(n=0;n<m;n++)
				{
					UART_SEND_BYTE(&buff[n]);
				}
				break;
			default:
				UART_SEND_BYTE(format);
				break;
		}
		format++;
	}
	uart_va_end(ap);	
	USART_SendChar(USART1, (u8*)&huiche);
	USART_SendChar(USART1, (u8*)&huanhang);




#endif
}

*/

#ifdef UART2_ENABLE


U8 Uart_Send_Buffer[UART_TX_LEN];



U8 Uart_Rx_Buffer[UART_RX_LEN];



U8 Uart_Rx_Ready_Buffer[UART_RX_LEN];
U8 Uart_Rx_Ready = 0;
U8 Uart_Rx_Real_Len = 0;





void Uart2_init(void) {



	DMA_InitTypeDef DMA_InitStructure;

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;						  


	printf("uart3 init start \r\n");
	
	/* Enable USART1 clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
	
	/* Configure USARTx_Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	/* Configure USARTx_Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	/* USARTx configuration ------------------------------------------------------*/
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Clock = USART_Clock_Disable;
	USART_InitStructure.USART_CPOL = USART_CPOL_Low;
	USART_InitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_InitStructure.USART_LastBit = USART_LastBit_Disable;
	
	/* Configure the USARTx */ 
	USART_Init(USART2, &USART_InitStructure);
	
	/* Enable the USART Receive interrupt: this interrupt is generated when the 
	 USART1 receive data register is not empty */
	USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);


 	#if 0
	DMA_DeInit(DMA_Channel7);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART2->DR);//外设地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&Uart_Send_Buffer;//内存地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//dma传输方向单向
	DMA_InitStructure.DMA_BufferSize = UART_TX_LEN;//设置DMA在传输时缓冲区的长度 word
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//设置DMA的外设递增模式，一个外设
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//设置DMA的内存递增模式，
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//外设数据字长
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//内存数据字长
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//设置DMA的传输模式：连续不断的循环模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//设置DMA的优先级别
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//设置DMA的2个memory中的变量互相访问
	DMA_Init(DMA_Channel7, &DMA_InitStructure);
	
	/* Enable DMA channel1 */
	//DMA_Cmd(DMA_Channel4, ENABLE);

	DMA_ITConfig(DMA_Channel7,DMA_IT_TC, ENABLE);  
	
	#endif
	
 

    DMA_Cmd(DMA_Channel6, DISABLE);                           // 关DMA通道

    DMA_DeInit(DMA_Channel6);                                 // 恢复缺省值

    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);// 设置串口接收数据寄存器

    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Uart_Rx_Buffer;         // 设置接收缓冲区首地址

    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                      // 设置外设为数据源，外设寄存器 -> 内存缓冲区

    DMA_InitStructure.DMA_BufferSize = UART_RX_LEN;                     // 需要最大可能接收到的字节数

    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        // 外设地址不做增加调整，调整不调整是DMA自动实现的

    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 // 内存缓冲区地址增加调整

    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // 外设数据宽度8位，1个字节

    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         // 内存数据宽度8位，1个字节

    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                           // 单次传输模式

    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                 // 优先级设置

    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            // 关闭内存到内存的DMA模式

    DMA_Init(DMA_Channel6, &DMA_InitStructure);               // 写入配置

    DMA_ClearFlag( DMA_FLAG_GL3);                                 // 清除DMA所有标志

    DMA_Cmd(DMA_Channel6, ENABLE);                            // 开启接收DMA通道，等待接收数据

    



	USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);	
	



	//采用DMA方式发送  
	USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);  


	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);  

	
	//启动串口    
	USART_Cmd(USART2, ENABLE);     
	  

}



#endif




