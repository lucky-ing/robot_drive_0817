/************************************************************************************
;copyright		:shenzhen coolwaveasia 
;filename		:rf.c
;RF				:A7105
;rf crystal		:16MHZ
;RF rate		:250k
;control mcu	:W78E52B	
;writeby		:dengyihong
;describe		:A7105 ¿ØÖÆ
;notice			:Fdev ¹Ì¶¨Îª 80k
;***********************************************************************
;                            --------------------
;                     P1.0  |1                 40|  VCC
;                     P1.1  |2                 39|  P0.0     ----  LCD_DATA0
;   RF_SCK  ----      P1.2  |3                 38|  P0.1     ----  LCD_DATA1
;   RF_SDIO ----      P1.3  |4                 37|  P0.2     ----  LCD_DATA2
;                     P1.4  |5                 36|  P0.3     ----  LCD_DATA3
;   RF_SCS  ----      P1.5  |6                 35|  P0.4     ----  LCD_DATA4
;                     P1.6  |7                 34|  P0.5     ----  LCD_DATA5
;                     P1.7  |8                 33|  P0.6     ----  LCD_DATA6
;                  RST/Vpd  |9                 32|  P0.7     ----  LCD_DATA7
;                 RXD/P3.0  |10                31|  /EA/Vpp
;                 TXD/P3.1  |11                30|  ALE/PROG
;  RF_GPIO2 --- /INT0/P3.2  |12                29|  /PSEN
;  RF_GPIO1 --- /INT1/P3.3  |13                28|  P2.7     ----  KEY4
;                  T0/P3.4  |14                27|  P2.6     ----  KEY3
;  RX\TX   ---     T1/P3.5  |15                26|  P2.5     ----  KEY2
;                 /WR/P3.6  |16                25|  P2.4     ----  KEY1
;                 /RD/P3.7  |17                24|  P2.3
;                    XTAL2  |18                23|  P2.2     ----  LCD_RW
;                    XTAL1  |19                22|  P2.1     ----  LCD_RS
;                      VSS  |20                21|  P2.0     ----  LCD_EN
;                            --------------------
;                                W78E52B(PDIP)
;***********************************************************************/
#include "config.h"
#include "rf.h"

extern INT8U auto_work_suspend;

U8 buzzer_once_flag ;
global_setting_t global_setting;
extern U8 voice_delay_flag;
clean_task_t global_clean_task;

U32 inter_task_wdg_counter = 0;
void* pKeyBuffer[3];
void* actionbuffer[3];

//void* pCleanEventBuffer[3];
OS_EVENT* pKeyValueMail=NULL;

OS_EVENT* actionmail = NULL;
//OS_EVENT* PCleanEventMail = NULL;
//U8 clean_event = 0;

extern volatile task_list_t * global_sub_task;
extern volatile U32 global_sub_task_index ;

volatile U8 inter_task_ready = 0;
volatile U8 lcm_task_ready = 0;
U8 key_event  = 0;
U32  presskey_task_wdg_counter = 0;
extern u8 wifi_set_mode;

#if 1
extern volatile U8 emu_key;
extern volatile U8 emu_key_state;

U32 motor_task_wdg_counter = 0;
motor_global_setting_t motor_global_setting;

volatile U32 global_sub_task_index = 0;
volatile U8 need_wakeup_event = 0;
U8 motor_task_ready ;


extern U8 buzzer_once_flag ;
#if 1
#define KEY_RETRY_OK_TIME   5
#else

#define KEY_RETRY_OK_TIME  ( (  global_sub_task_index== MACHINE_AUTO_SUB_CORNOR ||\
								global_sub_task_index==MACHINE_AUTO_SUB_ZIGZAG ||\
								global_sub_task_index == MACHINE_FINDING_CHARGE_SUB_CORNOR ||\
								global_sub_task_index==MACHINE_FINDING_CHARGE_SUB_ZIGZAG|| \
								global_sub_task_index == MACHINE_SHORT_MANUAL_ZIGZAG||\
								global_sub_task_index == MACHINE_AUTO_SUB_SIX)?30:15)

#endif 

#define KEY_ERROR_RETRY 8000
#define KEY_VERSION_DISPLAY 1000

#define KEY_RUNNING_TIME_DISPLAY 4000
#define KEY_CHARGE_TIME_DISPLAY   6000

#define KEY_DELAY_T 2

