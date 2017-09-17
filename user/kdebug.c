//  主要的debug 代码

#include "config.h"

#ifdef ROBOT_TEST
volatile U32 ir_skip_signal[4] ;
volatile U32 ir_wrong_times[4] ;
volatile U32 ir_success_count[4];
volatile U32 ir_wrong_step[4];
#endif

U8 key_no_stay = 0;

volatile U8 drop_disable = 0;

extern int get_bat_temp(U16 temp_adc);

#define LIGHT_NORMAL 0xdd0
#define LIGHT_D 0x05

extern volatile U8 emu_key_state;
extern volatile U8 emu_key;


extern volatile U8 global_char_pwm;
extern volatile U8 inter_task_ready;


ate_test_result_t ate_test_result;


U8 test_stay(void) {

	return 0;

}

void dust_motor_test(void) {

		U16 dust_motor_overflow = 0;
		U8 i = 0;	

		
		show_hour(8);
		show_min(0);


		
		dust_motor_stop(&motor_global_setting);
		dust_motor_overflow = GET_DUST_MOTOR_CUR;
		if(dust_motor_overflow > DUST_MOTOR_OVERFLOW) {
			printf("吸风:		上电自转:%d",dust_motor_overflow);
			ate_test_result.dust_motor_ok = 0;
			
					show_hour(8);
					show_min(55);
					test_stay();
		} 
		

		OSTimeDlyHMSM(0,0,0,100);
		dust_motor_forward(&motor_global_setting);

		OSTimeDlyHMSM(0,0,0,500);
		for(i = 0 ; i < 3; i++) {
			OSTimeDlyHMSM(0,0,0,30);		
				dust_motor_overflow = GET_DUST_MOTOR_CUR;
			if(dust_motor_overflow > DUST_MOTOR_OVERFLOW) {
				printf("吸风:		电流过流:%d",dust_motor_overflow);
				ate_test_result.dust_motor_ok = 0;
				//test_stay();
					show_hour(8);
					show_min(44);
					test_stay();
				break;
			} else if( dust_motor_overflow < 1) {

				OSTimeDlyHMSM(0,0,0,10);
				dust_motor_overflow = GET_DUST_MOTOR_CUR;
				if( dust_motor_overflow < 1){
					printf("吸风:		电流检测失败，正常值0x30左右，检测到:%d",dust_motor_overflow);

						show_hour(8);
						show_min(55);
						test_stay();
					break;
					}
			}	


		}
		

		
		dust_motor_stop(&motor_global_setting);


}
U8 side_motor_test(void)
{

	U16 left_side = 0;
	U8 right_side = 0;
	
	
					show_hour(6);
					show_min(0);
	side_motor_stop(&motor_global_setting);
	OSTimeDlyHMSM(0,0,0,30);


	left_side = GET_LEFT_SIDE_CURRENT;
	right_side = GET_RIGHT_SIDE_CURRENT;
	
	if(left_side > 10 ){

		printf("左边扫:		上电自转");
		//test_stay();
					show_hour(6);
					show_min(55);
					test_stay();
		goto out; //return 0;
	}
	if(right_side > 10 ){

		printf("右边扫:		上电自转");
		
					show_hour(7);
					show_min(55);
					test_stay();
		goto out;
	}


	
	side_motor_forward(&motor_global_setting, 0xf0);
	OSTimeDlyHMSM(0,0,1,0);

	left_side = GET_LEFT_SIDE_CURRENT;
	right_side = GET_RIGHT_SIDE_CURRENT;
	
	if(left_side > SIDE_MOTOR_OVERFLOW){

		printf("左边扫:		过流:	%d", left_side);
		
		show_hour(6);
		show_min(55);
		test_stay();
		goto out;
	}
	if(right_side > SIDE_MOTOR_OVERFLOW ){

		printf("右边扫:		过流:	%d", 	right_side);
		
		show_hour(7);
		show_min(55);
		test_stay();
		goto out;
	}	


	if(left_side <  1 ){

		printf("左边扫:		不转	%d",left_side);
		//test_stay();
					show_hour(6);
					show_min(55);
					test_stay();
		goto out;
	}
	if(right_side < 1 ){

		printf("右边扫:		不转	%d", right_side);
		//test_stay();
					show_hour(7);
					show_min(55);
					test_stay();
		goto out;
	}

out:
	side_motor_stop(&motor_global_setting);

}





