#include "config.h"

#define DLY_CNT			10				

//  定义管脚


volatile U8 global_char_pwm = 0;

/* Private  variables ----------------------------------------------------------------*/

//  AD 的定义


vu16 ADC_ConvertedValue[MAX_SAMPLE_CHS*SAMPLE_PER_CH];




u16 average(vu16 ADCDataTab[], u16 nChannel) 
{ 
	u16 averagevalue=0,i;
	u32 total= 0;
	U16 value = 0;
	U16 max = 0; 
	U16 min = 0xfff;

	
	
	for (i=0; i<SAMPLE_PER_CH; i++) {
		value = *(ADCDataTab+(nChannel-1)+i*MAX_SAMPLE_CHS);

		if(max < value) 
			max = value;
		if(min > value)
			min = value;
		
		total += value; 
	}
	averagevalue = ((total - max) -min)/(SAMPLE_PER_CH-2);
	return averagevalue;
}

void DETECT_GPIO_Config(void)
{
  	GPIO_InitTypeDef  GPIO_InitStructure; 

  	  /* Configure PC.01 (ADC Channel11) as analog input -------------------------*/
	  // used 12 channels.
	
	  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
	  
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3 |GPIO_Pin_4|GPIO_Pin_5;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);


	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);


	  /*    防跌落检测发送信号*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOE, &GPIO_InitStructure);


		/*  红外接受管使能控制信号   */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		// 水平红外发射使能
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);



		/*蜂鸣器使能信号 ，高电平有效 */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOD, &GPIO_InitStructure); 	  	  

		GPIO_WriteBit(GPIOD, GPIO_Pin_11, Bit_RESET);//(GPIO_TypeDef * GPIOx,u16 GPIO_Pin,BitAction BitVal)

		
		// Q13.C  轮子的
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOD, &GPIO_InitStructure); 	







		/*外接电源接入检测*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_13;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOD, &GPIO_InitStructure);  




		/*left wheel speed measurment  左右轮  */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(GPIOE, &GPIO_InitStructure);

		/* right wheel speed measurement */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(GPIOE, &GPIO_InitStructure);




	



		/* 左右轮抬起检测 */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOE, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOD, &GPIO_InitStructure);


		/* 碰撞  碰撞变低*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		/* 激光发射使能*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

#if 0
		// cmos 小板 电源
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
#endif






		/* 垃圾盒在位检测 */

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);


		/* 水箱在位检测 */

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOE, &GPIO_InitStructure);






}





extern volatile U8 dust_detected;
/*
*  channel 1: left,  0: right;
* open 1: open,  0: close;
*/
void speed_measure_ext_configure_init(U8 channel)
{
//	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

 	if(channel){//channel=1 left
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource9);

		/* Configure EXTI Line0 to generate an interrupt on falling edge */ 
		EXTI_InitStructure.EXTI_Line = EXTI_Line9;       //设定外部中断8
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;     //设定中断模式
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;    //设定下降沿触发模式

		EXTI_InitStructure.EXTI_LineCmd = DISABLE;
		EXTI_Init(&EXTI_InitStructure);
		EXTI_ClearFlag(EXTI_Line9);
 	}else{

		GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource14);   
		/* Configure EXTI Line0 to generate an interrupt on falling edge */ 
		EXTI_InitStructure.EXTI_Line = EXTI_Line14;       //设定外部中断8
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;     //设定中断模式
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;    //设定下降沿触发模式

		EXTI_InitStructure.EXTI_LineCmd = DISABLE;
		EXTI_Init(&EXTI_InitStructure); 	  
		EXTI_ClearFlag(EXTI_Line14);

	}

}



