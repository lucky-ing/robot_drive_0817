
#include "config.h"


void left_motor_stop(motor_global_setting_t *gt)
{
#if 1

		TIM_OC_Config(TIM4,ENABLE,TIM_Channel_3,0,TIM_ForcedAction_InActive);
		TIM_OC_Config(TIM4,ENABLE,TIM_Channel_4,0,TIM_ForcedAction_InActive);
#else

		TIM_OC_Config(TIM4,ENABLE,TIM_Channel_3,0,TIM_ForcedAction_Active);
		TIM_OC_Config(TIM4,ENABLE,TIM_Channel_4,0,TIM_ForcedAction_Active);
#endif


		gt->left_motor_state = MOTOR_STATE_STOP ;
}
#if 1 //def ROBOT_TEST
void left_motor_backward(motor_global_setting_t *gt, u16 speed)
{
	U32 last_int = l_int_finish;
	U32 now_int_finish = 0;

	if(speed > 250) {
		speed = 250;
	}

	//printf("left motor speed:%d\r\n", speed);
#if 1 
	if(gt->right_motor_state == MOTOR_STATE_STOP) {

		TIM_OC_Config(TIM4,ENABLE,TIM_Channel_3,(0xff - speed),TIM_ForcedAction_InActive);


		// need wait charge pump  ready;

		TIM_OC_Config(TIM4,ENABLE,TIM_Channel_4,(0xff - speed),TIM_ForcedAction_InActive) ;

	}
	

	
	TIM_OC_Config(TIM4,ENABLE,TIM_Channel_4,(0xff - speed),TIM_OCMode_PWM2) ;
#else



	TIM_OC_Config(TIM4,ENABLE,TIM_Channel_4,speed,TIM_ForcedAction_Active);

	TIM_OC_Config(TIM4,ENABLE,TIM_Channel_3,speed,TIM_OCMode_PWM2) ;


#endif

	gt->left_motor_state = MOTOR_STATE_BACKWARD;
}
#endif
void left_motor_forward(motor_global_setting_t *gt, u16 speed)
{
	U32 last_int = l_int_finish;
	U32 now_int_finish = 0;

	if(speed > 250) {
		speed = 250;
	}
#if 1
	if(gt->left_motor_state == MOTOR_STATE_STOP) {

		TIM_OC_Config(TIM4,ENABLE,TIM_Channel_4,(0xff - speed),TIM_ForcedAction_InActive);


		// need wait charge pump  ready;

		TIM_OC_Config(TIM4,ENABLE,TIM_Channel_3,(0xff - speed),TIM_ForcedAction_InActive) ;


	}

	TIM_OC_Config(TIM4,ENABLE,TIM_Channel_3,(0xff - speed),TIM_OCMode_PWM2);
#else
	TIM_OC_Config(TIM4,ENABLE,TIM_Channel_3,speed,TIM_ForcedAction_Active) ;


	TIM_OC_Config(TIM4,ENABLE,TIM_Channel_4,speed,TIM_OCMode_PWM2);


#endif
	gt->left_motor_state = MOTOR_STATE_FORWARD;
	
}

void left_motor_speed_change(U8 direction, U16 speed) {
	if(speed > 250)
		speed = 250;
	


	if(direction == MOTOR_STATE_FORWARD)
		TIM_SetCompare3(TIM4, (0xff - speed)); //TIM4->CCR3 = (0xff - speed);
	else if(direction == MOTOR_STATE_BACKWARD)
		TIM_SetCompare4(TIM4, (0xff - speed)); //TIM4->CCR4 = (0xff - speed);
	

}


void right_motor_speed_change(U8 direction, U16 speed) {

	if(speed > 250)
		speed = 250;
	


	if(direction == MOTOR_STATE_FORWARD)
		TIM_SetCompare1(TIM4, (0xff - speed)); //TIM4->CCR1 = (0xff - speed);
	else if(direction == MOTOR_STATE_BACKWARD)
		TIM_SetCompare2(TIM4, (0xff - speed)); //TIM4->CCR2 = (0xff - speed);
	

}


