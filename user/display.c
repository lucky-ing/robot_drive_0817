/*********************************************************
*   接口定义：DATA<--->P2.5; CS<--->P2.6; WR<--->P2.7    *
**********************************************************/
/*
	DATA->PE15
	CS    ->PE13
	WR   -->PE14
	背光  -> PD14
	lcd 屏使能 PD10
	
	数码管的显示

*/
#include "config.h"

#if defined(KL_SERIAL_2 )|| defined(KL_SERIAL_5)




U8 lcd_v[32];
#define lcd_update_addr(addr)  lcd_send_date(addr,lcd_v[addr])
/**********************************************************************
延时函数
***********************************************************************/
void Delay(void)
{
U16 i;
//OSTimeDlyHMSM(0,0,0,1);
for(i=0;i<10;i++); /*用于调整CLK 脉冲宽度*/
}



/*********************************************************************
发送命令函数A类
发送HT1621 命令时要先发送ID 值,及命令字用于设置HT1621.
*********************************************************************/
void SENDCOMA(uchar com)
{
Start_spi();
SendBit(0X80,4); /*发送设置命令ID=100 0*/
SendByte(com); /*发送命令字*/
}

/*********************************************************************
发送命令函数B 类
发送HT1621 命令时要先发送ID 值,后发送要写入数据起始地址,
用于对RAM 写操作(调用此函数后即可发送数据) adr 是高5 位有效
*********************************************************************/
void SENDCOMB(uchar adr)
{
Start_spi();
SendBit(0XA0,4); /*发送写显示RAM 命令ID=101 0*/
SendBit(adr,5); /*指定写入地址*/
}


/*********************************************************************
发送命令函数(C 类)
发送HT1621 命令时要先发送ID 值.然后发送C 类的命令字
*********************************************************************/
void SENDCOMC(uchar com)
{
Start_spi();
SendBit(0X90,4); /*发送命令ID=100 1*/
SendByte(com); /*发送命令字*/
}

/**********************************************************************
向显示缓冲区填充,以最简便的形式显示数据
**********************************************************************/
void disp(uchar dat)
{
uchar i;
SENDCOMB(0x00); /*把数据指针指回0 接着写入数据*/
for(i=0;i<32;i++) /*写入16 字节数据*/
{
SendByte(dat); /*写入数据*/
}
}

void lcd_send_date(U8 addr,U8 dat)
{

	return ;
	#if 0
	Start_spi();
		//OS_ENTER_CRITICAL(); 	/* Tell uC/OS-II that we are starting an ISR */

	
	SendBit(0xA0,4);
	SendBit(addr<<3,5);
	SendBit(dat<<4,4);

#if 0
	if(addr == 0x10) {

		printf("addr:	0x10, data:	%d\r\n", dat);
	}
	#endif
	#endif
	
	    	//OSIntNesting++;
	    	//OS_EXIT_CRITICAL();
}




/******************************************************
全显示
******************************************************/
void DISP_ALL(uchar data)
{
SENDCOMA(BIAS); /*设置偏压,背极数*/
SENDCOMA(RC256); /*设为内晶振256K*/
SENDCOMA(SYSEN); /*启动振荡器*/

SENDCOMA(LCDON); /*显示使能*/
SENDCOMA(TIMERDIS); /*禁止时基输出*/
disp(data); /*输出全显数据*/
}


/**********************************************************************
主函数
**********************************************************************/
extern U32 lcm_task_wdg_counter;
void lcd_init(void)
{

	int i;
	for(i=0;i<32;i++)
		lcd_v[i]=0;
	//if(resume_from_iwdg==0)
		DISP_ALL(0xFF); /*全显示测量*/



}

void DISPLAY_GPIO_Configure(void)
{


  
 
  GPIO_InitTypeDef  GPIO_InitStructure; 
  /* PIN57 PD10 ,LCD power enable */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  #if 1
 
	  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 |GPIO_Pin_9;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	  GPIO_Init(GPIOD, &GPIO_InitStructure); 
	  


	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure); 
	

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11 |GPIO_Pin_12 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
	


	#endif


	AUTO_LED_UP;
	DOCK_LED_UP;
	WIFI_LED_UP;
	pannel_led_control(LED_PANNEL_AUTO, LED_OPEN);

	
	


	led_gpio_init();
	led_init();


}

/************************************************************************
名称: 发送数据位
************************************************************************/


void SendBit(uchar dat,uchar bitcnt)
{
uchar i;
for(i=0;i<bitcnt;i++)
{
if(( dat & 0X80 ) == 0)
LCD_DAT_LOW();
//P2OUT&=~BIT5;//SDA_PORT = 0;
else
LCD_DAT_HIGH();
//P2OUT|=BIT5;//SDA_PORT = 1; /*发送数据由高位到低位传送*/
Delay();
LCD_WR_HIGH();
//P2OUT|=BIT7;//CLK_PORT = 1; /*置时钟线为高通知被控器开始接收数位*/
Delay();
LCD_WR_LOW();
Delay();
//P2OUT&=~BIT7;//CLK_PORT = 0; /*钳住总线准备下一个数据位*/
dat=dat<<1; /*发送数据左移一位*/
}
}

/**********************************************************************
起动ht1621
**********************************************************************/
void Start_spi(void)
{
LCD_CS_HIGH();
LCD_WR_HIGH();
LCD_DAT_HIGH();
//P1OUT|=BIT6;//CS_PORT=1;
//P1OUT|=BIT7;//CLK_PORT=1;
//P1OUT|=BIT5;//SDA_PORT=1;
Delay();
LCD_CS_LOW();
LCD_CS_LOW();
LCD_WR_LOW();
LCD_WR_LOW();
//P1OUT&=~BIT6;//CS_PORT=0; 
//P1OUT&=~BIT6;//CS_PORT=0; 
//P1OUT&=~BIT7;//CLK_PORT=0; 
//P1OUT&=~BIT7;//CLK_PORT=0; 
}

/************************************************************************
发送字节函数,向ht1621 发送字节数据数据单元dat
************************************************************************/
void SendByte(uchar dat)
{
SendBit(dat,8); /*发送字节*/
}


extern U32 lcm_task_wdg_counter;
U8 lcd_v[32];
void lcm_show_init(void)
{
	U8 i ;
	U8 j ;
	
	for(i=0;i<32;i++){
		lcd_v[i] = 0xff;

		lcd_send_date(i,lcd_v[i]);
		OSTimeDlyHMSM(0,0,0,1);
	}
	OSTimeDlyHMSM(0,0,0,600);





	
	for(i=0;i<32;i++){
		lcd_v[i] = 0x00;
		lcd_send_date(i,lcd_v[i]);
	}



}
#endif



#if defined(KL_SERIAL_2)||defined(KL_SERIAL_5)
U8 err_showing = 0;
extern volatile U32 rtc_retrive_counter;
void show_err_code(U8 code)
{}
#endif




