#include "config.h"
#define STEPLENTH 400//1600
#define ANGLELENTH 20//1620
#define RADIULETH 573.0f
#define HOR_LEFT_THRESHOLD 50
#define HOR_LEFTMID_THRESHOLD 100 
#define HOR_MIDDLE_THRESHOLD 210 
#define HOR_RIGHTMID_THRESHOLD 100
#define HOR_RIGHT_THRESHOLD 50
#define HOR_THRESHOLD 60
#define RUN_MOVE 1
#define RUN_TURN 2
#define RUN_ROUND 3
#define RUN_BACK 4
//u8 map[200][200]={0};
//#define abs(a) (a>0?a:-a)
uchar LineSpeed=150;
uchar TurnSpeed=130;
uchar roundspeed=130;
Car_base Car={0};
OS_EVENT 	*StartEvent=0;
OS_EVENT 	*ComEvent=0;
#define LEFTERROR ((Car.state&0x04)!=0x00)
#define RIGHTERROR ((Car.state&0x02)!=0x00)

//CAR_STATE
/*
0	0	0		0			0				0			0		0	B
			TIMEOVER	OVERFLOWERROR	LEFTERROR	RIGHTERROR	STOP
*/
char ask=0x03;
extern volatile U8 emu_key_state ;
extern volatile U8 emu_key ;
volatile char senddata[14]={0};
volatile int hordata[5]={0};
volatile char limit_msg=0x00;
void Car_limit_detect(void *pdata)
{
	char key=0;
	
	char limit_msg_old=0x02;
	
	while(1)
	{
		if (knock_detect_right()  && knock_detect_left() )
		{

			limit_msg=0x32;
			Car.state|=0x06;
			
		}
		else
			if(knock_detect_right())
			{
				
				limit_msg=0x12;
				Car.state&=0xf9;
				Car.state|=0x02;
			}
			else
				if(knock_detect_left())
				{
					limit_msg=0x22;
					Car.state&=0xf9;
					Car.state|=0x04;
				}
				else
				{
					limit_msg=0x02;
					Car.state&=0xf9;
				}

		if (limit_msg!=limit_msg_old)
		{
			
			limit_msg_old=limit_msg;
			if(limit_msg!=0x02)
			{
				OSSemPost(ComEvent);
			}
		}
		OSTimeDlyHMSM(0,0,0,5);
			
	}
}


u8 Car_move(Car_state task_temp)
{
	
	static float KP=7,KI=0.01,KD=0;
	char i=0;
	int odoerror_int=0;
	int odoleft_temp=0;
	int odoright_temp=0;
	float kip=1,kii=0;
	int odoerror=0;
	int odoerror_old=0;
	Car.direction=task_temp.direction;
	if(task_temp.direction==-1 )
	{
		Car.aim_angle=Car.angle;
		return Car_move_back(task_temp);
	}
	Car.aim_angle=task_temp.angle;
	if (Car.aim_angle>180)
		Car.aim_angle-=360;
	if (Car.aim_angle<-180)
		Car.aim_angle+=360;
	task_temp.distance=(u32)((u32)task_temp.step*STEPLENTH*2);
	task_temp.odoleftabs=0;
	//Car.state=0;
	task_temp.odorightabs=0;
	task_temp.odoleftabs_old=0;
	task_temp.odorightabs_old=0;
	task_temp.odoleft=l_int_finish;
	task_temp.odoright=r_int_finish;
	//angle_temp=Car.angle;
	
	left_motor_stop(&motor_global_setting);
	right_motor_stop(&motor_global_setting);
	Car.run_old=Car.run;
	Car.run=RUN_MOVE;
	
	while(task_temp.odoleftabs+task_temp.odorightabs<task_temp.distance&&Car.state==0)
	{
		odoerror=Car.angle-Car.aim_angle;
		if((Car.aim_angle>0)!=(Car.angle>0))
		{
			if((fabs(Car.aim_angle)>150 )&& (fabs(Car.angle)>150))
			{

				if ((int)Car.angle<-150)
				{
					odoerror=360-fabs((int)Car.aim_angle)-fabs(Car.angle);
				}
				if ((int)Car.angle>150)
				{
					odoerror=fabs((int)Car.aim_angle)+fabs(Car.angle)-360;
				}
			}
		}
		task_temp.motor_speed=odoerror*KP+(float)odoerror_int*KI;
		if((odoerror>0)!=(odoerror_old>0))
			odoerror_int=0;
		odoerror_old=odoerror;
		odoerror_int+=odoerror;
		if (odoerror_int>2000)
			odoerror_int=2000;
		if (odoerror_int<-2000)
			odoerror_int=-2000;
		
		task_temp.left_speed=task_temp.speed-task_temp.motor_speed;
		task_temp.right_speed=task_temp.speed+task_temp.motor_speed;
		if (task_temp.left_speed<30)
			task_temp.left_speed=30;
		if(task_temp.left_speed>200)
			task_temp.left_speed=200;
		if (task_temp.right_speed<30)
			task_temp.right_speed=30;
		if(task_temp.right_speed>200)
			task_temp.right_speed=200;

		if (task_temp.direction==1)
		{
			left_motor_forward(&motor_global_setting,task_temp.left_speed);
			right_motor_forward(&motor_global_setting,task_temp.right_speed);
		}

		OSTimeDlyHMSM(0,0,0,20);
		task_temp.odoleftabs=l_int_finish-task_temp.odoleft;
		task_temp.odorightabs=r_int_finish-task_temp.odoright;
		
		if (hordata[HOR_MIDDLE]>HOR_MIDDLE_THRESHOLD)
		{
			left_motor_stop(&motor_global_setting);
			right_motor_stop(&motor_global_setting);
			OSTimeDlyHMSM(0,0,0,5);
			Car.run=Car.run_old;
			return hor_middle_error;
		}
		if (hordata[HOR_LEFTMID]>HOR_LEFTMID_THRESHOLD)
		{
			left_motor_stop(&motor_global_setting);
			right_motor_stop(&motor_global_setting);
			OSTimeDlyHMSM(0,0,0,5);
			Car.run=Car.run_old;
			return hor_leftmid_error;
		}
		if (hordata[HOR_RIGHTMID]>HOR_RIGHTMID_THRESHOLD)
		{
			left_motor_stop(&motor_global_setting);
			right_motor_stop(&motor_global_setting);
			OSTimeDlyHMSM(0,0,0,5);
			Car.run=Car.run_old;
			return hor_rightmid_error;
		}
		
	}
	if (Car.state==0)
		{
			Car.run=Car.run_old;
			return ok;
		}
		else
		{

			left_motor_stop(&motor_global_setting);
			right_motor_stop(&motor_global_setting);
			Car.run=Car.run_old;
			if(Car.state&0x04)
				return left_click;
			else
				if(Car.state&0x02)
					return right_click;
				else
					if(Car.state&0x08)
						return overflow_error;
					else
						return error;
		}
	Car.run=Car.run_old;
	return ok;
	
}



