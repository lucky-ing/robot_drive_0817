/****************************Copyright (c)*********************************************                                     
**
**               (c) Copyright 2006-2008, hui lian. luo, china, zj. hz 
**                            All Rights Reserved
**
**							  ������Ӣ������Ϣ�������޹�˾
**                            http://www.embedinfo.com
**                            �����Ƽ����޹�˾
**                            http://www.bogodtech.com                         
**
**--------------�ļ���Ϣ--------------------------------------------------------------
** �� �� ��: uart.c
** �� �� ��: �޻��� 	
** ��������: 2007��12��28��
** ��    ��: uart����ʵ�岿��
** ��������: ¥����(������)  �㽭��ѧ�ŵ�ϵ
**
**---------- �汾��Ϣ------------------------------------------------------------------
** ��    ��: V1.0
** ˵    ��: uart ��غ�����Ҫ��UART����
**
**-------------------------------------------------------------------------------------
**************************************************************************************/












/* Includes ------------------------------------------------------------------*/
#include "config.h"




#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
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
** ��������: UART_onfiguration
** ��������: UART1����
**  ��ӡ�õ�

uart2 ʹ��DMA ģʽ  ���� ������

���� ģʽ  ����  һ��ʱ�� 

** ��    ��: None
** �� �� ֵ: None       
** ����  ��: �޻���
** ��  ����: 2008��1��7��
**---------------------------------------------------------------------------------------
** �� �� ��: 
** �ա�  ��: 
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
** ��������: USART_SendChar
** ��������: UART1 �����ַ�
** ��    ��: USARTx: ���ں�,  Data: ����������
** �� �� ֵ: None       
** ����  ��: �޻���
** ��  ����: 2008��1��7��
**---------------------------------------------------------------------------------------
** �� �� ��: 
** �ա�  ��: 
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
;** ��������: printf
;** ��������: �Բ�ѯ�ķ�ʽ�򴮿ڷ����ַ���
;** 
;** ��    ��: format: ��Ҫ���͵��ַ���USART_SendData(USART1);
;**  
;** �� �� ֵ: ��
;**         
;** ����  ��: ���
;** ��  ����: 2006��5��21��
;**-------------------------------------------------------------------------------------------------------
;** �� �� ��: 
;** �ա�  ��: 
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
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART2->DR);//�����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&Uart_Send_Buffer;//�ڴ��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//dma���䷽����
	DMA_InitStructure.DMA_BufferSize = UART_TX_LEN;//����DMA�ڴ���ʱ�������ĳ��� word
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//����DMA���������ģʽ��һ������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//����DMA���ڴ����ģʽ��
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//���������ֳ�
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�ڴ������ֳ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//����DMA�Ĵ���ģʽ���������ϵ�ѭ��ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//����DMA�����ȼ���
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//����DMA��2��memory�еı����������
	DMA_Init(DMA_Channel7, &DMA_InitStructure);
	
	/* Enable DMA channel1 */
	//DMA_Cmd(DMA_Channel4, ENABLE);

	DMA_ITConfig(DMA_Channel7,DMA_IT_TC, ENABLE);  
	
	#endif
	
 

    DMA_Cmd(DMA_Channel6, DISABLE);                           // ��DMAͨ��

    DMA_DeInit(DMA_Channel6);                                 // �ָ�ȱʡֵ

    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);// ���ô��ڽ������ݼĴ���

    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Uart_Rx_Buffer;         // ���ý��ջ������׵�ַ

    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                      // ��������Ϊ����Դ������Ĵ��� -> �ڴ滺����

    DMA_InitStructure.DMA_BufferSize = UART_RX_LEN;                     // ��Ҫ�����ܽ��յ����ֽ���

    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        // �����ַ�������ӵ�����������������DMA�Զ�ʵ�ֵ�

    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 // �ڴ滺������ַ���ӵ���

    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // �������ݿ��8λ��1���ֽ�

    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         // �ڴ����ݿ��8λ��1���ֽ�

    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                           // ���δ���ģʽ

    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                 // ���ȼ�����

    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            // �ر��ڴ浽�ڴ��DMAģʽ

    DMA_Init(DMA_Channel6, &DMA_InitStructure);               // д������

    DMA_ClearFlag( DMA_FLAG_GL3);                                 // ���DMA���б�־

    DMA_Cmd(DMA_Channel6, ENABLE);                            // ��������DMAͨ�����ȴ���������

    



	USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);	
	



	//����DMA��ʽ����  
	USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);  


	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);  

	
	//��������    
	USART_Cmd(USART2, ENABLE);     
	  

}



#endif




