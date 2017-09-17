#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include "config.h"

typedef struct{
	volatile double x;
	volatile double y;
	volatile u32 site_odoleft;
	volatile U32 site_odoright;
	volatile float angle;
	volatile float aim_angle;
	volatile int direction;
	volatile int base_angle;
	volatile u8 run;
	volatile u8 run_old;
	volatile u8 state;
}Car_base;
typedef struct{
	u16 speed;
	u16 left_speed;
	u16 right_speed;
	float motor_speed;
	
	
	float step;
	u32 distance;
	
	
	float radius;
	volatile float angle;
	volatile signed char direction;

	u32 odoleft;
	u32 odoright;
	u32 odoleftabs;
	u32 odorightabs;
	u32 odoleftabs_old;
	u32 odorightabs_old;
}Car_state;

typedef enum
{

	ok=0,
	error=1,
	middle_click=2,
	left_click=3,
	right_click=4,
	overflow_error=5,
	hor_left_error=6,
	hor_leftmid_error=7,
	hor_middle_error=8,
	hor_rightmid_error=9,
	hor_right_error=10,
	round_ok=11,
	over_time_error=12,
}RETURNERROR;
typedef enum
{
	HOR_LEFT=0,
	HOR_LEFTMID=1,
	HOR_MIDDLE=2,
	HOR_RIGHTMID=3,
	HOR_RIGHT=4,
}HOR;


void Car_limit_detect(void *pdata);
void Car_work(void *pdata);
void sensor_work(void *padata);
void ComTask(void * pdata);
void MapSend(void * pdata);

extern OS_EVENT *StartEvent;



u8 Car_moveX(Car_state car_temp);
u8 Car_turn(Car_state car_temp);
void Move_Back(Car_state car_temp);
void Car_move3step(void);
void update(void);
void stop_motor(Car_state car_state);
u8 thing_round(Car_state state_temp);
u8 Car_move_back(Car_state state_temp);
u8 Car_turn(Car_state state_temp);
void gopoint(float x,float y);


#endif



































