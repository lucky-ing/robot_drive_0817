/****************************************Copyright (c)**********************************
**                                      
**                                          
**                                博格达科技有限公司
**
**                                 http://www.bogodtech.com
**
**--------------文件信息----------------------------------------------------------------
** 文 件 名: stm32f10x_target.c
** 创 建 人: 罗辉联(armgcc@foxmail.com, wyuyun@hotmail.com, lhlzjut@hotmail.com) 	
** 创建日期: 2007年12月10日
** 描    述: 目标板初始化函数
** 技术顾问: 楼东武(副教授)  浙江大学信电系
**
**---------- 版本信息-------------------------------------------------------------------
** 版    本: V1.0
** 说    明: 
**-------------------------------------------------------------------------------------*
****************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "config.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ErrorStatus HSEStartUpStatus;

/* Public  variables ---------------------------------------------------------*/
/* Public  function  ---------------------------------------------------------*/

// zhongduan 
/***************************************************************************************
** 函数名称: RCC_Configuration
** 功能描述: stm32f10x时钟系统配置
** 参    数: None
** 返 回 值: None       
** 作　  者: 罗辉联
** 日  　期: 2007年11月28日
**--------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
 void RCC_Configuration(void)	
{

#if 1


	/* 这里是重置了RCC的设置，类似寄存器复位 */
	RCC_DeInit();

	/* 使能外部高速晶振 */
	RCC_HSEConfig(RCC_HSE_ON);

	/* 等待高速晶振稳定 */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	if (HSEStartUpStatus == SUCCESS)
	{
	    /* 使能flash预读取缓冲区 */
	    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

	    /* 令Flash处于等待状态，2是针对高频时钟的，这两句跟RCC没直接关系，可以暂且略过 */
	    FLASH_SetLatency(FLASH_Latency_2);

	    /* HCLK = SYSCLK 设置高速总线时钟=系统时钟*/
	    RCC_HCLKConfig(RCC_SYSCLK_Div1);

	    /* PCLK2 = HCLK 设置低速总线2时钟=高速总线时钟*/
	    RCC_PCLK2Config(RCC_HCLK_Div1);

	    /* PCLK1 = HCLK/2 设置低速总线1的时钟=高速时钟的二分频*/
	    RCC_PCLK1Config(RCC_HCLK_Div2);

	    /* ADCCLK = PCLK2/6 设置ADC外设时钟=低速总线2时钟的六分频*/
	    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

	    /* Set PLL clock output to 72MHz using HSE (8MHz) as entry clock */
	    //这句很关键
	    /* 利用锁相环讲外部8Mhz晶振9倍频到72Mhz */
	    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

	    /* Enable PLL 使能锁相环*/
	    RCC_PLLCmd(ENABLE);


	    /* Wait till PLL is ready 等待锁相环输出稳定*/
	    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
	    {}

	    /* Select PLL as system clock source 将锁相环输出设置为系统时钟 */
	    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	    /* Wait till PLL is used as system clock source 等待校验成功*/
	    while (RCC_GetSYSCLKSource() != 0x08)
	    {}
	}





#endif

	/* Enable GPIOx and AFIO clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | 
	                       RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |RCC_APB2Periph_GPIOE, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA , ENABLE);

    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);


 
    //启动DMA时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA, ENABLE);
    //启动ADC1时钟

	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);		
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);	

	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
	

    /* Enable PWR and BKP clocks */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);






    /* Allow access to BKP Domain */
    PWR_BackupAccessCmd(ENABLE);	
	
}




void RCC_Deconfigure(void)
{


	#if 0
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | 
	                       RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |RCC_APB2Periph_GPIOE, DISABLE);
#endif
//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOE, DISABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, DISABLE);
	  /* Enable PWR and BKP clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, DISABLE);
	   PWR_BackupAccessCmd(DISABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO  , DISABLE);
GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,DISABLE);
GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, DISABLE);

#if 1
    //启动DMA时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA, DISABLE);
    //启动ADC1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, DISABLE); 	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , DISABLE);
	    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, DISABLE);
    /* Enable PWR and BKP clocks */
  //  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, DISABLE);

    /* Allow access to BKP Domain */
   // PWR_BackupAccessCmd(ENABLE);	

//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
	                       //RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD , ENABLE);
#endif

#if 0
	/* Enable GPIOx and AFIO clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | 
	                       RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |RCC_APB2Periph_GPIOE, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	  /* Enable PWR and BKP clock */
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	//   PWR_BackupAccessCmd(ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA , ENABLE);
GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

 
    //启动DMA时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA, ENABLE);
    //启动ADC1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
	    GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
    /* Enable PWR and BKP clocks */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

    /* Allow access to BKP Domain */
    PWR_BackupAccessCmd(ENABLE);	
#endif
}

