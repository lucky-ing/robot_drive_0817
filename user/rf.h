#ifndef _RF_H
#define	_RF_H

#include "config.h"


void Enter_Rx_STATE(void);
void Enter_Tx_STATE(void);
//void Reset_Rx_FIFO(void);
void Reset_Tx_FIFO(void);
//void POWER_ON_RESET(void);
void Initial_RF_REG(void);
void Initial_frame(void);
void Initial_RF(void);

U32 get_ir_key_event(void );
void interaction_task_core(void *pdata);
extern U8 Rf_Rec_Data;
extern U8 Rf_Rec_Channel;
extern U8 Rf_Rate_Cnt;
extern U8 System_Mode;

extern U8 Rf_Rec_Buf[];
extern U8 Rf_Send_Buf[];

typedef struct{
	U8 unfinished ;
	U8 task_type ;
	U32 start_time;
	U32 need_time;
}stored_task_t;
void show_week_timing(void);

extern void delay_2us(U16 delay_cnt);
#if 0
#define KEY_POWER   2  //0x01
#define KEY_V		10//0x02
#define KEY_DOCK	6//0x03
#define KEY_UV		13//0x04
#define KEY_CLOCK	15//0x05
#define KEY_CYCLE   9//WORK_TIMING	0x06
#define KEY_TIMING	17//0x07
#define KEY_AUTO	 1   //0x08
#define KEY_FULL_GO 11//0x09

#define KEY_MON 12//0x16
#define KEY_TUE 8//0x15
#define KEY_WEN 4//0x14
#define KEY_THU 17//0x06 //dup
#define KEY_FRI  15//0x05 //dup
#define KEY_SAT 13//0x04 //dup
#define KEY_SUN 3//0x13

#define KEY_UP 5//0x0a
#define KEY_DOWN 7//0x0b
#define KEY_LEFT 18//0x0c
#define KEY_RIGHT 14//0x0d
#define KEY_OK 16//0x0e
#endif
#if 1//14key remote control

#define 		KEY_POWER		0xF7

#define 		KEY_UP			0x17

#define 		KEY_DOWN		0x97

#define 		KEY_RIGHT 		0x75

#define 		KEY_OK 			0xF5

#define			KEY_LEFT		0x0D

#define 		KEY_FULL_GO		0x47


#define          KEY_PRESS_FINISH 0x11


#define 		KEY_TIMING 		0x9D
#define			KEY_CLOCK   	0xC7

#define			KEY_AUTO    	0x67


#define			KEY_DOCK		0xE7

#define 		KEY_CORNOR		0x07

#define 		KEY_STOP    	0x88

#define 		KEY_SPOT		0xA7
#define			KEY_MUTE		0x87
#define			KEY_WIFI		0xED


#if 1 //def MULTI_COUNTRY
#define          KEY_SWITCH_COUNTRY 0x75
#define		KEY_VOLUME_CHANGE 0x66

#endif

#define		KEY_DEMO			KEY_UV

#endif


#define KEY_NULL 0xff

typedef enum {
	KEY_EVENT_POEWR = 1,
	KEY_EVENT_DOCK,
	KEY_EVENT_AUTO,
	KEY_EVENT_TIMING,
	KEY_EVENT_UP,
	KEY_EVENT_DOWN,
	KEY_EVENT_RIGHT,
	KEY_EVENT_LEFT,
	KEY_EVENT_SPEED,
	KEY_EVENT_PRESS_FINISH,
	KEY_EVENT_WHEEL_UPDATE,
	KEY_EVENT_STOP,
	KEY_EVENT_INCLINE,

	
}key_event_e;

typedef enum {
	I_STANDBY = 0,
	I_IDLE ,	
	I_WORKING ,


}interaction_state_e;

typedef struct  {
	U8 i_state ;
	U8 i_uv ;
}global_i_t;

typedef enum{
	POWER_SAVE = 0x55,
	POWER_NORMAL,
}power_mode_enum;

