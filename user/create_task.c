/*
***************************************************************************************
*
*               (c) Copyright 2006-2008, hui lian. luo, china, zj. hz 
*                            All Rights Reserved
*
*							 ������Ӣ������Ϣ�������޹�˾
*                            http://www.embedinfo.com
*                            �����Ƽ����޹�˾
*                            http://www.bogodtech.com                         
*
*--------------�ļ���Ϣ-----------------------------------------------------------------
* �� �� ��: create_task.c
* �� �� ��: �޻���(wyuyun@hotmail.com, lhlzjut@hotmail.com, armgcc@foxmail.com) 	
* ��������: 2007��11��10��
* ��    ��: ��������ļ�
* ��������: ¥����(������)  �㽭��ѧ�ŵ�ϵ
*
*---------- �汾��Ϣ-------------------------------------------------------------------
* ��    ��: V1.0
*
*--------------------------------------------------------------------------------------
****************************************************************************************
*/

// �������� һ����ң�ؽ�������  

#include "config.h"
//#include "core_task.h"


/* 
**************************************************************************************** 
* Private variables:	TASK STACK ARRAY 
****************************************************************************************
*/
 
//OS_STK		KpdTaskStk[OS_KPD_TASK_STACK_SIZE];		/* ���������ջ	*/
//OS_STK		DTDTaskStk[OS_DTD_TASK_STACK_SIZE];		/* ���������ջ	*/
OS_STK		RFTaskStk[OS_RF_TASK_STACK_SIZE];		/* ���������ջ	*/
//OS_STK		MmiTaskStk[OS_MMI_TASK_STACK_SIZE];		/* ���������ջ */
//OS_STK		SnrTaskStk[OS_SNR_TASK_STACK_SIZE];		/* �����źŶ�ջ	*/
//OS_STK		ComTaskStk[OS_COM_TASK_STACK_SIZE];		/* ���������ջ */
//OS_STK		MOTORTaskStk[OS_MOTOR_TASK_STACK_SIZE];
//OS_STK		MISCTaskStk[OS_MISC_TASK_STACK_SIZE];
//OS_STK		PRESSKEYTaskStk[OS_KEY_TASK_STACK_SIZE];
OS_STK		LIMITTaskStk[OS_LIMTI_TASK_STACK_SIZE];
OS_STK		COMTaskStk[OS_COM_TASK_STACK_SIZE];
OS_STK		WORKTaskStk[OS_WORK_TASK_STACK_SIZE];
OS_STK		MAPTaskStk[OS_MAP_TASK_STACK_SIZE];
OS_STK		SENSORTaskStk[OS_SENOR_TASK_STACK_SIZE];





//  debug  �����õ�

#ifndef ROBOT_TEST
//OS_STK		DebugTaskStk[OS_DEBUG_TASK_STACK_SIZE];
#endif
#ifdef VOICE_SUPPORT
//OS_STK		VoiceTaskStk[OS_VOICE_TASK_STACK_SIZE];
#endif


//2013.4.22
#ifdef WIFI_SUPPORT
OS_STK		WifiTaskStk[OS_WIFI_TASK_STACK_SIZE];
#endif		
//OS_STK		ultrasonicTaskStk[OS_ULTRASONIC_TASK_STACK_SIZE];
//OS_STK		wheelTaskStk[OS_WHEEL_TASK_STACK_SIZE];
//__align(8) OS_STK		AdxlTaskStk[OS_ADXL235_TASK_STACK_SIZE];


/* 
**************************************************************************************** 
* Public variables:	OS EVENT ECB
****************************************************************************************
*/ 

OS_EVENT 	*ComSem;

extern volatile U8 inter_task_ready;


extern void debug_task_core(void *pdata);

