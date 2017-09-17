
#include "config.h"



#define ADC_AWD_HIGH 0x300

extern volatile U8 ul_left_side_rx_flag ;
extern volatile U32 ul_left_side_rx_time2 ;

extern volatile U8 ul_right_side_rx_flag ;
extern volatile U32 ul_right_side_rx_time2 ;


extern volatile U32 adc_awd_ostime;


extern volatile U32 ul_adc_awd_flag;
extern volatile U32 ul_adc_awd_tick ;
extern volatile U32 ul_adc_awd_ostime ;
extern volatile U16 ul_adc_value;


extern volatile U8 tim1_eight_pluse;

extern volatile U8 ul_ch4_flag ;
extern volatile U32 ul_ch4_time;

extern volatile U8 ul_ch3_flag;
extern volatile U32 ul_ch3_time;


ultrasonic_record_t ultrasonic_record;
U8 ultrasonic_global_event = OB_POSITION_NONE;
U8 ultrasonic_global_event_process = 0;
U16 ultrasonic_global_nearest_dist  = 0;
U8 ultrasonic_global_nearest_position = 0;
U8 ultrasonic_global_adjust_forward = 0;

U16 ultrasonic_global_dist[6];



volatile U8 new_event_wait_old_finish = 0;

U8 ultrasonic_global_event_set(U8 event, U8 process) {

	U32 i = 0;
	//printf("new event:	%d\r\n", event);


	if(event == OB_POSITION_NONE) {
		OS_ENTER_CRITICAL();
		ultrasonic_global_event = event;
		ultrasonic_global_event_process = process;
		OS_EXIT_CRITICAL();
		
		return 0;
		
	}

	if(ultrasonic_global_event != OB_POSITION_NONE && event == OB_POSITION_PARSE_CORNOR_WALKING ){
		return 0;
	}


	#if 1
	if((event <= OB_POSITION_PARSE_CORNOR_WALKING)  && (ultrasonic_global_event>= OB_POSITION_PARSE_CORNOR_WALKING) ) {
		return 0;

	}
	#endif
	
#if 1
	if(ultrasonic_global_event == OB_POSITION_LEFT_DOWN ||
		ultrasonic_global_event == OB_POSITION_MID_DOWN ||
		ultrasonic_global_event == OB_POSITION_RIGHT_DOWN ) {

		return 0;

	}
#endif

	if(event == OB_POSITION_PARSE_CORNOR_WALKING) {
		OS_ENTER_CRITICAL();
		
		ultrasonic_global_event = event;
		ultrasonic_global_event_process = process;
		OS_EXIT_CRITICAL();
		
		return 0;
	}


	new_event_wait_old_finish = 1;

	wheel_action_set_finish_status();

	
	while(ultrasonic_global_event != OB_POSITION_NONE) {
		//printf("wait old finish: old evnet:	%d, new event:	%d\r\n",ultrasonic_global_event, event );
		OSTimeDlyHMSM(0,0,0,5);
		i++;
		//if(i > 100)
		//	printf("wait old finish: old evnet:	%d, new event:	%d\r\n",ultrasonic_global_event, event );
		

	}
	new_event_wait_old_finish = 0;

	OS_ENTER_CRITICAL();
	
	ultrasonic_global_event = event;
	ultrasonic_global_event_process = process;
	OS_EXIT_CRITICAL();
	
	return 0;

}




extern volatile U8 inter_task_ready;


volatile U32 ultrasonic_task_counter = 0;

void ultrasonic_task_core(void *pdata){



	while(inter_task_ready==0){
		OSTimeDlyHMSM(0,0,0,1);
		motor_task_wdg_counter++;
	}

	printf("ultrasonick task start....\r\n");
	clean_fsm_init();




	while(1){

		if(motor_global_setting.machine_cur_state!=MACHINE_WORKING
							|| global_clean_task.main_task ==MAIN_STOP
							|| global_sub_task_index == MACHINE_DOCKING)
		{
			OSTimeDlyHMSM(0,0,1,0);			
			continue ;
		}

		ultrasonic_task_counter ++;
	


		if(ultrasonic_global_event_process) {
			OSTimeDlyHMSM(0,0,0,10);
			continue;
		}
	
		

		OSTimeDlyHMSM(0,0,0,10);

		if(ul_walking_update()){

		
		}

	
		
	}

}









