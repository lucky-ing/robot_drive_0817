#ifndef _DETECT_H__
#define _DETECT_H__



#define ADC1_DR_Address    ((u32)0x4001244C)
#define MAX_SAMPLE_CHS 16
#define SAMPLE_PER_CH    12  //  6// 3 //8 //20

#define CHAR_PWM_MAX_THRESHOLD 220
#define CHAR_PWM_MIN_THRESHOLD 10 //50




#define NO_CHARGE_DETECTED 0
#define CHARGE_STATION_DETECTED 1
#define DC_SOCKET_DETECTED 2

#define VIR_CENTER 0x26a5
#define VIR_SIDE   0x26a5
//#endif

#if 0

#define CHAR_STA_TOP_MASK 0xa55
#define CHAR_STA_LEFT_MASK  0x655
#define CHAR_STA_MID_MASK 0x555
#define CHAR_STA_RIGHT_MASk 0x955
#define VIR_CENTER_MASK  0x2a5
#define ALL_MASK 0xfff




#define CHAR_STA_TOP 0x6a55
#define CHAR_STA_LEFT  0x2655
#define CHAR_STA_MID  0x1555
#define CHAR_STA_RIGHT 0x2955


#define CHAR_STA_MID_NEAR 0x5555
#define CHAR_STA_LEFT_NEAR 0x1655
#define CHAR_STA_RIGHT_NEAR 0x1955
#endif

#if 1

#define CHAR_STA_TOP_MASK 0xa55
#define CHAR_STA_RIGHT_MASK  0x655
#define CHAR_STA_MID_MASK 0x555
#define CHAR_STA_LEFT_MASK 0x955
#define VIR_CENTER_MASK  0x2a5
#define ALL_MASK 0xfff




#define CHAR_STA_RIGHT 	0xFA
#define CHAR_STA_LEFT	0xF5


#define CHAR_STA_TOP 0xFF

#define CHAR_STA_MID  0x1555


#define CHAR_STA_MID_NEAR 0x5555
#define CHAR_STA_RIGHT_NEAR 0x1655
#define CHAR_STA_LEFT_NEAR 0x1955


#endif


#define drop_detect_disable() GPIO_WriteBit(GPIOE,  GPIO_Pin_8, Bit_SET)
#define drop_detect_enable() GPIO_WriteBit(GPIOE,  GPIO_Pin_8, Bit_RESET)


#define hor_detect_disable() GPIO_WriteBit(GPIOB,  GPIO_Pin_14, Bit_SET)
#define hor_detect_enable() GPIO_WriteBit(GPIOB,  GPIO_Pin_14, Bit_RESET)

#define pickup_detect_enable()  GPIO_WriteBit(GPIOD,  GPIO_Pin_2, Bit_RESET)
#define pickup_detect_disable() GPIO_WriteBit(GPIOD,  GPIO_Pin_2, Bit_SET)

#define rf_receive_enable() GPIO_WriteBit(GPIOB,  GPIO_Pin_15, Bit_RESET)
#define rf_receive_disable() GPIO_WriteBit(GPIOB,  GPIO_Pin_15, Bit_SET)


#define knock_detect_right()  (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0)
#define knock_detect_left()  (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==0)


#define front_wheel_pickup_detect()  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)

#define right_wheel_pickup_detect() GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1)
#define left_wheel_pickup_detect()   GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12)

#define water_box_pin_detect()   GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7)


#define charge_station_input_detect()  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_14)
#define exteral_voltage_input_detect()  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13)


#define laser_power_enable() GPIO_WriteBit(GPIOB,GPIO_Pin_15, Bit_RESET)
#define laser_power_disable() GPIO_WriteBit(GPIOB,GPIO_Pin_15, Bit_SET) 

#define cmos_power_enable() GPIO_WriteBit(GPIOD,GPIO_Pin_1, Bit_SET)
#define cmos_power_disable() GPIO_WriteBit(GPIOD,GPIO_Pin_1, Bit_RESET) 

#define buzzer_enable()  GPIO_WriteBit(GPIOD,GPIO_Pin_11,Bit_SET)
#define buzzer_disable()  GPIO_WriteBit(GPIOD,GPIO_Pin_11,Bit_RESET)

#define speed_detect_enable() GPIO_WriteBit(GPIOD, GPIO_Pin_2, Bit_RESET)


#define tank_present_detect() GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7)