void right_motor_stop(motor_global_setting_t *gt)
{
#if 1
	TIM_OC_Config(TIM4,ENABLE,TIM_Channel_1,0,TIM_ForcedAction_InActive);
	TIM_OC_Config(TIM4,ENABLE,TIM_Channel_2,0,TIM_ForcedAction_InActive);
#else

	TIM_OC_Config(TIM4,ENABLE,TIM_Channel_1,0,TIM_ForcedAction_Active);
	TIM_OC_Config(TIM4,ENABLE,TIM_Channel_2,0,TIM_ForcedAction_Active);
#endif

	gt->right_motor_state = MOTOR_STATE_STOP;
}
#if 1 //def ROBOT_TEST
void right_motor_backward(motor_global_setting_t *gt, u16 speed)
{
	U32 last_int = r_int_finish;
	U32 now_int_finish = 0;

	if(speed > 250) {
		speed = 250;
	}

#if 1
	if(gt->right_motor_state == MOTOR_STATE_STOP) {	
		TIM_OC_Config(TIM4,ENABLE,TIM_Channel_1,(0xff - speed),TIM_ForcedAction_InActive);


		// need wait charge pump  ready;

		TIM_OC_Config(TIM4,ENABLE,TIM_Channel_2,(0xff - speed),TIM_ForcedAction_InActive) ;

	}

	TIM_OC_Config(TIM4,ENABLE,TIM_Channel_2,(0xff - speed),TIM_OCMode_PWM2);
#else

	TIM_OC_Config(TIM4,ENABLE,TIM_Channel_2,speed,TIM_ForcedAction_Active) ;

	TIM_OC_Config(TIM4,ENABLE,TIM_Channel_1,speed,TIM_OCMode_PWM2);


#endif
	gt->right_motor_state = MOTOR_STATE_BACKWARD ;
}

void right_motor_forward(motor_global_setting_t *gt, u16 speed)
{
	U32 last_int = r_int_finish;
	U32 now_int_finish = 0;


	//printf("r speed :	%d \r\n", speed);

	if(speed > 250) {
		speed = 250;
	}

#if 1
	if(gt->right_motor_state == MOTOR_STATE_STOP) {
		TIM_OC_Config(TIM4,ENABLE,TIM_Channel_2,(0xff - speed),TIM_ForcedAction_InActive);

		// need wait charge pump  ready;

		TIM_OC_Config(TIM4,ENABLE,TIM_Channel_1,(0xff - speed),TIM_ForcedAction_InActive) ;

	}
	


	TIM_OC_Config(TIM4,ENABLE,TIM_Channel_1,(0xff - speed),TIM_OCMode_PWM2);
#else
	TIM_OC_Config(TIM4,ENABLE,TIM_Channel_1,speed,TIM_ForcedAction_Active) ;


	TIM_OC_Config(TIM4,ENABLE,TIM_Channel_2,speed,TIM_OCMode_PWM2);


#endif
	gt->right_motor_state = MOTOR_STATE_FORWARD ;
}
#endif

void main_motor_stop(motor_global_setting_t *gt)
{
	GPIO_WriteBit(GPIOC,  GPIO_Pin_9, Bit_RESET);
	gt->main_motor_state = MOTOR_STATE_STOP;
}

void main_motor_left(motor_global_setting_t *gt)
{
	U16 bat_vol = 0;
	U16 carpet_pwm_add = 0;
	
	GPIO_WriteBit(GPIOC,  GPIO_Pin_9, Bit_SET);	
	gt->main_motor_state = MOTOR_STATE_FORWARD;
	OSTimeDlyHMSM(0,0,0,10);

}




#ifdef SIDE_SPEED_ADJUST

void side_speed_configure(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	u16 CCR1_Val = CHAR_PWM_HIGH;
	GPIO_InitTypeDef gpioInitStruct;



	//printf("side speed configure \r\n");

	gpioInitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 ;
	gpioInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &gpioInitStruct);


	TIM_DeInit(TIM3);
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 256 ;   
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;       
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

//	TIM_PrescalerConfig(TIM3, 22, TIM_PSCReloadMode_Immediate);
	TIM_PrescalerConfig(TIM3, 12, TIM_PSCReloadMode_Immediate);

	TIM_OC_Config(TIM3,ENABLE,TIM_Channel_2,CCR1_Val,TIM_ForcedAction_Active);
	TIM_OC_Config(TIM3,ENABLE,TIM_Channel_3,CCR1_Val,TIM_ForcedAction_Active);
	//TIM_OC_Config(TIM3,ENABLE,TIM_Channel_4,CCR1_Val,TIM_ForcedAction_Active);

	TIM_ClearFlag(TIM3, TIM_FLAG_Update);/*清除更新标志位*/
	TIM_ARRPreloadConfig(TIM3, DISABLE);/*预装载寄存器的内容被立即传送到影子寄存器 */

	//TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);    
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);
//	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Disable);

	TIM_Cmd(TIM3, ENABLE);


}


#endif

void side_motor_stop(motor_global_setting_t *gt)
{
#ifdef SIDE_SPEED_ADJUST
	//TIM_PrescalerConfig(TIM3, 1, TIM_PSCReloadMode_Immediate);
	TIM_OC_Config(TIM3,ENABLE,TIM_Channel_3,CHAR_PWM_LOW,TIM_ForcedAction_Active);
#else
	side_motor_close();
#endif


	gt->side_motor_state = MOTOR_STATE_STOP;
}




