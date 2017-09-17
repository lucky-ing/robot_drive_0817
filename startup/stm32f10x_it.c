/****************************Copyright (c)*********************************************                                     
*
*               (c) Copyright 2006-2008, hui lian. luo, china, zj. hz 
*                            All Rights Reserved
*
*							  深圳市英蓓特信息技术有限公司
*                            http://www.embedinfo.com
*                            博格达科技有限公司
*                            http://www.bogodtech.com                         
*
*---------- File Info ---------------------------------------------------------------
* File name: 		stm32f10x_it.c
* Created By: 		罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date: 	2007.11.28
* Descriptions: 	Main Interrupt Service Routines.
*                   -This file can be used to describe all the exceptions 
*                   -subroutines that may occur within user application.
*                   -When an interrupt happens, the software will branch 
*                   -automatically to the corresponding routine.
*                   -The following routines are all empty, user can write code 
*                   -for exceptions handlers and peripherals IRQ interrupts.
* Adviser: 			楼东武(professor)  浙江大学信电系
*
*---------- History Info -------------------------------------------------------------
* Version: 			Ver1.0
* Descriptions: 	Create Initilze file
*

*  红外遥控接收 中断做的
* 
*-------------------------------------------------------------------------------------
**************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "config.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile vu32	wdg_clr_flag = 1;
volatile U32 int_times[6] = {0,0,0,0,0,0};
volatile U32 tmr_times[6] = { 0,0,0,0,0,0};
volatile U8 head_ok[6];
volatile U32 code_data[6];
volatile U8 flagh[6];
volatile U32 shuju[6];

volatile U8 flag_near[6];
volatile U32 shuju_near[6];

volatile U8 flagr[6];
volatile U32 shujur[6];


volatile U32 r_int_finish = 0;
volatile U32 l_int_finish = 0;



volatile U8 flagr[6];


extern  volatile U16  turn_cycyle_to_find_mid_ir ;
extern volatile U16 turn_cycle_to_found_side_ir ;
extern volatile U16 turn_cycle_to_find_ir ;
volatile U32 right_wheel_counter= 0;
volatile U32 left_wheel_counter = 0;
extern volatile U32 r_int_finish ;
extern volatile U32 max_int_tick;
extern volatile U32 l_int_finish ;

extern volatile U16 side_ir_found ;
//extern volatile U16 no_found_position;
volatile U8 emu_key_state =0;
volatile U8 emu_key =0;
extern volatile U8 sl_forward_type;
extern OS_EVENT* pKeyValueMail;
extern U8 key_event;
extern volatile U8 need_wakeup_event ;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#define ck_not_yet
volatile U32 right_wheel_record = 0;
volatile U32 left_wheel_record  = 0;
extern volatile U32 rtc_retrive_counter;
extern volatile U16 turn_cycle_to_let_top_out;
extern machine_speed_s *last_speed_s1 ;
//#define weak_signal
//extern  vu16 ADC_SampleValue[2];
#define WRONG_WALK_TICK 0x7000

#if 1
volatile U32 l_ostime_old = 0;
volatile U32 l_tick_old = 0;
volatile U32  l_tick_delta = 0;
volatile U32 l_tick_now = 0;
volatile U32 l_tick_wrong = 0 ;
#endif

volatile U32 last_turn_tick_record = 0;
volatile U32 last_turn_ward = 0;

#ifdef UART_ENABLE
volatile U32 left_wheel_wrong = 0;
volatile U32 right_wheel_wrong = 0;
#endif

extern volatile U8 tx_int_count;


#define DUST_DETECT_TWICE


#define DUST_SENSOR_1 1000



#if 0 //def DUST_DETECT_TWICE
volatile U32 old_dust_time = 0;
volatile U32 dust_time_delta;
#endif

volatile U32 r_ostime_old = 0;
volatile U32 r_tick_old = 0;
volatile U32  r_tick_delta = 0;
volatile U32 r_tick_now = 0;
#ifdef ROBOT_TEST
volatile U32 r_tick_wrong = 0;
#endif

//volatile U32 tim1_eight_pluse = 0;

/*******************************************************************************
* Function Name : SysTickHandler
* Description   : This function handles SysTick Handler.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
//volatile U32 tmp_tk = 0 ;
U32 wheel_count = 0;
void SysTickHandler(void)
{
    OS_ENTER_CRITICAL(); /* Tell uC/OS-II that we are starting an ISR  */
    OSIntNesting++;
    OS_EXIT_CRITICAL();

    		OSTimeTick();        /* Call uC/OS-II's OSTimeTick()               */

	//it's for rf timer;
	//++ ;
	//wheel_count++;

	#if 0
	tmr_times[0]++;
	tmr_times[1]++;
	tmr_times[2]++;
	tmr_times[3]++;
	tmr_times[4]++;
	tmr_times[5]++;
	#endif
	

	//tmr_times[3]++;
	
    OSIntExit();         /* Tell uC/OS-II that we are leaving the ISR  */
}