// 测试电机

U8  walk_motor_test(void)
{

			U16 left_motor_overflow, right_motor_overflow;
			U8 i = 0 ;			
			//machine_stop(&motor_global_setting);
			

			left_motor_stop(&motor_global_setting);
			right_motor_stop(&motor_global_setting);
			show_hour(3);
			show_min(0);
			
			OSTimeDlyHMSM(0,0,0,1);
			
			// pWM 256  0xEf
			
			left_motor_forward(&motor_global_setting,0xEf);
			right_motor_backward(&motor_global_setting, 0xEf);
			OSTimeDlyHMSM(0,0,0,100);
			for(i = 0; i < 10; i ++) {
			
				OSTimeDlyHMSM(0,0,0,30);
				
				// 得到轮子的电流 
				
				left_motor_overflow = GET_MOTOR_CUR_L;
				right_motor_overflow = GET_MOTOR_CUR_R;

				if(left_motor_overflow <2 ) {
					printf("左轮:		电流检测失败，电流偏低:%d",left_motor_overflow);
					right_motor_stop(&motor_global_setting);
					left_motor_stop(&motor_global_setting);

					
					show_hour(3);
					show_min(22);
					test_stay();
					return 1;					
				} else if(left_motor_overflow >  DRIVER_MOTOR_THRESHOLD) {
					printf("左轮:		过流!!! :%d", left_motor_overflow);
					right_motor_stop(&motor_global_setting);
					left_motor_stop(&motor_global_setting);
					//test_stay();
					show_hour(3);
					show_min(33);
					test_stay();
					return 1;				
				}
				if(right_motor_overflow < 2) {
					printf("右 轮:		电流检测失败，电流偏低:%d",right_motor_overflow);
					right_motor_stop(&motor_global_setting);
					left_motor_stop(&motor_global_setting);
					//test_stay();
					show_hour(3);
					show_min(44);
					test_stay();
					return 1;
				} else if(right_motor_overflow >  DRIVER_MOTOR_THRESHOLD) {
					printf("右轮:		过流!!! :%d", right_motor_overflow);
					right_motor_stop(&motor_global_setting);
					left_motor_stop(&motor_global_setting);
					//test_stay();
					show_hour(3);
					show_min(55);
					test_stay();
					return 1;
				}

			}


			
			right_motor_stop(&motor_global_setting);
			left_motor_stop(&motor_global_setting);


			OSTimeDlyHMSM(0,0,0,100);
			//printf("freq:%d",step*8);
			//TIM_PrescalerConfig(TIM4, 36, TIM_PSCReloadMode_Immediate);
			//speed_calc_val_init();
			//max_int_tick = 10000*ONE_CM_CYCLE_NUM ;
			
			
			// 测出开始 打开测速中断
			
			speed_measure_ext_configure(1,1);	
			speed_measure_ext_configure(0,1);
			
			OSTimeDlyHMSM(0,0,0,1);
			left_motor_backward(&motor_global_setting,0xEf);
			right_motor_backward(&motor_global_setting, 0xEf);
			OSTimeDlyHMSM(0,0,0,100);

			for(i = 0; i < 10; i ++) {
			
				OSTimeDlyHMSM(0,0,0,30);
				left_motor_overflow = GET_MOTOR_CUR_L;
				right_motor_overflow = GET_MOTOR_CUR_R;

				if(left_motor_overflow < 2) {
					printf("左轮:		电流检测失败; 电流偏低:%d",left_motor_overflow);
					right_motor_stop(&motor_global_setting);
					left_motor_stop(&motor_global_setting);
					//test_stay();
					show_hour(3);
					show_min(22);
					test_stay();
					return 1;					
				} else if(left_motor_overflow >  DRIVER_MOTOR_THRESHOLD) {
					printf("左轮:		过流!!! :%d", left_motor_overflow);
					right_motor_stop(&motor_global_setting);
					left_motor_stop(&motor_global_setting);
					//test_stay();
					show_hour(3);
					show_min(33);
					test_stay();
					return 1;				
				}
				if(right_motor_overflow < 2) {
					printf("右 轮:		电流检测失败，电流偏低:%d",right_motor_overflow);
					right_motor_stop(&motor_global_setting);
					left_motor_stop(&motor_global_setting);
					//test_stay();
					show_hour(3);
					show_min(44);
					test_stay();
					return 1;					
				} else if(right_motor_overflow >  DRIVER_MOTOR_THRESHOLD) {
					printf("右轮:		过流!!! :%d", right_motor_overflow);
					right_motor_stop(&motor_global_setting);
					left_motor_stop(&motor_global_setting);
					//test_stay();
					show_hour(3);
					show_min(55);
					test_stay();
					return 1;
				}

			}
			
			// 走的距离 和 里程计不一致的时候 错误
			if(l_int_finish < 0x180) {
				printf("左轮:		测速不正常%d", l_int_finish);
				//test_stay();
					show_hour(3);
					show_min(11);
					test_stay();
			}

			if(r_int_finish < 0x180) {
				printf("右轮:		测速不正常:%d", r_int_finish);
			//	test_stay();
					show_hour(3);
					show_min(18);
					test_stay();
			}

			speed_measure_ext_configure(1,0);	
			speed_measure_ext_configure(0,0);
			printf("leftspeed:%d",l_int_finish);
			printf("righttspeed:%d",r_int_finish);
			right_motor_stop(&motor_global_setting);
			left_motor_stop(&motor_global_setting);
		printf("walk wheel test end \r\n");
		OSTimeDlyHMSM(0,0,0,50);
		return 0 ;



		
	}