u8 Car_move_back(Car_state task_temp)
{
	
	static float KP=3,KI=0.01,KD=0;
	char i=0;
	int odoerror_int=0;
	int odoleft_temp=0;
	int odoright_temp=0;
	float kip=1,kii=0;
	int odoerror=0;
	int odoerror_old=0;

	

	task_temp.distance=(int)(task_temp.step*STEPLENTH*2);
	task_temp.odoleftabs=0;
	task_temp.odorightabs=0;
	task_temp.odoleftabs_old=0;
	task_temp.odorightabs_old=0;
	task_temp.odoleft=l_int_finish;
	task_temp.odoright=r_int_finish;

	left_motor_stop(&motor_global_setting);
	right_motor_stop(&motor_global_setting);
	Car.run_old=Car.run;
	Car.run=RUN_BACK;
	while(task_temp.odoleftabs+task_temp.odorightabs<task_temp.distance)
	{

		odoerror=Car.aim_angle-Car.angle;
		if((Car.aim_angle>0)!=(Car.angle>0))
		{
			if((abs(Car.aim_angle)>150 )&& (abs(Car.angle)>150))
			{

				if (Car.angle>150)
				{
					odoerror=360-abs(Car.aim_angle)-abs(Car.angle);
				}
				if (Car.angle<-150)
				{
					odoerror=abs(Car.aim_angle)+abs(Car.angle)-360;
				}
			}
		}
		task_temp.motor_speed=odoerror*KP+(float)odoerror_int*KI;//+(odoerror-odoerror_old)*KD
		if((odoerror>0)!=(odoerror_old>0))
			odoerror_int=0;
		odoerror_old=odoerror;
		odoerror_int+=odoerror;
		if (odoerror_int>1000)
			odoerror_int=1000;
		if (odoerror_int<-1000)
			odoerror_int=-1000;
		
		task_temp.left_speed=task_temp.speed-task_temp.motor_speed;
		task_temp.right_speed=task_temp.speed+task_temp.motor_speed;
		if (task_temp.left_speed<30)
			task_temp.left_speed=30;
		if(task_temp.left_speed>200)
			task_temp.left_speed=200;
		if (task_temp.right_speed<30)
			task_temp.right_speed=30;
		if(task_temp.right_speed>200)
			task_temp.right_speed=200;
		left_motor_backward(&motor_global_setting,task_temp.left_speed);
		right_motor_backward(&motor_global_setting,task_temp.right_speed);	
		
		OSTimeDlyHMSM(0,0,0,20);
		task_temp.odoleftabs=l_int_finish-task_temp.odoleft;
		task_temp.odorightabs=r_int_finish-task_temp.odoright;	
	}
	Car.run=Car.run_old;
	return ok;
}

u8 Car_turnX(Car_state task_temp)
{
	static float KP=1,KI=0,KD=0;
	static int odoerror_int=0;
	char i=0;
	int odoleft_temp=0;
	int odoright_temp=0;
	int odoerror=0;
	int odoerror_old=0;
	task_temp.odoleftabs=0;
	task_temp.odorightabs=0;
	task_temp.odoleftabs_old=0;
	task_temp.odorightabs_old=0;
	task_temp.odoleft=l_int_finish;
	task_temp.odoright=r_int_finish;
	Car.aim_angle=task_temp.angle+Car.angle;
	task_temp.distance=ANGLELENTH*task_temp.angle;
	left_motor_stop(&motor_global_setting);
	right_motor_stop(&motor_global_setting);
	Car.run_old=Car.run;
	Car.run=RUN_TURN;

	while(task_temp.odoleftabs+task_temp.odorightabs<task_temp.distance && Car.state==0)
	{
		
		odoleft_temp=task_temp.odoleftabs-task_temp.odoleftabs_old;
		odoright_temp=task_temp.odorightabs-task_temp.odorightabs_old;
		task_temp.odoleftabs_old=task_temp.odoleftabs;
		task_temp.odorightabs_old=task_temp.odorightabs;
		odoerror=odoleft_temp-odoright_temp;
		task_temp.motor_speed=odoerror*KP+odoerror_int*KI+(odoerror-odoerror_old)*KD;
		odoerror_old=odoerror;
		odoerror_int+=odoerror;
		if (odoerror_int>10000)
			odoerror_int=10000;
		if (odoerror_int<-10000)
			odoerror_int=-10000;
		task_temp.left_speed=task_temp.speed-task_temp.motor_speed;
		task_temp.right_speed=task_temp.speed+task_temp.motor_speed;
		if (task_temp.left_speed<30)
			task_temp.left_speed=30;
		if(task_temp.left_speed>200)
			task_temp.left_speed=200;
		if (task_temp.right_speed<30)
			task_temp.right_speed=30;
		if(task_temp.right_speed>200)
			task_temp.right_speed=200;
		//printf("direction!%d",task_temp.direction);
		if (task_temp.direction==1)
		{
			left_motor_forward(&motor_global_setting,task_temp.left_speed);
			right_motor_backward(&motor_global_setting,task_temp.right_speed);
		}
		if (task_temp.direction==-1)
		{
			left_motor_backward(&motor_global_setting,task_temp.left_speed);
			right_motor_forward(&motor_global_setting,task_temp.right_speed);
		}	

		OSTimeDlyHMSM(0,0,0,20);
		task_temp.odoleftabs=l_int_finish-task_temp.odoleft;
		task_temp.odorightabs=r_int_finish-task_temp.odoright;
	}
	left_motor_stop(&motor_global_setting);
	right_motor_stop(&motor_global_setting);
	Car.run=Car.run_old;
	return ok;
}