/*******************************************************************************
* Function Name : WWDG_IRQHandler
* Description   : This function handles WWDG interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/

void WWDG_IRQHandler(void)
{
	//OS_ENTER_CRITICAL(); 	/* Tell uC/OS-II that we are starting an ISR */
   // OSIntNesting++;
   // OS_EXIT_CRITICAL();

	/* Update WWDG counter */
	//if(wdg_clr_flag == 1)
	//{
  	//	WWDG_SetCounter(0xFF);
	//	wdg_clr_flag = 0;
	//}
	
  	/* Clear EWI flag */
  //	WWDG_ClearFlag();

	//OSIntExit();         /* Tell uC/OS-II that we are leaving the ISR  */
}

/*******************************************************************************
* Function Name : PVD_IRQHandler
* Description   : This function handles PVD interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void PVD_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name : TAMPER_IRQHandler
* Description   : TThis function handles Tamper interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void TAMPER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name : RTC_IRQHandler
* Description   : This function handles RTC global interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
//extern u32 TimeDisplay; 
#define COUNTER_VALUE_23H_59M_59S 0x00015180
extern vu32 TimeDisplay;
U8 min_count = 0;
void RTC_IRQHandler(void)
{
#ifndef DS1302
//	U8 i;
		OS_ENTER_CRITICAL(); 	/* Tell uC/OS-II that we are starting an ISR */
	    OSIntNesting++;
	    OS_EXIT_CRITICAL();

#if defined(KL_SERIAL_5)||defined(KL_SERIAL_2)	
   if(RTC_GetITStatus(RTC_IT_SEC) != RESET)
  {
  	//IWDG_ReloadCounter();
    /* Clear the RTC Second interrupt */
    RTC_ClearITPendingBit(RTC_IT_SEC);
    
    /* Toggle led connected to PC.06 pin each 1s */
   // GPIO_WriteBit(GPIOC, GPIO_Pin_6, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_6)));

    /* Enable time update */
    min_count++;
    if(min_count>=60)
    	{
    	min_count = 0;
    	TimeDisplay = 1;
	rtc_retrive_counter = 0;
    	}
    /* Wait until last write operation on RTC registers has finished */
    //RTC_WaitForLastTask();
    #if 0
    /* Reset RTC Counter when Time is 23:59:59 */
    if(RTC_GetCounter() == 0x00015180)
    {
         //IWDG_ReloadCounter();
      RTC_SetCounter(0x0);
	 for(i=0;i<100;i++);
	   //RTC_WaitForLastTask();
      /* Wait until last write operation on RTC registers has finished */

    }
	#endif
  }
#endif
   OSIntExit();
#endif
}

/*******************************************************************************
* Function Name : FLASH_IRQHandler
* Description   : This function handles Flash interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void FLASH_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name : RCC_IRQHandler
* Description   : This function handles RCC interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void RCC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name : EXTI0_IRQHandler
* Description   : This function handles External interrupt Line 0 request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
	volatile U8 speed_delay = 0;

void EXTI0_IRQHandler(void)
{
 	OS_ENTER_CRITICAL(); 	/* Tell uC/OS-II that we are starting an ISR */
	OSIntNesting++;
	OS_EXIT_CRITICAL();

	OSIntExit();
}

