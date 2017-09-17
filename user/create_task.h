/*
***************************************************************************************
*                                                                              
*                       博格达科技有限公司
*
*               (c) Copyright 2006-2008, hui lian. luo, china, zj
*                            All Rights Reserved
*
*                           http://www.bogodtech.com                         
*
*--------------文件信息-----------------------------------------------------------------
* 文 件 名: create_task.h
* 创 建 人: 罗辉联 	
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

#ifndef CREATE_TASK_H
#define CREATE_TASK_H


/* 
**************************************************************************************** 
* Public define:	TASK PRIORITIES 
****************************************************************************************
*/
#if 1

////////////////by lucky
#define OS_LIMIT_TASK_PRIO 5
#define OS_COM_TASK_PRIO 12
#define OS_MAP_TASK_PRIO 13
#define OS_WORK_TASK_PRIO 11
#define OS_SENSOR_TASK_PRIO 9









#define OS_ADXL235_TASK_PRIO   5
#define OS_ULTRASONIC_TASK_PRIO		6
#define OS_RF_TASK_PRIO		7
#define OS_MOTOR_TASK_PRIO	8
#define OS_WHEEL_TASK_PRIO		9
#define OS_KEY_TASK_PRIO		10
#if 1 //def WIFI_SUPPORT
#define OS_WIFI_TASK_PRIO		11
#endif

#define OS_DTD_TASK_PRIO		12
//#define OS_COM_TASK_PRIO		13

#define OS_MISC_TASK_PRIO		14



#ifdef VOICE_SUPPORT
#define OS_VOICE_TASK_PRIO		15
#endif

#ifdef ROBOT_TEST
#define OS_DEBUG_TASK_PRIO      16
#endif



#endif
/* 
**************************************************************************************** 
* Private define:	TASK STACK SIZES 
****************************************************************************************
*/


/////////by lucky
#define OS_LIMTI_TASK_STACK_SIZE 128
#define OS_COM_TASK_STACK_SIZE 256
#define OS_MAP_TASK_STACK_SIZE 128
#define OS_WORK_TASK_STACK_SIZE 512
#define OS_SENOR_TASK_STACK_SIZE 512










#if  1//def ROBOT_TEST

//#define	OS_KPD_TASK_STACK_SIZE		64		/* 键盘任务堆栈大小 	*/ 
#define   OS_DTD_TASK_STACK_SIZE  64                  /*远程探测*/
#define   OS_RF_TASK_STACK_SIZE  96                  /*远程探测*/
//#define	OS_MMI_TASK_STACK_SIZE		256		/* 界面任务堆栈大小		*/
//#define	OS_SNR_TASK_STACK_SIZE	    80		/* 传感信号任务堆栈   	*/
//#define	OS_COM_TASK_STACK_SIZE		64		/* 串口任务堆栈大小 	*/
#define   OS_MOTOR_TASK_STACK_SIZE  312 //512 //637
#define   OS_MISC_TASK_STACK_SIZE 64
#define   OS_KEY_TASK_STACK_SIZE 64

#ifdef ROBOT_TEST
#define OS_DEBUG_TASK_STACK_SIZE 96
#endif
#else
//#define	OS_KPD_TASK_STACK_SIZE		64		/* 键盘任务堆栈大小 	*/ 
#define   OS_DTD_TASK_STACK_SIZE  64                  /*远程探测*/
#define   OS_RF_TASK_STACK_SIZE  64                  /*远程探测*/
//#define	OS_MMI_TASK_STACK_SIZE		256		/* 界面任务堆栈大小		*/
//#define	OS_SNR_TASK_STACK_SIZE	    80		/* 传感信号任务堆栈   	*/
#define	OS_COM_TASK_STACK_SIZE		64		/* 串口任务堆栈大小 	*/
#define   OS_MOTOR_TASK_STACK_SIZE  192 //512 //637
#define   OS_MISC_TASK_STACK_SIZE 64
#define   OS_KEY_TASK_STACK_SIZE 64
#endif

#define OS_VOICE_TASK_STACK_SIZE 64

//2013.4.22
#define OS_WIFI_TASK_STACK_SIZE	128

#define OS_ULTRASONIC_TASK_STACK_SIZE	324
#define OS_WHEEL_TASK_STACK_SIZE	256
#define OS_ADXL235_TASK_STACK_SIZE  384 //256

extern OS_EVENT 	*ComSem;


/* 
**************************************************************************************** 
* Public function 	
****************************************************************************************
*/ 

void create_os_task(void);

void create_task_status(void);

void create_os_semphore(void);

void create_os_mutex(void);

void create_os_mailbox(void);

void create_os_queue(void);

void create_os_timer(void);

#endif


/*********************** http://www.bogodtech.com *******End of file **********************/



