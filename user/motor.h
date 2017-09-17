#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "config.h"


extern volatile U8 ir_signal_detected;
#define FRONT_M_RF_REPORT_THRESHOLD 0x0dd0
#define FRONT_MR_RF_REPORT_THRESHOLD 0x0dd0
#define FRONT_ML_RF_REPORT_THRESHOLD 0x0dd0
#define FRONT_L_RF_REPORT_THRESHOLD 0x0dd0
#define FRONT_R_RF_REPORT_THRESHOLD 0x0dd0



#define C 16
#define K 5

#define STEP_0  0
#define STEP_1 (STEP_0+C)
#define STEP_2 (STEP_1+K)
#define STEP_3 (STEP_2+C)
#define LOOP	(STEP_3+K)



#define HH_DELTA_M 			(0x48 + ir_mid_ex) 
#define HH_DELTA_MR			(0x48 + ir_mid_right_ex)
#define HH_DELTA_ML			(0x48 + ir_mid_left_ex)
#define HH_DELTA_R			(0x48 + ir_right_ex)		
#define HH_DELTA_L   		(0x48 + ir_left_ex)







#define CHAR_FINDING_TIMEOUT_CORNOR 9000000
#define CHAR_FINDING_TIMEOUT_ZIGZAG  250000

#define DOCKING_TIMEOUT  0x5f00000 //0x6e00000 //0x4e00000 //  0x70000 ;//000 //0

#define MACHINE_DOWN_BACK_LEN 3
#define MACHINE_DOWN_BACK_LEN2 3

#define MACHINE_SPEED_TEST_DEFAULT 4

#define WHEEL_ONE_CYCLE 22 //cm

#if 0
#define ONE_CM_CYCLE_NUM   13
#else
#define ONE_CM_CYCLE_NUM   42 //52 //60
#endif
#define MACHINE_DIAMETER 28 //cm
#define MACHINE_CYCLE_LEN  88 //cm

#define  side_motor_open()	GPIO_WriteBit(GPIOC,  GPIO_Pin_8, Bit_SET)
#define  side_motor_close()	GPIO_WriteBit(GPIOC,  GPIO_Pin_8, Bit_RESET)


#define MOTOR_DEAD_TIME()  OSTimeDlyHMSM(0,0,0,15)

#define RECALC_ADC   15 // 3  // 15


#define QUICK_RECALC_ADC  15//  3

#define MOTOR_TIMEOUT    10  // 15 

extern volatile U32 right_wheel_record ;
extern volatile U32 left_wheel_record;
#ifdef WHEEL_HAS_CAP
#define CYCLE_LEFT_SPEED_BASE  0x20
#else
#define CYCLE_LEFT_SPEED_BASE  0x58 // 0x60
#endif
#ifdef WHEEL_HAS_CAP
#define CYCLE_LEFT_SPEED_STEP 3
#else
#define CYCLE_LEFT_SPEED_STEP 3
#endif
#define CYCLE_LEFT_BACK_STEP  10
#define MACHINE_CYCLE_RIGHT_SPEED_ONE  0xa8 //e0 //0xe0
#define MACHINE_CYCLE_RIGHT_SPEED_TWO 0xd0
#define IR_MAX 0xe10

#define MAX_TASK_LIST  		12		//total sub task buffers. it's alloced when system bootup.

#define MAIN_MOTOR_OVERFLOW_THRESHOLD 0x100

#ifdef X5B
#define DUST_MOTOR_OVERFLOW  0x80
#endif
#ifdef X5A
#define DUST_MOTOR_OVERFLOW  0x100

#endif
#define DRIVER_MOTOR_THRESHOLD 0x70
#define DROP_THRESHOLD 0xdd0
//#define DROP_DELTA 0x40



#define SHORT_ZIGZAG_TIMEOUT 50000
#define CHAR_PWM_LOW  130 //14
#define CHAR_PWM_MID 140
#define CHAR_PWM_HIGH 150

#define MOTOR_TOO_OVERFLOW 0xc0



#define WHEEL_ADJUST_STEP 4
#define WHEEL_DELTA_TIME 10

extern volatile U8 flagr[] ;
extern volatile U32 shujur[] ;

extern volatile U8 flagh[] ;
extern volatile U32 shuju[] ;
extern volatile u32 int_times[];
extern volatile u32 tmr_times[];
extern volatile U8 head_ok[];
extern volatile U32 code_data[];

extern volatile U8 flag_near[];
extern volatile U32 shuju_near[];

extern volatile U32 temp_ignore_near_chg_check;

