
#include "config.h"

extern U8 lcd_v[];

#ifdef HOOVER_LCD


void show_timing_week_7(void)
{
	lcd_v[0x16] |= 0x8;
	
	lcd_send_date(0x16, lcd_v[0x16]);
	
}
void hide_timing_week_7(void)
{
	lcd_v[0x16] &= ~0x8;
	
	lcd_send_date(0x16, lcd_v[0x16]);
			
}
void show_timing_week_6(void)
{
	lcd_v[0x15] |= 0x8;
	
	lcd_send_date(0x15, lcd_v[0x15]);
	
}
void hide_timing_week_6(void)
{
	lcd_v[0x15] &= ~0x8;
	
	lcd_send_date(0x15, lcd_v[0x15]);
			
}


void show_timing_week_5(void)
{
	lcd_v[0x14] |=0x8;

	lcd_send_date(0x14, lcd_v[0x14]);
//	lcd_send_date(0x0d,lcd_v[0x0d]);	
}
void hide_timing_week_5(void)
{
	lcd_v[0x14] &= ~0x8;
	//lcd_v[] &= ~ ;
	lcd_send_date(0x14, lcd_v[0x14]);
//	lcd_send_date(0x0d,lcd_v[0x0d]);		
}


void show_timing_week_4(void)
{
	lcd_v[0x13] |= 0x8;
	//lcd_v[] |= ;
	lcd_send_date(0x13, lcd_v[0x13]);
	//lcd_send_date(0x0d,lcd_v[0x0d]);	
}
void hide_timing_week_4(void)
{
	lcd_v[0x13] &= ~0x8;
//	lcd_v[] &= ~ ;
	lcd_send_date(0x13, lcd_v[0x13]);
	//lcd_send_date(0x0d,lcd_v[0x0d]);		
}


void show_timing_week_3(void)
{
	//lcd_v[0x0c] |= 0x08;
	lcd_v[0x12] |= 0x08;
	//lcd_send_date(0x0c, lcd_v[0x0c]);
	lcd_send_date(0x12,lcd_v[0x12]);	
}
void hide_timing_week_3(void)
{
	//lcd_v[0x0c] &= ~0x08 ;
	lcd_v[0x12] &= ~0x8;
	//lcd_send_date(0x0c, lcd_v[0x0c]);
	lcd_send_date(0x12,lcd_v[0x12]);		
}


void show_timing_week_2(void)
{
	//lcd_v[0x0c] |=0x01 ;
	lcd_v[0x11] |= 0x8;
	//lcd_send_date(0x0c, lcd_v[0x0c]);
	lcd_send_date(0x11,lcd_v[0x11]);	
}
void hide_timing_week_2(void)
{
	//lcd_v[0x0c] &= ~0x01 ;
	lcd_v[0x11] &= ~0x8;
	//lcd_send_date(0x0c, lcd_v[0x0c]);
	lcd_send_date(0x11,lcd_v[0x11]);		
}


void show_timing_week_1(void)
{

	//printf("show timing week 1\r\n");
	//lcd_v[0x0c] |= 0x04;
	lcd_v[0x10] |= 0x08;
	//lcd_send_date(0x0c, lcd_v[0x0c]);
	lcd_send_date(0x10,lcd_v[0x10]);	
}
void hide_timing_week_1(void)
{


	//lcd_v[0x0c] &= ~0x04 ;
	lcd_v[0x10] &= ~0x08;
	//lcd_send_date(0x0c, lcd_v[0x0c]);
	lcd_send_date(0x10,lcd_v[0x10]);		
}


void show_uv(void)
{

}
void hide_uv(void)
{

}



//显示星期的字母——OK
void show_week_table(U8 show)
{
	U8 i = 0;
	if(show) {
		
		for(i = 0x10;i <= 0x16;i++){
		  lcd_v[i] |= 0x04 ;
		  lcd_update_addr(i);
		}

	}else {
		for(i = 0x10;i <= 0x16 ;i++){
		  lcd_v[i] &= ~0x04 ;
		  lcd_update_addr(i);
		}

	}

}