u8 Car_turn(Car_state task_temp)
{
	static float KP=1,KI=0,KD=0;
	static int odoerror_int=0;
	char i=0;
	int odoleft_temp=0;
	int odoright_temp=0;
	int odoerror=0;
	int odoerror_old=0;
	float angle_temp=0.0;
	task_temp.odoleftabs=0;
	task_temp.odorightabs=0;
	task_temp.odoleftabs_old=0;
	task_temp.odorightabs_old=0;
	task_temp.odoleft=l_int_finish;
	task_temp.odoright=r_int_finish;
	if(task_temp.angle>180.0)
		task_temp.angle-=360.0;
	if(task_temp.angle<=-180.0)
		task_temp.angle+=360.0;
	Car.aim_angle=task_temp.angle;
	angle_temp=task_temp.angle-Car.angle;
	if (angle_temp>0)
	{
		if(fabs(angle_temp)<180.0)
			task_temp.direction=1;
		else
			task_temp.direction=-1;
	}
	else
	{
		if(fabs(angle_temp)<180.0)
			task_temp.direction=-1;
		else
			task_temp.direction=1;
	}
	Car.run_old=Car.run;
	Car.run=RUN_TURN;
	task_temp.distance=ANGLELENTH*angle_temp;
	left_motor_stop(&motor_global_setting);
	right_motor_stop(&motor_global_setting);

	while( Car.state==0)
	{
		if ((fabs(task_temp.angle-Car.angle)<4.0||fabs(task_temp.angle-Car.angle)>356.0))
		{
			Car.run=Car.run_old;
			left_motor_stop(&motor_global_setting);
			right_motor_stop(&motor_global_setting);
			break;
		}
		odoleft_temp=task_temp.odoleftabs-task_temp.odoleftabs_old;
		odoright_temp=task_temp.odorightabs-task_temp.odorightabs_old;
		task_temp.odoleftabs_old=task_temp.odoleftabs;
		task_temp.odorightabs_old=task_temp.odorightabs;
		odoerror=odoleft_temp-odoright_temp;
		task_temp.motor_speed=odoerror*KP+odoerror_int*KI+(odoerror-odoerror_old)*KD;
		odoerror_old=odoerror;
		odoerror_int+=odoerror;
		if (odoerror_int>10000)
			odoerror_int=10000;
		if (odoerror_int<-10000)
			odoerror_int=-10000;
		task_temp.left_speed=task_temp.speed-task_temp.motor_speed;
		task_temp.right_speed=task_temp.speed+task_temp.motor_speed;
		if (task_temp.left_speed<30)
			task_temp.left_speed=30;
		if(task_temp.left_speed>200)
			task_temp.left_speed=200;
		if (task_temp.right_speed<30)
			task_temp.right_speed=30;
		if(task_temp.right_speed>200)
			task_temp.right_speed=200;

		if (task_temp.direction==1)
		{
			left_motor_forward(&motor_global_setting,task_temp.left_speed);
			right_motor_backward(&motor_global_setting,task_temp.right_speed);
		}
		if (task_temp.direction==-1)
		{
			left_motor_backward(&motor_global_setting,task_temp.left_speed);
			right_motor_forward(&motor_global_setting,task_temp.right_speed);
		}	
		OSTimeDlyHMSM(0,0,0,20);
		task_temp.odoleftabs=l_int_finish-task_temp.odoleft;
		task_temp.odorightabs=r_int_finish-task_temp.odoright;
	}
	left_motor_stop(&motor_global_setting);
	right_motor_stop(&motor_global_setting);
	Car.run=Car.run_old;
	return ok;
}