/*
*  channel 1: left,  0: right;
* open 1: open,  0: close;
*  配置轮子的外部中断
// 打开 关闭 测速中断
*/
void speed_measure_ext_configure(U8 channel,U8 open)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	OS_ENTER_CRITICAL(); 	/* Tell uC/OS-II that we are starting an ISR */

	
 	if(channel == 1){//channel=1 left

		/* Configure EXTI Line0 to generate an interrupt on falling edge */ 
		EXTI_InitStructure.EXTI_Line = EXTI_Line9;       //设定外部中断8
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;     //设定中断模式
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;    //设定下降沿触发模式

		EXTI_InitStructure.EXTI_LineCmd = open?ENABLE:DISABLE;
		EXTI_Init(&EXTI_InitStructure);
		EXTI_ClearITPendingBit(EXTI_Line9);
		
 	}else{

		/* Configure EXTI Line0 to generate an interrupt on falling edge */ 
		EXTI_InitStructure.EXTI_Line = EXTI_Line14;       //设定外部中断8
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;     //设定中断模式
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;    //设定下降沿触发模式

		EXTI_InitStructure.EXTI_LineCmd = open?ENABLE:DISABLE;
		EXTI_Init(&EXTI_InitStructure); 	  
		EXTI_ClearITPendingBit(EXTI_Line14);

	}
   OS_EXIT_CRITICAL();
}

#if 0
void mpu6050_int_configure(U8 Enable) {
  	GPIO_InitTypeDef  GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode =	 GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure); 


	OS_ENTER_CRITICAL();
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);   
	/* Configure EXTI Line0 to generate an interrupt on falling edge */ 
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;		 //设定外部中断8
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 	//设定中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	  //设定下降沿触发模式
	EXTI_InitStructure.EXTI_LineCmd = Enable?ENABLE:DISABLE;
	EXTI_Init(&EXTI_InitStructure); 
	EXTI_ClearITPendingBit(EXTI_Line2);

	OS_EXIT_CRITICAL();

}
#endif

// 遥控器接受的配置