U8 main_motor_test(void)
{
		U16 main_motor_overflow ;			
		U8 i ;

		
							show_hour(5);
							show_min(0);

				
		main_motor_stop(&motor_global_setting);
		OSTimeDlyHMSM(0,0,0,1);
		main_motor_left(&motor_global_setting);
		OSTimeDlyHMSM(0,0,0,500);

		for(i = 0 ; i < 3; i++) {
			OSTimeDlyHMSM(0,0,0,30);
			main_motor_overflow = GET_MAIN_MOTOR_CUR;

			if(main_motor_overflow > MAIN_MOTOR_OVERFLOW_THRESHOLD) {
				printf("主扫:		电机过流:%d", main_motor_overflow);
				//test_stay();
					show_hour(5);
					show_min(44);
					test_stay();
				break;
			} else if (main_motor_overflow < 5){ 
				printf("主扫:		电机电流检测失败，主扫电机不在位?:%d", main_motor_overflow);
				//test_stay();
					show_hour(5);
					show_min(55);
					test_stay();
				break;
			}
		}

		
		main_motor_stop(&motor_global_setting);


}






 U8 mpu_test_result;

U8 mpu_test(void) {

	show_hour(01);
	show_min(0);

	MPU_IIC_Init();//IIC总线的初始化，尼玛纠结了这么长时间
	OSTimeDlyHMSM(0,0,0,30);

	mpu_test_result = mpu_init();
	

	if(mpu_test_result != 0) {
		buzzer_once_flag = 1;

		show_min(55);
		test_stay();
		return 0;

	}
	

	
}


U8 rtc_test(void) {

	SYSTEMTIME time,time1;


	show_hour(02);
	show_min(0);



	DS1302_GetTime( &time);
	OSTimeDlyHMSM(0,0,2,0);
	DS1302_GetTime(&time1);
	if(time1.Second ==time.Second) {
		printf("时钟模块:			时钟芯片读取失败"); 

		buzzer_once_flag = 1;
		
		show_min(55);
		test_stay();
		return 0;

		
	}
	else
		{
			printf("time:%d",time1);
			return 0;
		}







}