extern Schedule_Configure_Clean(void);
extern struct s_schedule_program *read_schedule_stored(void);


U8 clean_sub_type = 0;




U8 rf_enable = 1 ;


void pannel_led_control(U8 pannel, U8 open) {

	
#if  1
	
	//if(pannel & LED_PANNEL_AUTO) 
		{
		if(open == LED_OPEN) {

	  		GPIO_WriteBit(GPIOD, GPIO_Pin_8, Bit_RESET);

		}else {
	  		GPIO_WriteBit(GPIOD, GPIO_Pin_8, Bit_SET);


		}


	}
	//if(pannel & LED_PANNEL_DOCK)

	{
		if(open == LED_OPEN) {

			  GPIO_WriteBit(GPIOD, GPIO_Pin_9, Bit_RESET);

		}else {
			  GPIO_WriteBit(GPIOD, GPIO_Pin_9, Bit_SET);


		}


	}



#endif

}


U8 show_version_no_display_time = 0;
U8  get_key_event(void)
{
	U32  retry=0;
	U8  err = 0;
	U16 battery_voltage;

	if(GET_KEY_AUTO_STATE()==0x00){
		OSTimeDlyHMSM(0,0,0,KEY_DELAY_T);
		retry=0;
	#if 1
		if(GET_KEY_AUTO_STATE()==0x00){

			WIFI_LED_DOWN;
			
			while(GET_KEY_AUTO_STATE()==0x00){
				OSTimeDlyHMSM(0,0,0,KEY_DELAY_T);
				presskey_task_wdg_counter++;


				retry++;
				

				

			}

			WIFI_LED_UP;
			
			//pannel_led_control(LED_PANNEL_DOCK, LED_OPEN);
			show_version_no_display_time = 0;


			if(retry >= KEY_ERROR_RETRY) {
				goto error;
			}
			
			if(retry < KEY_RETRY_OK_TIME)
				goto error;


			//global_setting.velocity = 1;
			return KEY_WIFI;
		}	
	#endif
		return KEY_NULL;
	}


	if(GET_KEY_CYCLE_STATE()==0x00){
		OSTimeDlyHMSM(0,0,0,KEY_DELAY_T);
		retry=0;
		#if 1
		if(GET_KEY_CYCLE_STATE()==0x00){
			//pannel_led_control(LED_PANNEL_DOCK, LED_CLOSE);
			DOCK_LED_DOWN;
			while(GET_KEY_CYCLE_STATE()==0x00){
				OSTimeDlyHMSM(0,0,0,KEY_DELAY_T);
				presskey_task_wdg_counter++;


				retry++;
				
				if(retry == KEY_VERSION_DISPLAY) {
					show_version_no_display_time = 1;
					//display_software_version(SW_VERSION);
				}

				if(retry == KEY_RUNNING_TIME_DISPLAY) {
					show_version_no_display_time = 1;
					//display_running_time();
				}

				if(retry == KEY_CHARGE_TIME_DISPLAY) {
					show_version_no_display_time = 1;
					//display_charge_cycle();
				}
				

			}
			DOCK_LED_UP;
			
			//pannel_led_control(LED_PANNEL_DOCK, LED_OPEN);
			show_version_no_display_time = 0;
			if(retry >= KEY_VERSION_DISPLAY) {
				show_hour(global_setting.clock_hour);
				show_min(global_setting.clock_min);
				
				goto error;
			}

			if(retry >= KEY_ERROR_RETRY) {
				goto error;
			}
			
			if(retry < KEY_RETRY_OK_TIME)
				goto error;


			//global_setting.velocity = 1;
			return KEY_DOCK;
		}	
		#endif
		return KEY_NULL;
	}


	if(GET_KEY_START_STATE()==0x00){
		OSTimeDlyHMSM(0,0,0,KEY_DELAY_T);
		retry=0;
		#if 1
		if(GET_KEY_START_STATE()==0x00){
			//pannel_led_control(LED_PANNEL_AUTO, LED_CLOSE);

			AUTO_LED_DOWN;
			while(GET_KEY_START_STATE()==0x00){
				OSTimeDlyHMSM(0,0,0,KEY_DELAY_T);
				presskey_task_wdg_counter++;
				
					if(++retry == KEY_VERSION_DISPLAY) {
						#ifdef WIFI_SUPPORT
						while(wifi_set_mode){
							OSTimeDlyHMSM(0,0,0,KEY_DELAY_T);
							presskey_task_wdg_counter++;
						}
						buzzer_once_flag = 1;
						wifi_set_mode = want_to_set;
						#endif
						
	
					
					}	
					
				}
				//pannel_led_control(LED_PANNEL_AUTO, LED_OPEN);
				AUTO_LED_UP;
				
				if(++retry>=KEY_VERSION_DISPLAY){
					goto error;
				}	

			show_version_no_display_time = 0;
			if(retry >= KEY_VERSION_DISPLAY) {
				show_hour(global_setting.clock_hour);
				show_min(global_setting.clock_min);
				goto error;
			}

			
			if(retry >= KEY_ERROR_RETRY) {
				goto error;
			}		
			if(retry < KEY_RETRY_OK_TIME)
				goto error;
			
			//global_setting.velocity = 1;
			clean_sub_type = MIX_CLEAN;
			return KEY_AUTO;
		}	
		#endif
		return KEY_NULL;
	}

	if(GET_KEY_MECH_STATE()==0x00){
		OSTimeDlyHMSM(0,0,0,KEY_DELAY_T);
		retry=0;
	#if 1
		if(GET_KEY_MECH_STATE()==0x00){
			pannel_led_control(LED_PANNEL_AUTO, LED_CLOSE);

			while(GET_KEY_MECH_STATE()==0x00){
				OSTimeDlyHMSM(0,0,0,KEY_DELAY_T);
				presskey_task_wdg_counter++;
				
					if(++retry == KEY_VERSION_DISPLAY) {
					#ifdef WIFI_SUPPORT
						while(wifi_set_mode){
							OSTimeDlyHMSM(0,0,0,KEY_DELAY_T);
							presskey_task_wdg_counter++;
						}
						buzzer_once_flag = 1;
						wifi_set_mode = want_to_set;
					#endif
						
	
					
					}	
					
				}
				pannel_led_control(LED_PANNEL_AUTO, LED_OPEN);
				
				if(++retry>=KEY_VERSION_DISPLAY){
					goto error;
				}	

			show_version_no_display_time = 0;
			if(retry >= KEY_VERSION_DISPLAY) {
				show_hour(global_setting.clock_hour);
				show_min(global_setting.clock_min);
				goto error;
			}

			
			if(retry >= KEY_ERROR_RETRY) {
				goto error;
			}		
			if(retry < KEY_RETRY_OK_TIME)
				goto error;
			
			//global_setting.velocity = 1;
			clean_sub_type = MIX_CLEAN;
			buzzer_once_flag = 1;
			
			return KEY_NULL;
		}	
	#endif
		return KEY_NULL;
	}




	return KEY_NULL;
error:
	//printf("key error;\r\n");
	return KEY_NULL;
}



