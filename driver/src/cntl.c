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
** �� �� ��: CNTL.c
** �� �� ��: �޻��� 	
** ��������: 2007��12��28��
** ��    ��: CNTL����ʵ�岿��
** ��������: ¥����(������)  �㽭��ѧ�ŵ�ϵ
**
**---------- �汾��Ϣ------------------------------------------------------------------
** ��    ��: V1.0
** ˵    ��: ��������ܣ�����������
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
** ��������: Buzzer_Configuration
** ��������: Buzzer ����
** ��    ��: None
** �� �� ֵ: None       
** ����  ��: �޻���
** ��  ����: 2008��1��7��
**---------------------------------------------------------------------------------------
** �� �� ��: 
** �ա�  ��: 
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
** ��������: LED_Configuration
** ��������: LED����ܽ�����
** ��    ��: None
** �� �� ֵ: None       
** ����  ��: �޻���
** ��  ����: 2008��1��7��
**---------------------------------------------------------------------------------------
** �� �� ��: 
** �ա�  ��: 
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
** ��������: Buzzer_On
** ��������: ����������
** ��    ��: None
** �� �� ֵ: None       
** ����  ��: �޻���
** ��  ����: 2008��1��7��
**---------------------------------------------------------------------------------------
** �� �� ��: 
** �ա�  ��: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void Buzzer_On(void)
{
  	GPIO_SetBits(GPIOB, GPIO_Pin_8);

	OSTimeDlyHMSM(0,0,0,200);

	GPIO_ResetBits(GPIOB, GPIO_Pin_8);  	
}

/****************************************************************************************
** ��������: Diode_Show
** ��������: �Ź������ѭ����ʾ
** ��    ��: None
** �� �� ֵ: None       
** ����  ��: �޻���
** ��  ����: 2008��1��7��
**---------------------------------------------------------------------------------------
** �� �� ��: 
** �ա�  ��: 
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