typedef enum{
	UV_OFF = 0,
	UV_ON ,
}uv_mode;
typedef enum{
	CLEAN_STOP=0,
	CLEAN_AUTO,
	CLEAN_TIMING ,
	CLEAN_FULL_GO ,

}clean_mode;
typedef enum{
	MAIN_WINDOW,
	VELOCITY_WINDOW,
	WEEK_SETTING,
	CLOCK_HOUR_SETTING,
	CLOCK_MIN_SETTING,
	CORNER_SETTING,
	CYCLE_SETTING,
	FULL_GO_SETTING,
	DOCK_SETTING,
	VELOCITY_SETTING,
	TIMING_WEEK_SETTING,
	TIMING_HOUR_SETTING,
	TIMING_MIN_SETTING,
	

}window_highlight;
typedef struct {

	#if 0
	U8 mon;
	U8 tue;
	U8 wen;
	U8 thu;
	U8 fri;
	U8 sat;
	U8 sun;
	#endif
	U8 hour;
	U8 min;
	
	U8 d;
}timing_week_set;
#if 0
enum {
	NO_DOCKING,
	DOCKING,
}dock_state;
#endif
typedef struct{
	U8 power_mode ;
	U8 velocity;
	U8 uv_state;
	//U8 clean_method;
	U8 window_hl;
	//U8 docking_state;
	timing_week_set t_week_set;
	U8 clock_week;
	U8 clock_hour;
	U8 clock_min;
#if 1//def MULTI_COUNTRY
	U8 country;
	U8 country_name_index;
	U8 volume;
	U8 volume_percent;
	U8 country_init_state ;
#endif
	U8 sync_id0;
	U8 sync_id1;

	U8 timing_week_index ;


	U8 mop_mode;
	
	//stored_task_t stored_task;	
}global_setting_t;

void lcm_show_task_core(void *pdata);

#ifdef KL_SERIAL_2

#define GET_KEY_AUTO_STATE()  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_15)
#define GET_KEY_CYCLE_STATE() GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)
#define GET_KEY_START_STATE() GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14)

#define GET_KEY_MECH_STATE() GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10)

#endif





#define UV_LIGHT_HIGH()  // GPIO_WriteBit(GPIOB, GPIO_Pin_14, Bit_SET)
#define UV_LIGHT_LOW()  //GPIO_WriteBit(GPIOB, GPIO_Pin_14, Bit_RESET)
void UV_close(void);
void UV_open(void);

void process_auto_clean_key(void);
#define	RC_CMD_KEY  0x5a,
#define 	RC_CMD_SET_SYNC 0xa5 


void process_auto_clean_key(void);


extern U8 clean_sub_type;

typedef struct{
	U8 rc_cmd;
	U8 sync_id0;
	U8 sync_id1;
	U8 rc_key;

}rc_data_t;

void process_power_key(void);
U32  sleep_get_key_event(void);
void press_key_task_core(void *pdata);
extern global_setting_t global_setting;
void process_timing_week_key(int key);
void interaction_parse_recv_key(U8 rf_key);

#ifdef DEMO_SUPPORT
extern volatile U8 global_demo_mode ;
extern volatile U8 global_demo_step ;
extern volatile U8 global_demo_change;
#endif
extern U8 clock_cola_hide;

void process_stop_clean_key(void);

#define LED_PANNEL_ALL 		0xFF
//#define LED_PANNEL_WIFI      0x01
#define LED_PANNEL_AUTO     0x02
//#define LED_PANNEL_SPOT	0x04
#define LED_PANNEL_DOCK      0x08

#define LED_OPEN  0x01
#define LED_CLOSE 0x00
void pannel_led_control(U8 pannel, U8 open) ;
void ResumeAllTask(void);

extern U16 show_plug_times;
#define MAX_SHOW_PLUG_TIME 10
extern U8 wifi_enable0;


extern U32 inter_task_wdg_counter ;
extern U8 buzzer_once_flag ;

extern volatile U8 weak_up_from_wifi ;

void process_wheel_update(void);

extern volatile U8 global_stop_event;

#endif