/*******************************************************************************
* Function Name : EXTI1_IRQHandler
* Description   : This function handles External interrupt Line 1 request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/

void EXTI1_IRQHandler(void)
{
	OS_ENTER_CRITICAL(); 	/* Tell uC/OS-II that we are starting an ISR */
	OSIntNesting++;
	OS_EXIT_CRITICAL();
	OSIntExit();

}

/*******************************************************************************
* Function Name : EXTI2_IRQHandler
* Description   : This function handles External interrupt Line 2 request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void EXTI2_IRQHandler(void)
{


}
/*******************************************************************************
* Function Name : EXTI3_IRQHandler
* Description   : This function handles External interrupt Line 3 request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/


void EXTI3_IRQHandler(void)
{


}

/*******************************************************************************
* Function Name : EXTI4_IRQHandler
* Description   : This function handles External interrupt Line 4 request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/


void EXTI4_IRQHandler(void)
{

}
/*******************************************************************************
* Function Name : DMAChannel1_IRQHandler
* Description   : This function handles DMA Stream 1 interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void DMAChannel1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name : DMAChannel2_IRQHandler
* Description   : This function handles DMA Stream 2 interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void DMAChannel2_IRQHandler(void)
{
	DMA_ClearFlag(DMA_FLAG_TC2);	
	//关闭DMA	
	DMA_Cmd(DMA_Channel2,DISABLE);  

}

/*******************************************************************************
* Function Name : DMAChannel3_IRQHandler
* Description   : This function handles DMA Stream 3 interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void DMAChannel3_IRQHandler(void)
{
		   //清除标志位  
	DMA_ClearFlag(DMA_FLAG_TC3);	
	//关闭DMA	
	DMA_Cmd(DMA_Channel3,DISABLE);   

}

/*******************************************************************************
* Function Name : DMAChannel4_IRQHandler
* Description   : This function handles DMA Stream 4 interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void DMAChannel4_IRQHandler(void)
{
		   //清除标志位  
	DMA_ClearFlag(DMA_FLAG_TC4);	
	//关闭DMA	
	DMA_Cmd(DMA_Channel4,DISABLE);   


}

/*******************************************************************************
* Function Name : DMAChannel5_IRQHandler
* Description   : This function handles DMA Stream 5 interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void DMAChannel5_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name : DMAChannel6_IRQHandler
* Description   : This function handles DMA Stream 6 interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void DMAChannel6_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name : DMAChannel7_IRQHandler
* Description   : This function handles DMA Stream 7 interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void DMAChannel7_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name : ADC_IRQHandler
* Description   : This function handles ADC global interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/

void ADC_IRQHandler(void)
{


}


/*******************************************************************************
* Function Name : USB_HP_CAN_TX_IRQHandler
* Description   : This function handles USB High Priority or CAN TX interrupts 
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void USB_HP_CAN_TX_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name : USB_LP_CAN_RX0_IRQHandler
* Description   : This function handles USB Low Priority or CAN RX0 interrupts 
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void USB_LP_CAN_RX0_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name : CAN_RX1_IRQHandler
* Description   : This function handles CAN RX1 interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void CAN_RX1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name : CAN_SCE_IRQHandler
* Description   : This function handles CAN SCE interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void CAN_SCE_IRQHandler(void)
{
}


//U32 head_ok_count = 0;
volatile U32 err_count[6] = {0,0,0,0,0,0};



volatile U32 ir_data[6][40];
volatile U32 ir_index[6] = {0,0,0,0,0,0};

void wrong(U8 i)
{

   int_times[i]=0;
 
   head_ok[i]=0;
  
   flagr[i] = 0;
} 

#define START_MAX_COUNT  ((i >=4)?0x240: 0x5b0)
#define START_MIN_COUNT  ((i >=4)?0x180: 0x400)

volatile U32 forward_long_key[6] = {0,0,0,0,0,0};
volatile U32 forward_long_key_last_ostime[6] = {0,0,0,0,0,0};

U32 long_ostime_delta = 0;
void ir_check_long_key(U8 i) {

	if(forward_long_key[i] != 0) {
		long_ostime_delta = OSTimeGet() - forward_long_key_last_ostime[i];
		
		if(long_ostime_delta < 0x100) {


			forward_long_key_last_ostime[i] = OSTimeGet();
			
		
			int_times[i]=0;         
			head_ok[i]=0;                             
			
			shujur[i]=forward_long_key[i];          
			flagr[i]=1;
			ir_index[i] = 0;
			


		}else {

			forward_long_key_last_ostime[i] = 0;
			forward_long_key[i] = 0;



		}



	}



}

//  中断

void ir_parse(U8 i, U32 counter ){


	err_count[i]++;
	
	
#if 1
		
		if(head_ok[i]==0)
		{
			if( counter >START_MIN_COUNT && counter < START_MAX_COUNT)  
			{
				head_ok[i]=1;
				int_times[i]=0;
				
				code_data[i] = 0;// 0x8000;
				//head_ok_count ++;
				
				
				ir_index[i] = 0;
				ir_check_long_key(i);
				//buzzer_once_flag = 1;
				
				//ir_data[i][ir_index[i]] = counter;
			}
			else
			{
				wrong(i);
			}
		}
		else
		{   
			OS_ENTER_CRITICAL();

			if(counter >START_MIN_COUNT){

				if(counter < START_MAX_COUNT){
					
					head_ok[i]=1;
					int_times[i]=0;
					
					code_data[i] = 0x00000000;//0x8000;
					//head_ok_count ++;

					
					ir_index[i] = 0;

					ir_check_long_key(i);
					
					
					//err_count ++;
				}else {
					
					wrong(i);
				}
				
				
				OS_EXIT_CRITICAL();
				return ;
			}


					

			{


				if(counter  > 0xa0)
									
				{
					
					code_data[i]|=0x1;
				}    
				
				int_times[i]++;
				

				
				OS_EXIT_CRITICAL();


				if(int_times[i]==32)
				{
					
					
					OS_ENTER_CRITICAL();
					int_times[i]=0;         
					head_ok[i]=0;                             
					
					shujur[i]=code_data[i];          
					flagr[i]=1;
					ir_index[i] = 0;
					

					OS_EXIT_CRITICAL();
					
					if((shujur[i]&0xff) == KEY_UP ||(shujur[i]&0xff) == KEY_DOWN ||
						(shujur[i]&0xff) == KEY_LEFT ||(shujur[i]&0xff) == KEY_RIGHT  ){

						//printf("long ");
						forward_long_key[i] = shujur[i];
						forward_long_key_last_ostime[i] = OSTimeGet();

					}


				}
				
				else if((int_times[i]==8) && 
					((code_data[i] == CHAR_STA_LEFT)||(code_data[i]== CHAR_STA_RIGHT ) ||(code_data[i]== CHAR_STA_TOP ))){
					OS_ENTER_CRITICAL();
					int_times[i]=0;         
					head_ok[i]=0;                             

					if(code_data[i]== CHAR_STA_TOP ){
						shuju_near[i] = code_data[i];			
						flag_near[i] = 1;

					}else {
						shuju[i] = code_data[i];
						flagh[i] = 1;
					}
					

					ir_index[i] = 0;
					

					OS_EXIT_CRITICAL();


				}

				
				#if 1
				else {

					
						code_data[i]=code_data[i]<<1;
						

				}    
				#endif
				


			}
	}

#endif
}





void EXTI9_5_IRQHandler(void)
{
	OS_ENTER_CRITICAL(); 	/* Tell uC/OS-II that we are starting an ISR */
    	OSIntNesting++;
    	OS_EXIT_CRITICAL();