/****************************************************************************************
** ��������: create_os_task
** ��������: ����ϵͳ�еĴ󲿷�����
** ��    ��: None
** �� �� ֵ: None       
** ����  ��: �޻���
** ��  ����: 2007��12��25��
**---------------------------------------------------------------------------------------
** �� �� ��: 
** �ա�  ��: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void create_os_task(void)
{
//	#if (OS_TASK_NAME_SIZE >= 16)
//		INT8U err;
//	#endif
	U8 rc = 0;


		#if 1
	rc = OSTaskCreateExt(interaction_task_core, (void *)0, (OS_STK *)&RFTaskStk[OS_RF_TASK_STACK_SIZE - 1],
					OS_RF_TASK_PRIO,
					OS_RF_TASK_PRIO,
					(OS_STK *)&RFTaskStk[0],
					OS_RF_TASK_STACK_SIZE,
					(void *)0,
					OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
		//OSTaskNameSet(OS_RF_TASK_PRIO, (INT8U *)"RF task", &err);
		#endif

		while(inter_task_ready == 0){

			OSTimeDlyHMSM(0,0,0,10);
		}

	if(rc != OS_NO_ERR) {

		printf("create exit fail:	%d", rc);
	}

		StartEvent=OSSemCreate(0);


#ifndef ROBOT_TEST
	OSTaskCreateExt(debug_task_core, (void *)0, (OS_STK *)&DebugTaskStk[OS_DEBUG_TASK_STACK_SIZE - 1],
					OS_DEBUG_TASK_PRIO,
					OS_DEBUG_TASK_PRIO,
					(OS_STK *)&DebugTaskStk[0],
					OS_DEBUG_TASK_STACK_SIZE,
					(void *)0,
					OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);	

#endif

#if 1
	OSTaskCreate(Car_limit_detect,(void *) 0,(OS_STK *)&LIMITTaskStk[OS_LIMTI_TASK_STACK_SIZE-1],OS_LIMIT_TASK_PRIO);
	OSTaskCreate(sensor_work,(void *) 0,(OS_STK *)&SENSORTaskStk[OS_SENOR_TASK_STACK_SIZE-1],OS_SENSOR_TASK_PRIO);
	OSTaskCreate(MapSend,(void *) 0,(OS_STK *)&MAPTaskStk[OS_MAP_TASK_STACK_SIZE-1],OS_MAP_TASK_PRIO);
	OSTaskCreate(Car_work,(void *) 0,(OS_STK *)&WORKTaskStk[OS_WORK_TASK_STACK_SIZE-1],OS_WORK_TASK_PRIO);
	OSTaskCreate(ComTask,(void *) 0,(OS_STK *)&COMTaskStk[OS_COM_TASK_STACK_SIZE-1],OS_COM_TASK_PRIO);
	
#endif



}
/****************************************************************************************
** ��������: create_task_status
** ��������: ������������ĳ�ʼ״̬
** ��    ��: None
** �� �� ֵ: None       
** ����  ��: �޻���
** ��  ����: 2007��12��25��
**---------------------------------------------------------------------------------------
** �� �� ��: 
** �ա�  ��: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void create_task_status(void)
{


}

/****************************************************************************************
** ��������: create_os_semphore
** ��������: ����ϵͳ�еĴ󲿷��ź���
** ��    ��: None
** �� �� ֵ: None       
** ����  ��: �޻���
** ��  ����: 2007��12��25��
**---------------------------------------------------------------------------------------
** �� �� ��: 
** �ա�  ��: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void create_os_semphore(void)
{
	/* ���ڽ����ַ�֪ͨ�ź������� */
	ComSem = OSSemCreate(0);
				
}


/****************************************************************************************
** ��������: create_os_mutex
** ��������: ����ϵͳ�еĴ󲿷ֻ�����
** ��    ��: None
** �� �� ֵ: None       
** ����  ��: �޻���
** ��  ����: 2007��12��25��
**---------------------------------------------------------------------------------------
** �� �� ��: 
** �ա�  ��: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void create_os_mutex(void)
{
					
}
/****************************************************************************************
** ��������: create_os_mailbox
** ��������: ����ϵͳ�е�ͨ����Ϣ����
** ��    ��: None
** �� �� ֵ: None       
** ����  ��: �޻���
** ��  ����: 2007��12��25��
**---------------------------------------------------------------------------------------
** �� �� ��: 
** �ա�  ��: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void create_os_mailbox(void)
{
	/* MMI��Ϣ���䴴��������MMIϵͳ�ͼ�����Ϣ */
	//mmi_create_msg_mbox();
}

/****************************************************************************************
** ��������: create_os_queue
** ��������: ����ϵͳ�е�ͨ����Ϣ����
** ��    ��: None
** �� �� ֵ: None       
** ����  ��: �޻���
** ��  ����: 2007��12��25��
**---------------------------------------------------------------------------------------
** �� �� ��: 
** �ա�  ��: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void create_os_queue(void)
{
	/* ��Ϣ���д���ʵ�� */
	
}

/****************************************************************************************
** ��������: create_os_timer
** ��������: ����OS�����ʱ��
** ��    ��: None
** �� �� ֵ: None       
** ����  ��: �޻���
** ��  ����: 2007��12��25��
**---------------------------------------------------------------------------------------
** �� �� ��: 
** �ա�  ��: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void create_os_timer(void)
{
	/* Os�����ʱ��ʵ�崴�� */
	
}

/************************************** end of file ************************************/



