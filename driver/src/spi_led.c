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
** �� �� ��: spi_led.c
** �� �� ��: �޻��� 	
** ��������: 2007��12��28��
** ��    ��: spi_led����ʵ�岿��
** ��������: ¥����(������)  �㽭��ѧ�ŵ�ϵ
**
**---------- �汾��Ϣ------------------------------------------------------------------
** ��    ��: V1.0
** ˵    ��: SPI DRIVER HC595, AND HC595 DRIVE LED
**
**-------------------------------------------------------------------------------------
**************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "config.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SPI_CS_LOW()     GPIO_ResetBits(GPIOB, GPIO_Pin_9)
#define SPI_CS_HIGH()    GPIO_SetBits(GPIOB, GPIO_Pin_9)

#define SPI_MISO_LOW()	 GPIO_ResetBits(GPIOA, GPIO_Pin_6)
#define SPI_MOSI_LOW()	 GPIO_ResetBits(GPIOA, GPIO_Pin_7)
#define SPI_SCLK_LOW()	 GPIO_ResetBits(GPIOA, GPIO_Pin_5)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Public  variables ---------------------------------------------------------*/
 
/****************************************************************************************
** ��������: SPI_Config
** ��������: ��ʼ��SPI1
** ��    ��: None
** �� �� ֵ: None       
** ����  ��: �޻���
** ��  ����: 2008��1��7��
**---------------------------------------------------------------------------------------
** �� �� ��: 
** �ա�  ��: 
**--------------------------------------------------------------------------------------
****************************************************************************************/

void SPI_Config(void)
{
 	SPI_InitTypeDef  SPI_InitStructure;
  	GPIO_InitTypeDef GPIO_InitStructure;
   
  	/* Enable SPI1 clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 , ENABLE);
  
  	/* Configure SPI1 pins: NSS, SCK, MISO and MOSI */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

  	/* Configure PA.4 as Output push-pull, used as Flash Chip select */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);

  	/* Deselect the FLASH: Chip Select high */
  	SPI_CS_HIGH();

   /* SPI1 Config */
  	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
  	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  	SPI_InitStructure.SPI_CRCPolynomial = 7;
  	SPI_Init(SPI1, &SPI_InitStructure);
  
  	/* Enable SPI1  */
  	SPI_Cmd(SPI1, ENABLE);
	
}


/****************************************************************************************
** ��������: SPI_SendByte
** ��������: ͨ��SPI�ӿڷ���һ���ֽ�
** ��    ��: byte: ���͵��ֽ�
** �� �� ֵ: None       
** ����  ��: �޻���
** ��  ����: 2008��1��7��
**---------------------------------------------------------------------------------------
** �� �� ��: 
** �ա�  ��: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void SPI_SendByte(INT8U data)
{
	SPI_CS_LOW();

  	/* Wait until the transmit buffer is empty */
  	while (SPI_GetFlagStatus(SPI1, SPI_FLAG_TXE) == RESET);
  	/* Send the byte */
  
  	SPI_SendData(SPI1, data);

  	SPI_CS_HIGH();
}





/****************************** http://www.bogodtech.com *********************************/