#if 1
	
		if(EXTI_GetITStatus(EXTI_Line9)!=RESET){
			EXTI_ClearITPendingBit(EXTI_Line9);
			//for(speed_delay= 0; speed_delay<200; speed_delay++);
			//if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)==1) 
			{
				OS_ENTER_CRITICAL();
				
				// l_int_finish left 里程计 计数
				
				// 42脉冲  1cm
				// #define ONE_CM_CYCLE_NUM   42

				
				l_int_finish++;
		#if 0
							if(l_ostime_old == 0) {
								l_tick_old = SysTick_GetCounter();
								l_ostime_old = OSTime;
								l_int_finish++;
							}else {
								l_tick_now = SysTick_GetCounter();
				
								if((OSTime == l_ostime_old) && (l_tick_old > l_tick_now))
									l_tick_delta =	l_tick_old	-l_tick_now ;
								else
									l_tick_delta = l_tick_old + ((OSTime-l_ostime_old)*81000) -l_tick_now;
				
								
								if(l_tick_delta > WRONG_WALK_TICK) {
									l_ostime_old = OSTime ;
									l_tick_old = l_tick_now;
									l_int_finish++;
				
								}
							}
		#endif
			
				OS_EXIT_CRITICAL();
		
			}
		}
	#endif


	




 	OSIntExit();
}