typedef enum motor_action{
	MACHINE_SL_FORWARD=0x40,
	MACHINE_FORWARD,
	MACHINE_TURN_LEFT,
	MACHINE_TURN_RIGHT,
	MACHINE_BACKWARD,
	MACHINE_CYCLE,
	MACHINE_STOP,

}motor_action_ee;


#if 1
#define MAX_V 2
typedef enum motor_speed_type_e {
MACHINE_FORWARD_FIND_CHARGE_ZIGZAG_FINDING = 0, // finding charge zigzag  
MACHINE_FORWARD_FIND_CHARGE_ZIGZAG_FOUND,
MACHINE_FORWARD_FIND_CHARGE_ZIGZAG_NEAR_STATION,
MACHINE_FORWARD_CORNOR_FINDING,
MACHINE_FORWARD_CORNOR_WALKING,

MACHINE_FORWARD_FIND_CORNOR_FINDING,
MACHINE_FORWARD_FIND_CORNOR_WALKING,

MACHINE_FORWARD_MANU_ZIGZAG,
MACHINE_FORWARD_DEFAULT,

MACHINE_FORWARD_SLOW, 

MACHINE_LR_DOWN_BACK_TURN,
MACHINE_LR_FIND_ZIGZAG_TURN_FIND_SIDE_IR,
MACHINE_LR_FIND_ZIGZAG_TURN_FIND_MID_IR,
MACHINE_LR_FIND_ZIGZAG_TURN,
MACHINE_LR_MANU_ZIGZAG,
MACHINE_LR_CORNOR_WALK,
MACHINE_LR_OTHER,
MACHINE_BACK_DOWN_FAST_BACK,
MACHINE_BACK_CORNOR,
MACHINE_BACK_OTHER,
MOTOR_CLEAN_CYCLE_SPEED,
MOTOR_SPEED_STEP_MAX,
}motor_speed_type_ee;

typedef struct {
	U8 index ;
	U32 speed_per_second;
	U16 left_pwm;
	U16 right_pwm;
}machine_speed_s;
#endif


//whether knocked ,picked up ,or ed found.
typedef enum AZIMUTH{
	//A_RIGHT_OVERFLOW =0,
	//A_LEFT_OVERFLOW,
	
	A_LEFT_DOWN =0,
	A_RIGHT_DOWN,
	A_MID_DOWN,


	A_MAX,
}azimuth_e;


typedef enum TURN_DIR{
	TURN_RIGHT =0 ,
	TURN_RIGHT_LITTLE ,
	TURN_BACKWARD,
	TURN_SPEED_DOWN,
	TURN_GO_AHEAD,
	TURN_LEFT_LITTLE,
	TURN_LEFT,
	TURN_LEFT_ROTATE,
	TURN_RIGHT_ROTATE,
}turn_dir_e;

typedef enum {
	CORNOR_FINDING_CORNOR=0,
	CORNOR_WALKING1,
	FINDING_CYCLE_CENTER ,
	CYCLE_BIGGER,
	CYCLE_SMALLER,	

}cornor_sub_state_e;

typedef struct {
	U8 sub_state;
	U8 cycle_ward ;//0 shun shizheng,1 ni shizheng;
	U8 left_speed;
	U8 right_speed;
	
}cycle_sub_tasks_t;


typedef struct {
	U8 cornor_sub_state;
	U8 last_cornor_sub_state ;
}cornor_sub_tasks_t;

typedef enum {
	NO_NEED=0,
	INIT ,
	DOING,
	PAUSED_REASON_TIMEOUT,
	PAUSED_REASON_PICKED,
	PAUSE_REASON_DOCKING,
	PAUSE_REASON_HIGH_TEMP,
	PAUSE_REASON_HIGH_VOL,
	PAUSE_REASON_TEMP_SENSOR_INVALID,
	PAUSE_REASON_VOL_TOO_LOW,
	PAUSE_REASON_CUR_TOO_LOW,
	DONE,

}sub_task_state_e;

typedef enum {
	MAIN_STOP=0x66,
	AUTO_CLEAN,
	MOP_CLEAN,
	TIMING_CLEAN,
	MAIN_DOCKING,
	

}main_mode_e;


typedef enum {
		SUB_INVALID=0x77,
	CYCLE_CLEAN ,
	MAP_CLEAN,
	CORNOR_CLEAN,
	MIX_CLEAN,
	FINDING_CHARGE,
	DOCKING,

}sub_mode_e;


typedef enum{
	MOTOR_STATE_STOP = 0x88,
	MOTOR_STATE_FORWARD,
	MOTOR_STATE_BACKWARD,
	MOTOR_STATE_CYCLE,
	MOTOR_STATE_TURN_LEFT,
	MOTOR_STATE_TURN_RIGHT,
}motor_state_e;