void RCC_Reconfigure(void)
{
	/* Enable GPIOx and AFIO clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | 
	                       RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |RCC_APB2Periph_GPIOE, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	  /* Enable PWR and BKP clock */
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	//   PWR_BackupAccessCmd(ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA , ENABLE);

	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);


 
    //启动DMA时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA, ENABLE);
    //启动ADC1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
	

    /* Enable PWR and BKP clocks */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);




 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);	


    /* Allow access to BKP Domain */
    PWR_BackupAccessCmd(ENABLE);	
	

	dtd_adc_init();


}




/***************************************************************************************
** 函数名称: NVIC_Configuration
** 功能描述: stm32f10x配置基本向量中断
** 参    数: None
** 返 回 值: None       
** 作　  者: 罗辉联
** 日  　期: 2007年11月28日
**--------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
#if 0
static void NVIC_Configuration(void)
{ 
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Set the Vector Table base location at 0x08000000 */ 
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
	
	/* Configure one bit for preemption priority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
#ifdef UART_ENABLE	
	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
#endif
#if 0
	/* Enable the WDG Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
#endif

   NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQChannel;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

   NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQChannel;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
#if 0
   NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQChannel;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
#endif

  /* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);   

#if 0
  NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
  NVIC_Init(&NVIC_InitStructure);
  #endif
//	NVIC_SystemHandlerPriorityConfig(SystemHandler_SysTick, 3, 0);
	NVIC_SystemHandlerPriorityConfig(SystemHandler_SysTick, 1, 0);
}
#endif
static void NVIC_Configuration(void)
{ 
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Set the Vector Table base location at 0x08000000 */ 
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
	
	/* Configure one bit for preemption priority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
#ifdef UART_ENABLE	
	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStructure);


	//DMA发送中断设置  
	NVIC_InitStructure.NVIC_IRQChannel = DMAChannel2_IRQChannel;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	NVIC_Init(&NVIC_InitStructure);  



	
#endif


#ifdef UART3_ENABLE	
	/* Enable the USART3 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
#endif


#if 0
	/* Enable the WDG Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
#endif

   NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQChannel;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

   NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQChannel;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
#if 0
   NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQChannel;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
#endif

   NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQChannel;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);


	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);






#if 1

		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQChannel;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
#endif




//	NVIC_SystemHandlerPriorityConfig(SystemHandler_SysTick, 3, 0);
	NVIC_SystemHandlerPriorityConfig(SystemHandler_SysTick, 1, 3);
	speed_measure_ext_configure_init(0);
	speed_measure_ext_configure_init(1);
}
/***************************************************************************************
** 函数名称: GPIOX_Configuration
** 功能描述: 特殊的GPIO管脚配置
** 参    数: None
** 返 回 值: None       
** 作　  者: 罗辉联
** 日  　期: 2007年11月28日
**--------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
static void GPIOX_Configuration(void)
{
     //    GPIO_InitTypeDef GPIO_InitStruct;
		 GPIO_DeInit(GPIOA);
		 GPIO_DeInit(GPIOB);
		 GPIO_DeInit(GPIOC);
		 GPIO_DeInit(GPIOD);
		 GPIO_DeInit(GPIOE);
		 


		  	 
}

/***************************************************************************************
** 函数名称: Target_Init
** 功能描述: 板级初始化函数
** 参    数: None
** 返 回 值: None       
** 作　  者: 罗辉联
** 日  　期: 2007年11月28日
**--------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void Target_Init (void)
{
	/* System Clocks Configuration */
	//RCC_Configuration();

	RCC_Configuration();
	

	NVIC_DeInit();
	      
	/* NVIC configuration */
	NVIC_Configuration();

	GPIOX_Configuration();
	#if 0
	 Initial_RF();
		while(1){
			Read_EM198810_REG(80);
			

	};
		#endif
}

/***************************************************************************************
** 函数名称: Tmr_TickInit
** 功能描述: OS tick 初始化函数
** 参    数: None
** 返 回 值: None       
** 作　  者: 罗辉联
** 日  　期: 2007年11月28日
**--------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void Tmr_TickInit (void)
{
       SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
    /* SysTick end of count event each 1ms with input clock equal to 9MHz (HCLK/8, default) */
  	SysTick_SetReload(81000);//(40500);
  	/* Enable SysTick interrupt */
  	SysTick_ITConfig(ENABLE);
  	/* Enable the SysTick Counter */
  	SysTick_CounterCmd(SysTick_Counter_Enable);	
}


/***************************************************************************************
** 函数名称: sleep
** 功能描述: 简单的延时函数
** 参    数: None
** 返 回 值: None       
** 作　  者: 罗辉联
** 日  　期: 2007年11月28日
**--------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void sleep(u32 cnt)
{
	u32 i = 0;

	for(i = 0; i < cnt; i++);
}



#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
#if 0
  /* Infinite loop */
  while (1)
  {
  }
  #endif
}
#endif

/****************** http://www.bogodtech.com *******End of file ******************/