void Car_work(void *pdata)
{
	char key=0,i=0,msg=0;
	u8 err;
	Car_state task_main={0};
	Car_state task_temp={0};
	task_main.speed=LineSpeed;
	left_motor_stop(&motor_global_setting);
	right_motor_stop(&motor_global_setting);
	speed_measure_ext_configure(1,1);	
	speed_measure_ext_configure(0,1);
	task_main.direction=1;
	task_main.step=100;
	Car.base_angle=0;
	while(1)
	{
		
		OSSemPend((OS_EVENT *)StartEvent,0,&err);
		while(1)
		{
			Car.state=0;
			task_temp.speed=TurnSpeed;
			task_temp.direction=1;
			task_temp.angle=task_main.direction*(-90)+90;
			Car_turn(task_temp);
			task_temp.speed=LineSpeed;
			task_temp.direction=1;
			task_temp.step=150;
			task_temp.angle=task_main.direction*(-90)+90;
			msg=Car_move(task_temp);
			Car.run=0;
			if (msg!=ok)
			{
				if(msg>=2&&msg<=5)
				{
					task_temp.direction=-1;
					task_temp.step=0.5;
					task_temp.angle=Car.angle;
					Car_move(task_temp);
				}
				task_temp.angle=Car.angle;
				i=0;

				if(Car.base_angle==0)
				{
					if (task_main.direction==1)
					{
						while(hordata[0]<50)
						{
							i++;
							task_temp.speed=TurnSpeed;
							task_temp.angle+=task_main.direction*15;
							msg=Car_turn(task_temp);
							if(i>4)
								break;
						}
					}
					else
					{
						while(hordata[4]<50)
						{
							i++;
							task_temp.speed=TurnSpeed;
							task_temp.angle+=task_main.direction*15;
							msg=Car_turn(task_temp);
							if(i>4)
								break;
						}
					}
					task_temp.direction=task_main.direction;
				}
				else
					if(Car.base_angle==180)
					{
						if (task_main.direction==-1)
						{
							while(hordata[0]<50)
							{
								i++;
								task_temp.speed=TurnSpeed;
								task_temp.angle-=task_main.direction*15;
								msg=Car_turn(task_temp);
								if(i>4)
									break;
							}
						}
						else
						{
							while(hordata[4]<50)
							{
								i++;
								task_temp.speed=TurnSpeed;
								task_temp.angle-=task_main.direction*15;
								msg=Car_turn(task_temp);
								if(i>4)
									break;
							}
						}
						task_temp.direction=-task_main.direction;
					}
				task_temp.speed=roundspeed;
				msg=thing_round(task_temp);
				if(msg==round_ok)
				{
					task_temp.angle=task_main.direction*90-90;
					msg=Car_turn(task_temp);

					continue;
				}
				if(msg==over_time_error)
				{
					OSTaskSuspend(OS_MAP_TASK_PRIO);
					OSTimeDlyHMSM(0,0,0,200);
					msg=0x11;
					USART_SendChar(USART1,&(msg));
					OSTimeDlyHMSM(0,0,0,200);
					break;
				}
				Car.run=0;
				OSTimeDlyHMSM(0,0,0,200);
			}
			else
			{
				task_temp.speed=TurnSpeed;
				task_temp.direction=task_main.direction;
				task_temp.angle=Car.angle+task_main.direction*90+Car.base_angle;
				msg=Car_turn(task_temp);
				Car.run=0;
				task_temp.speed=LineSpeed;
				task_temp.direction=1;
				task_temp.step=3;
				task_temp.angle=Car.angle;
				msg=Car_move(task_temp);
				Car.run=0;
				OSTimeDlyHMSM(0,0,0,200);
			}
			task_main.direction=-task_main.direction;
		}
	}
}




void sensor_work(void *padata)
{
	int i=0,timeover=0;
	double theta=0.0,radiu=0.0,delta_x=0.0,delta_y=0.0,length=0.0;
	int odo_left=0;
	int odo_right=0;
	float angle_old=0.0;
	char key=0,t=0;
	float pitch,roll,yaw;
	float pitch0=0.0,roll0=0.0,yaw0=0.0;
	U16 l_0,ml_0,mr_0,m_0,r_0;
	U16 l_1, ml_1, mr_1,m_1,r_1;
	Car.site_odoleft=r_int_finish;
	Car.site_odoright=l_int_finish;
	senddata[0]=0x01;
	while(MPU_Init())
	{
		t=0;
	}
	OSTimeDlyHMSM(0,0,0,50);
	while(mpu_dmp_init())
	{
		t=0;
	}
	OSTimeDlyHMSM(0,0,5,0);
	while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0)
		OSTimeDlyHMSM(0,0,0,1);
	yaw0=-yaw;
	angle_old=yaw0;
	pitch0=pitch;
	roll0=roll;
	OSSemPost(StartEvent);
	hor_detect_disable();
	while(1)
	{
		OSTimeDlyHMSM(0,0,0,5);
		
		if(1)
		{
			while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0)
				OSTimeDlyHMSM(0,0,0,1);
			Car.angle=(double)(-yaw-yaw0);
			if (Car.angle>180.0)
			{
				Car.angle-=360.0;
			}
			if (Car.angle<-180.0)
			{
				Car.angle+=360.0;
			}
			if(abs(pitch-pitch0)>8||abs(roll-roll0)>8)
			{
				Car.state|=0x08;			
			}
			else
			{
				Car.state&=0xf7;
			}
		}
		
		if(Car.run!=0&&t%3==0)
		{
			odo_left=l_int_finish-Car.site_odoleft;
			odo_right=r_int_finish-Car.site_odoright;
			Car.site_odoleft=l_int_finish;
			Car.site_odoright=r_int_finish;
			
			delta_x=0.0;
			delta_y=0.0;
			if(Car.run==RUN_MOVE)
			{
				if(Car.direction==1)
				{
					delta_x=sin((Car.angle+angle_old)/57.294/2.0)*(odo_right+odo_left)/2.0/STEPLENTH;
					delta_y=cos((Car.angle+angle_old)/57.294/2.0)*(odo_right+odo_left)/2.0/STEPLENTH;
				}
				else
				{
					delta_x=-sin((Car.angle+angle_old)/57.294/2.0)*(odo_right+odo_left)/2.0/STEPLENTH;
					delta_y=-cos((Car.angle+angle_old)/57.294/2.0)*(odo_right+odo_left)/2.0/STEPLENTH;
				}
			}
			if(Car.run==RUN_BACK)
			{
				delta_x=-sin((Car.angle+angle_old)/57.294/2.0)*(odo_right+odo_left)/2.0/STEPLENTH;
				delta_y=-cos((Car.angle+angle_old)/57.294/2.0)*(odo_right+odo_left)/2.0/STEPLENTH;
			}
			if(Car.run==RUN_ROUND)
			{
				theta=Car.angle-angle_old;
				
				if (fabs(theta)>0.1)
				{
					radiu=(odo_right+odo_left)*57.294/2.0/theta;
					length=radiu*sin(theta/114.5914)*2/STEPLENTH;
					length=fabs(length);
					delta_y=length*cos((Car.angle+angle_old)/57.294/2.0);
					delta_x=length*sin((Car.angle+angle_old)/57.294/2.0);
				}
				else
				{
						delta_x=sin((Car.angle+angle_old)/57.294/2.0)*(odo_right+odo_left)/2.0/STEPLENTH;
						delta_y=cos((Car.angle+angle_old)/57.294/2.0)*(odo_right+odo_left)/2.0/STEPLENTH;
				}
			}
			angle_old=Car.angle;
			Car.x+=(float)delta_x;
			Car.y+=(float)delta_y;
			if(odo_left<=2 && odo_right<=2)
			{
				timeover++;
				if (timeover>50)
				{
					Car.state|=0x10;
					timeover=51;
				}
			}
			else
			{
				timeover=0;
				Car.state&=0xef;
			}
		}

		t++;
		if((t%2==0)&&(t%4!=0))
		{
			l_0 =  GET_INFRA_L;
			mr_0 = GET_INFRA_MR;
			r_0 =  GET_INFRA_R;
			ml_0 = GET_INFRA_ML;
			m_0 = GET_INFRA_M;
			hor_detect_enable();
		}
		if(t%4==0)
		{
			l_1 = GET_INFRA_L;
			mr_1 = GET_INFRA_MR;
			r_1 = GET_INFRA_R;
			ml_1 = GET_INFRA_ML;
			m_1 =GET_INFRA_M;
			hordata[0]=KL_DELTA(l_0,l_1);
			hordata[1]=KL_DELTA(ml_0,ml_1);
			hordata[2]=KL_DELTA(m_0,m_1);
			hordata[3]=KL_DELTA(mr_0,mr_1);
			hordata[4]=KL_DELTA(r_0,r_1);
			hor_detect_disable();
		}
		if(t>100||t<0)
		{
			t=0;
		}
	}

}
void update(void)
{
	uchar key=0;
	int x=0,y=0;
	float x_temp=0.0,y_temp=0.0;
	static uchar key_old=0,m=0,aa[4]={0};
	if(emu_key_state==1)
	{
		
		key = emu_key ;
		emu_key_state = 0;
		if (key_old!=0)
		{
			switch(key_old)
			{
				case 'G':aa[m]=key;m++;if (m>=4){m=0;if((aa[0]&0x80)!=0)
{aa[0]&=0x7f;x=((int)(aa[0])<<8|(int)aa[1]);x=-x;}
else 
	x=((int)(aa[0])<<8|(int)aa[1]);
if((aa[2]&0x80)!=0)
{aa[2]&=0x7f;y=((int)(aa[2])<<8|(int)aa[3]);y=-y;}
else 
	y=((int)(aa[2])<<8|(int)aa[3]);
x_temp=(float)x;y_temp=(float)y;gopoint(x_temp,y_temp);USART_SendChar(USART1,&ask);key_old=0;}   break;
				case 'F':if (key==0x01) Car.base_angle=0;if(key==0x02) Car.base_angle=180;key_old=0;OSSemPost(StartEvent);OSTaskResume(OS_COM_TASK_PRIO);break;
				default:break;
			}
		}
		else
		{
			if(key=='S')
			{
				Car.state|=0x01;
				USART_SendChar(USART1,&ask);
			}
			else
			{
				m=0;
				key_old=key;
			}
		}
	}
}