typedef struct {

	U8 sub_task_state;
	U8 cur_motor_state ;
	U8 sub_task;
	int timeout;

}clean_sub_task_t;

typedef enum wheel_state{
	NORMAL = 0,
	PICK_UP,
}wheel_state_e;

typedef enum machine_state_e{
  MACHINE_STANDBY = 0,	  //power key pressed ,power standby.
  MACHINE_STOP_STATE ,  //stay at original place ,not move;

  MACHINE_WORKING,
  MACHINE_WORK_PAUSE,
  MACHINE_MAX_STATE,
  
  MACHINE_AUTO_STOP,  //main mode:auto,sub mode :stop,maybe the machine is picked up or droped.
  MACHINE_AUTO_SUB_CYCYLE,  //main mode:auto ,sub mode: cycyle ;
  MACHINE_AUTO_SUB_ZIGZAG, //main mode :auto ,sub mode: zigzag;
  //MACHINE_AUTO_SUB_LINEAR, //main mode:auto, sub mode:linear;
  MACHINE_AUTO_SUB_CORNOR, //main mode:auto,sub mode:cornor;
  MACHINE_AUTO_SUB_SIX, // walk like flower.
//  MACHINE_AUTO_FINDING_CHARGE, //main mode:auto,sub mode:finding charge;
//  MACHINE_AUTO_DOCKING, //main mode:auto,sub mode:docking;
  MACHINE_AUTO_SUB_MAP,


  MACHINE_TIMING_STOP,  //main mode:timing,sub :stop
 // MACHINE_TIMING_FINDING_CHARGE, //main mode:timing,sub:finding charge,
 // MACHINE_TIMING_DOCKING, //main mode:timing,sub:docking,
  MACHINE_TIMING_CYCYLE, //main mode:timing,sub:cycle


  MACHINE_FINDING_CHARGE,
  MACHINE_FINDING_CHARGE_SUB_ZIGZAG,
  MACHINE_FINDING_CHARGE_SUB_CORNOR,
  MACHINE_DOCKING,
  MACHINE_SHORT_MANUAL_ZIGZAG,
  MACHINE_AUTO_SUB_MOP,
  MACHINE_AUTO_SUB_MOP_SIX, 
  MACHINE_PREV_STATE,
  INVALID_STATE,
}machine_state_ee;

typedef enum MOP_state{
	FMS_NONE = 0,
	FSM_A_R_L = 1,
	FSM_A_LEFT_DOWN = 2,
	FSM_A_RIGHT_DOWN = 3,
	FSM_A_M_LEFT_DOWN = 2,
	FSM_A_M_RIGHT_DOWN =3,
	FSM_M_KNOCKED =4,
	FSM_L_KNOCKED = 5,
	FSM_R_KNOCKED =6,
	FSM_A_M_R =7,
	FSM_A_LEFT = 8,
	FSM_A_RIGHT = 9,
	FSM_A_M =7,
	FSM_A_M_L = 7,
}MOP_state_e;


typedef enum machine_event_e{
	MACHINE_EVENT_KEY_AUTO = 0, // change to auto mode.
	MACHINE_EVENT_KEY_TIMING,
	MACHINE_EVENT_KEY_DOCKING,
	MACHINE_EVENT_KEY_POWER,
	//MACHINE_EVENT_MAIN_MODE_TIMEOUT,
	//MACHINE_EVENT_SUB_MODE_TIMEOUT,
	MACHINE_EVENT_PICKED_UP,
	MACHINE_EVENT_PUT_DOWN,
	//MACHINE_EVENT_POWER_LESS_THAN_15,
	//MACHINE_EVENT_POWER_BIG_THAN_95,
	//MACHINE_EVENT_CHARGE_STATION_FOUND,
	//MACHINE_EVENT_DC_SOCKET_CONNECTED,
	MACHINE_EVENT_KEY_STOP_WORK, //stop auto docking,timing,

	MACHINE_EVENT_MAX,
}machine_event_ee;

typedef enum turn_center{
	CENTER_CENTER = 0,
	CENTER_LEFT,
	CENTER_RIGHT,
}turn_center_ee;
void machine_sl_forward(U16 dist);

typedef void (*motor_fsm_f)(void *arg);


#define FRONT_WHEEL_MAX_COUNT 100