void show_week_table_seperate(U8 day, U8 show)
{
	if(day>7 || day<1){
	   return ;
	}else{
	  day = 0x0f + day;
	  if(show){
	     
	  	 lcd_v[day] |= 0x04 ;
	  }else{
	  	 lcd_v[day] &= ~0x04 ;
	  }
	  lcd_update_addr(day);
	}
	return;

}



//下划线
void show_clock_week(U8 week, U8 show)
{
#if 0
	if(week>7 || week<1){
	   return ;
	}else{
	  week = 0x0f + week;
	  if(show){
	  	 lcd_v[week] |= 0x02;
	  }else{
	  	lcd_v[week] &= ~0x02 ;
	  }
	  lcd_update_addr(week);
	}
#endif

	return;

}

void show_clean_timing(void)
{


	g_led[SEG_ICON] |=  ICON_SPOT;

	led_update(SEG_ICON);	

}

void hide_clean_timing(void)
{

	g_led[SEG_ICON] &=  ~ICON_SPOT;

	led_update(SEG_ICON);		

}

void show_docking(void)
{

}

void hide_docking(void)
{

}



//AUTO -OK
void show_clean_auto(void)
{

}

void hide_clean_auto(void)
{

}



//电池框 --OK
void show_charging(void)
{

}

void hide_charging(void)
{

}




//电池电量-ok
void show_charging_quality(u8 q)
{
	g_led[SEG_ICON] &=	~ICON_BAT;


	switch(q){
		case 0:


			break;
			
		case 1:

			g_led[SEG_ICON] |=  ICON_BAT_1;
			break;

		case 2:
		
			g_led[SEG_ICON] |=	ICON_BAT_2;
			break;

		case 3:
		
			g_led[SEG_ICON] |=	ICON_BAT_3;
			break;


	}


	led_update(SEG_ICON);	



}

void hide_charging_quality(void)
{
	lcd_v[0x0f] &=~0x07;
	lcd_update_addr(0x0f);
}



void show_speed(u8 v){}



//显示HOOVER 标志OK
void show_hoover_brand(U8 show)
{}


void hide_hour(void)
{
	int ten = 0;


	g_led[SEG_HOUR_TEN] &= ~0x7f;
	g_led[SEG_HOUR_SINGLE] &= ~0x7f;
	


	led_update(SEG_HOUR_TEN);
	led_update(SEG_HOUR_SINGLE);
	

}


void show_hour_special(U8 hour, U8 special) 
{
}



void show_hour(U8 hour)
{
	U8 ten,nib;


	ten = hour/10;
	nib = hour%10;

	switch(hour){
		case 24:
			ten = 'E';
			nib = 'r';
			break;
		case 25:
			ten = 'S';
#ifdef RBC050
			nib = 5;
#endif

#ifdef RBC070
			nib = 7;
#endif

#ifdef RBC090
			nib = 9;
#endif
				
			break;

			
		default:
			 break;

	}
	g_led[SEG_HOUR_TEN] &= ~0x7f;
	g_led[SEG_HOUR_SINGLE] &= ~0x7f;
	


	if(hour == 0xff)
		goto out;




	switch(ten){
		case 0:
		case 1:
		case 2:
			g_led[SEG_HOUR_TEN] |=	digit_num[ten];
			break;
			
		case 'S':
			g_led[SEG_HOUR_TEN] |=	CHAR_S;
			

			break;

		case 'E':
			g_led[SEG_HOUR_TEN] |=  CHAR_E;
			break;


			
		default:
			//printf("error hour:%d",hour);
			break;
	
	}
		
	switch(nib){

		case 0:

		case 1:

		case 2:

		case 3:

		case 4:

		case 5:

		case 6:

		case 7:

		case 8:

		case 9:
			g_led[SEG_HOUR_SINGLE] |=  digit_num[nib];
			break;

		case 'r':
			g_led[SEG_HOUR_SINGLE] |=  CHAR_R;
			break;

			

		default:
			break;
	
	}
out:
	led_update(SEG_HOUR_TEN);
	led_update(SEG_HOUR_SINGLE);

	


}

