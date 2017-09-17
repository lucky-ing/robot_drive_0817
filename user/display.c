/*********************************************************
*   �ӿڶ��壺DATA<--->P2.5; CS<--->P2.6; WR<--->P2.7    *
**********************************************************/
/*
	DATA->PE15
	CS    ->PE13
	WR   -->PE14
	����  -> PD14
	lcd ��ʹ�� PD10
	
	����ܵ���ʾ

*/
#include "config.h"

#if defined(KL_SERIAL_2 )|| defined(KL_SERIAL_5)




U8 lcd_v[32];
#define lcd_update_addr(addr)  lcd_send_date(addr,lcd_v[addr])
/**********************************************************************
��ʱ����
***********************************************************************/
void Delay(void)
{
U16 i;
//OSTimeDlyHMSM(0,0,0,1);
for(i=0;i<10;i++); /*���ڵ���CLK ������*/
}



/*********************************************************************
���������A��
����HT1621 ����ʱҪ�ȷ���ID ֵ,����������������HT1621.
*********************************************************************/
void SENDCOMA(uchar com)
{
Start_spi();
SendBit(0X80,4); /*������������ID=100 0*/
SendByte(com); /*����������*/
}

/*********************************************************************
���������B ��
����HT1621 ����ʱҪ�ȷ���ID ֵ,����Ҫд��������ʼ��ַ,
���ڶ�RAM д����(���ô˺����󼴿ɷ�������) adr �Ǹ�5 λ��Ч
*********************************************************************/
void SENDCOMB(uchar adr)
{
Start_spi();
SendBit(0XA0,4); /*����д��ʾRAM ����ID=101 0*/
SendBit(adr,5); /*ָ��д���ַ*/
}


/*********************************************************************
���������(C ��)
����HT1621 ����ʱҪ�ȷ���ID ֵ.Ȼ����C ���������
*********************************************************************/
void SENDCOMC(uchar com)
{
Start_spi();
SendBit(0X90,4); /*��������ID=100 1*/
SendByte(com); /*����������*/
}

/**********************************************************************
����ʾ���������,���������ʽ��ʾ����
**********************************************************************/
void disp(uchar dat)
{
uchar i;
SENDCOMB(0x00); /*������ָ��ָ��0 ����д������*/
for(i=0;i<32;i++) /*д��16 �ֽ�����*/
{
SendByte(dat); /*д������*/
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
ȫ��ʾ
******************************************************/
void DISP_ALL(uchar data)
{
SENDCOMA(BIAS); /*����ƫѹ,������*/
SENDCOMA(RC256); /*��Ϊ�ھ���256K*/
SENDCOMA(SYSEN); /*��������*/

SENDCOMA(LCDON); /*��ʾʹ��*/
SENDCOMA(TIMERDIS); /*��ֹʱ�����*/
disp(data); /*���ȫ������*/
}


/**********************************************************************
������
**********************************************************************/
extern U32 lcm_task_wdg_counter;
void lcd_init(void)
{

	int i;
	for(i=0;i<32;i++)
		lcd_v[i]=0;
	//if(resume_from_iwdg==0)
		DISP_ALL(0xFF); /*ȫ��ʾ����*/



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
����: ��������λ
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
//P2OUT|=BIT5;//SDA_PORT = 1; /*���������ɸ�λ����λ����*/
Delay();
LCD_WR_HIGH();
//P2OUT|=BIT7;//CLK_PORT = 1; /*��ʱ����Ϊ��֪ͨ��������ʼ������λ*/
Delay();
LCD_WR_LOW();
Delay();
//P2OUT&=~BIT7;//CLK_PORT = 0; /*ǯס����׼����һ������λ*/
dat=dat<<1; /*������������һλ*/
}
}

/**********************************************************************
��ht1621
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
�����ֽں���,��ht1621 �����ֽ��������ݵ�Ԫdat
************************************************************************/
void SendByte(uchar dat)
{
SendBit(dat,8); /*�����ֽ�*/
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




