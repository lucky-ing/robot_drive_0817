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
** 文 件 名: CNTL.c
** 创 建 人: 罗辉联 	
** 创建日期: 2007年12月28日
** 描    述: CNTL函数实体部分
** 技术顾问: 楼东武(副教授)  浙江大学信电系
**
**---------- 版本信息------------------------------------------------------------------
** 版    本: V1.0
** 说    明: 发光二极管，轰鸣器控制
**
**-------------------------------------------------------------------------------------
**************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "config.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Public  variables ---------------------------------------------------------*/

/****************************************************************************************
** 函数名称: Buzzer_Configuration
** 功能描述: Buzzer 配置
** 参    数: None
** 返 回 值: None       
** 作　  者: 罗辉联
** 日  　期: 2008年1月7日
**---------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void Buzzer_Configuration(void)
{
  	GPIO_InitTypeDef  GPIO_InitStructure;
 
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOB, GPIO_Pin_8);
}

/****************************************************************************************
** 函数名称: LED_Configuration
** 功能描述: LED输出管脚配置
** 参    数: None
** 返 回 值: None       
** 作　  者: 罗辉联
** 日  　期: 2008年1月7日
**---------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void LED_Configuration(void)
{
  	GPIO_InitTypeDef  GPIO_InitStructure;
 
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOA, GPIO_Pin_8);	
   	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 | GPIO_Pin_8;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);

   	GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	GPIO_ResetBits(GPIOB, GPIO_Pin_15);

	
	
}

/****************************************************************************************
** 函数名称: Buzzer_On
** 功能描述: 轰鸣器轰鸣
** 参    数: None
** 返 回 值: None       
** 作　  者: 罗辉联
** 日  　期: 2008年1月7日
**---------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void Buzzer_On(void)
{
  	GPIO_SetBits(GPIOB, GPIO_Pin_8);

	OSTimeDlyHMSM(0,0,0,200);

	GPIO_ResetBits(GPIOB, GPIO_Pin_8);  	
}

/****************************************************************************************
** 函数名称: Diode_Show
** 功能描述: 放光二极管循环显示
** 参    数: None
** 返 回 值: None       
** 作　  者: 罗辉联
** 日  　期: 2008年1月7日
**---------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void Diode_Show(u8 data)
{
	if(data == 8)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);
		GPIO_ResetBits(GPIOB, GPIO_Pin_14);
		GPIO_SetBits(GPIOB, GPIO_Pin_13);
		
	}
	else if(data == 7)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
		GPIO_SetBits(GPIOB, GPIO_Pin_14);
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);
		
	}
	else if(data == 6)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
		GPIO_ResetBits(GPIOB, GPIO_Pin_14);
		GPIO_SetBits(GPIOB, GPIO_Pin_13);
		
	}
	else if(data == 5)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);
		GPIO_SetBits(GPIOB, GPIO_Pin_14);
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);
		
	}
	else if(data == 4)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
		GPIO_SetBits(GPIOB, GPIO_Pin_14);
		GPIO_SetBits(GPIOB, GPIO_Pin_13);
		
	}
	else if(data == 3)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);
		GPIO_SetBits(GPIOB, GPIO_Pin_14);
		GPIO_SetBits(GPIOB, GPIO_Pin_13);
	}
	else if(data == 2)
	{
	 	GPIO_SetBits(GPIOA, GPIO_Pin_8);
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
		GPIO_ResetBits(GPIOB, GPIO_Pin_14);
		GPIO_SetBits(GPIOB, GPIO_Pin_13);
	}
	else if(data == 1)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
		GPIO_SetBits(GPIOB, GPIO_Pin_14);
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	}
	else if(data == 0)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);
		GPIO_ResetBits(GPIOB, GPIO_Pin_14);
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	}

}



/****************************** http://www.bogodtech.com **********************************/