void speed_measure_ext_configure_init(U8 channel);
//void speed_measure_ext_configure1(U8 channel,U8 open);
typedef enum{

 CH_BAT_VOL_DETECT_CH1 = 1,
 CH_RIGHT_DROP_DETECT_CH2,
 CH_LEFT_DROP_DETECT_CH3,

 CH_MID_DROP_DETECT_CH4,


 CH_HOR_LEFT_DETECT_CH5,
 

 CH_RIGHT_SIDE_MOTOR_CURRENT_CH6,
	CH_HOR_M_DETECT_CH7,

 CH_HOR_ML_DETECT_CH8,


 CH_LEFT_SIDE_MOTOR_CURRENT_CH9,

 CH_HOR_MR_DETECT_CH10,
 
 CH_MAIN_MOTOR_CH11,
 CH_DUST_AB_CH12,
 CH_L_MOTOR_CH13,
 CH_R_MOTOR_CH14,

 CH_HOR_RIGHT_DETECT_15,
 

 CH_FRONT_WHEEL_DETECT_16,
 




}adc_ch;


typedef enum{
	EVENT_START_PASSBY=1,
	EVENT_CLEAN_STOP,
	EVENT_CYCLE_CLEAN,
	EVENT_CORNOR_CLEAN,
	EVENT_DOCKING_START,
	EVENT_DOCKING_STOP,
	EVENT_STEP_FORWARD,
	EVENT_STEP_BACKWARD,
	EVENT_STEP_LEFT,
	EVENT_STEP_RIGHT,
	EVENT_FRONT_WHEEL_PICKUP,
	EVENT_LEFT_WHEEL_PICKUP,
	EVENT_RIGHT_WHEEL_PICKUP,
	EVENT_LEFT_KNOCKED,
	EVENT_RIGHT_KNOCKED,
	EVENT_RF_MIDDLE_DETECT,
	EVENT_RF_LEFT_DETECT,
	EVENT_RF_RIGHT_DETECT,
	EVENT_RF_M_LEFT_DETECT,
	EVENT_RF_M_RIGHT_DETECT,
	EVENT_MAIN_MOTOR_OVERFLOW,
	EVENT_SIDE_MOTOR_OVERFLOW,
	EVENT_DUST_AB_OVERFLOW,
	EVENT_RIGHT_MOTOR_OVERFLOW,
	EVENT_LEFT_MOTOR_OVERFLOW,
	EVENT_LEFT_DETECT_VIRTUAL_WALL,
	EVENT_RIGHT_DETECT_VIRTUAL_WALL,
	EVENT_TOP_DETECT_VIRTUAL_WALL,
	EVENT_FRONT_DETECT_VIRTUAL_WALL,
	EVENT_LEFT_DETECT_DOCKING,
	EVENT_TOP_DETECT_DOCKING,
	EVENT_RIGHT_DETECT_DOCKING,
	EVENT_FRONT_DETECT_DOCKING,
	EVENT_MOTOR_SPEED_1,
	EVENT_MOTOR_SPEED_2,
	EVENT_DOCKING_STATION_CONNECT,
	EVENT_DOCKING_STATION_DISCONNECT,
	EVENT_LEFT_DORP,
	EVENT_RIGHT_DROP,
	EVENT_MR_DROP,
	EVENT_ML_DROP,
}detect_event ;
struct event_mail{
	U16 type;
	U16 data;

};


u16 average(vu16 ADCDataTab[], u16 nChannel) ;
void DETECT_GPIO_Config(void);
void ir_recv_ext_config(U8 channel,U8 Enable);
void startup_buzzer_ring(void);
void detect_init(void);
U8 dc_socket_detect(void);
void detect_close(void);
void detect_open(void);

void speed_measure_ext_configure(U8 channel,U8 open);
int wdg_init(void);
void dtd_adc_init(void);
void dtd_adc_open(void);
void dtd_adc_close(void);
//void short_buzzer_ring(void);
void poll_ir_receiver(U8 *mid_l,U8 *mid_r,U8 *right,U8 *left, U8 *right_back, U8 *left_back);
U8  poll_ir_key(void);


void dtd_task_core(void *pdata);
extern OS_EVENT *pDetectValueMail[];


extern vu16 ADC_ConvertedValue[MAX_SAMPLE_CHS*SAMPLE_PER_CH];

#define GET_FRONT_WHEEL_WALK	average(ADC_ConvertedValue,CH_FRONT_WHEEL_DETECT_16)



#ifndef DISABLE_DROP

#define GET_INFRA_DROP_R	average(ADC_ConvertedValue,CH_MID_DROP_DETECT_CH4)
#define GET_INFRA_DROP_L	average(ADC_ConvertedValue,CH_RIGHT_DROP_DETECT_CH2)		
#define GET_INFRA_DROP_M	average(ADC_ConvertedValue,CH_LEFT_DROP_DETECT_CH3)