void drop_test(void) {

	INT16S drop_left;//=IR_MAX;
	INT16S drop_mid;
	INT16S drop_right;//=IR_MAX;


	INT16S env_drop_l;//=IR_MAX;
	INT16S env_drop_m;
	INT16S env_drop_r;//=IR_MAX;
	U16 f_0, f_1;
				

	show_hour(9);
	show_min(0);


	detect_open();
	printf("------------------------------- \r\n"); 
	printf("close drop tx signal\r\n");
	drop_detect_disable();
	OSTimeDlyHMSM(0,0,0,200);
	env_drop_l = GET_INFRA_DROP_L;//  average(ADC_ConvertedValue,CH_LEFT_DROP_DETECT_CH4);
	env_drop_m = GET_INFRA_DROP_M;//average(ADC_ConvertedValue,CH_RIGH_DROP_DETECT_CH5);
	env_drop_r = GET_INFRA_DROP_R;//average(ADC_ConvertedValue,CH_M_LEFT_DROP_DETECT_CH7);
	f_0 = GET_FRONT_WHEEL_AD;
	


	drop_detect_enable();
	OSTimeDlyHMSM(0,0,0,200);
	drop_left = GET_INFRA_DROP_L;//average(ADC_ConvertedValue,CH_LEFT_DROP_DETECT_CH4);
	drop_mid = GET_INFRA_DROP_M;//average(ADC_ConvertedValue,CH_RIGH_DROP_DETECT_CH5);
	drop_right = GET_INFRA_DROP_R;//average(ADC_ConvertedValue,CH_M_LEFT_DROP_DETECT_CH7);

	f_1 = GET_FRONT_WHEEL_AD;
	




	printf("左侧跌落，关闭: %d, 打开:	%d, 差值:	%d\r\n",env_drop_l, drop_left, KL_DELTA(env_drop_l, drop_left));
	printf("中间跌落，关闭: %d, 打开:	%d, 差值:	%d\r\n",env_drop_m, drop_mid, KL_DELTA(env_drop_m, drop_mid));
	printf("右侧跌落，关闭: %d, 打开:	%d, 差值:	%d\r\n",env_drop_r, drop_right, KL_DELTA(env_drop_r, drop_right));	

	printf("前轮	%d		%d, 差值:	%d\n",f_0,f_1, KL_DELTA(f_0, f_1));


	if((drop_left > env_drop_l) ||( KL_DELTA(env_drop_l, drop_left) < DROP_DELTA)){
		
		show_hour(9);
		show_min(33);
		test_stay();

	}

	if((drop_mid > env_drop_m) ||( KL_DELTA(env_drop_m, drop_mid) < DROP_DELTA)){
		
		show_hour(9);
		
		show_min(44);
		test_stay();

	}
	if((drop_right > env_drop_r) ||( KL_DELTA(env_drop_r, drop_right) < DROP_DELTA)){
		
		show_hour(9);
		show_min(55);
		test_stay();

	}

	if((f_1 > f_0) ||( KL_DELTA(f_0, f_1) < 0x30)){
		
		show_hour(9);
		show_min(22);
		test_stay();

	}



}