void stop_motor(Car_state task_main)
{
	while(1)
	{
		left_motor_stop(&motor_global_setting);
		right_motor_stop(&motor_global_setting);
		OSTimeDlyHMSM(0,0,0,5);
	}
}
u8 thing_round(Car_state task_main)
{
	u16 r=0;
	char msg;
	float hor_old=0.0,hor_temp=0.0,sitex=0.0,sitey=0.0;
	Car_state task_temp={0};
	sitex=Car.x;
	sitey=Car.y;
	Car.run_old=Car.run;
	Car.run=RUN_ROUND;

	while(1)
	{
		r++;		
		if(task_main.direction==1)
		{
			hor_temp=hordata[0];
			task_main.motor_speed=(hor_temp-HOR_THRESHOLD)*2.0+(hor_old-hor_temp)*0.5;
			hor_old=hor_temp;
			if (task_main.motor_speed>60.0)
				task_main.motor_speed=60.0;
			if (task_main.motor_speed<-60.0)
				task_main.motor_speed=-60.0;
			task_main.left_speed=task_main.speed+task_main.motor_speed;
			task_main.right_speed=task_main.speed-task_main.motor_speed;
			left_motor_forward(&motor_global_setting,(int)(task_main.left_speed));
			right_motor_forward(&motor_global_setting,(int)(task_main.right_speed));

			OSTimeDlyHMSM(0,0,0,5);
			
			if(hordata[HOR_RIGHT]>HOR_THRESHOLD+10)
			{

				OSTimeDlyHMSM(0,0,0,100);
				task_temp.direction=task_main.direction;
				task_temp.speed=TurnSpeed;
				task_temp.angle=120+Car.angle;
				msg=Car_turn(task_temp);

			}
			if(hordata[HOR_LEFTMID]>HOR_THRESHOLD+60)
			{

				OSTimeDlyHMSM(0,0,0,100);
				task_temp.direction=task_main.direction;
				task_temp.speed=TurnSpeed;
				task_temp.angle=30+Car.angle;
				msg=Car_turn(task_temp);

			}
			if(hordata[HOR_MIDDLE]>HOR_THRESHOLD+160)
			{

				OSTimeDlyHMSM(0,0,0,100);
				task_temp.direction=task_main.direction;
				task_temp.speed=TurnSpeed;
				task_temp.angle=60+Car.angle;
				msg=Car_turn(task_temp);

			}
			if(hordata[HOR_RIGHTMID]>HOR_THRESHOLD+60)
			{

				OSTimeDlyHMSM(0,0,0,100);
				task_temp.direction=task_main.direction;
				task_temp.speed=TurnSpeed;
				task_temp.angle=90+Car.angle;
				msg=Car_turn(task_temp);

			}
		}
		else
		{
			hor_temp=hordata[4];
			task_main.motor_speed=(hor_temp-HOR_THRESHOLD)*2.0+(hor_old-hor_temp)*0.5;
			hor_old=hor_temp;
			if (task_main.motor_speed>60.0)
				task_main.motor_speed=60.0;
			if (task_main.motor_speed<-60.0)
				task_main.motor_speed=-60.0;
			task_main.left_speed=task_main.speed-task_main.motor_speed;
			task_main.right_speed=task_main.speed+task_main.motor_speed;
			left_motor_forward(&motor_global_setting,(int)(task_main.left_speed));
			right_motor_forward(&motor_global_setting,(int)(task_main.right_speed));
			OSTimeDlyHMSM(0,0,0,5);
			//printf("direction ooo\n");
			if(hordata[HOR_LEFT]>HOR_THRESHOLD+10)
			{

				OSTimeDlyHMSM(0,0,0,100);
				task_temp.angle=Car.angle-120;
				task_temp.speed=TurnSpeed;
				msg=Car_turn(task_temp);

			}
			if(hordata[HOR_LEFTMID]>HOR_THRESHOLD+60)
			{

				OSTimeDlyHMSM(0,0,0,100);
				task_temp.direction=task_main.direction;
				task_temp.speed=TurnSpeed;
				task_temp.angle=Car.angle-90;
				msg=Car_turn(task_temp);

			}
			if(hordata[HOR_MIDDLE]>HOR_THRESHOLD+160)
			{

				OSTimeDlyHMSM(0,0,0,100);
				task_temp.direction=task_main.direction;
				task_temp.speed=TurnSpeed;
				task_temp.angle=Car.angle-60;
				msg=Car_turn(task_temp);

			}
			if(hordata[HOR_RIGHTMID]>HOR_THRESHOLD+60)
			{

				OSTimeDlyHMSM(0,0,0,100);
				task_temp.direction=task_main.direction;
				task_temp.speed=TurnSpeed;
				task_temp.angle=Car.angle-30;
				msg=Car_turn(task_temp);

			}
		}
		if(Car.state!=0)
		{
			if(RIGHTERROR)
			{

				if(task_main.direction==-1)
				{
					while(1)
					{
						task_temp.direction=-1;
						task_temp.step=0.1;
						task_temp.speed=LineSpeed-20;
						Car_move(task_temp);
						OSTimeDlyHMSM(0,0,0,200);
						//task_temp.direction=task_main.direction;
						task_temp.angle=Car.angle-45;
						task_temp.speed=TurnSpeed;
						msg=Car_turn(task_temp);
						if(msg!=ok)
							continue;
						OSTimeDlyHMSM(0,0,0,200);

						break;
					}
				}
				else
				{
					while(1)
					{
						task_temp.direction=-1;
						task_temp.step=0.1;
						task_temp.speed=LineSpeed-20;
						Car_move(task_temp);
						OSTimeDlyHMSM(0,0,0,200);
						//task_temp.direction=task_main.direction;
						task_temp.angle=90+Car.angle;
						task_temp.speed=TurnSpeed;
						msg=Car_turn(task_temp);
						if(msg!=ok)
							continue;
						OSTimeDlyHMSM(0,0,0,200);

						break;
					}
				}
			}
			else
				if(LEFTERROR)
				{
					if(task_main.direction==1)
					{
						while(1)
						{
							task_temp.direction=-1;
							task_temp.step=0.1;
							task_temp.speed=LineSpeed-20;
							Car_move(task_temp);
							OSTimeDlyHMSM(0,0,0,200);
							task_temp.speed=TurnSpeed;
							task_temp.angle=45+Car.angle;
							msg=Car_turn(task_temp);
							if(msg!=ok)
							{
								continue;
							}
							OSTimeDlyHMSM(0,0,0,200);
							break;
						}
					}
					else
					{
						while(1)
						{
							task_temp.direction=-1;
							task_temp.step=0.1;
							task_temp.speed=LineSpeed-20;
							Car_move(task_temp);
							OSTimeDlyHMSM(0,0,0,200);
							task_temp.angle=Car.angle-90;
							task_temp.speed=TurnSpeed;
							msg=Car_turn(task_temp);
							if(msg!=ok)
							{
								continue;
							}
							OSTimeDlyHMSM(0,0,0,200);

							break;
						}
					}
				}
				else
				{
					task_temp.direction=-1;
					task_temp.step=0.5;
					task_temp.speed=LineSpeed-20;
					Car_move(task_temp);
					OSTimeDlyHMSM(0,0,0,200);

					Car.run=Car.run_old;
					return error;
				}
			
		}
		
		if (Car.base_angle==0)
		{
			if((Car.x-sitex)>3.0)
			{
				Car.run=Car.run_old;
				left_motor_stop(&motor_global_setting);
				right_motor_stop(&motor_global_setting);
				return ok;
			}
			if(task_main.direction==1)
			{
				if(fabs(sitex-Car.x)<=0.3&&(Car.y-sitey)>=1.0)
				{
					left_motor_stop(&motor_global_setting);
					right_motor_stop(&motor_global_setting);
					Car.run=Car.run_old;
					return round_ok;
				}
			}
			else
			{
				if(fabs(sitex-Car.x)<=0.3&&(sitey-Car.y)>=1.0)
				{
					left_motor_stop(&motor_global_setting);
					right_motor_stop(&motor_global_setting);
					Car.run=Car.run_old;
					return round_ok;
				}
			}
		}
		if (Car.base_angle==180)
		{
			if((Car.x-sitex)<-3.0)
			{
				Car.run=Car.run_old;
				left_motor_stop(&motor_global_setting);
				right_motor_stop(&motor_global_setting);
				return ok;
			}
			if(task_main.direction==1)
			{
				if(fabs(sitex-Car.x)<=0.3&&(sitey-Car.y)>=1.0)
				{
					left_motor_stop(&motor_global_setting);
					right_motor_stop(&motor_global_setting);
					Car.run=Car.run_old;
					return round_ok;
				}
			}
			else
			{
				if(fabs(sitex-Car.x)<=0.3&&(Car.y-sitey)>=1.0)
				{
					left_motor_stop(&motor_global_setting);
					right_motor_stop(&motor_global_setting);
					Car.run=Car.run_old;
					return round_ok;
				}
			}
		}
		if(r>1500)
		{
			r=0;
			left_motor_stop(&motor_global_setting);
			right_motor_stop(&motor_global_setting);
			Car.run=Car.run_old;
			return over_time_error;
		}
	}
	Car.run=Car.run_old;
	return error;
}