/*******************************************************************************
* Function Name : TIM1_BRK_IRQHandler
* Description   : This function handles TIM1 Break interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void TIM1_BRK_IRQHandler(void)
{
TIM1_ClearFlag(TIM1_FLAG_Break);
}

/*******************************************************************************
* Function Name : TIM1_UP_IRQHandler
* Description   : This function handles TIM1 overflow and update interrupt
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/


void TIM1_UP_IRQHandler(void)
{
	OS_ENTER_CRITICAL(); 	/* Tell uC/OS-II that we are starting an ISR */
    	OSIntNesting++;
    	OS_EXIT_CRITICAL();


		if (TIM1_GetITStatus(TIM1_FLAG_Update) != RESET){
			TIM1_ClearFlag(TIM1_FLAG_Update);
			#if 0
			tim1_eight_pluse++;
			
			if(tim1_eight_pluse >=9) {
				TIM1_ITConfig(TIM1_IT_Update, DISABLE);
				TIM1_ClearFlag(TIM1_FLAG_Update);

			}
			#endif

		}
	OSIntExit();
}

/*******************************************************************************
* Function Name : TIM1_TRG_COM_IRQHandler
* Description   : This function handles TIM1 Trigger and Commutation interrupts 
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void TIM1_TRG_COM_IRQHandler(void)
{

OS_ENTER_CRITICAL();	/* Tell uC/OS-II that we are starting an ISR */
	OSIntNesting++;
	OS_EXIT_CRITICAL();


TIM1_ClearFlag(TIM1_FLAG_COM);
OSIntExit();

}