void ir_recv_ext_config(U8 channel, U8 Enable)
{

	
		TIM1_TimeBaseInitTypeDef  TIM1_TimeBaseStructure;

		TIM_TimeBaseInitTypeDef  TIM2_TimeBaseStructure;


		GPIO_InitTypeDef GPIO_InitStructure;
	
		TIM1_ICInitTypeDef TIM1_ICInitStructure;
		TIM_ICInitTypeDef TIM2_ICInitStructure;
	


		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
		
		GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
		

		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11 | GPIO_Pin_13;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOE, &GPIO_InitStructure);



		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11 | GPIO_Pin_10 | GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);


		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);


	
		/* TIM1 Peripheral Configuration */ 
		TIM1_DeInit();
	
		/* Time Base configuration */
		TIM1_TimeBaseStructure.TIM1_Prescaler = 755;
		TIM1_TimeBaseStructure.TIM1_CounterMode = TIM1_CounterMode_Up;
		TIM1_TimeBaseStructure.TIM1_Period = 0xffff;// 0x3a0; //0x3b0;
	
		TIM1_TimeBaseStructure.TIM1_ClockDivision = 0x0;
		TIM1_TimeBaseStructure.TIM1_RepetitionCounter = 0x0;
	
		TIM1_TimeBaseInit(&TIM1_TimeBaseStructure);
	
	
	
		//TIM1_PrescalerConfig( 36, TIM1_PSCReloadMode_Immediate); // 28 : 5k;	14: 10k 7: 20k
	
		TIM1_ARRPreloadConfig(ENABLE);
	
	
	
		
		
		//TIM1_ICInitStructure.TIM1_ICMode = TIM1_ICMode_ICAP ;
	
		TIM1_ICInitStructure.TIM1_ICPolarity= TIM_ICPolarity_Falling;//上升沿
		TIM1_ICInitStructure.TIM1_ICSelection= TIM_ICSelection_DirectTI;//通道方向选择
		TIM1_ICInitStructure.TIM1_ICPrescaler = TIM_ICPSC_DIV1; //2;/*每次检测到捕获输入就触发一次捕获 */
		TIM1_ICInitStructure.TIM1_ICFilter= 0;/* 对分频率没有影响 选择输入比较滤波器*/
	
	
		TIM1_ICInitStructure.TIM1_Channel= TIM_Channel_2;//选择通道2
		TIM1_ICInit(&TIM1_ICInitStructure);
		
		TIM1_ICInitStructure.TIM1_Channel= TIM_Channel_3;//选择通道2
		TIM1_ICInit(&TIM1_ICInitStructure);
		
	
	
	
		TIM1_ITConfig(TIM_IT_CC2, ENABLE);	//打开中断
		TIM1_ITConfig(TIM_IT_CC3, ENABLE);	//打开中断
		
		TIM1_ClearITPendingBit( TIM1_IT_CC2);
		TIM1_ClearITPendingBit(TIM1_IT_CC3);
	
	
		TIM1_ClearFlag(TIM1_FLAG_Update);
	
		/* TIM1 counter enable */
		TIM1_Cmd(ENABLE);
	
	
	
	
	
	
	



		/* TIM2 Peripheral Configuration */ 
		TIM_DeInit(TIM2);

		/* Time Base configuration */
		TIM2_TimeBaseStructure.TIM_Prescaler = 755;
		TIM2_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM2_TimeBaseStructure.TIM_Period = 0xffff;// 0x3a0; //0x3b0;

		TIM2_TimeBaseStructure.TIM_ClockDivision = 0x0;
		
		TIM_TimeBaseInit(TIM2, &TIM2_TimeBaseStructure);



		TIM_ARRPreloadConfig(TIM2, ENABLE);

		TIM2_ICInitStructure.TIM_ICMode = TIM_ICMode_ICAP;
		
		TIM2_ICInitStructure.TIM_ICPolarity= TIM_ICPolarity_Falling;//上升沿
		TIM2_ICInitStructure.TIM_ICSelection= TIM_ICSelection_DirectTI;//通道方向选择
		TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; //2;/*每次检测到捕获输入就触发一次捕获 */
		TIM2_ICInitStructure.TIM_ICFilter= 0;/* 对分频率没有影响 选择输入比较滤波器*/


		TIM2_ICInitStructure.TIM_Channel= TIM_Channel_1;//选择通道2
		TIM_ICInit(TIM2, &TIM2_ICInitStructure);

		TIM2_ICInitStructure.TIM_Channel= TIM_Channel_2;//选择通道2
		TIM_ICInit(TIM2, &TIM2_ICInitStructure);

		TIM2_ICInitStructure.TIM_Channel= TIM_Channel_3;//选择通道2
		TIM_ICInit(TIM2, &TIM2_ICInitStructure);

		TIM2_ICInitStructure.TIM_Channel= TIM_Channel_4;//选择通道2
		TIM_ICInit(TIM2, &TIM2_ICInitStructure);



	
		//TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);	//打开中断

		TIM_ITConfig(TIM2, TIM_IT_CC1, DISABLE); //打开中断
		TIM_ITConfig(TIM2, TIM_IT_CC2, DISABLE); //打开中断
		TIM_ITConfig(TIM2, TIM_IT_CC3, DISABLE); //打开中断
		TIM_ITConfig(TIM2, TIM_IT_CC4, DISABLE); //打开中断
		

		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC4);


		TIM_ClearFlag(TIM2, TIM_FLAG_Update);

		/* TIM2 counter enable */
		TIM_Cmd(TIM2, ENABLE);

	TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE); //打开中断
	TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE); //打开中断
	TIM_ITConfig(TIM2, TIM_IT_CC3, ENABLE); //打开中断
	TIM_ITConfig(TIM2, TIM_IT_CC4, ENABLE); //打开中断
	
	
}