U8 global_side_speed  = 0;
void side_motor_forward(motor_global_setting_t *gt, U8 speed)
{
#ifdef SIDE_SPEED_ADJUST

	global_side_speed = speed;

	TIM_OC_Config(TIM3,ENABLE,TIM_Channel_3, speed, TIM_OCMode_PWM2);
#else
	side_motor_open();
#endif

	
	gt->side_motor_state = MOTOR_STATE_FORWARD;
}


void side_motor_up_speed(void){
#ifdef SIDE_SPEED_ADJUST	

	printf("side speed up!!!!!!!!!!!!!!\r\n");
	buzzer_once_flag = 1;
	
	if(global_side_speed == SIDE_MOTOR_SPEED_1) {
		side_motor_forward(&motor_global_setting, SIDE_MOTOR_SPEED_2);
	} else if (global_side_speed == SIDE_MOTOR_SPEED_2) {
		side_motor_forward(&motor_global_setting, SIDE_MOTOR_SPEED_3);	
	}

#endif
	return ;
	
}

void side_motor_down_speed(void){
#ifdef SIDE_SPEED_ADJUST	
	if(global_side_speed == SIDE_MOTOR_SPEED_3) {
		side_motor_forward(&motor_global_setting, SIDE_MOTOR_SPEED_2);
	} else if (global_side_speed == SIDE_MOTOR_SPEED_2) {
		side_motor_forward(&motor_global_setting, SIDE_MOTOR_SPEED_1);	
	} 
#endif	
	return ;
	
}


U8 side_motor_get_threashold(void){

#ifdef SIDE_SPEED_ADJUST
	if(global_side_speed == SIDE_MOTOR_SPEED_1) {

		return SIDE_MOTOR_OVERFLOW1;
	}else if(global_side_speed == SIDE_MOTOR_SPEED_2){
		return SIDE_MOTOR_OVERFLOW2;

	}else if(global_side_speed == SIDE_MOTOR_SPEED_3){
		return SIDE_MOTOR_OVERFLOW;

	}else {
		return SIDE_MOTOR_OVERFLOW;
	}
#else
	return SIDE_MOTOR_OVERFLOW;
#endif

}


void dust_motor_stop(motor_global_setting_t *gt)
{
#ifndef SIDE_SPEED_ADJUST
	GPIO_WriteBit(GPIOC,  GPIO_Pin_7, Bit_RESET);
#else
	TIM_OC_Config(TIM3,ENABLE,TIM_Channel_2, 192, TIM_ForcedAction_Active);	


#endif

	gt->dust_motor_state = MOTOR_STATE_STOP;
	
}

void dust_motor_forward(motor_global_setting_t *gt)
{
	U16 bat_vol ;
	U16 turbo_add = 0;
	U16 i = 0;
#ifndef SIDE_SPEED_ADJUST
	GPIO_WriteBit(GPIOC,  GPIO_Pin_7, Bit_SET);

#else 
	bat_vol = GET_BAT_VOL;

	if(global_setting.velocity)
		turbo_add  = 10;
	else
		turbo_add = 0;
	printf("dust motor , bat vol : 	%d \r\n", bat_vol);

#if defined(X5A)

	for(i = 30; i< 80; (i = i+5)) {
	
		TIM_OC_Config(TIM3,ENABLE,TIM_Channel_2, i, TIM_OCMode_PWM2);

		OSTimeDlyHMSM(0,0,0,5);

	}

	

#endif

#if defined(X5B)
	TIM_OC_Config(TIM3,ENABLE,TIM_Channel_2, 250, TIM_OCMode_PWM2);
#endif


//TIM_OC_Config(TIM3,ENABLE,TIM_Channel_2, 250, TIM_OCMode_PWM2);

#endif
gt->dust_motor_state = MOTOR_STATE_FORWARD;


}
void total_motor_stop(void)
{
	printf("total motor stop \r\n");
	printf("stop clean motor \r\n");
	main_motor_stop(&motor_global_setting);
	side_motor_stop(&motor_global_setting);
	dust_motor_stop(&motor_global_setting);

}

void Motor_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;




//right motor
//PB6 right_up
//PE3 left_down
/*			start 	stop
	PB6        PWM		low	
	PE3		low		high
	
*/
//PB7  left_up
//PE2   right_down
/*			start		stop
	PB7		PWM		low	
	PE2		low		high

*/

  

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 |GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

//PB8   left_up  
//PE0   right_down
/*			start 	stop
	PB8        PWM		low
	PE0        low		high

*/

