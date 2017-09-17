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
** 文 件 名: spi_led.c
** 创 建 人: 罗辉联 	
** 创建日期: 2007年12月28日
** 描    述: spi_led函数实体部分
** 技术顾问: 楼东武(副教授)  浙江大学信电系
**
**---------- 版本信息------------------------------------------------------------------
** 版    本: V1.0
** 说    明: SPI DRIVER HC595, AND HC595 DRIVE LED
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
** 函数名称: SPI_Config
** 功能描述: 初始化SPI1
** 参    数: None
** 返 回 值: None       
** 作　  者: 罗辉联
** 日  　期: 2008年1月7日
**---------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
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
** 函数名称: SPI_SendByte
** 功能描述: 通过SPI接口发送一个字节
** 参    数: byte: 发送的字节
** 返 回 值: None       
** 作　  者: 罗辉联
** 日  　期: 2008年1月7日
**---------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
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