/*******************************************************************************
* Function Name : TIM1_CC_IRQHandler
* Description   : This function handles TIM1 capture compare interrupt request. 
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/


volatile U32 ir_tim1_counter2= 0;
volatile U32 ir_tim1_counter3 = 0;

volatile U32 ir_tim1_last_counter2 = 0;
volatile U32 ir_tim1_last_counter3 = 0;

volatile U32 delta_counter = 0;

U32 debug_index = 0;
U32 debug_info[128];

void TIM1_CC_IRQHandler(void)
{

	OS_ENTER_CRITICAL();	/* Tell uC/OS-II that we are starting an ISR */
	OSIntNesting++;
	OS_EXIT_CRITICAL();

	if (TIM1_GetITStatus(TIM1_IT_CC2) != RESET)
	{
		TIM1_ClearITPendingBit(TIM1_IT_CC2);
		


		 ir_tim1_counter2 = TIM1_GetCapture2();

		 if(ir_tim1_counter2 > ir_tim1_last_counter2) {
			delta_counter = ir_tim1_counter2 - ir_tim1_last_counter2;
		 }else	{

			delta_counter = ir_tim1_counter2 + 0xffff - ir_tim1_last_counter2;
		 }

		 ir_tim1_last_counter2 = ir_tim1_counter2;
		 

		//buzzer_once_flag = 1;
		
		 ir_parse(5, delta_counter);

	}	

	
	if (TIM1_GetITStatus(TIM1_IT_CC3) != RESET)
	{
		TIM1_ClearITPendingBit(TIM1_IT_CC3);
		ir_tim1_counter3 = TIM1_GetCapture3();
		
		if(ir_tim1_counter3 > ir_tim1_last_counter3) {
		   delta_counter = ir_tim1_counter3 - ir_tim1_last_counter3;
		}else  {
		
		   delta_counter = ir_tim1_counter3 + 0xffff - ir_tim1_last_counter3;
		}
		
		ir_tim1_last_counter3 = ir_tim1_counter3;

		debug_info[debug_index] = delta_counter;
		debug_index ++;
		if(debug_index >= 128)
			debug_index  = 0;
		
		

		ir_parse(4, delta_counter);

	}	

	OSIntExit();

}


/*******************************************************************************
* Function Name : TIM2_IRQHandler
* Description   : This function handles TIM2 global interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/

volatile U32 ir_tim2_counter1= 0;
volatile U32 ir_tim2_counter2 = 0;
volatile U32 ir_tim2_counter3= 0;
volatile U32 ir_tim2_counter4 = 0;

volatile U32 ir_tim2_last_counter1 = 0;
volatile U32 ir_tim2_last_counter2 = 0;
volatile U32 ir_tim2_last_counter3 = 0;
volatile U32 ir_tim2_last_counter4 = 0;



volatile U32 tim2_delta_counter = 0;

U32 tick0,tick1;


void TIM2_IRQHandler(void)
{
	OS_ENTER_CRITICAL(); 	/* Tell uC/OS-II that we are starting an ISR */
    OSIntNesting++;
    OS_EXIT_CRITICAL();
	

	 if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	 {
	 
		  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	 }

	 if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
		


		 ir_tim2_counter1 = TIM_GetCapture1(TIM2);

		 if(ir_tim2_counter1 > ir_tim2_last_counter1) {
			tim2_delta_counter = ir_tim2_counter1 - ir_tim2_last_counter1;
		 }else	{

			tim2_delta_counter = ir_tim2_counter1 + 0xffff - ir_tim2_last_counter1;
		 }

		 ir_tim2_last_counter1 = ir_tim2_counter1;
		 
		// printf("%d \r\n", tim2_delta_counter);


		//buzzer_once_flag = 1;

		 ir_parse(0, tim2_delta_counter);

	}	



	if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);
		

			//show_hour(22);
			
		 ir_tim2_counter2 = TIM_GetCapture2(TIM2);

			
		 if(ir_tim2_counter2 > ir_tim2_last_counter2) {
			tim2_delta_counter = ir_tim2_counter2 - ir_tim2_last_counter2;
		 }else	{

			tim2_delta_counter = ir_tim2_counter2 + 0xffff - ir_tim2_last_counter2;
		 }

		 ir_tim2_last_counter2 = ir_tim2_counter2;
		 
		 //buzzer_once_flag = 1;

			//printf("%d \r\n", tim2_delta_counter);
		 ir_parse(1, tim2_delta_counter);

	}	


	if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)
	{

		 TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);
			


		 ir_tim2_counter3 = TIM_GetCapture3(TIM2);

		 if(ir_tim2_counter3 > ir_tim2_last_counter3) {
			tim2_delta_counter = ir_tim2_counter3 - ir_tim2_last_counter3;
		 }else	{

			tim2_delta_counter = ir_tim2_counter3 + 0xffff - ir_tim2_last_counter3;
		 }

		 ir_tim2_last_counter3 = ir_tim2_counter3;
		 
		 //printf("%d \r\n",tim2_delta_counter);
		 ir_parse(2, tim2_delta_counter);
		 //buzzer_once_flag = 1;

				 

	}	

	if (TIM_GetITStatus(TIM2, TIM_IT_CC4) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC4);
		
		

		 ir_tim2_counter4 = TIM_GetCapture4(TIM2);

		 if(ir_tim2_counter4 > ir_tim2_last_counter4) {
			tim2_delta_counter = ir_tim2_counter4 - ir_tim2_last_counter4;
		 }else	{

			tim2_delta_counter = ir_tim2_counter4 + 0xffff - ir_tim2_last_counter4;
		 }
		// printf("3: %d \r\n",tim2_delta_counter);

		 ir_tim2_last_counter4 = ir_tim2_counter4;
		 
		 ir_parse(3, tim2_delta_counter);
		// buzzer_once_flag = 1;

	}	

	




	

	OSIntExit();



}

