#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#define BIAS 0X52 /*定义1 3 偏压4 背极*/
#define XTAL32 0X28 /*使用外部晶振*/
#define RC256 0X30 /*使用内部256KRC 振荡器*/
#define SYSEN 0X02 /*打开振荡发生器*/
#define LCDON 0X06 /*打开LCD*/
#define SYSDIS 0X00 /*关闭振荡发生器*/
#define LCDOFF 0X04 /*显示关闭*/
#define TONE4 0X80 /*设置BZ 输出频率为4K*/
#define TONEON 0X12 /*打开BZ 音频输出*/
#define TONEOFF 0X10 /*关闭BZ 音频输出*/
#define CLRWDT 0X1c /*清零WDT*/
#define F1 0X40 /*WDT设置为4 秒溢出*/
#define IRQEN 0X10 /*IRQ 输出禁止*/
#define IRQDIS 0X00 /*IRQ 输出允许*/
#define WDTEN 0X0e /*打开WDT*/
#define WDTDIS 0X0a /*关闭WDT*/
#define TIMERDIS 0X08 /*关闭时基输出*/

void Start_spi(void);
void Stop_spi(void);
void Delay(void);
void Delay1s(void);
void SENDCOMA(uchar com);
void SENDCOMB(uchar adr);
void SENDCOMC(uchar com);
void disp(uchar dat);
void DISP_ALL(uchar data);
void SendByte(uchar dat);
void SendBit(uchar dat,uchar bitcnt);


#define lcd_update_addr(addr)  lcd_send_date(addr,lcd_v[addr])

typedef enum {

	
	V_VOLUME_OFF = 0 ,
	V_VOLUME_ON ,


	V_ENGLISH = 100,
	V_FRANCE,
	V_ESPAIN,
	V_ITALY,
	V_SWEDISH,
	V_DEMO,
	
	V_VOLUME_ONE,
	V_VOLUME_TWO,
	V_VOLUME_THREE,
	V_MAX,
}v_country_e;

#define DUSTBIN_FULL_INDEX 200
void show_dustbin_full(void);

void show_volume(U8 volume,U8 show);
void show_country(U8 country);


#if defined(KL_SERIAL_2 )|| defined(KL_SERIAL_5)
#define    LCD_CS_HIGH()    GPIO_WriteBit(GPIOB, GPIO_Pin_4, Bit_SET)
#define    LCD_CS_LOW()     GPIO_WriteBit(GPIOB, GPIO_Pin_4, Bit_RESET) 
#define    LCD_WR_HIGH()   //	GPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_SET) 
#define    LCD_WR_LOW()   //	GPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_RESET) 
#define    LCD_DAT_HIGH()   // GPIO_WriteBit(GPIOE, GPIO_Pin_6, Bit_SET)  
#define    LCD_DAT_LOW()    // GPIO_WriteBit(GPIOE, GPIO_Pin_6, Bit_RESET) 

#define LCD_OPEN_LOW()  led_down() //GPIO_WriteBit(GPIOD,GPIO_Pin_0,Bit_SET)
#define LCD_OPEN_HIGH() //GPIO_WriteBit(GPIOD,GPIO_Pin_0,Bit_RESET)

#define BACK_LIGHT_LOW()  // pannel_led_control(LED_PANNEL_ALL, LED_CLOSE)//GPIO_WriteBit(GPIOD,GPIO_Pin_1,Bit_SET)
#define BACK_LIGHT_HIGH() // pannel_led_control(LED_PANNEL_ALL, LED_OPEN) //GPIO_WriteBit(GPIOD,GPIO_Pin_1,Bit_RESET)



void SENDCOMA(uchar com);
void SENDCOMB(uchar adr);
void SENDCOMC(uchar com);
void disp(uchar dat);
void DISP_ALL(uchar data);
void lcd_init(void);

void lcd_send_date(U8 addr,U8 dat);
#ifdef OLD_LCD
void show_timing_week_d(void);

void hide_timing_week_d(void);
#endif

void show_timing_week_1(void);

void hide_timing_week_1(void);

void show_timing_week_2(void);

void hide_timing_week_2(void);