// AD 的初始化  
void dtd_adc_init(void)
{
  ADC_InitTypeDef ADC_InitStructure;
  DMA_InitTypeDef DMA_InitStructure;

  DMA_DeInit(DMA_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;//外设地址
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC_ConvertedValue;//内存地址
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//dma传输方向单向
  DMA_InitStructure.DMA_BufferSize = MAX_SAMPLE_CHS*SAMPLE_PER_CH;//设置DMA在传输时缓冲区的长度 word
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//设置DMA的外设递增模式，一个外设
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//设置DMA的内存递增模式，
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//外设数据字长
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//内存数据字长
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//设置DMA的传输模式：连续不断的循环模式
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;//设置DMA的优先级别
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//设置DMA的2个memory中的变量互相访问
  DMA_Init(DMA_Channel1, &DMA_InitStructure);
  
  /* Enable DMA channel1 */
  DMA_Cmd(DMA_Channel1, ENABLE);

  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//独立工作模式
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;//扫描方式
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//连续转换
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//外部触发禁止
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//数据右对齐
  ADC_InitStructure.ADC_NbrOfChannel = MAX_SAMPLE_CHS;//用于转换的通道数

  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channels configuration [规则模式通道配置]*/

 
  

#if 1
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0 , CH_BAT_VOL_DETECT_CH1, ADC_SampleTime_71Cycles5);

  ADC_RegularChannelConfig(ADC1, ADC_Channel_1 , CH_RIGHT_DROP_DETECT_CH2, ADC_SampleTime_71Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_2 , CH_LEFT_DROP_DETECT_CH3, ADC_SampleTime_71Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_3 , CH_MID_DROP_DETECT_CH4, ADC_SampleTime_71Cycles5);
  
  ADC_RegularChannelConfig(ADC1, ADC_Channel_4 , CH_HOR_LEFT_DETECT_CH5, ADC_SampleTime_71Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_5 , CH_RIGHT_SIDE_MOTOR_CURRENT_CH6, ADC_SampleTime_71Cycles5);

  
  ADC_RegularChannelConfig(ADC1, ADC_Channel_6 , CH_HOR_M_DETECT_CH7,  ADC_SampleTime_71Cycles5);  
  ADC_RegularChannelConfig(ADC1, ADC_Channel_7 , CH_HOR_ML_DETECT_CH8, ADC_SampleTime_71Cycles5);


  ADC_RegularChannelConfig(ADC1, ADC_Channel_8, CH_LEFT_SIDE_MOTOR_CURRENT_CH9, ADC_SampleTime_71Cycles5); 

  ADC_RegularChannelConfig(ADC1, ADC_Channel_9, CH_HOR_MR_DETECT_CH10, ADC_SampleTime_71Cycles5); 


	
  ADC_RegularChannelConfig(ADC1, ADC_Channel_10, CH_MAIN_MOTOR_CH11, ADC_SampleTime_71Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_11, CH_DUST_AB_CH12, ADC_SampleTime_71Cycles5); 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_12, CH_L_MOTOR_CH13, ADC_SampleTime_71Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_13, CH_R_MOTOR_CH14, ADC_SampleTime_71Cycles5);

  
  ADC_RegularChannelConfig(ADC1, ADC_Channel_14, CH_HOR_RIGHT_DETECT_15, ADC_SampleTime_71Cycles5); 	
  ADC_RegularChannelConfig(ADC1, ADC_Channel_15, CH_FRONT_WHEEL_DETECT_16, ADC_SampleTime_71Cycles5); 
#endif
 /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibaration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibaration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
     
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);

}

void dtd_adc_open(void)
{
}

void dtd_adc_close(void)
{
#if 1
  /* Enable DMA channel1 */
  DMA_Cmd(DMA_Channel1, DISABLE);

  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, DISABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, DISABLE);
    /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, DISABLE);
#endif
}