/*******************************************************************************
* Function Name : TIM3_IRQHandler
* Description   : This function handles TIM3 global interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void TIM3_IRQHandler(void)
{

}

/*******************************************************************************
* Function Name : TIM4_IRQHandler
* Description   : This function handles TIM4 global interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
//U16 capture4 = 0;
//U16 capture3 = 0;

void TIM4_IRQHandler(void)
{
	OS_ENTER_CRITICAL(); 	/* Tell uC/OS-II that we are starting an ISR */
    	OSIntNesting++;
    	OS_EXIT_CRITICAL();

  /* TIM2_CH2 toggling with frequency = 366.2 Hz */
  if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)
  {

     TIM_ClearITPendingBit(TIM4, TIM_IT_CC4);

  }	


	OSIntExit();
	
  #if 0
    if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)
  {
     TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);
	capture3 = TIM_GetCapture3(TIM4);
    TIM_SetCompare3(TIM4, capture3);
  }	
  printf("tim4 int\n");
#endif
}

/*******************************************************************************
* Function Name : I2C1_EV_IRQHandler
* Description   : This function handles I2C1 Event interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void I2C1_EV_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name : I2C1_ER_IRQHandler
* Description   : This function handles I2C1 Error interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void I2C1_ER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name : I2C2_EV_IRQHandler
* Description   : This function handles I2C2 Event interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void I2C2_EV_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name : I2C2_ER_IRQHandler
* Description   : This function handles I2C2 Error interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void I2C2_ER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name : SPI1_IRQHandler
* Description   : This function handles SPI1 global interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void SPI1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name : SPI2_IRQHandler
* Description   : This function handles SPI2 global interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void SPI2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name : USART1_IRQHandler
* Description   : This function handles USART1 global interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
#ifdef UART_ENABLE
u8 RxBuffer[RxBufferSize];
u8 RxCounter = 0; 
#endif

void USART3_IRQHandler(void)
{
#ifdef UART3_ENABLE
    uint32_t temp = 0;  
    uint16_t i = 0;  
    

	
    OS_ENTER_CRITICAL(); 	/* Tell uC/OS-II that we are starting an ISR */
    OSIntNesting++;
    OS_EXIT_CRITICAL();
#ifdef UART3_ENABLE

  
    if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)  
    {  
        //USART_ClearFlag(USART3,USART_IT_IDLE);  
		
        temp = USART3->SR;  
        temp = USART3->DR; //清USART_IT_IDLE标志  
        DMA_Cmd(DMA_Channel3,DISABLE);  
  
        temp = UART_RX_LEN - DMA_GetCurrDataCounter(DMA_Channel3);  

		Uart_Rx_Real_Len = temp;
		
		memset(Uart_Rx_Ready_Buffer, 0, UART_RX_LEN);
		
        for (i = 0;i < temp;i++)  
        {  

			Uart_Rx_Ready_Buffer[i] = Uart_Rx_Buffer[i];
			  
             
        }  

		Uart_Rx_Ready = 1;
		
  
        //设置传输数据长度  
        DMA_SetCurrDataCounter(DMA_Channel3, UART_RX_LEN);  
        //打开DMA  
        DMA_Cmd(DMA_Channel3,ENABLE);  
    }   
      