void hide_min(void)
{
	U8 ten = 0;
	g_led[SEG_MIN_TEN] &= ~0x7f;
	g_led[SEG_MIN_SINGLE] &= ~0x7f;
	

	led_update(SEG_MIN_TEN);
	led_update(SEG_MIN_SINGLE);

	

	
	return ;



}

void show_min_pass(U8 min) {



}

void show_boot(void) {


}


void show_min_special(U8 min, U8 special)
{}
void show_min(U8 min)
{
	U8 ten,nib;

	if(min<=59){
		ten = min/10;
		nib = min%10;

		clock_cola_hide = 0;
	}
	g_led[SEG_MIN_TEN] &= ~0x7f;
	g_led[SEG_MIN_SINGLE] &= ~0x7f;
	

	if(min == 0xff)
		goto out;


	g_led[SEG_MIN_TEN] |= digit_num[ten] ;
	g_led[SEG_MIN_SINGLE] |= digit_num[nib];
	

out:

	led_update(SEG_MIN_TEN);
	led_update(SEG_MIN_SINGLE);

	


	
	return;

}

U8 clock_cola_hide;
extern U32 rtc_retrive_counter;

void show_country(U8 country)
{


}


/*
void show_volume(U8 volume)
{
	if(volume<V_VOLUME_OFF || volume>=V_MAX) {
		
		return;
	}
	clock_cola_hide = 1;
	rtc_retrive_counter = 100;
	hide_clock_cola();
	
	show_hour(volume);
	show_min(volume);
	
	return;



}

*/

void show_volume(U8 volume,U8 show){


}


#if defined(RBC050)

void show_rf_status(U8 show){


}

#endif

void show_demo_flag(U8 show){


}


void show_demo_step(U8 step)
{


}

void show_dustbin_full(void)
{


}




void show_clock_cola(void)
{

	g_led[SEG_HOUR_SINGLE] |= 0x80;
	g_led[SEG_MIN_TEN] |= 0x80;

//	printf("show clock cola\r\n");

		
	led_update(SEG_HOUR_SINGLE);
	led_update(SEG_MIN_TEN);

}

void hide_clock_cola(void)
{

	g_led[SEG_HOUR_SINGLE] &= ~0x80;
	g_led[SEG_MIN_TEN] &= ~0x80;

	led_update(SEG_HOUR_SINGLE);
	led_update(SEG_MIN_TEN);


}


//kuang
void show_timing_week(U8 day, U8 show)
{


}

void show_repair(void)
{


}

void hide_repair(void)
{

}

void show_plug(void)
{

}

void show_wifi(U8 show){

#if 0
	if(show)
		g_led[SEG_ICON] |=  ICON_WIFI;
	else
#endif

		g_led[SEG_ICON] &=  ~ICON_WIFI;

	led_update(SEG_ICON);	

}

void show_mop(U8 show){


}


void show_full_and_go(U8 show){
#if 0
	if(show)
		g_led[SEG_ICON] |=  ICON_FULL_GO;
	else
	#endif
	
		g_led[SEG_ICON] &=  ~ICON_FULL_GO;

	led_update(SEG_ICON);	



}

volatile U8 cornor_step = 0;