U8 dc_socket_detect(void)
{
#ifndef OLD_PCB_WRONG_CHARGE
	if(charge_station_input_detect()&&exteral_voltage_input_detect()){
		return DC_SOCKET_DETECTED; //CHARGE_STATION_DETECTED;

	}else if(exteral_voltage_input_detect()){
		//printf("external dc socket detect \n");
		return CHARGE_STATION_DETECTED;

	}else
		return NO_CHARGE_DETECTED;
#else

	if(exteral_voltage_input_detect()){
		//printf("external dc socket detect \n");
		return DC_SOCKET_DETECTED;

	}else
		return NO_CHARGE_DETECTED;

#endif
}


U8 water_box_detect(void)
{
	return water_box_pin_detect();
	
}


volatile U32 last_virtual_wall_ostime = 0;


extern U32 debug_info[128];

void poll_ir_receiver(U8 *mid_l,U8 *mid_r,U8 *right,U8 *left, U8 *right_back, U8 *left_back)
{
	U16 tmp=0;
	U16 i = 0;
	U8 key[6] = {0,0,0,0,0,0};
	U32 data;
	U8 data0, data1;
	
	*left = *right = *mid_r = *mid_l = *left_back = *right_back  = 0;

	
	

#if 0


		for(i=0;i<6;i++){

			if(flagh[i] ==1) {
				
				flagh[i] = 0;
				#ifdef  ROBOT_TEST
				printf("index:	%d, ostime:	%d shuju:%d\r\n",i, OSTimeGet(), shuju[i]);
				#endif
					
				data = shuju[i];
				if((data&0xffffff00) == 0x00000000){	
					key[i] = (U8)data&0xff;
				}

			}
		

		}

		*mid_r = key[0];
		*mid_l = key[1];
		*left = key[2];
		*right = key[3];
		*left_back = key[5];
		*right_back = key[4];
		
		
		//printf("poll_ir:	%d	%d	%d	%d	%d	%d",*left , *right , *mid_r , *mid_l , *left_back , *right_back  );





#endif


	
}



U8 poll_if_near_chg(void)
{
	U16 tmp=0;
	U16 i = 0;
	U8 key[6] = {0,0,0,0,0,0};
	U32 data;
	U8 data0, data1;
	


#if 0


		for(i=0;i<6;i++){

			if(flag_near[i] ==1) {
				
				flag_near[i] = 0;
				#ifdef  ROBOT_TEST
				printf("index:	%d, ostime:	%d shuju:%d\r\n",i, OSTimeGet(), shuju[i]);
				#endif
					
				data = shuju_near[i];
				if(data == CHAR_STA_TOP){	
					key[i] = (U8)data;
				}

			}



		}


		if(key[0] || key[1]){

			return MID_R_NEAR_CHG;
		}
		else if(key[1]){
			return MID_L_NEAR_CHG;

		}
		else if(key[2]){
			return LEFT_NEAR_CHG;
		}else if(key[3]){
			return RIGHT_NEAR_CHG;
		}else if(key[4]){
			return 0;
		}else if(key[5]){
			return 0;
		}


		return 0;


#endif


	
}



volatile U32 last_key_ostime = 0;
volatile U8 last_recv_key = KEY_NULL;

U16 key_ok[6] = {0,0,0,0,0,0};