typedef struct {
	U8 env_light_detect;	

	/* infra detection. */
	#if 1
	INT16S front_rf_right;//=IR_MAX;
	INT16S front_rf_middle_right;//=IR_MAX;
	INT16S front_rf_left;//=IR_MAX;
	INT16S front_rf_middle_left;//=IR_MAX;
	INT16S front_rf_middle;//=IR_MAX ;


	INT16U front_ad_right;//=IR_MAX;
	INT16U front_ad_middle_right;//=IR_MAX;
	INT16U front_ad_left;//=IR_MAX;
	INT16U front_ad_middle_left;//=IR_MAX;
	INT16U front_ad_middle;//=IR_MAX ;




	INT16S env_r;//=IR_MAX;
	INT16S env_mr;//=IR_MAX;
	INT16S env_l;//=IR_MAX;
	INT16S env_ml;//=IR_MAX;
	INT16S env_m;//=IR_MAX;

	U8 front_knock_left;
	U8 front_knock_right;


	U8 drop_left_block;
	U8 drop_right_block;
	U8 drop_mid_block;
	U8 front_wheel_block;
	U8 climb_block;

	U8 near_chg_block;
	U8 chg_block_type;
	

	U8 left_side_block;
	U8 right_side_block;

	U8 main_motor_block;

	U8 tank_capert_block;





	U8 front_near_right;
	U8 front_near_m;
	U8 front_near_mr;
	U8 front_near_ml;
	U8 front_near_left;

	U16 tank_capert_block_count;
	
	U16 tank_capert_block_ignore_count;
	U16 cornor_lost_count;
	U16 cornor_too_near_count;
	U16 cornor_too_out_count;
	
	U16 front_right_delta;

	
	U16 front_left_delta;
	U16 left_cornor_lost_count;
	U16 left_cornor_too_near_count;
	U16 left_cornor_too_out_count;
		
	
	U16 front_right_max_delta;
	U16 front_right_out_count;
	U16 front_right_near_count;
	


	U16 front_left_max_delta;
	U16 front_left_out_count;
	U16 front_left_near_count;
	

	
	U16 front_left_near_level;
	
	

	

#endif
	
	INT16S drop_left;//=IR_MAX;
	INT16S drop_mid;//=IR_MAX;
	//INT16S drop_m_right;//=IR_MAX;
	INT16S drop_right;//=IR_MAX;
	//INT16S drop_m;//=IR_MAX;

	INT16S front_wheel;
	
	INT16S drop_back_r;//=IR_MAX;
	INT16S drop_back_l;//=IR_MAX;
	

	INT16S env_drop_l;//=IR_MAX;
	INT16S env_drop_m;//=IR_MAX;
	//INT16S env_drop_mr;//=IR_MAX;
	INT16S env_drop_r;//=IR_MAX;

	INT16S env_front_wheel;

//	INT16S env_drop_m;//=IR_MAX;
	INT16S env_drop_back_r;//=IR_MAX;
	INT16S env_drop_back_l;//=IR_MAX;
		
	INT16S last_drop_l;//=IR_MAX;
	INT16S last_drop_m;//=IR_MAX;
	//INT16S last_drop_mr;//=IR_MAX;
	INT16S last_drop_r;//=IR_MAX;



	U16 front_wheel_delta;
	U16 last_front_wheel_delta ;
	U16 front_wheel_live_count;

	U32 front_wheel_check_count;
	U32 front_wheel_ok_count ;
	
	

	U32 front_wheel_function_ready ;
	U32 front_wheel_function_count ;

	

	/* charge or dock. */
	int last_3min_t;//=0;
	int last_3min_v ;//= 0;
	int cur_3min_count;//=0;
	int char_pwm_step ;//= 0;
	U8 char_pwm_step_later;// = 0;


}running_config_t;



typedef struct{
	U8 mop_err_times;
	U8 machine_change_times;
	U8 last_change_status;

}auto_sub_mop;


#define CHARGING_LCD_TURNOFF_TIMEOUT (motor_global_setting.machine_cur_state==MACHINE_WORKING?(0x10*400):300)
typedef struct {
	U8 machine_state;
	U8 machine_state_setting;

	
	U8 front_wheel_pickup;
	U8 left_wheel_pickup;
	U8 right_wheel_pickup;
	U8 machine_pickup;

	U8 left_motor_state ;
	U8 right_motor_state;
	U8 main_motor_state ;
	U8 dust_motor_state ;
	U8 side_motor_state ;

	U8 machine_prev_state;
	U8 machine_cur_state;

	U8 machine_main_mode ;
	U8 machine_charge_type ;
	//U8 velocity;

	running_config_t running;

	U16 left_speed;
	U16 right_speed;
	U16 main_motor_ref_current ;

	U16 left_side_ref_current;
	U16 right_side_ref_current;
	
	

	U8 charging_lcd_off ;
	INT32S charging_lcd_turnoff_timeout;


	U8 drop_ignore_left;
	U8 drop_ignore_right;
	U8 drop_ignore_mid;


	
}motor_global_setting_t;