//PB9 right_up
//PE1  left_down
/*			start		stop
	PB9		PWM		low
	PE1		low		high

*/

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 |GPIO_Pin_9 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);





/*
	pc13  main motor control signal 

*/



	//side motor ; main motor
#ifdef SIDE_SPEED_ADJUST
	side_speed_configure();

#if 1    // main brush.
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_WriteBit(GPIOC,  GPIO_Pin_9, Bit_RESET);

#endif


#else
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_WriteBit(GPIOC,  GPIO_Pin_7, Bit_RESET);
	GPIO_WriteBit(GPIOC,  GPIO_Pin_8, Bit_RESET);
	GPIO_WriteBit(GPIOC,  GPIO_Pin_9, Bit_RESET);


  
 #endif



}



void Motor_TIM4_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	//TIM_OCInitTypeDef  TIM_OCInitStructure;
	u16 CCR1_Val = 0x7f;




	TIM_DeInit(TIM4);
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 256;          
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;       
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

#ifdef SAIGE_MOTOR
 	TIM_PrescalerConfig(TIM4, 15, TIM_PSCReloadMode_Immediate); // 28 : 5k;  14: 10k 7: 20k
	//TIM_PrescalerConfig(TIM4, 36, TIM_PSCReloadMode_Immediate);
#else
	TIM_PrescalerConfig(TIM4, 22, TIM_PSCReloadMode_Immediate);
#endif


	TIM_OC_Config(TIM4,DISABLE,TIM_Channel_1,CCR1_Val,TIM_ForcedAction_Active);
	TIM_OC_Config(TIM4,DISABLE,TIM_Channel_2,CCR1_Val,TIM_ForcedAction_Active);
	TIM_OC_Config(TIM4,DISABLE,TIM_Channel_3,CCR1_Val,TIM_ForcedAction_Active);
	TIM_OC_Config(TIM4,DISABLE,TIM_Channel_4,CCR1_Val,TIM_ForcedAction_Active);

	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Disable);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Disable);
	//TIM_ARRPreloadConfig(TIM4, ENABLE);
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	TIM_Cmd(TIM4,ENABLE);
	/*   No need interrupt */	
	// TIM_ITConfig(TIM4, /*TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 |*/ TIM_IT_CC4, ENABLE);
	//TIM_ClearITPendingBit(TIM4, TIM_IT_CC4);
}




void clean_motor_open(motor_global_setting_t *gt)
{

#if 1
	printf("clean_motor open\r\n");
	detect_open();

	side_motor_forward(gt, SIDE_MOTOR_SPEED_1);	
	OSTimeDlyHMSM(0,0,0,50);
	main_motor_left(gt);
	OSTimeDlyHMSM(0,0,0,450);
	dust_motor_forward(gt);
	//OSTimeDlyHMSM(0,0,0,50);

	OSTimeDlyHMSM(0,0,0,200);

#endif



}

void clean_motor_close(motor_global_setting_t *gt)
{
	dust_motor_stop(gt);
	OSTimeDlyHMSM(0,0,0,20);
	main_motor_stop(gt);
	OSTimeDlyHMSM(0,0,0,20);
	side_motor_stop(gt);
	OSTimeDlyHMSM(0,0,0,20);
}

void detct_init_rf(motor_global_setting_t *gt)
{


	gt->drop_ignore_left = 0;
	gt->drop_ignore_right = 0;
	gt->drop_ignore_mid = 0;


	drop_detect_enable();

	OSTimeDlyHMSM(0,0,0,QUICK_RECALC_ADC);

	motor_global_setting.running.drop_mid= GET_INFRA_DROP_M; 
	motor_global_setting.running.drop_left =  GET_INFRA_DROP_L;
			motor_global_setting.running.drop_right = GET_INFRA_DROP_R; 

	drop_detect_disable();
	OSTimeDlyHMSM(0,0,0,QUICK_RECALC_ADC);
	motor_global_setting.running.env_drop_r = GET_INFRA_DROP_R;
	motor_global_setting.running.env_drop_m = GET_INFRA_DROP_M;
	motor_global_setting.running.env_drop_l = GET_INFRA_DROP_L;




	if((motor_global_setting.running.drop_mid > (motor_global_setting.running.env_drop_m -0x60))) {
		printf("drop ignore mid \r\n");
		gt->drop_ignore_mid = 1;

		
	}
	if((motor_global_setting.running.drop_left > (motor_global_setting.running.env_drop_l -0x60))) {
		printf("drop ignore left \r\n");
		gt->drop_ignore_left = 1;

		
	}

	if((motor_global_setting.running.drop_right > (motor_global_setting.running.env_drop_r -0x60))) {
		printf("drop ignore right \r\n");
		gt->drop_ignore_right = 1;

	}
					
	


}

