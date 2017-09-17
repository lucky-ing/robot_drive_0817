/*
***************************************************************************************
*
*               (c) Copyright 2006-2008, hui lian. luo, china, zj. hz 
*                            All Rights Reserved
*
*							 深圳市英蓓特信息技术有限公司
*                            http://www.embedinfo.com
*                            博格达科技有限公司
*                            http://www.bogodtech.com                         
*
*--------------文件信息-----------------------------------------------------------------
* 文 件 名: create_task.c
* 创 建 人: 罗辉联(wyuyun@hotmail.com, lhlzjut@hotmail.com, armgcc@foxmail.com) 	
* 创建日期: 2007年11月10日
* 描    述: 任务管理文件
* 技术顾问: 楼东武(副教授)  浙江大学信电系
*
*---------- 版本信息-------------------------------------------------------------------
* 版    本: V1.0
*
*--------------------------------------------------------------------------------------
****************************************************************************************
*/

// 两个进程 一个是遥控接收命令  

#include "config.h"
//#include "core_task.h"


/* 
**************************************************************************************** 
* Private variables:	TASK STACK ARRAY 
****************************************************************************************
*/
 
//OS_STK		KpdTaskStk[OS_KPD_TASK_STACK_SIZE];		/* 键盘任务堆栈	*/
//OS_STK		DTDTaskStk[OS_DTD_TASK_STACK_SIZE];		/* 键盘任务堆栈	*/
OS_STK		RFTaskStk[OS_RF_TASK_STACK_SIZE];		/* 键盘任务堆栈	*/
//OS_STK		MmiTaskStk[OS_MMI_TASK_STACK_SIZE];		/* 界面任务堆栈 */
//OS_STK		SnrTaskStk[OS_SNR_TASK_STACK_SIZE];		/* 传感信号堆栈	*/
//OS_STK		ComTaskStk[OS_COM_TASK_STACK_SIZE];		/* 串口任务堆栈 */
//OS_STK		MOTORTaskStk[OS_MOTOR_TASK_STACK_SIZE];
//OS_STK		MISCTaskStk[OS_MISC_TASK_STACK_SIZE];
//OS_STK		PRESSKEYTaskStk[OS_KEY_TASK_STACK_SIZE];
OS_STK		LIMITTaskStk[OS_LIMTI_TASK_STACK_SIZE];
OS_STK		COMTaskStk[OS_COM_TASK_STACK_SIZE];
OS_STK		WORKTaskStk[OS_WORK_TASK_STACK_SIZE];
OS_STK		MAPTaskStk[OS_MAP_TASK_STACK_SIZE];
OS_STK		SENSORTaskStk[OS_SENOR_TASK_STACK_SIZE];





//  debug  任务用的

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
** 函数名称: create_os_task
** 功能描述: 创建系统中的大部分任务
** 参    数: None
** 返 回 值: None       
** 作　  者: 罗辉联
** 日  　期: 2007年12月25日
**---------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
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
** 函数名称: create_task_status
** 功能描述: 设置特殊任务的初始状态
** 参    数: None
** 返 回 值: None       
** 作　  者: 罗辉联
** 日  　期: 2007年12月25日
**---------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void create_task_status(void)
{


}

/****************************************************************************************
** 函数名称: create_os_semphore
** 功能描述: 创建系统中的大部分信号量
** 参    数: None
** 返 回 值: None       
** 作　  者: 罗辉联
** 日  　期: 2007年12月25日
**---------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void create_os_semphore(void)
{
	/* 串口接收字符通知信号量创建 */
	ComSem = OSSemCreate(0);
				
}


/****************************************************************************************
** 函数名称: create_os_mutex
** 功能描述: 创建系统中的大部分互斥量
** 参    数: None
** 返 回 值: None       
** 作　  者: 罗辉联
** 日  　期: 2007年12月25日
**---------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void create_os_mutex(void)
{
					
}
/****************************************************************************************
** 函数名称: create_os_mailbox
** 功能描述: 创建系统中的通用消息邮箱
** 参    数: None
** 返 回 值: None       
** 作　  者: 罗辉联
** 日  　期: 2007年12月25日
**---------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void create_os_mailbox(void)
{
	/* MMI消息邮箱创建，发送MMI系统和键盘消息 */
	//mmi_create_msg_mbox();
}

/****************************************************************************************
** 函数名称: create_os_queue
** 功能描述: 创建系统中的通用消息队列
** 参    数: None
** 返 回 值: None       
** 作　  者: 罗辉联
** 日  　期: 2007年12月25日
**---------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void create_os_queue(void)
{
	/* 消息队列创建实体 */
	
}

/****************************************************************************************
** 函数名称: create_os_timer
** 功能描述: 创建OS软件定时器
** 参    数: None
** 返 回 值: None       
** 作　  者: 罗辉联
** 日  　期: 2007年12月25日
**---------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void create_os_timer(void)
{
	/* Os软件定时器实体创建 */
	
}

/************************************** end of file ************************************/