void show_cornor_clean(void ) {



	//printf("cornor_step:	%d\r\n", cornor_step);
	
g_led[SEG_HOUR_TEN] &= 0x80;
g_led[SEG_HOUR_SINGLE] &= 0x80;

g_led[SEG_MIN_TEN] &= 0x80;
g_led[SEG_MIN_SINGLE] &= 0x80;


	switch(cornor_step) {

		case 0:

			g_led[SEG_HOUR_TEN] |= _A  ;
						
			g_led[SEG_HOUR_SINGLE] |= _A ;			
				

			g_led[SEG_MIN_TEN] |= _A  ;
			break;
		
		case 1:
		
			g_led[SEG_MIN_SINGLE] |= _A  ;
						
			g_led[SEG_HOUR_SINGLE] |= _A ;			
				
		
			g_led[SEG_MIN_TEN] |= _A  ;

			break;
			
		case 2:
		
			g_led[SEG_MIN_SINGLE] |= _A | _B ;
	
			g_led[SEG_MIN_TEN] |= _A  ;
			break;
			
		case 3:
		
			g_led[SEG_MIN_SINGLE] |= _A | _B | _C;

			break;
		case 4:
		
			g_led[SEG_MIN_SINGLE] |= _D | _B | _C;

			break;
		
		case 5:
		
			g_led[SEG_MIN_SINGLE] |= _D | _C;
				g_led[SEG_MIN_TEN] |= _D ;	
			break;
		case 6:
		
			g_led[SEG_MIN_SINGLE] |= _D;
				g_led[SEG_MIN_TEN] |= _D ;	
				g_led[SEG_HOUR_SINGLE] |= _D ;	
			break;
		case 7:
		
			g_led[SEG_HOUR_TEN] |= _D;
				g_led[SEG_MIN_TEN] |= _D ;	
				g_led[SEG_HOUR_SINGLE] |= _D ;	
			break;
		case 8:
		
			g_led[SEG_HOUR_TEN] |= _D | _E;

				g_led[SEG_HOUR_SINGLE] |= _D ;	
			break;								

		case 9:
		
			g_led[SEG_HOUR_TEN] |= _D | _E | _F;

	
			break;								
				
		
		case 10:
		
			g_led[SEG_HOUR_TEN] |= _A | _E | _F;
		
		
			break;								
		case 11:
		
			g_led[SEG_HOUR_TEN] |= _A  | _F;
		
			g_led[SEG_HOUR_SINGLE] |= _A ;
				
			break;								
		



	}






	led_update(SEG_HOUR_TEN);
	led_update(SEG_HOUR_SINGLE);


	led_update(SEG_MIN_TEN);
	led_update(SEG_MIN_SINGLE);


	cornor_step++;

	if(cornor_step > 11)
		cornor_step = 0;
	





}



U8 cycle_step = 0;
void show_cycle_clean(void){



	//printf("cycle_step:	%d\r\n", cycle_step);
	
	g_led[SEG_HOUR_TEN] &= 0x80;
	g_led[SEG_HOUR_SINGLE] &= 0x80;

	g_led[SEG_MIN_TEN] &= 0x80;
	g_led[SEG_MIN_SINGLE] &= 0x80;


	switch(cycle_step) {

		case 0:


			g_led[SEG_HOUR_SINGLE] |= _B | _C ;			
				

			g_led[SEG_MIN_TEN] |= _E | _F  ;
			break;
		
		case 1:
		

						
			g_led[SEG_HOUR_SINGLE] |= _E | _F ;			
				
		
			g_led[SEG_MIN_TEN] |= _B | _C  ;

			break;
			
		case 2:
		
			g_led[SEG_MIN_SINGLE] |= _C | _B ;
	
			g_led[SEG_HOUR_TEN] |= _E | _F  ;
			break;
			
							
		



	}






	led_update(SEG_HOUR_TEN);
	led_update(SEG_HOUR_SINGLE);


	led_update(SEG_MIN_TEN);
	led_update(SEG_MIN_SINGLE);


	cycle_step++;

	if(cycle_step > 2)
		cycle_step = 0;
	





}


volatile U8 zigzag_step = 0;

