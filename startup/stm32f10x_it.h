/****************************Copyright (c)*********************************************                                     
*                                          
*                      博格达科技有限公司
*
*                        http://www.bogodtech.com
*
*---------- File Info ---------------------------------------------------------------
* File name: 		stm32f10x_it.h
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
*-------------------------------------------------------------------------------------
**************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_IT_H
#define __STM32F10x_IT_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void PendSVC(void);
void SysTickHandler(void);
void WWDG_IRQHandler(void);
void PVD_IRQHandler(void);
void TAMPER_IRQHandler(void);
void RTC_IRQHandler(void);
void FLASH_IRQHandler(void);
void RCC_IRQHandler(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void DMAChannel1_IRQHandler(void);
void DMAChannel2_IRQHandler(void);
void DMAChannel3_IRQHandler(void);
void DMAChannel4_IRQHandler(void);
void DMAChannel5_IRQHandler(void);
void DMAChannel6_IRQHandler(void);
void DMAChannel7_IRQHandler(void);
void ADC_IRQHandler(void);
void USB_HP_CAN_TX_IRQHandler(void);
void USB_LP_CAN_RX0_IRQHandler(void);
void CAN_RX1_IRQHandler(void);
void CAN_SCE_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void TIM1_BRK_IRQHandler(void);
void TIM1_UP_IRQHandler(void);
void TIM1_TRG_COM_IRQHandler(void);
void TIM1_CC_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void I2C1_EV_IRQHandler(void);
void I2C1_ER_IRQHandler(void);
void I2C2_EV_IRQHandler(void);
void I2C2_ER_IRQHandler(void);
void SPI1_IRQHandler(void);
void SPI2_IRQHandler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
void RTCAlarm_IRQHandler(void);
void USBWakeUp_IRQHandler(void);

#endif /* __STM32F10x_IT_H */

/****************** http://www.bogodtech.com *******End of file ******************/