void hor_test(void)
	{

	
#define LIGHT_DELTA 0x40
				U16 l_0,ml_0,mr_0,m_0,r_0;
				U16 l_1, ml_1, mr_1,m_1,r_1;

				show_hour(10);
				show_min(0);	
				printf("-------------------------------");
				printf("水平红外有遮挡测试，请保持水平条前有遮挡");
				
				//printf("关闭水平红外测距发光管检测");
				hor_detect_disable();
				OSTimeDlyHMSM(0,0,0,50);
				l_0 =  GET_INFRA_L;// average(ADC_ConvertedValue,CH_F_RF_DETECT_R_CH8);
				mr_0 = GET_INFRA_MR;//average(ADC_ConvertedValue,CH_F_RF_DETECT_MR_CH9);
				r_0 =  GET_INFRA_R;//average(ADC_ConvertedValue,CH_F_RF_DETECT_L_CH10);	
				ml_0 = GET_INFRA_ML;//average(ADC_ConvertedValue,CH_F_RF_DETECT_ML_CH15);
				m_0 = GET_INFRA_M;//average(ADC_ConvertedValue,CH_F_RF_DETECT_M_CH16);

	
				hor_detect_enable();
				OSTimeDlyHMSM(0,0,0,50);
				l_1 = GET_INFRA_L;//average(ADC_ConvertedValue,CH_F_RF_DETECT_R_CH8);
				mr_1 = GET_INFRA_MR;//average(ADC_ConvertedValue,CH_F_RF_DETECT_MR_CH9);
				r_1 = GET_INFRA_R;//average(ADC_ConvertedValue,CH_F_RF_DETECT_L_CH10);	
				ml_1 = GET_INFRA_ML;//average(ADC_ConvertedValue,CH_F_RF_DETECT_ML_CH15);
				m_1 =GET_INFRA_M;/// average(ADC_ConvertedValue,CH_F_RF_DETECT_M_CH16);
	

#if 1
				
					printf("水平左	%d		%d, 差值:	%d",l_0, l_1, KL_DELTA(l_0,l_1));
				
					printf("水平中	%d		%d, 差值:	%d",m_0,m_1, KL_DELTA(m_0, m_1));
				
					printf("水平中左 %d 	%d, 差值:	%d",ml_0,ml_1, KL_DELTA(ml_0, ml_1));
				
					printf("水平中右 %d 	%d, 差值:	%d",mr_0,mr_1, KL_DELTA(mr_0, mr_1));
				
					printf("水平右	%d		%d, 差值:	%d\n",r_0,r_1, KL_DELTA(r_0, r_1));
					
				printf("-------------------------------");	
#endif

				if((l_1 > l_0) ||( KL_DELTA(l_0, l_1) < LIGHT_DELTA)){
					
					show_hour(10);
					show_min(11);
					test_stay();
				
				}

				if((ml_1 > ml_0) ||( KL_DELTA(ml_0, ml_1) < LIGHT_DELTA)){
					
					show_hour(10);
					show_min(22);
					test_stay();
				
				}

				if((m_1 > m_0) ||( KL_DELTA(m_0, m_1) < LIGHT_DELTA)){
					
					show_hour(10);
					show_min(33);
					test_stay();
				
				}				
				if((mr_1 > mr_0) ||( KL_DELTA(mr_0, mr_1) < LIGHT_DELTA)){
					
					show_hour(10);
					show_min(44);
					test_stay();
				
				}

				if((r_1 > r_0) ||( KL_DELTA(r_0, r_1) < LIGHT_DELTA)){
					
					show_hour(10);
					show_min(55);
					test_stay();
				
				}




				printf("------------------------------------------");
				printf("测试结束");
	
				
			}