typedef struct  {
       struct list_head list;
		
	U8 sub_task_state;
	U8 cur_motor_state ;
	U8 sub_task;
	U32 timeout;
	
}task_list_t;


typedef struct {
	s16 left_speed;
	s16 right_speed;
	U8 bigger ;
	U16 step ;

}motor_cycle_t;
typedef struct {
	U16 max_len;  // max len, exceed, then stop this mode.
	U16 len_step;  // now time len;
	U16 step_count; // step counter, if equal six, len_step ++;
	U16 three_cm_count; 
}motor_six_t;



#define MAX_TURN_OBSERVE_WINDOW 10
typedef struct {
	U32 timestamp;
	U16 arc;
}turn_record_t;

#define MAX_BLOCK_OBSERVE_WINDOW 8
typedef struct {
	U32 timestamp;
	U8 block_type;
	
}block_record_t;

#define MAX_DUST_OBSERVE_WINDOW 50
typedef struct {
	U32 timestamp;
	
}dust_record_t;


#define DUST_LIKELY_THRESHOLD 0x0050


#define MAX_DUST_DELTA_RECORD 30


typedef enum  env_dust_leve{
	ENV_DUST_LEVEL_INVALID = 0x00,
	ENV_DUST_LEVEL_0 = 0x01,
	ENV_DUST_LEVEL_1 = 0x50,
	ENV_DUST_LEVEL_2 = 0x60,
	ENV_DUST_LEVEL_3 = 0x70,
	ENV_DUST_LEVEL_4 = 0x78,

}env_dust_leve_e;
typedef struct {
	U16 delta_record[MAX_DUST_DELTA_RECORD];
	U8   index;
	U8	env_level;

}dust_env_t;

#define MAX_FRONT_RF_ENV 20
typedef struct {
	U16 mid[MAX_FRONT_RF_ENV];
	U16 mid_r[MAX_FRONT_RF_ENV];
	U16 mid_l[MAX_FRONT_RF_ENV];
	U16 left[MAX_FRONT_RF_ENV];
	U16 right[MAX_FRONT_RF_ENV];
	U8 index;
	U8 round_flag ;
}front_rf_env_t;


void motor_record_init(void);

 typedef struct {
	U8 main_task;
	U8 sub_task;
	
	U8 main_task_state;

	struct list_head free_head_list;	
	struct list_head work_head_list;

	cornor_sub_tasks_t cornor_sub_task;


	/*statistics or state */
	U8 cycle_or_square ;//= 1;
	U8 need_c_or_s;
	U8 cornor_count ;
	U32 need_calc_env_drop ;
	motor_cycle_t motor_cycle;
	motor_six_t motor_six;
	U16 side_motor_overflow_counter;//=0;
	U16 left_side_motor_overflow_counter;


	U16 side_motor_normal_counter ;

	U8 front_wheel_inact_counter ;//= 0;
	U16 main_motor_overflow_counter ;//= 0;
	//U16 walk_motor_overflow_counter ;//= 0;
	U16 dust_motor_overflow_counter ;//= 0;
	turn_record_t turn_record[MAX_TURN_OBSERVE_WINDOW];
	block_record_t block_record[MAX_BLOCK_OBSERVE_WINDOW];
	dust_record_t dust_record[MAX_DUST_OBSERVE_WINDOW];
	dust_env_t dust_env;
	front_rf_env_t front_env;

#ifdef SCHEDULE_ONE_HOUR
	U8 schedule_end_hour;
	U8 schedule_end_min;
#endif


#ifdef STATISTIC_ENABLE
	U32 task_start_time;
	U32 task_start_charge_time;
	U32 sub_task_start_time;
	U32 sub_task_total_time;
	

#endif
	
}clean_task_t;


#define SIX_ANGLE_LEN_MAX 150
#define SIX_ANGLE_LEN_STEP 12
#define SIX_ANGLE_FIRST 12
#define SIX_ANGLE_STEP 4

#ifdef OLD_2000_PCS
#define CHAR_VOL_17V 0x89f
#define CHAR_VOL_16_75V 0x86f
#define CHAR_VOL_16_5V  0x84f
#define CHAR_VOL_16_25V 0x82f
#define CHAR_VOL_16V     0x80f
#define CHAR_VOL_15_75V 0x7ef
#else
#define CHAR_VOL_17V 0x850
#define CHAR_VOL_16_75V 0x820
#define CHAR_VOL_16_5V  0x800
#define CHAR_VOL_16_25V 0x7E0
#define CHAR_VOL_16V     0x7C0
#define CHAR_VOL_15_75V 0x7A0
#endif