U8  poll_ir_key(void)
{
	U16 tmp=0;
	U16 i = 0;
	U8 key[6] = {0,0,0,0,0,0};
	U32 data;
	U8 data0, data1;
	U32 key_ostime  = 0;
	U32 delta_time = 0;
	U8 key_this = 0;
	for(i=0;i<6;i++){

		if(flagr[i] ==1) {
			
			flagr[i] = 0;
			#ifdef  ROBOT_TEST
			//printf("index:	%d, ostime:	%d shuju:%d\r\n",i, OSTimeGet(), shujur[i]);
			#endif
				
			data = shujur[i];

			if((data&0xffff0000) == 0x01980000 ){
			

				data0 = (U8)data&0xff;
				data1 = (U8)((data&0xff00)>>8);

				if((data1+data0)== 0xff) 
				{
					key[i] = data0;
					
				}
			}
		}
	

	}


	for(i =0 ; i< 6; i++) {

		if(key[i] == KEY_OK)  {

				key_ok[i] = 1;
				
				key_this = KEY_OK;
		}
		else if(key[i] == KEY_AUTO)  {

				key_ok[i] = 1;
				key_this = KEY_AUTO;
				

		}


	}

	if(key_this == 0)
		return KEY_NULL;
	

	for(i = 0 ; i< ((key_this == KEY_OK)?6:4);i++) {

		if(key_ok[i] == 0)
			return  KEY_NULL;
		

	}


	buzzer_once_flag = 1;
	
	key_ok[0] = 0;
	key_ok[1] = 0;
	key_ok[2] = 0;
	key_ok[3] = 0;
	key_ok[4] = 0;
	key_ok[5] = 0;
	

	return KEY_NULL;
	
	
}






U8 if_detect_open = 0;
void detect_close(void)
{

	OSTimeDlyHMSM(0,0,0,5);
	
	speed_measure_ext_configure(0, 0);
	speed_measure_ext_configure(1, 0);

//OSTimeDlyHMSM(0,0,0,20);
	drop_detect_disable();
	//OSTimeDlyHMSM(0,0,0,20);
	pickup_detect_disable();

	//OSTimeDlyHMSM(0,0,0,20);

	//rf_receive_disable();
	
#ifdef FRONT_WHEEL_DETECT
	front_wheel_detect_configure(0);
#endif 
       if_detect_open = 0;
//rf_receive_enable();




}

void detect_open(){

	OSTimeDlyHMSM(0,0,0,2);
	#if 1
	ir_recv_ext_config(0,1);

	#endif

	pickup_detect_enable();




	OSTimeDlyHMSM(0,0,0,15);

	//front_pickup_enable = 0;
	
	if_detect_open =1 ;

	rf_receive_enable();


}


void detect_init(void)
{
	//U16 battery_voltage = 0;
	
	DETECT_GPIO_Config();
	//OSTimeDlyHMSM(0,0,0,2);
	dtd_adc_init();
	//OSTimeDlyHMSM(0,0,0,2);
	//hor_detect_enable();
	//OSTimeDlyHMSM(0,0,0,2);
	pickup_detect_enable();
	//OSTimeDlyHMSM(0,0,0,2);
	//drop_detect_enable();
	//OSTimeDlyHMSM(0,0,0,2);

	OSTimeDlyHMSM(0,0,0,10);

		//battery_voltage =  average(ADC_ConvertedValue,CH_BAT_VOL_DETECT_CH1);
		//printf("detect init, battery voltage: %d", battery_voltage);
		//if(battery_voltage > MANUAL_CHAR_THRESHOLD) {
		//	startup_buzzer_ring();
		//}

	rf_receive_enable();
	ir_recv_ext_config(0,1);
	
		laser_power_disable();

		cmos_power_disable();

		//printf("\n laser cmos power enable \r\n");
		

	return ;

}

void startup_buzzer_ring(void)
{

#ifdef VOICE_SUPPORT
	voice_send_msg(V_BUZZER);
	return ;
#else
	printf("ding!");
	buzzer_enable();
	OSTimeDlyHMSM(0,0,0,200);
	buzzer_disable();
	 return;
#endif

}



int wdg_init(void)
{

  /* IWDG timeout equal to 350ms (the timeout may varies due to LSI frequency
     dispersion) -------------------------------------------------------------*/
  /* Enable write access to IWDG_PR and IWDG_RLR registers */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

  /* IWDG counter clock: 32KHz(LSI) / 32 = 1KHz */
  IWDG_SetPrescaler(IWDG_Prescaler_32);

  /* Set counter reload value to 349 */
  IWDG_SetReload(349);

  /* Reload IWDG counter */
  IWDG_ReloadCounter();

  /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
  IWDG_Enable();
	return 0;

}