void ComTask(void * pdata)
{
	while(1)
	{
		OSTimeDlyHMSM(0,0,0,10);
		update();
	}
}
void MapSend(void * pdata)
{
	u8 err=0,i=0;
	ComEvent=OSSemCreate(0);
	while(1)
	{
		
		OSSemPend((OS_EVENT *)ComEvent,100,&err);
		senddata[0]=0x01;
		senddata[1]=0x0C;
		if (Car.x<0)
		{
			senddata[2]=(u8)((int)(fabs(Car.x)*10)>>8)|0x80;
			senddata[3]=(u8)(((int)(fabs(Car.x)*10))&0x00ff);
		}
		else
		{
			senddata[2]=(u8)((int)((Car.x)*10)>>8);
			senddata[3]=(u8)(((int)((Car.x)*10))&0x00ff);
		}
		if (Car.y<0)
		{
			senddata[4]=(u8)((int)(fabs(Car.y)*10)>>8)|0x80;
			senddata[5]=(u8)(((int)(fabs(Car.y)*10))&0x00ff);
		}
		else
		{
			senddata[4]=(u8)((int)((Car.y)*10)>>8);
			senddata[5]=(u8)(((int)((Car.y)*10))&0x00ff);
		}
		if (Car.angle<0)
		{
			senddata[6]=(u8)((int)(fabs(Car.angle)*10)>>8)|0x80;
			senddata[7]=(u8)(((int)(fabs(Car.angle)*10))&0x00ff);
		}
		else
		{
			senddata[6]=(u8)((int)((Car.angle)*10)>>8);
			senddata[7]=(u8)(((int)((Car.angle)*10))&0x00ff);
		}
		senddata[8]=(u8)(hordata[0]>>2);
		senddata[9]=(u8)(hordata[1]>>2);
		senddata[10]=(u8)(hordata[2]>>2);
		senddata[11]=(u8)(hordata[3]>>2);
		senddata[12]=(u8)(hordata[4]>>2);
		senddata[13]=(u8)((limit_msg&0x10)>>4)|((limit_msg&0x20)>>1);
		OS_ENTER_CRITICAL();
		for(i=0;i<14;i++)
		{
			USART_SendChar(USART1,&(senddata[i]));
		}
		OS_EXIT_CRITICAL();
		
	}
}
void gopoint(float x,float y)
{
	float angle=0.0;
	float step=0.0;
	u8 msg=0,i=0;
	u16 hor_temp,hor_old;
	Car_state task_temp={0};
	if(1)
	{
		angle=atan2(x-Car.x,y-Car.y)*57.2596;
		task_temp.angle=angle;
		task_temp.speed=110;
		task_temp.step=1;
		msg=Car_turn(task_temp);
		while(1)
		{
			
			msg=0;
			while(msg==0)
			{
				msg=0;
				angle=atan2(x-Car.x,y-Car.y)*57.2596;
				task_temp.angle=angle;
				step=sqrt((x-Car.x)*(x-Car.x)+(y-Car.y)*(y-Car.y));
				if (step<0.5)
				{
					left_motor_stop(&motor_global_setting);
					right_motor_stop(&motor_global_setting);
					break;
				}
				task_temp.direction=1;
				task_temp.speed=110;
				task_temp.step=1;
				//msg=Car_turn(task_temp);
				msg=Car_move(task_temp);
			}
			
			if(msg==0)
				break;
			if(msg==right_click||msg==hor_right_error)
			{
				i=0;
				Car.run_old=Car.run;
				Car.run=RUN_ROUND;
				while(hordata[4]<50)
				{
					i++;
					task_temp.speed=TurnSpeed;
					task_temp.angle-=15;
					msg=Car_turn(task_temp);
					if(i>4)
						break;
				}
				task_temp.speed=110;
				while(1)
				{
					hor_temp=hordata[4];
					task_temp.motor_speed=(hor_temp-HOR_THRESHOLD)*2.0+(hor_temp-hor_old)*0.5;
					hor_old=hor_temp;
					if (task_temp.motor_speed>60.0)
						task_temp.motor_speed=60.0;
					if (task_temp.motor_speed<-60.0)
						task_temp.motor_speed=-60.0;
					task_temp.left_speed=task_temp.speed-task_temp.motor_speed;
					task_temp.right_speed=task_temp.speed+task_temp.motor_speed;
					left_motor_forward(&motor_global_setting,(int)(task_temp.left_speed));
					right_motor_forward(&motor_global_setting,(int)(task_temp.right_speed));
					OSTimeDlyHMSM(0,0,0,5);
					if(hordata[HOR_LEFT]>HOR_THRESHOLD+10)
					{

						OSTimeDlyHMSM(0,0,0,100);
						task_temp.direction=1;
						task_temp.speed=TurnSpeed;
						task_temp.angle=Car.angle-120;
						msg=Car_turn(task_temp);
					}
					if(hordata[HOR_RIGHTMID]>HOR_THRESHOLD+60)
					{
						//printf("2\n");
						//task_temp.direction=-1;
						//task_temp.step=1;
						//task_temp.speed=LineSpeed;
						//Car_move(task_temp);
						OSTimeDlyHMSM(0,0,0,100);
						task_temp.direction=1;
						task_temp.speed=TurnSpeed;
						task_temp.angle=Car.angle-30;
						msg=Car_turn(task_temp);
						//task_temp.speed=LineSpeed;
						//task_temp.direction=1;
						//task_temp.step=2;
						//msg=Car_move(task_temp);
					}
					if(hordata[HOR_MIDDLE]>HOR_THRESHOLD+160)
					{
						//printf("3\n");
						//task_temp.direction=-1;
						//task_temp.step=1;
						//task_temp.speed=LineSpeed;
						//Car_move(task_temp);
						OSTimeDlyHMSM(0,0,0,100);
						task_temp.direction=1;
						task_temp.speed=TurnSpeed;
						task_temp.angle=Car.angle-60;
						msg=Car_turn(task_temp);
						//task_temp.speed=LineSpeed;
						//task_temp.direction=1;
						//task_temp.step=2;
						//msg=Car_move(task_temp);
					}
					if(LEFTERROR)
					{
						while(1)
						{
							task_temp.direction=-1;
							task_temp.step=0.1;
							task_temp.speed=LineSpeed-20;
							Car_move(task_temp);
							OSTimeDlyHMSM(0,0,0,200);
							task_temp.speed=TurnSpeed;
							task_temp.angle=Car.angle-90;
							msg=Car_turn(task_temp);
							if(msg!=ok)
							{
								continue;
							}
							OSTimeDlyHMSM(0,0,0,200);
							break;
						}
					}
					if(RIGHTERROR)
					{
						while(1)
						{
							task_temp.direction=-1;
							task_temp.step=0.1;
							task_temp.speed=LineSpeed-20;
							Car_move(task_temp);
							OSTimeDlyHMSM(0,0,0,200);
							task_temp.angle=Car.angle-45;
							task_temp.speed=TurnSpeed;
							msg=Car_turn(task_temp);
							if(msg!=ok)
								continue;
							OSTimeDlyHMSM(0,0,0,200);
							break;
						}
					}
					angle=atan2(x-Car.x,y-Car.y)*57.2957;

					if (fabs(angle-Car.angle)<2.0)
					{
						Car.run=Car.run_old;
						break;
					}
				}
			}
			else//(msg==left_click||msg==hor_left_error||msg==middle_click||msg==hor_middle_error)//msg==left_click||msg==hor_left_error
			{
				i=0;
				Car.run_old=Car.run;
				Car.run=RUN_ROUND;
				while(hordata[0]<50)
				{
					i++;
					task_temp.speed=TurnSpeed;
					task_temp.angle+=15;
					msg=Car_turn(task_temp);
					if(i>4)
						break;
				}
				task_temp.speed=110;
				while(1)
				{
					hor_temp=hordata[0];
					task_temp.motor_speed=(hor_temp-HOR_THRESHOLD)*2.0+(hor_temp-hor_old)*0.5;
					hor_old=hor_temp;
					if (task_temp.motor_speed>60.0)
						task_temp.motor_speed=60.0;
					if (task_temp.motor_speed<-60.0)
						task_temp.motor_speed=-60.0;
					task_temp.left_speed=task_temp.speed+task_temp.motor_speed;
					task_temp.right_speed=task_temp.speed-task_temp.motor_speed;
					left_motor_forward(&motor_global_setting,(int)(task_temp.left_speed));
					right_motor_forward(&motor_global_setting,(int)(task_temp.right_speed));
					OSTimeDlyHMSM(0,0,0,5);
					if(hordata[HOR_RIGHT]>HOR_THRESHOLD+10)
					{

						OSTimeDlyHMSM(0,0,0,100);
						task_temp.direction=1;
						task_temp.speed=TurnSpeed;
						task_temp.angle=120+Car.angle;
						msg=Car_turn(task_temp);
					}
					if(hordata[HOR_LEFTMID]>HOR_THRESHOLD+60)
					{

						OSTimeDlyHMSM(0,0,0,100);
						task_temp.direction=1;
						task_temp.speed=TurnSpeed;
						task_temp.angle=30+Car.angle;
						msg=Car_turn(task_temp);

					}
					if(hordata[HOR_MIDDLE]>HOR_THRESHOLD+160)
					{

						OSTimeDlyHMSM(0,0,0,100);
						task_temp.direction=1;
						task_temp.speed=TurnSpeed;
						task_temp.angle=60+Car.angle;
						msg=Car_turn(task_temp);

					}
					if(LEFTERROR)
					{
						while(1)
						{
							task_temp.direction=-1;
							task_temp.step=0.1;
							task_temp.speed=LineSpeed-20;
							Car_move(task_temp);
							OSTimeDlyHMSM(0,0,0,200);
							task_temp.speed=TurnSpeed;
							task_temp.angle=45+Car.angle;
							msg=Car_turn(task_temp);
							if(msg!=ok)
							{
								continue;
							}
							OSTimeDlyHMSM(0,0,0,200);
							break;
						}
					}
					if(RIGHTERROR)
					{
						while(1)
						{
							task_temp.direction=-1;
							task_temp.step=0.1;
							task_temp.speed=LineSpeed-20;
							Car_move(task_temp);
							OSTimeDlyHMSM(0,0,0,200);
							task_temp.angle=90+Car.angle;
							task_temp.speed=TurnSpeed;
							msg=Car_turn(task_temp);
							if(msg!=ok)
								continue;
							OSTimeDlyHMSM(0,0,0,200);
							break;
						}
					}
					angle=atan2(x-Car.x,y-Car.y)*57.2957;
					if (fabs(angle-Car.angle)<2.0)
					{
						Car.run=Car.run_old;
						break;
					}
						
				}
			}
		}
	}
	
}