void show_zigzag_clean(void ) {



//	printf("zigzag_step:	%d\r\n", zigzag_step);
	
g_led[SEG_HOUR_TEN] &= 0x80;
g_led[SEG_HOUR_SINGLE] &= 0x80;

g_led[SEG_MIN_TEN] &= 0x80;
g_led[SEG_MIN_SINGLE] &= 0x80;


	switch(zigzag_step) {
		case 0:
			g_led[SEG_HOUR_TEN] |=  _F | _E | _A;

			break;
			
		case 1:
			g_led[SEG_HOUR_TEN] |=  _A | _B | _F;

			break;
			
		case 2:
			g_led[SEG_HOUR_TEN] |=   _A | _B | _C;

			break;
		
		case 3:

			
			g_led[SEG_HOUR_TEN] |= _B | _C;
			g_led[SEG_HOUR_SINGLE] |= _D  ;

			break;
	

		case 4:
		
		
			g_led[SEG_HOUR_TEN] |=  _C;
			g_led[SEG_HOUR_SINGLE] |= _C |_D  ;

			break;
		
		case 5:
		
			
			g_led[SEG_HOUR_SINGLE] |= _B | _C |_D  ;

			break;
					
		case 6:
		
			g_led[SEG_HOUR_SINGLE] |= _B | _C  ;

			g_led[SEG_MIN_TEN] |=  _F ;

			break;
		
		case 7:
		
			g_led[SEG_HOUR_SINGLE] |= _B   ;

			g_led[SEG_MIN_TEN] |= _E | _F ;

			break;
		
		case 8:
		

			g_led[SEG_MIN_TEN] |=_D | _E | _F ;
		
			break;
		
		case 9:
		

			g_led[SEG_MIN_TEN] |= _D | _E  ;
			g_led[SEG_MIN_SINGLE] |= _E  ;
				
			break;
	
	
		case 10:
		
		
			g_led[SEG_MIN_TEN] |= _D  ;
			g_led[SEG_MIN_SINGLE] |= _E | _F ;
				
			break;
		
		case 11:
		
			g_led[SEG_MIN_SINGLE] |= _A |_E | _F ;
				
			break;
	
		case 12:
		
			g_led[SEG_MIN_SINGLE] |= _A |_B | _F ;
				
			break;
		case 13:
		
			g_led[SEG_MIN_SINGLE] |= _A |_B | _C ;
				
			break;		

		case 14:
		
			g_led[SEG_MIN_SINGLE] |= _D |_B | _C ;
				
			break;		

		case 15:
			g_led[SEG_MIN_TEN] |= _D  ;
						
			g_led[SEG_MIN_SINGLE] |= _D | _C ;
				
			break;		
		case 16:
			g_led[SEG_HOUR_SINGLE] |= _D  ;
			
			g_led[SEG_MIN_TEN] |= _D ;
						
			g_led[SEG_MIN_SINGLE] |= _D  ;
				
			break;		
		case 17:
			g_led[SEG_HOUR_SINGLE] |= _D  ;
			
			g_led[SEG_MIN_TEN] |= _D ;
						
			g_led[SEG_HOUR_TEN] |= _D  ;
				
			break;		

		case 18:
			g_led[SEG_HOUR_SINGLE] |= _D  ;
		
			g_led[SEG_HOUR_TEN] |= _E |_D  ;
				
			break;		

		case 19:

			g_led[SEG_HOUR_TEN] |= _E |_D | _F ;
				
			break;		



	}






	led_update(SEG_HOUR_TEN);
	led_update(SEG_HOUR_SINGLE);


	led_update(SEG_MIN_TEN);
	led_update(SEG_MIN_SINGLE);


	zigzag_step++;

	if(zigzag_step > 19)
		zigzag_step = 0;
	





}



void show_clean_type(void) {



	if(motor_global_setting.machine_cur_state!=MACHINE_WORKING
						|| global_clean_task.main_task ==MAIN_STOP)
	{
		return ;
	}	

	

	if(global_sub_task_index == MACHINE_STOP_STATE)
		return ;

	clock_cola_hide = 1;

	if(err_showing) {
		return ;
	}
	
	if(global_sub_task_index == MACHINE_AUTO_SUB_MAP ||
		global_sub_task_index == MACHINE_SHORT_MANUAL_ZIGZAG||
		global_sub_task_index == MACHINE_FINDING_CHARGE_SUB_ZIGZAG) {

		show_zigzag_clean();

	}else if(global_sub_task_index == MACHINE_AUTO_SUB_CORNOR ||
			global_sub_task_index == MACHINE_FINDING_CHARGE_SUB_CORNOR) {

		show_cornor_clean();

	}else if(global_sub_task_index == MACHINE_AUTO_SUB_CYCYLE ||
		global_sub_task_index == CYCLE_CLEAN) {

		show_cycle_clean();

	}else {

		show_hour(global_setting.clock_hour);
		show_min(global_setting.clock_min);
		clock_cola_hide = 0;
	}






}






#endif