void show_timing_week_3(void);

void hide_timing_week_3(void);

void show_timing_week_4(void);

void hide_timing_week_4(void);


void show_timing_week_5(void);

void hide_timing_week_5(void);


void show_timing_week_6(void);
void hide_timing_week_6(void);


void show_timing_week_7(void);

void hide_timing_week_7(void);
#ifdef OLD_LCD
void show_timing_week_face(void);

void hide_timing_week_face(void);
#endif
void show_uv(void);

void hide_uv(void);

#ifdef HOOVER_LCD
void show_docking(void);
void hide_docking(void);
void show_week_table_seperate(U8 day, U8 show);
#endif
#ifdef HOOVER_LCD
void show_clock_week(U8 week, U8 show);
void show_week_table(U8 show);
void show_hoover_brand(U8 show);
void show_timing_week(U8 day, U8 show);
#else
void show_clock_week(U8 week);
#endif


void hide_clock_week(void);

void show_clean_timing(void);

void hide_clean_timing(void);

void show_clean_auto(void);

void hide_clean_auto(void);
#ifdef OLD_LCD

void show_lower_face(void);

void hide_lower_face(void);
#endif
void show_charging(void);

void hide_charging(void);

void show_charging_quality(u8 q);

void hide_charging_quality(void);


void show_speed(u8 v);
#ifdef OLD_LCD
void show_speed_wheel(U8 s);
#endif
void show_hour(U8 hour);
void hide_hour(void);

void show_min(U8 min);
void hide_min(void);

void show_clock_cola(void);


void hide_clock_cola(void);
void lcm_show_init(void);
#endif

void DISPLAY_GPIO_Configure(void);

typedef enum {
	LEFT_GROUND_DETECTED = 1,
	LM_GROUND_DETECTED ,
	RM_GROUND_DETECTED,
	RIGHT_GROUND_DETECTED=4,
	LEFT_COLLISION,
	RIGHT_COLLISION,
	LEFT_WALL_DETECTED,
	LM_WALL_DETECTED,
	M_WALL_DETECTED,
	TOP_INFRARED_RECV=10,
	LEFT_INFRARED_RECV,
	MID_INFRARED_RECV,
	RIGHT_INFRARED_RECV,
	RIGHT_WALL_DETECTED,
	RM_WALL_DETECTED,
	M_BRUSH_CURRENT,
	DUST_BLOWER_CURRENT,
	LOW_BATTERY,
	NO_LEFT_SPEED_DETECTED,
	NO_RIGHT_SPEED_DETECTED=20,
	NO_FRONT_ROTATIONAL_SPEED,
	LEFT_WHEEL_OFF,
	RIGHT_WHEEL_OFF,
	BATTERY_TEMP,
	BATTERY_NTC_SHORT_CIRCUIT,
	BATTERY_NTC_OPEN_CIRCUIT,
	RIGHT_WHEEL_EXCESSIVE_CURRENT=31,
	LEFT_WHEEL_EXCESSIVE_CURRENT,
	NO_CURRENT_IN_DUST_BOX_MOTOR,
	MID_BRUSH_FAILURE,

}error_e;
void show_repair(void);
void hide_repair(void);



void show_demo_step(U8 step);

void show_plug(void);


void show_min_pass(U8 min) ;
void show_full_and_go(U8 show);
#if defined(RBC050)
void show_rf_status(U8 show);
#endif

void show_min_special(U8 min, U8 special);
void show_hour_special(U8 hour, U8 special) ;


void show_boot(void) ;



#define WIFI_LED_DOWN  GPIO_WriteBit(GPIOC, GPIO_Pin_11, Bit_RESET)
#define WIFI_LED_UP    GPIO_WriteBit(GPIOC, GPIO_Pin_11, Bit_SET)

#define AUTO_LED_DOWN  GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET)
#define AUTO_LED_UP  GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET)

#define DOCK_LED_DOWN  GPIO_WriteBit(GPIOD, GPIO_Pin_0, Bit_RESET)
#define DOCK_LED_UP  GPIO_WriteBit(GPIOD, GPIO_Pin_0, Bit_SET)


#endif