#define CHAR_LOW_CONSIS   40

typedef enum  CHAR_STEP_E{
#ifdef OLD_2000_PCS
	CHAR_STEP_ZERO = 172,
	CHAR_STEP_ONE = 176,
	CHAR_STEP_TWO =178,
	CHAR_STEP_THREE =180,
	CHAR_STEP_FOUR = 182,
	CHAR_STEP_FIVE = 186,
	CHAR_STEP_SIX = 182,
#else	
#if 0
	CHAR_STEP_ZERO = 171,
	CHAR_STEP_ONE = 179,
	CHAR_STEP_TWO =182,
	CHAR_STEP_THREE =185,
	CHAR_STEP_FOUR = 186,
	CHAR_STEP_FIVE = 188,
	CHAR_STEP_SIX = 181,
#endif
	CHAR_STEP_ZERO = 168,
	CHAR_STEP_ONE = 175,
	CHAR_STEP_TWO =178,
	CHAR_STEP_THREE =180,
	CHAR_STEP_FOUR = 182,
	CHAR_STEP_FIVE = 184,
	CHAR_STEP_SIX = 179,
#endif
}char_step_ee;


#ifdef FRONT_WHEEL_DETECT
extern volatile U32 front_heel_walk_counter;
#endif
U8 motor_deal_with_front_wheel(void);

void motor_delay(U16 delay);
void machine_stop(void);

#if 0
typedef enum  walk_bg_e{ 
	WALK_BG_NULL = 0,
	WALK_BG_KNOCK_TURN ,  /* when knocked or will knocking, turn round, the speed should from low to high. */
	WALK_BG_KNOCK_SLOW_DOWN,
	WALK_BG_CORNOR_KNOCK_TURN_LEFT,
	WALK_BG_BACK_CHECK_PICKUP,
	WALK_BG_TURN_FAST,
	WALK_BG_TURN_IGNORE_DROP,
	WALK_BG_BACKWARD_IGNORE_DROP,
	WALK_BG_IGNORE_HOR,	
}WALK_BG_EE;
#endif


struct auto_sub_mop{
	U8 mop_err_times;
	U8 machine_change_times;
	U8 last_change_status;
	U16 step_count;
	U16 max_len;
	U16 len_step;
	U16 three_cm_count;
};


U8 machine_forward(U16 dist, U8 bg);
U8 machine_backward(U16 dist, U8 bg);


U16  machine_turn_left(U8 center, U16 arc, U8 bg);
U16  machine_turn_right(U8 center, U16 arc, U8 bg);
void machine_cycle(void);
void left_motor_stop(motor_global_setting_t *gt);
#if 1 //def ROBOT_TEST
void left_motor_backward(motor_global_setting_t *gt, u16 speed);
#endif
void left_motor_forward(motor_global_setting_t *gt, u16 speed);
void right_motor_stop(motor_global_setting_t *gt);
#if 1 //def ROBOT_TEST
void right_motor_forward(motor_global_setting_t *gt, u16 speed);
void right_motor_backward(motor_global_setting_t *gt, u16 speed);
#endif
void motor_task_core(void *pdata);

void main_motor_stop(motor_global_setting_t *gt);
void main_motor_left(motor_global_setting_t *gt);
#ifdef ROBOT_TEST
void main_motor_right(motor_global_setting_t *gt);
#endif
void side_motor_stop(motor_global_setting_t *gt);
void side_motor_forward(motor_global_setting_t *gt, U8 speed);
void dust_motor_stop(motor_global_setting_t *gt);
void dust_motor_forward(motor_global_setting_t *gt);
void Motor_GPIO_Configuration(void);
void Motor_TIM4_Configuration(void);

U8 motor_deal_with_detect_distance_event(void);
U8 motor_deal_with_ir_receiver_event(void);
U8 motor_deal_with_key_event(U8 key);

void motor_task_core(void *pdata);
U8 charging_clean_task_init2(clean_task_t *clean_task);
U8 Docking_add_zigzag(void);
U8 motor_deal_with_side_motor(void);
//U8 motor_deal_with_drop_event(void);
U8 motor_deal_with_dust_motor(void);
U8 motor_deal_with_main_motor(void);
U8 motor_deal_with_charge_event(void);
U8 motor_deal_with_pickup_event(void);
U8 zigzag_add_short_cornor(void);
void clean_motor_open(motor_global_setting_t *gt);
void clean_motor_close(motor_global_setting_t *gt);
U8 auto_clean_task_init(clean_task_t *clean_task, U8 type);
U8 timing_clean_task_init(clean_task_t *clean_task);
U8 docking_clean_task_init(clean_task_t *clean_task);
U8 global_clean_task_init(clean_task_t *clean_task);

