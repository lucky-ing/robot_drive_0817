/****************************Copyright (c)*********************************************                                     
**                                          
**                      博格达科技有限公司
**
**                        http://www.bogodtech.com
**
**--------------文件信息--------------------------------------------------------------
** 文 件 名: uart.h
** 创 建 人: 罗辉联 	
** 创建日期: 2007年12月28日
** 描    述: uart函数实体部分
** 技术顾问: 楼东武(副教授)  浙江大学信电系
**
**---------- 版本信息------------------------------------------------------------------
** 版    本: V1.0
** 说    明: UART 相关函数主要是pwm和gpio的设置与配置
**
**-------------------------------------------------------------------------------------
**************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H
#define __UART_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define RxBufferSize   0x1
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Public  variables ---------------------------------------------------------*/

/* Public  functions ---------------------------------------------------------*/
#ifdef UART_ENABLE
void UART_onfiguration (void);  


#define TS_DIRECTION_FORWARD   0
#define TS_DIRECTION_BACKWARD  1

#define TS_DIRECTION_TURN_LEFT_CENTER_DEFAULT 2
#define TS_DIRECTION_TURN_LEFT_CENTER_LEFT 3

#define TS_DIRECTION_TURN_RIGHT_CENTER_DEFAULT 4
#define TS_DIRECTION_TURN_RIGHT_CENTER_RIGHT 5

#define WALK_DURATION_START 0
#define WALK_DURATION_DOING 1
#define WALK_DURATION_END 	2


#define ACTION_STEP_START 1
#define ACTION_STEP_DOING 2
#define ACTION_STEP_FINISH 3


typedef struct {
	U16 start_code;
	U16 direction;
	U16 right_distance;
	U16 left_distance;
	U32 frame_count;
	float start_yaw;
	float current_yaw;

	U8 action_step;
	
	U8 end_code;
	U8 huiche;
	U8  huanhang;



	
}uart_command_t ;






typedef struct {

	U16 start_code;

	U16 dest_dist;
	U16 dest_arc;

	U8 dest_action;
	U8 dest_center;
	U8 scene;
	
	U8 crc;
	U16 end_code;

}robot_action_command_t;


//extern uart_command_t Uart_Send_Buffer;
void uart_send_data(void ) ;




#define   UART_RX_LEN 128

#ifdef UART3_ENABLE
extern U8 Uart_Rx_Buffer[];

extern U8 Uart_Rx_Ready_Buffer[];
extern U8 Uart_Rx_Ready ;
extern U8 Uart_Rx_Real_Len ;
#endif


#endif
//void printf(char * format, ...);


#endif /* __UART_H */

/****************************** http://www.bogodtech.com *******END OF FILE******************/