#endif
	OSIntExit();         	/* Tell uC/OS-II that we are leaving the ISR */
#endif

}


/*******************************************************************************
* Function Name : USART2_IRQHandler
* Description   : This function handles USART2 global interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/

#define MAX_RX3_DATA 64
U8 rx3_data[MAX_RX3_DATA];
U8 rx3_index = 0;

U8 rx3_command[MAX_RX3_DATA];
U8 rx3_finish = 0;

void USART2_IRQHandler(void)
{
    OS_ENTER_CRITICAL(); 	/* Tell uC/OS-II that we are starting an ISR */
    OSIntNesting++;
    OS_EXIT_CRITICAL();

	OSIntExit();         	/* Tell uC/OS-II that we are leaving the ISR */
	

}
/*******************************************************************************
* Function Name : USART3_IRQHandler
* Description   : This function handles USART3 global interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/






void USART1_IRQHandler(void)
{

	OS_ENTER_CRITICAL(); 	/* Tell uC/OS-II that we are starting an ISR */
	OSIntNesting++;
	OS_EXIT_CRITICAL();

#ifdef UART_ENABLE
		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
		{
			/* Read one byte from the receive data register */
			//RxBuffer[RxCounter++] = (USART_ReceiveData(USART1) );		  
			RxBuffer[0] = (USART_ReceiveData(USART1) );	
			/* Clear the USART1 Receive interrupt */
			USART_ClearITPendingBit(USART1, USART_IT_RXNE);
			
			emu_key = RxBuffer[0];
			emu_key_state = 1;
			
				
			//if(RxCounter >= RxBufferSize)
			//{  
				/* Disable the USART Receive interrupt */
				//USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
				RxCounter = 0;
				//OSSemPost(ComSem);

			//}
		}
#endif

	OSIntExit();         	/* Tell uC/OS-II that we are leaving the ISR */
}

/*******************************************************************************
* Function Name : EXTI15_10_IRQHandler
* Description   : This function handles External lines 15 to 10 interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
	OS_ENTER_CRITICAL(); 	/* Tell uC/OS-II that we are starting an ISR */
	OSIntNesting++;
	OS_EXIT_CRITICAL();


	if(EXTI_GetITStatus(EXTI_Line14)!=RESET){
		EXTI_ClearITPendingBit(EXTI_Line14);

		//for(speed_delay= 0; speed_delay<200; speed_delay++);
		
		//if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1) 

		{
			OS_ENTER_CRITICAL();
	#if 0
					
					if(r_ostime_old == 0) {
						r_tick_old = SysTick_GetCounter();
						r_ostime_old = OSTime;
						r_int_finish++;
					}else {
						r_tick_now = SysTick_GetCounter();
			
						if((OSTime == r_ostime_old) && (r_tick_old > r_tick_now))
							r_tick_delta = r_tick_old -r_tick_now ;
						else
							r_tick_delta = r_tick_old + ((OSTime-r_ostime_old)*81000) -r_tick_now;
			
						if(r_tick_delta > WRONG_WALK_TICK) {
							r_ostime_old = OSTime ;
							r_tick_old = r_tick_now;
							r_int_finish++;
			
						}

						
					}
	#endif			
			r_int_finish ++;
			OS_EXIT_CRITICAL();
		}
		
		
	}

	



	OSIntExit();
}

/*******************************************************************************
* Function Name : RTCAlarm_IRQHandler
* Description   : This function handles RTC Alarm interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void RTCAlarm_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name : USBWakeUp_IRQHandler
* Description   : This function handles USB WakeUp interrupt request.
* Input         : None
* Return        : None
* Created By	: 罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date	: 2007.11.28
*-------------------------------------------------------------------------------
*******************************************************************************/
void USBWakeUp_IRQHandler(void)
{
}

/****************** http://www.bogodtech.com *******End of file ******************/