U8 motor_deal_with_left_right_motor(void);
U8 add_small_zigzag_task(clean_task_t *clean_task);
void total_motor_stop(void);
U8 get_bat_vol_stage(void);
#ifdef ROBOT_TEST
void robot_test_function(void);
void robot_test_function2(void);
#endif



void fsm_a_r_l(void *arg);
void fsm_a_m_right_down(void * arg);
void fsm_a_right_down(void * arg);

void fsm_a_m_left_down(void * arg);
void fsm_a_left_down(void * arg);
void fsm_a_m(void *arg);
void fsm_a_right(void *arg);
void fsm_a_left(void *arg);
void fsm_a_m_r(void *arg);
void fsm_a_m_l(void *arg);
void fsm_r_knocked(void *arg);
void fsm_l_knocked(void *arg);
void fsm_m_knocked(void *arg);
U8 auto_clean_task_init2(clean_task_t *clean_task);

extern motor_global_setting_t motor_global_setting;
extern clean_task_t global_clean_task;
#define MOTOR_MAX_SPEED 0xfb
void show_err_code(U8 code);

#define BATTERY_TEMP_SENSOR_INVALID 0xf00

void task_list_init(struct list_head *free_head_list,struct list_head *work_head_list);
void task_list_deinit(struct list_head *free_head_list,struct list_head *work_head_list);


U8 deal_with_motor_overflow(void);

void motor_clear_front_rf_env(void);

U8 machine_update_timeout_event(void);

extern volatile task_list_t * global_sub_task;
extern volatile U32 global_sub_task_index;
extern U8 wait_motor_finish;

void motor_cycle_init(void);
U8 machine_update_forward_timeout(task_list_t *tl);
extern U32 wheel_count;

extern volatile U32 right_wheel_counter;
extern volatile U32 left_wheel_counter;
	extern U32 motor_task_wdg_counter;

extern U32 arc_index;



void motor_six_init(void);
void detct_init_rf(motor_global_setting_t *gt);


extern volatile U16 side_ir_found ; /*it's to mid recv ir*/
extern volatile U16 mid_ir_found ; /*it's to mid recv ir*/

extern int mid_found_retry;//FOUND_RETRY ;
extern int side_found_retry;// FOUND_RETRY;


#define NO_FOUND_TIMEOUT_B 550
#define NO_FOUND_TIMEOUT  550
#define NO_FOUND_TIMEOUT_Q 200


#define TASK_TIMEOUT_NEAR 180
extern int no_found_timeout;
void speed_calc_val_init(void);

extern INT8U auto_work_suspend;
U8 docking_clean_task_init2(clean_task_t *clean_task);
extern volatile U8 sl_forward_type ;
extern volatile U8 machine_sl_backward_notimeout;

extern volatile U32 r_int_finish ;
extern volatile U32 l_int_finish ;
extern volatile u32 max_int_tick ;
extern volatile U8 machine_sl_forward_notimeout;

extern volatile U8 fast_backward_once;

extern volatile U8 machine_sl_backward_flag;

#define FOUND_RETRY  250  //  70
#define FOUND_RETRY_S 180
extern U8 side_conor_find_again ;
extern volatile U8 machine_sl_forward_flag;

extern volatile U16  turn_cycyle_to_find_mid_ir;
extern volatile U16 turn_cycle_to_found_side_ir;
extern volatile U16 sl_forward_to_let_side_find_mid;

extern U8 very_near_char_station;
#define IR_WALL_DT (global_setting.velocity? 800:1000)   //300:400
#define IR_WALL_DT_S (global_setting.velocity?300:600)  //150:300
extern volatile U16 turn_cycle_to_find_ir;
#define TEMP_IGNORE_IR_MAX 70
#define TEMP_IGNORE_IR_HUGE 70
U8 motor_deal_with_speed_detection(void);

U8 motor_save_turn_record(U16 arc);
U8 motor_parse_turn_record(void);
U8 motor_save_block_record(U8 block_type);
U8  motor_parse_block_record(void);
U8 motor_save_dust_record(void);
U8  motor_parse_dust_record(void);
U8  motor_deal_with_dust_event(void);

U8 zigzag_add_short_cycle(void);