U8 wait_motor_finish = 0;




volatile U8 global_stop_event = 0;





#endif
void panel_key_GPIO_Config()
{
#if 1
	GPIO_InitTypeDef  GPIO_InitStructure; 


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);


#endif


}



U16 stop_count =0;	  
void interaction_task_core(void *pdata)
{

	U8 key ;
//	int key_skip = 1;
	U8 i = 0;  
	U16 battery_voltage;
	


		DETECT_GPIO_Config();


		IIC_PCF8563_Init();

	
#if 1

		DISPLAY_GPIO_Configure();	
		BACK_LIGHT_LOW();	
		LCD_OPEN_LOW();
		
		BACK_LIGHT_HIGH();	
		LCD_OPEN_HIGH();


#endif




	inter_task_ready = 1;



	/* motor related GPIO init, tim4 timer init. */
	Motor_GPIO_Configuration();
	Motor_TIM4_Configuration();

	
	/* initialize detect module. */
	detect_init();


	
	/* notify other task that motor task is ready. */
	
	OSTimeDlyHMSM(0,0,0,15);



	while(1){

		
		inter_task_wdg_counter++;

		OSTimeDlyHMSM(0,0,0,20);

		if(buzzer_once_flag) {
			buzzer_once_flag = 0;
			startup_buzzer_ring();
		}


		key = poll_ir_key();

		

		
		if(key==KEY_NULL || rf_enable == 0 ){
			continue;
		}


		//printf("rf key :%d\r\n", key);

		stop_count = 0;



		

	}


}

volatile U8 auto_test_once = 0;