#else
#define GET_INFRA_DROP_L 	0x800 //average(ADC_ConvertedValue,CH_LEFT_DROP_DETECT_CH4)
#define GET_INFRA_DROP_ML	0x800 //average(ADC_ConvertedValue,CH_RIGH_DROP_DETECT_CH5)
#define GET_INFRA_DROP_MR	0x800 //average(ADC_ConvertedValue,CH_M_RIGHT_DROP_DETECT_CH6)
#define GET_INFRA_DROP_R	0x800 //average(ADC_ConvertedValue,CH_M_LEFT_DROP_DETECT_CH7)	
#endif


#define GET_INFRA_M 	average(ADC_ConvertedValue,CH_HOR_ML_DETECT_CH8)  // right
#define GET_INFRA_ML	average(ADC_ConvertedValue,CH_HOR_M_DETECT_CH7)
#define GET_INFRA_L		average(ADC_ConvertedValue,CH_HOR_LEFT_DETECT_CH5)	
#define GET_INFRA_MR	average(ADC_ConvertedValue,CH_HOR_RIGHT_DETECT_15)//average(ADC_ConvertedValue,CH_HOR_ML_DETECT_CH6)
#define GET_INFRA_R		average(ADC_ConvertedValue,CH_HOR_MR_DETECT_CH10)


#define GET_MOTOR_CUR_R average(ADC_ConvertedValue,CH_L_MOTOR_CH13)
#define GET_MOTOR_CUR_L average(ADC_ConvertedValue,CH_R_MOTOR_CH14)
#define GET_MAIN_MOTOR_CUR average(ADC_ConvertedValue,CH_DUST_AB_CH12)
#define GET_DUST_MOTOR_CUR average(ADC_ConvertedValue,CH_MAIN_MOTOR_CH11)


#define GET_RIGHT_SIDE_CURRENT average(ADC_ConvertedValue,CH_LEFT_SIDE_MOTOR_CURRENT_CH9)
#define GET_LEFT_SIDE_CURRENT average(ADC_ConvertedValue,CH_RIGHT_SIDE_MOTOR_CURRENT_CH6)
extern volatile U32 last_virtual_wall_ostime;


extern volatile U8 dust_detected;

#define GET_FRONT_WHEEL_AD average(ADC_ConvertedValue,CH_FRONT_WHEEL_DETECT_16)


#define MID_R_NEAR_CHG 			1
#define MID_L_NEAR_CHG 			2

#define LEFT_NEAR_CHG 			3
#define RIGHT_NEAR_CHG 			4
#define LEFT_BACK_NEAR_CHG 		5
#define RIGHT_BACK_NEAR_CHG		6



U8 poll_if_near_chg(void);

typedef struct {
	U8 press_key_ok;
	U8 press_key[4];   // 0: left, 1:mid, 2:right; 3: down;
	U8 mid_motor_ok;
	U8 mid_motor_current;
	U8 left_motor_ok;
	U8 left_motor_current;
	U8 left_motor_speed;
	U8 left_motor_pickup[2];


	U8 left_knock[2];
	U8 right_knock[2];
	U8 left_knock_ok;
	U8 right_knock_ok;
	
	
	U8 left_motor_pickup_ok ;
	U8 right_motor_ok;
	U8 right_motor_current;
	U8 right_motor_speed;
	U8 right_motor_pickup[2];
	U8 right_motor_pickup_ok;
	U8 dust_motor_ok;
	U8 dust_motor_current;
	U8 side_motor_ok;
	U8 side_motor_current;
	U8 left_side_motor_current;
	U8 uv_ok;
	U8 uv_current;
	U8 hor_distance_detect_ok;
	U8 hor_left_ok;
	U8 hor_right_ok;
	U8 hor_mid_ok;
	U8 hor_mid_right_ok;
	U8 hor_mid_left_ok;
	U8 hor_infra_signal_ok;
	U8 hor_infra_left_ok;
	U8 hor_infra_right_ok;
	U8 hor_infra_mid_ok;
	U8 hor_infra_top_ok;
	U8 hor_knock_ok;
	U8 hor_knock_left_ok[2];
	U8 hor_knock_right_ok[2];
	U8 vertical_ok;
	U8 vertical_left_ok;
	U8 vertical_right_ok;
	U8 vertical_mid_left_ok;
	U8 vertical_mid_right_ok;
	U8 remote_control_ok;
	U8 charge_ok;
	U16 charge_current_ok;
	U16 charge_voltage_ok;

}ate_test_result_t;



#endif