U8 motor_deal_with_drop_event(U8 ag);
U8 motor_current_quick_test(void) ;

#ifdef FRONT_WHEEL_DETECT
extern volatile U32 front_wheel_walk_counter;

#endif

extern U8 err_showing;
extern U8 drop_side_flag ;

extern U16 left_walk_motor_overflow_counter ;
extern U16 right_walk_motor_overflow_counter ;

extern U16 left_invalid_counter ;
extern U16 right_invalid_counter ;


#if 0

#define V_THREE_GRADE 0x700  //  14.6
#define V_TWO_GRADE   0x6e0  // 13.9
#define  V_ONE_GRADE   0x6d0



#define FIND_CHAR_THRESHOLD    0x690
#define FIND_CHAR_THRESHOLD2   0x690
#define MANUAL_CHAR_THRESHOLD   0x640
#define POWER_ON_SHUTDOWN_THRESHOLD 0x610
#else

#define V_THREE_GRADE 0x700  //  14.6
#define V_TWO_GRADE   0x6e0  // 13.9
#define  V_ONE_GRADE   0x6d0



#define FIND_CHAR_THRESHOLD    0x680
#define FIND_CHAR_THRESHOLD2   0x680
#define MANUAL_CHAR_THRESHOLD   0x670
#define POWER_ON_SHUTDOWN_THRESHOLD 0x610


#endif

#define CHAR_OVERFLOW    0x800  //test1111

#define BATTERY_FULL_BEFORE_CHAR 0x860

#define PUSH_UP_RES 10000
#define PUSH_UP_V 3300
#define ADC_FULL 0xFFF
extern U16 temp_ignore_ir;

extern volatile U8 ignore_shutdown_buzzer;

U8 deal_with_clean_motor_overflow(void);
void walk_wheel_invalid_check(void);
extern U8 front_pickup_enable;

#ifdef LEAK_LIGHT


//#define DROP_DELTA 0x20

#if 0
#define DROP_DELTA_0 0x28
#define DROP_DELTA_1 0x28
#define DROP_DELTA_2 0x28

#define DROP_DELTA_LEFT 0x28
#define DROP_DELTA_MID 0x28
#define DROP_DELTA_RIGHT 0x28



#define DROP_DELTA   0x28

#define MOP_DROP_DELTA 0x60
#endif

#if 1
extern U16 ir_left_ex ;
extern U16 ir_right_ex ;
extern U16 ir_mid_ex ;
extern U16 ir_mid_left_ex ;
extern U16 ir_mid_right_ex ;



#define DROP_DELTA_0 0x18
#define DROP_DELTA_1 0x18
#define DROP_DELTA_2 0x18

#define DROP_DELTA_LEFT 0x18
#define DROP_DELTA_MID 0x18
#define DROP_DELTA_RIGHT 0x18



#define DROP_DELTA   0x18 


#define MOP_DROP_DELTA 0x40




#endif

#endif
extern  U8 if_detect_open;

#define GET_BAT_VOL average(ADC_ConvertedValue,CH_BAT_VOL_DETECT_CH1)
void motor_mop_init(void);
machine_speed_s * machine_get_speed_s(U8 action);

extern volatile U8 side_motor_overcurrent_half ;

#define IR_WALL_SIDE_LEFT 1
#define IR_WALL_SIDE_RIGHT 2
extern U8 ir_wall_side;



extern U16 forward_total ;

U8  motor_clear_virtual_wall_record(void);
U8  motor_parse_virtual_wall_record(void);


void ir_flag_set(U16 flag);


#define SIDE_MOTOR_SPEED_1  80

#define SIDE_MOTOR_SPEED_2  100

#define SIDE_MOTOR_SPEED_3  120


#define SIDE_MOTOR_OVERFLOW1 0x1c

#define SIDE_MOTOR_OVERFLOW2  0x1e

#define SIDE_MOTOR_OVERFLOW 0x20


extern U8 global_side_speed;

void side_motor_down_speed(void);
void side_motor_up_speed(void);

U8 motor_deal_with_detect_distance_event(void);



#define KL_DELTA(a, b ) (((a)>(b))?((a)-(b)):((b)-(a)))


extern U8 turn_center_offset;

extern U8 maybe_capert ;


void right_motor_speed_change(U8 direction, U16 speed);
void left_motor_speed_change(U8 direction, U16 speed);


#define RIGHT_LOST_MAX_COUNT   15
#define RIGHT_LOST_MAX_COUNT1   20

#define RIGHT_LOST_MAX_COUNT2    40
extern volatile U32 right_lost_max_count;

#endif  /* __MOTOR_H__*/