void hor_test_leak(void)
	{

	
#define LIGHT_DELTA_LEAK 0x30
				U16 l_0,ml_0,mr_0,m_0,r_0;
				U16 l_1, ml_1, mr_1,m_1,r_1;

				show_hour(19);
				show_min(0);	
				printf("-------------------------------");
				printf("水平红外有遮挡测试，请保持水平条前有遮挡");
				
				//printf("关闭水平红外测距发光管检测");
				hor_detect_disable();
				OSTimeDlyHMSM(0,0,0,50);
				l_0 =  GET_INFRA_L;// average(ADC_ConvertedValue,CH_F_RF_DETECT_R_CH8);
				mr_0 = GET_INFRA_MR;//average(ADC_ConvertedValue,CH_F_RF_DETECT_MR_CH9);
				r_0 =  GET_INFRA_R;//average(ADC_ConvertedValue,CH_F_RF_DETECT_L_CH10);	
				ml_0 = GET_INFRA_ML;//average(ADC_ConvertedValue,CH_F_RF_DETECT_ML_CH15);
				m_0 = GET_INFRA_M;//average(ADC_ConvertedValue,CH_F_RF_DETECT_M_CH16);

	
				hor_detect_enable();
				OSTimeDlyHMSM(0,0,0,50);
				l_1 = GET_INFRA_L;//average(ADC_ConvertedValue,CH_F_RF_DETECT_R_CH8);
				mr_1 = GET_INFRA_MR;//average(ADC_ConvertedValue,CH_F_RF_DETECT_MR_CH9);
				r_1 = GET_INFRA_R;//average(ADC_ConvertedValue,CH_F_RF_DETECT_L_CH10);	
				ml_1 = GET_INFRA_ML;//average(ADC_ConvertedValue,CH_F_RF_DETECT_ML_CH15);
				m_1 =GET_INFRA_M;/// average(ADC_ConvertedValue,CH_F_RF_DETECT_M_CH16);
	

#if 1
				
					printf("水平左	%d		%d, 差值:	%d",l_0, l_1, KL_DELTA(l_0,l_1));
				
					printf("水平中	%d		%d, 差值:	%d",m_0,m_1, KL_DELTA(m_0, m_1));
				
					printf("水平中左 %d 	%d, 差值:	%d",ml_0,ml_1, KL_DELTA(ml_0, ml_1));
				
					printf("水平中右 %d 	%d, 差值:	%d",mr_0,mr_1, KL_DELTA(mr_0, mr_1));
				
					printf("水平右	%d		%d, 差值:	%d\n",r_0,r_1, KL_DELTA(r_0, r_1));
					
				printf("-------------------------------");	
#endif

				if(( KL_DELTA(l_0, l_1) > LIGHT_DELTA_LEAK)){
					
					show_hour(19);
					show_min(11);
					test_stay();
					return ;
				
				}

				if(( KL_DELTA(ml_0, ml_1) > LIGHT_DELTA_LEAK)){
					
					show_hour(19);
					show_min(22);
					test_stay();

					return ;
				}

				if(( KL_DELTA(m_0, m_1) > LIGHT_DELTA_LEAK)){
					
					show_hour(19);
					show_min(33);
					test_stay();
					return ;
				
				}				
				if(( KL_DELTA(mr_0, mr_1) > LIGHT_DELTA_LEAK)){
					
					show_hour(19);
					show_min(44);
					test_stay();
					return;
				
				}

				if(( KL_DELTA(r_0, r_1) > LIGHT_DELTA_LEAK)){
					
					show_hour(19);
					show_min(55);
					test_stay();
					return ;
				
				}




				printf("------------------------------------------");
				printf("测试结束");
	
				
			}


void charge_test(void){

	U8 connect ;
	U16 vol;
	


	connect = dc_socket_detect();
	
	if(connect != NO_CHARGE_DETECTED){

		printf("charge connect: %d \r\n", connect);
		buzzer_once_flag = 1;
		
	}


}

void voltage_test(void) {
	U16 vol;
	


	vol = GET_BAT_VOL;


	if(vol > 0xf00 || vol < 0x500){
			
		show_hour(11);
		show_min(55);
		test_stay();	


	}



}




void tank_test(void) {
	U8 present = tank_present_detect();

	if(present == 0) {
		printf("tank persent \r\n");
		buzzer_once_flag = 1;
		
	}
}



volatile U8 rf_crc_err = 0;
extern volatile U8 auto_test_once;

// 

#ifdef ROBOT_TEST
void robot_test_function(void)
{
	U8 key;
//	int i ;

	SYSTEMTIME time,time1;


	OS_MemClr((INT8U *)&ate_test_result, sizeof(ate_test_result_t));



	OSTimeDlyHMSM(0,0,1,0);
	
	detect_open();

// 

while(1)
	{
	//motor_task_wdg_counter++;
	OSTimeDlyHMSM(0,0,0,100);
/*
	if(emu_key_state){

				key = emu_key ;
				USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
				emu_key_state = 0;		
				
	}else
		continue;



	switch(key){


		case 'a':

	

			mpu_test();
			break;
		case 'b':

			rtc_test();
			break;
		case 'c':


			walk_motor_test();
			break;
		case 'd':
			
			// 滚刷
			main_motor_test();
			break;
		case 'e':

		// 边扫
			side_motor_test();
			break;
		case 'f':
		// 吸尘
			dust_motor_test();	
			
			break;
		case 'g':

			drop_test();
			break;
		case 'h':
			hor_test();
			break;
		case 'i':
	 
			voltage_test();
			break;
		case 'D':
			
	
			break;

		
		}*/
	}

	}


#endif



#ifdef ROBOT_TEST
void debug_task_core(void *pdata)
{

	while(inter_task_ready==0){
		OSTimeDlyHMSM(0,0,0,10);
	}

	robot_test_function();

}
#endif

